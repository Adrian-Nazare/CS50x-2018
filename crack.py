import sys, crypt

def main():
    if len(sys.argv) == 2:
        password, salt  = "", ""
        salt += sys.argv[1][0] + sys.argv[1][1]
        alphabet = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K','L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']
        for a in alphabet:
            for b in alphabet:
                for c in alphabet:
                    for d in alphabet:
                        for e in alphabet:
                            password = a + b + c + d + e
                            if crypt.crypt(password, salt) == sys.argv[1]:
                                print(f"The Correct Key is {password}")
                                return 0
                            password = ""
                        password = a + b + c + d
                        #print(password)
                        if crypt.crypt(password, salt) == sys.argv[1]:
                            print(f"The Correct Key is {password}")
                            return 0
                        password = ""
                    password = a + b + c
                    if crypt.crypt(password, salt) == sys.argv[1]:
                        print(f"The Correct Key is {password}")
                        return 0
                    password = ""
                password = a + b
                if crypt.crypt(password, salt) == sys.argv[1]:
                    print(f"The Correct Key is {password}")
                    return 0
                password = ""
            password = a
            if crypt.crypt(password, salt) == sys.argv[1]:
                print(f"The Correct Key is {password}")
                return 0
            password = ""
        print("No key was found")
        return 1


if __name__ == "__main__":
    main()

