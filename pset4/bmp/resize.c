/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize koef infile outfile\n");
        return 1;
    }

    // remember filenames
    int koef;
    koef=atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if ((inptr == NULL) || koef <1)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    BITMAPFILEHEADER bf2;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf2= bf;
    

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    BITMAPINFOHEADER bi2;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi2=bi;
    
    

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // transform new data:
    int padding2= (4 - (bi.biWidth *koef* sizeof(RGBTRIPLE)) % 4) % 4;
    bi2.biWidth=bi.biWidth*koef;
    bi2.biHeight=bi.biHeight*koef;
    bi2.biSizeImage=bi2.biWidth*sizeof(RGBTRIPLE)*abs(bi2.biHeight);
    DWORD tmp;
    tmp=bf.bfSize-bi.biSizeImage;
    bf2.bfSize=tmp+bi2.biSizeImage+padding2*abs(bi2.biHeight);
    

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf2, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi2, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    

    // iterate over infile's scanlines
    for (int i = 0; i < abs(bi2.biHeight); i++)
    {
        
        
            
                
                    
                 // iterate over pixels in scanline
                    for (int j = 0; j < bi.biWidth; j++)
                    {
                        // temporary storage
                        RGBTRIPLE triple;
                        // read RGB triple from infile
                        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                        
                        
                        for (int n=0; n < koef; n++)
                            {
                                                  

                                // write RGB triple to outfile
                                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                
                            }
        
                        
            
                    }
                    // skip over padding, if any
                        fseek(inptr, padding, SEEK_CUR);

                        // then add it back (to demonstrate how)
                        for (int k = 0; k < padding2; k++)
                        {
                            fputc(0x00, outptr);
                        }
                         // skip the virtual line of the file (even lines - copy)
                        if ((i+1)%koef!=0)
                        { 
                            
                                fseek(inptr, -(bi.biWidth*sizeof(RGBTRIPLE)+padding), SEEK_CUR);  
                            
                        }
                    
                    
                     
                
             
        
    
       
        
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
