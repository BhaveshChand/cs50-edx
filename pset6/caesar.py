import sys
import cs50

def main():
    if len(sys.argv)!=2:
        print("Usage: python caesar.py k")
        exit(1)
    k=int(sys.argv[1])
    ptext=cs50.get_string("plaintext: ")
    ctext=[]
    for c in ptext:
        if str.islower(c):
            ctext.append(chr(((ord(c)-ord('a')+k)%26)+ord('a')))
        elif str.isupper(c):
            ctext.append(chr(((ord(c)-ord('A')+k)%26)+ord('A')))
        else:
            ctext.append(c)
    ctext=''.join(ctext)
    print("ciphertext: "+ctext)
    exit(0)

if __name__=="__main__":
    main()