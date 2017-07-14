import cs50
def main():
    
    global row
    global space
    global hash

    while True:
        print ("Height: ", end="")
        height = cs50.get_int()
        if height <= 0 or height > 23:
            print ("Number must be 1 - 23")
            break
        
        row = 1 
        for row in range (height):
            for space in range (height - row):
                print(" ", end="")
            for h in range (row + 2):
                print("#", end="")
            print()

if __name__ == "__main__":
 main()
