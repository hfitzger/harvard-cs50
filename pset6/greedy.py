import cs50

#prompt user for the amount of change they should receive
while True:
    print ("How much change is owed? ", end="")
    change = cs50.get_float()
    if change > 0:
        break

#declare coins variable
coins = 0

#convert $1 into 100cents
amt = round(change * 100)

#determine the amount of coins that should be used for change
while amt > 0:
    if (amt - 25) >= 0:
        amt = amt - 25
        coins += 1
    elif (amt - 10) >= 0:
        amt = amt - 10
        coins += 1
    elif (amt - 5) >= 0:
        amt = amt - 5
        coins += 1
    elif (amt - 1) >= 0:
        amt = amt - 1
        coins += 1
        
#display the least amount of coins used for change needed
print (coins)
