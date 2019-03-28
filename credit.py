



def main():
    n = int(input("Number of credit card = "))
    if n >= 5100000000000000 and n < 5600000000000000:
        c = "MASTERCARD"
    elif (n >= 4000000000000000 and n < 5000000000000000) or (n >= 4000000000000 and n<5000000000000):
        c = "VISA"
    elif (n >= 340000000000000 and n < 350000000000000) or (n >= 370000000000000 and n < 380000000000000):
        c = "AMEX"
    else:
        c = "INVALID"

    if c != "INVALID":
        s1, s2 = 0, 0
        for i in range(0, len(str(n)), 1):
            digit = n % 10
            if i % 2 == 1:
                s1 += digit
            else:
                s2 += (digit * 2) // 10 + (digit * 2) % 10
            n //= 10
        if (s1 + s2) % 10 != 0:
            c = "INVALID"

if __name__ == "__main__":
    main()