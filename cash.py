



def main():
    while True:
        change_owned = float(input("How much change are you owned? "))
        if change_owned > 0:
            break
    cents_owned = int(round(change_owned * 100))
    coins = cents_owned // 25
    cents_owned %=25
    coins += cents_owned // 10
    cents_owned %=10
    coins += cents_owned // 5
    cents_owned %=5
    coins += cents_owned
    print(f"total coins = {coins}")

if __name__ == "__main__":
    main()
