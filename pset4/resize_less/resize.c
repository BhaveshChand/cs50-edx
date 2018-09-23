/**
 * Resizes a BMP to n times its dimensions
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    //check for int<=100 and remember
    int n=atoi(argv[1]);
    if(n<1||n>100){
        fprintf(stderr,"n should be a positive integer <=100.\n");
        return 2;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER inbf;
    fread(&inbf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER inbi;
    fread(&inbi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (inbf.bfType != 0x4d42 || inbf.bfOffBits != 54 || inbi.biSize != 40 || 
        inbi.biBitCount != 24 || inbi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    
    //create new BITMAPFILEHEADER and BITMAPINFOHEADER for outfile
    BITMAPFILEHEADER outbf=inbf;
    BITMAPINFOHEADER outbi=inbi;
    
    //change BITMAPINFOHEADER for outfile
    outbi.biWidth=n*inbi.biWidth;
    outbi.biHeight=n*inbi.biHeight;
    
    // determine padding for scanlines
    int inpadding = (4 - (inbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outpadding = (4 - (outbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //change BITMAPFILEHEADER and BITMAPINFOHEADER for outfile
    outbi.biSizeImage=(sizeof(RGBTRIPLE)*outbi.biWidth+outpadding)*abs(outbi.biHeight);
    outbf.bfSize=outbi.biSizeImage+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&outbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&outbi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    //allocate dynamic memory of size equivalent to that of one row of pixels of the resized image
    RGBTRIPLE *ptr=(RGBTRIPLE *)calloc(outbi.biWidth,sizeof(RGBTRIPLE));

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(inbi.biHeight); i < biHeight; i++)
    {
        int copy=0;
        
        // iterate over pixels in scanline
        for (int j = 0; j < inbi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to allocated memory n times
            for(int k=0;k<n;k++){
                *(ptr+copy+k)=triple;
            }
            copy+=n;
        }
        
        // skip over inpadding, if any
        fseek(inptr, inpadding, SEEK_CUR);

        //iterate n times to put n rows of pixels to outfile
        for(int row=0;row<n;row++){
            //write whole row of pixels to outfile
            fwrite(ptr, sizeof(RGBTRIPLE), outbi.biWidth, outptr);
            
            // then add outpadding (to demonstrate how)
            for (int k = 0; k < outpadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }
    
    //free allocated memory
    free(ptr);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
