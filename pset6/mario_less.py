import cs50

def main():
    while True:
        height=cs50.get_int("Height: ")
        if height>=0 and height<=23:
            break
    for i in range(2,height+2):
        print(" "*(height+1-i),end="")
        print("#"*i)

if __name__=="__main__":
    main()