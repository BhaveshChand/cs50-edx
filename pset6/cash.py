import cs50

def main():
    while True:
        change=cs50.get_float("Change owed: ")
        if change>=0:
            break
    coins=0
    change*=100
    change=round(change)
    coins+=change//25
    change%=25
    coins+=change//10
    change%=10
    coins+=change//5
    change%=5
    coins+=change
    print(coins)

if __name__=="__main__":
    main()