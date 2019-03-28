import sys

def main():
    if len(sys.argv) == 1:
        print ("Please enter key word as well")
        return 1
    elif len(sys.argv) == 2 and sys.argv[1].isalpha():
        key = sys.argv[1].upper()
        key_len = len(key)
        for char in key:
            char = ord(char) - 65
            #print(char)
        text = input("Message to encypt ")
        encrypted = ""
        for i in range(len(text)):
            if ord(text[i]) > 64 and ord(text[i]) < 91:
                encrypted += chr(65 + (ord(text[i]) + ord(key[i % key_len])) % 26) #chr((65 + (ord(text[i]) - 65 + ord(key[i % key_len]))) % 26)
            elif ord(text[i]) > 96 and ord(text[i]) < 123:
                encrypted += chr(97 + (ord(text[i]) + ord(key[i % key_len])) % 26)
            else:
                encrypted += text[i]
        print(f"Cyphertext: {encrypted}")
        return 0
    else:
        print("error, more than 1 keyword")
        return 1

if __name__ == "__main__":
    main()