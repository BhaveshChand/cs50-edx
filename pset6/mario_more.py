import cs50

def main():
    while True:
        height=cs50.get_int("Height: ")
        if height>=0 and height<=23:
            break
    for i in range(1,height+1):
        print(" "*(height-i),end="")
        print("#"*i,end="")
        print(" "*2,end="")
        print("#"*i)

if __name__=="__main__":
    main()