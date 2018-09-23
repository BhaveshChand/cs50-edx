import sys
import crypt

if len(sys.argv)!=2:
    print("Usage: python crack.py hash")
    exit(1)
salt=sys.argv[1][0:2]
alphabet=[chr(c) for c in range(ord('a'),ord('z')+1)]
alphabet.extend([chr(c) for c in range(ord('A'),ord('Z')+1)])

def main():
    for i in alphabet:
        key=i
        if sys.argv[1]==crypt.crypt(key,salt):
            print(key)
            exit(0)
        for j in alphabet:
            key=i+j
            if sys.argv[1]==crypt.crypt(key,salt):
                print(key)
                exit(0)
            for k in alphabet:
                key=i+j+k
                if sys.argv[1]==crypt.crypt(key,salt):
                    print(key)
                    exit(0)
                for l in alphabet:
                    key=i+j+k+l
                    if sys.argv[1]==crypt.crypt(key,salt):
                        print(key)
                        exit(0)
                    for m in alphabet:
                        key=i+j+k+l+m
                        if sys.argv[1]==crypt.crypt(key,salt):
                            print(key)
                            exit(0)

if __name__=="__main__":
    main()