import cs50

def checksum(card):
    sum=0
    while card>0:
        sum+=card%10
        card//=10
        sum+=(((card%10)*2)%10)+(((card%10)*2)//10)
        card//=10
    return sum%10

def main():
    card=cs50.get_int("Number: ")
    if(not(checksum(card))):
        if card//(10**13) in (34,37):
            print("AMEX")
        elif card//(10**14) in range(51,56):
            print("MASTERCARD")
        elif card//(10**15)==4 or card//(10**12)==4:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")

main()