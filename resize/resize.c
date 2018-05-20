// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy multiplier infile outfile\n");
        return 1;
    }

    //initialize resize factor
    int mult = atoi(argv[1]);
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    //printf("The Factor is: %c\n", *factor);
    printf("The multiplier is: %i\n", mult);

     if (mult < 0 || mult > 100)
    {
        fprintf(stderr, "Multiplier must be an integer greater than 1 and less than 100\n");
        return 2;
    }

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
        return 5;
    }

    BITMAPFILEHEADER NEWbf = bf;
    BITMAPINFOHEADER NEWbi = bi;

    //int newWidth = bi.biWidth * mult;
    //printf("new width: %i\n", newWidth);
    NEWbi.biWidth *= mult;

    //int newHeight = bi.biHeight * mult;
    //printf("new hidth: %i\n", newHeight);
    NEWbi.biHeight *= mult;
    //printf("old higth: %i\n", bi.biHeight);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4)%4;
    //printf("padding = %i\n", padding);

    int NEWpadding = (4 - (NEWbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //printf("New padding = %i\n", NEWpadding);

    NEWbi.biSizeImage = (sizeof(RGBTRIPLE) * NEWbi.biWidth + NEWpadding) * abs(NEWbi.biHeight);
    //printf("new bi Size: %i\n", NEWbibiSizeImage);

    NEWbf.bfSize = NEWbi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    //printf("new bf Size: %i\n", NEWbfbfSize);


/*
use the newly calculated variables for biSizeImage (affects the INFOHEADER) and bfSize (affects the FILEHEADER)
Dereference the struct!!!
*/

    // read infile's BITMAPFILEHEADER
   // BITMAPFILEHEADER NEWbf;
    //NEWbf.bfSize = NEWbfbfSize;
    //printf("%i\n", NEWbfbfSize);
    // read infile's BITMAPINFOHEADER
   // BITMAPINFOHEADER NEWbi;
    //bi.biSizeImage = NEWbibiSizeImage;
    //printf("%i\n", NEWbibiSizeImage);


    // write outfile's BITMAPFILEHEADER
    fwrite(&NEWbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&NEWbi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //iterate for mult times (adjusts the height)
        for (int j = 0; j < mult; j++)
        {
            // iterate over pixels in scanline
            for (int p = 0; p < NEWbi.biWidth; p++)
            {
            // temporary storage
            RGBTRIPLE triple;
            //RGBTRIPLE lines[sizeof(newWidth)];
            //RGBTRIPLE newLines[sizeof(NEWbi.biWidth)];
            //int m = 0; //always less than then newWidth


            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (int l = 0; l < mult; l++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                //newLine
                //Write to the array multiplier times
                //newLines[ m ] = triple;
               // printf("variable n is %i\n", n);
                // printf("Variable m is %i\n", m);
                // printf("Variable l is %i\n", l);
                // printf("Variable j is %i\n", j);

                // m += 1;
                // write RGB triple to outfile
                //fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                //fwrite(&triple, sizeof(RGBTRIPLE), 1, &lines);
            }

            // for (int n = 0; n < mult; n++ )
            // {
            //     for ( int o = 0; o < sizeof(newLines); o++)
            //     {
            //     //fwrite(&newLines[o], sizeof(RGBTRIPLE), 1, outptr);
            //     }
            // }


//Array is written
//Write the Array to the the scanline (multiplier number of times)
        }


            //printf("The index of the array is: %i", m);

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            //add padding back in
            for (int k = 0; k < NEWpadding; k++)
            {
                fputc(0x00, outptr);
            }


        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        if (j < mult - 1)
        {
            fseek(inptr, -(bi.biWidth * 3 + padding), SEEK_CUR);
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


/*WHAT CHANGES

bi is a struct
Create a new strut? Name it NEW
Create new variable to store calculated amount of padding


NEW.biWidth = bi.biWidth *= multiplier

NEW.biHeight = bi.biHeight *= multiplier

Calculate new padding:
NEW PADDING = int NEWpadding = (4 - (NEWbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


NEW.biSizeImage = bi.biSizeImage = (sizeof(RGBTRIPLE) * bi.Width * multiplier) + NEWpadding) * (abs(bi.Height) * multipier)
ALTERNATIVE.biSizeImage = bi.biSizen = (sizeof(RGBTRIPLE) * (NEW.biWidth + Newpadding)) * (abs(NEW.biHeight)




NEW.bf.bfSize = NEW.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)

I is confused





you must dereference the pointer!!! Reassign the variables!!!

new bi Size Image

and

and new bf.bfsize


*/