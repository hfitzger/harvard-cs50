#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error: Try Again!\n");
        return 1;
    }
    else
    {
    for(int i=0;i < strlen(argv[1]); i++)
    {
    if isalpha(argv[1][i]) {}
    else {

    printf("Error: Try Again!\n");
        return 1;
        }
    }
        printf("plaintext: ");
    }
    
    string pt = get_string();
    if (pt != NULL)
    {
    printf("ciphertext: ");
    int x = 0;
    
    
    for (int i = 0, length = strlen(pt); i < length; i++)
    {
        x = x % strlen(argv[1]);
        
        if (isalpha (pt[i]))
            {
                if (isupper(pt[i]) && isupper(argv[1][x]))
                {
                    printf("%c", (((pt[i] - 65) + (argv[1][x] - 65)) % 26) + 65);
                }
                else if (islower(pt[i]) && islower(argv[1][x]))
                {  
                    printf("%c", (((pt[i] - 97) + (argv[1][x] - 97)) % 26) + 97);
                }
                else if (isupper(pt[i]) && islower(argv[1][x]))
                {
                    printf("%c", (((pt[i] - 65) + (argv[1][x] - 97)) % 26) + 65);
                }
                else if (islower(pt[i]) && isupper(argv[1][x]))
                {  
                    printf("%c", (((pt[i] - 97) + (argv[1][x] - 65)) % 26) + 97);
                }
                x++;
            }
        else
            {
                printf("%c", pt[i]);
            }
        }
    }
    printf("\n");
    return 0;
}
