
from cs50 import get_int

def main():
    while True:
        n = get_int("Pyramid number =")
        if n > 0 or n <= 23:
            break
    for i in range (n):
        for j in range (n - 1 - i):
            print(" ", end = "")
        for j in range (i):
            print("#", end = "")
        print ("# #", end = "")
        for j in range (i):
            print ("#", end = "")
        print()

if __name__ == "__main__":
    main()
