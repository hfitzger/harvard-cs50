/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4) //CHANGE THIS TO 4 SO YOU CAN INSERT N VALUE TO RESIZE
    {
        fprintf(stderr, "Usage: ./copy infile outfile\n");
        return 1;
    }
    //REMEMBER N VALUE
    int n = atoi(argv[1]);
    
    //N MUST BE (0 - 100]
    if (n < 1 || n > 100){
    fprintf(stderr, "Must insert integer 1-100\n");
    return 5;
    }
  
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        printf("outptr=null");
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
//INITIALIZE SECTION
    //CREATE NEW HEADER VARIABLES FOR OUTFILE
    BITMAPFILEHEADER bfNEW;
    BITMAPINFOHEADER biNEW;
    
    //COPY THE INFILE VALUES INTO THE NEW OUTFILE VARIABLES
    bfNEW = bf;
    biNEW = bi;
    
    //MULTIPLY THE INFOHEADER HEIGHT AND WIDTH BY n
    biNEW.biHeight *= n;
    biNEW.biWidth *= n; //does not include padding 

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingNEW = (4 - (biNEW.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //SET NEW INFOHEADER SIZE IMAGE 
    biNEW.biSizeImage = (biNEW.biWidth *sizeof(RGBTRIPLE) + paddingNEW) * abs(biNEW.biHeight);
    
    //SET NEW FILEHEADER SIZE
    bfNEW.bfSize = biNEW.biSizeImage + 54;
    
//INITIALIZE SECTION ENDED

    // write NEW outfile's BITMAPFILEHEADER
    fwrite(&bfNEW, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write NEW outfile's BITMAPINFOHEADER
    fwrite(&biNEW, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    //CREATE A VARIABLE THAT IS THE LENGTH OF INFILE'S SCANLINE
    int offset = (bi.biWidth * sizeof(RGBTRIPLE) + padding);

    // iterate over infile's scanlines
    for (int i = 0, OLD_biHeight = abs(bi.biHeight); i < OLD_biHeight; i++)
    {
        //VERTICAL FOR LOOP
        for (int v=0; v < n; v++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                //HORIZONTAL FOR LOOP
                for (int h=0; h < n; h++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);
    
                // then add it back (to demonstrate how)
                for (int k = 0; k < paddingNEW; k++)
                {
                    fputc(0x00, outptr);
                }
            //RETURN POINTER TO START OF INFILE TO WRITE VERTICALS
                if (v < n-1)   
                {
                fseek (inptr, -offset, SEEK_CUR);
                }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
