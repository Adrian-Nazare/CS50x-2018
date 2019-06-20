import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Query database for info to pupulate the table
    rows_users = db.execute("SELECT * FROM users WHERE id = :id",
                          id=session["user_id"])
    rows_overview = db.execute('SELECT * FROM overview WHERE username = :username',
                          username=rows_users[0]["username"])
    matrix =[]
    stock_values = 0

    #populate matrix with the necessary dict values to be passed into render_template
    for row in rows_overview:
        share=lookup(row['stock_symbol'])
        matrix.append({
            'stock_name': share['name'],
            'stock_symbol': row['stock_symbol'],
            'no_shares': row['no_shares'],
            'price_share': share['price'],
            'total_value': float(share['price'] * row['no_shares'])
        })
        stock_values += share['price'] * row['no_shares']
    #make a tuple for the values of cash and total asset values to be passed into render_template
    values = rows_users[0]['cash'], float(rows_users[0]['cash'] + (stock_values))

    return render_template("index.html", matrix = matrix, values=values)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide stock symbol and number of shares", 403)
        if (not request.form.get("shares")) or (float(request.form.get("shares")) <= 0):
            return apology("must provide valid number of stocks", 403)

        values = lookup(request.form.get("symbol"))
        if not values:
            return apology("stock symbol not valid", 403)


        rows = db.execute("SELECT * FROM users WHERE id = :id",
                          id=session["user_id"])

        #verify that you can affort to buy the stock
        if (values['price'] * float(request.form.get("shares"))) >= rows[0]['cash']:
            return apology("Sorry bro, shares too expensive")

        #verify that the share already exists, if not: add it in; if it exists, add stocks to it
        share = db.execute("SELECT * FROM overview WHERE username = :username AND stock_symbol = :stock_symbol",
                           username = rows[0]["username"], stock_symbol = request.form.get("symbol"))
        if not share:
            db.execute('INSERT INTO "overview" ("username", "stock_symbol", "no_shares") VALUES (:username, :stock_symbol, :no_shares)',
                       username=rows[0]["username"], stock_symbol=request.form.get("symbol"), no_shares=request.form.get("shares"))
        else:
            db.execute("UPDATE \"overview\" SET \"no_shares\"= :new WHERE \"id\"= :id",
                       new=share[0]["no_shares"]+int(request.form.get("shares")), id=share[0]["id"])

        #updating the cash after the purchase
        db.execute("UPDATE \"users\" SET \"cash\"= :new WHERE \"id\"= :id",
                       new=rows[0]['cash']-values['price'] * float(request.form.get("shares")), id=rows[0]['id'])

        #updating history
        db.execute('INSERT INTO "history" ("username", "stock_symbol", "share_price", "no_shares") VALUES (:username, :stock_symbol, :share_price, :no_shares)',
                   username=rows[0]["username"], stock_symbol=request.form.get("symbol"), share_price=values['price'], no_shares=request.form.get("shares"))
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows_users = db.execute("SELECT * FROM users WHERE id = :id",
                          id=session["user_id"])
    rows_overview = db.execute('SELECT * FROM history WHERE username = :username ORDER BY time',
                          username=rows_users[0]["username"])

    #populate matrix with the necessary dict values to be passed into render_template
    matrix =[]
    for row in rows_overview:
        matrix.append({
            'stock_symbol': row['stock_symbol'],
            'transaction': 'buy' if float(row['no_shares']) > 0 else 'sell',
            'no_shares': row['no_shares'],
            'price_share': row['share_price'],
            'total_value': float(row['share_price'] * row['no_shares']),
            'time': row['time']
        })

    return render_template("history.html", matrix = matrix)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 403)

        values = lookup(request.form.get("symbol"))

        if not values:
            return apology("stock symbol not valid", 403)

        return render_template("quoted.html", values=values)

    else:
        return render_template("quote.html")

@app.route("/loan", methods=["GET", "POST"])
@login_required
def loan():
    """Get stock quote."""
    if request.method == "POST":

        #check if a positive number has been inputed
        if not request.form.get("money") or float(request.form.get("money")) < 0:
            return apology("must provide a valid number", 403)

        #query database for cash
        rows = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])

        #update database with the new sum
        db.execute("UPDATE \"users\" SET \"cash\"= :new WHERE \"id\"= :id",
                   new=rows[0]['cash']+float(request.form.get("money")), id=session["user_id"])

        return redirect("/")

    else:
        return render_template("loan.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    session.clear()
    if request.method == "POST":

        #check all input
        if not request.form.get("username"):
            return apology("must provide username", 403)
        elif not request.form.get("password"):
            return apology("must provide password", 403)
        elif not request.form.get("cpassword"):
            return apology("please confirm password", 403)

        #check if passwords match
        if request.form.get("password") != request.form.get("cpassword"):
            return apology("sorry, passwords do not match, please try again", 403)

        #query database for username
        rows = db.execute("SELECT * from users WHERE username = :username",
                          username=request.form.get("username"))
        if len(rows) == 1:
            return apology("username already exists, please try another username", 403)

        #if the username does not exist already, add it to the database
        db.execute("INSERT INTO users(username, hash) VALUES(:username, :hash)",
                   username=request.form.get("username"),
                   hash=generate_password_hash(request.form.get("password")))

        #query database for the user id and then log them in usign that id
        rows = db.execute("SELECT * from users WHERE username = :username",
                          username=request.form.get("username"))
        session["user_id"] = rows[0]["id"]

        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide stock symbol and number of shares", 403)
        shares = float(request.form.get("shares"))
        if (not shares) or shares <= 0:
            return apology("must provide valid number of stocks", 403)

        values = lookup(request.form.get("symbol"))
        if not values:
            return apology("stock symbol not valid", 403)

        rows_users = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])


        # query database for that particular share
        share = db.execute("SELECT * FROM overview WHERE username = :username AND stock_symbol = :stock_symbol",
                           username = rows_users[0]["username"], stock_symbol = request.form.get("symbol"))

        #updating the stock overview
        if not share:
            return apology("You don't have any of that stock to sell", 403)
        else:
            #if you sell less shares than you have, that number will be subtracted from the total
            if shares < share[0]['no_shares']:
                db.execute("UPDATE \"overview\" SET \"no_shares\"= :new WHERE \"id\"= :id",
                           new=share[0]["no_shares"]-shares, id=share[0]["id"])
            #if you want to sell more shares than you have, you will automatically sell all available shares
            else:
                db.execute('DELETE FROM "overview" WHERE "id"= :id', id=share[0]["id"])
                shares = share[0]['no_shares']

        #updating the cash after the purchase
        db.execute("UPDATE \"users\" SET \"cash\"= :new WHERE \"id\"= :id",
                       new=rows_users[0]['cash']+values['price'] * shares, id=rows_users[0]['id'])

        #updating history
        db.execute('INSERT INTO "history" ("username", "stock_symbol", "share_price", "no_shares") VALUES (:username, :stock_symbol, :share_price, :no_shares)',
                   username=rows_users[0]["username"], stock_symbol=request.form.get("symbol"), share_price=values['price'], no_shares= -shares)
        return redirect("/")
    else:
        return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
