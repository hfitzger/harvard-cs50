// TODO:
// Open memory card file
// Find beginning of JPEG
// Open a new JPEG
// Write 512 bytes until new JPEG is found
// detect end of file

// PSEUDOCODE:
// open card file
// repeat until end of card
//     read 512 bytes into a buffer
//     start a new jpeg?
//         -yes...
//         -no...
//     already found a jpeg?
//         -no...
//         -yes...
// close any remaining files
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE; //create a type of unsigned integers of length of 8 bits (1 byte)

int main (int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Error: accepts exactly one command-line argument\n");
        return 1;
    }
    
    char* memcard = argv[1];
    //open card.raw
    FILE* inptr = fopen(memcard, "r");
    
    //check if NULL
    if (inptr == NULL)
    {
    fprintf(stderr,"%s cannot be opened for reading\n", memcard);
    return 2;
    }    

    //Initialize
    char pic [8];
    FILE* img = NULL;
    BYTE buffer [512];
    int samejpeg = 0;
    int newjpeg = 1; 
    
    //read each 512 MB block
    while (fread(&buffer, 512, 1, inptr)  == 1)
    {
        if (newjpeg == 1) //the start of a new jpeg
        {
            if(buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3]>=0xe0 || buffer [3] <= 0xef))
            {
                newjpeg = 0;
                
                sprintf(pic, "%03d.jpg", samejpeg);
                img = fopen(pic, "w");
                fwrite(&buffer, 512, 1, img);
            }
        }
        else //already found a jpeg?
        {
            if (buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3]==0xe0 || buffer [3] == 0xe1))
            {
                fclose(img);
                samejpeg++;
                
                sprintf(pic, "%03d.jpg", samejpeg);
                img = fopen(pic, "w");
                fwrite(&buffer, 512, 1, img);
            }
            else
            {
                fwrite(&buffer, 512, 1, img);
            }
        }
    }
    fclose(img);
return 0; 
}
