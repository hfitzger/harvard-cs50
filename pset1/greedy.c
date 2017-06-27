#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // indetifying my variables
    float change;
    int coins = 0;
    // print question and prompt user to insert their answer
    do
    {
    printf("How much change is owed?\n");
    change = get_float();
    }
    while (change < 0);
    
    // convert the float to an integer (0.41 to 41) aka amt
    // while loop with (if, else if) statements inside of it to determine amount of each coin should result in the change given
    int amt = round(change * 100);
    while (amt > 0)
    {
        if ((amt - 25) >= 0) {amt = amt - 25; coins++;}
        else if ((amt - 10) >= 0) {amt = amt - 10; coins++;}
        else if ((amt - 5) >= 0) {amt = amt - 5; coins++;}
        else if ((amt - 1) >= 0) {amt = amt - 1; coins++;}
    }
    
    //print number of coins customer should receive 
    printf("%i\n", coins);
}
