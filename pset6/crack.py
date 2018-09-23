import sys
import crypt

if len(sys.argv)!=2:
    print("Usage: python crack.py hash")
    exit(1)
salt=sys.argv[1][0:2]
alphabet=[chr(c) for c in range(ord('a'),ord('z')+1)]
alphabet.extend([chr(c) for c in range(ord('A'),ord('Z')+1)])

def iterate(key):
    if len(key)==5:
        return
    for i in alphabet:
        keymod=key+i
        print(keymod)
        if sys.argv[1]==crypt.crypt(keymod,salt):
            print(keymod)
            exit(0)
        iterate(keymod)
    return

iterate('')