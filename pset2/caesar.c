#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    
    if (argc != 2)
    {
        printf("Error: Try Again\n");
        return 1;
    }
    else
    {
        printf("plaintext: ");
    }
    
    int key = atoi(argv[1]); //change integers in argv[1] to chars
    
    string p = GetString(); //get plaintext from the user
    if (p != NULL)
    {
        printf("ciphertext: ");
        for (int i = 0, length = strlen(p); i < length; i++)
        {
            //check if it is upper or lower case
            if isupper(p[i])
            {
                printf("%c", (((p[i] + key) - 65) % 26) + 65);
            }
            else if islower(p[i])
            {
                printf("%c", (((p[i] + key) - 97) % 26) + 97);
            }
            else //print everything that is not a character as is
            {
                printf("%c", p[i]);
            }
        }
    }
    printf("\n");
    return 0;
}
