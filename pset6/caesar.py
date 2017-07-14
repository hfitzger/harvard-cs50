import cs50
import sys
    
if len(sys.argv) != 2:
    print("Error: Try Again")
else:
    print("plaintext: ", end="")

key = int(sys.argv[1])

ptext = cs50.get_string()

if ptext != None:
    print("ciphertext: ", end="")
    
    for i in range (len(ptext)):
        if ptext[i].isupper():
            print ("{}".format(chr((ord(ptext[i]) - (65) + key) % 26 + 65)), end="")
        elif ptext[i].islower():
            print ("{}".format(chr((ord(ptext[i]) - (97) + key) % 26 + 97)), end="")
        else:
            print("{}".format(chr(ord (ptext[i]))), end="")
    print()
