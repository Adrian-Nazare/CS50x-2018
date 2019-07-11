import cs50
import re
from flask import Flask, abort, redirect, render_template, request
from werkzeug.exceptions import default_exceptions, HTTPException

#from base import  Cell, get_base
app = Flask(__name__)

@app.after_request
def after_request(response):
    response.headers["Cach environment/pset9e-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/")
def index():
    return render_template("layout.html")
    
@app.route("/paired", methods=["POST"])
def score(): #"↘↓→"
    s1 = request.form.get("string1")
    s2 = request.form.get("string2")

    if not s1 or not s2:
        print(s1)
        print(s2)
        abort(400, "missing strings")
    s1 += '-'
    s2 += '-'
    cell = [[[0, 0, 0, 0] for y in range(len(s2))] for x in range(len(s1))]
    base_pairs = []
        
    def get_base(a, b):
    
        def concatenate(word1, word2, i, j):
            if cell[i][j][1] == 1:
                concatenate(word1 + a[i], word2 + '-', i + 1, j)
            if cell[i][j][2] == 1:
                concatenate(word1 + a[i], word2 + b[j], i + 1, j + 1)
            if cell[i][j][3] == 1:
                concatenate(word1 + '-', word2 + b[j], i, j + 1)
            if (i == len(a) - 1 ) and (j == len(b) -1 ):
                base_pairs.append((word1, word2))
        
        def match (baseA, baseB):
            if baseA == baseB:
                return 0
            return 1
            
        for i in range(len(a)-2, -1, -1):
            cell[i][len(b)-1][0] = cell[i+1][len(b)-1][0] + 2
            cell[i][len(b)-1][1] = 1
        for j in range(len(b)-2, -1, -1):
            cell[len(a)-1][j][0] = cell[len(a)-1][j+1][0] + 2
            cell[len(a)-1][j][3] = 1
    
        for j in range (len(b)-2, -1, -1):
            for i in range (len(a)-2, -1, -1):
                m = min(cell[i+1][j][0] + 2, cell[i][j+1][0] + 2, cell[i+1][j+1][0] + match(a[i], b[j]))
                if cell[i+1][j][0] + 2 == m:
                    cell[i][j][1] = 1
                if cell[i][j+1][0] + 2 == m:
                    cell[i][j][3] = 1
                if cell[i+1][j+1][0] + match(a[i], b[j]) == m:
                    cell[i][j][2] = 1
                cell[i][j][0] = m
                
        concatenate("", "", 0, 0)
        
    
    get_base(s1, s2)
#    return matrix
    for i in range(len(s1)):
        for j in range(len(s2)):
            cell[i][j][0] = "{}".format(cell[i][j][0])
            if cell[i][j][1] == 1:
                cell[i][j][0] += "↓"
            if cell[i][j][2] == 1:
                cell[i][j][0] += "↘"
            if cell[i][j][3] == 1:
                cell[i][j][0] += "→"
                
    print(cell)
    print(base_pairs)

    return render_template("result.html", matrix=cell, s1=s1, s2=s2, pairs=base_pairs)
    
@app.errorhandler(HTTPException)
def errorhandler(error):
    """Handle errors"""
    return render_template("error.html", error=error), error.code

for code in default_exceptions:
    app.errorhandler(code)(errorhandler)