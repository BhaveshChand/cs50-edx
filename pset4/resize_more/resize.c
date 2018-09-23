/**
 * Resizes a BMP to f times its dimensions
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
    double n=atof(argv[1]);
    if(n<=0||n>100){
        fprintf(stderr,"n should be a positive real number <=100.\n");
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
    
    //create nearest possible value ratios for both Height and Width
    double nw=(double)inbi.biWidth/outbi.biWidth;
    double nh=(double)inbi.biHeight/outbi.biHeight;
    
    // iterate over outfile's scanlines
    int hout=abs(outbi.biHeight),wout=outbi.biWidth,hin=abs(inbi.biHeight),win=inbi.biWidth;
    double iin=1e-9;
    for (int iout=0;iin<hin&&iout<hout;iout++)
    {
        // iterate over pixels in scanline
        double jin=1e-9;
        for (int jout=0;jin<win&&jout<wout;jout++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            
            //change counters and seek as necessary
            jin+=nw;
            fseek(inptr,sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+((int)iin)*(sizeof(RGBTRIPLE)*inbi.biWidth+inpadding)+((int)jin)*sizeof(RGBTRIPLE),SEEK_SET);
    
        }
        
        // skip over inpadding, if any
        fseek(inptr, inpadding, SEEK_CUR);

        // then add outpadding (to demonstrate how)
        for (int k = 0; k < outpadding; k++)
        {
            fputc(0x00, outptr);
        }
        
        //change counters and seek as necessary
        iin+=nh;
        fseek(inptr,sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+((int)iin)*(sizeof(RGBTRIPLE)*inbi.biWidth+inpadding),SEEK_SET);
        
    }
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
