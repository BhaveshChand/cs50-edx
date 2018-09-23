import cs50
import sys

def main():
    if len(sys.argv)!=2 or not str.isalpha(sys.argv[1]):
        print("Usage: python vigenere.py k")
        exit(1)
    key=str.upper(sys.argv[1])
    ptext=cs50.get_string("plaintext: ")
    ctext=[]
    j=0
    for c in ptext:
        if str.islower(c):
            ctext.append(chr(((ord(c)-ord('a')+ord(key[j%len(key)])-ord('A'))%26)+ord('a')))
            j+=1
        elif str.isupper(c):
            ctext.append(chr(((ord(c)-ord('A')+ord(key[j%len(key)])-ord('A'))%26)+ord('A')))
            j+=1
        else:
            ctext.append(c)
    ctext=''.join(ctext)
    print("ciphertext: "+ctext)
    exit(0)

if __name__=="__main__":
    main()