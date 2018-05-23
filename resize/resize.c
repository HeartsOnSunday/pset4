// Copies a BMP file

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
    /*Create variable for multiplier used to change photo size*/
    //multiplier
    int mult = atoi(argv[1]);

    /*Use pointers to access location of files*/
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    ///*Use a file pointer to open the infile*/
    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        /*if it isnt opened:
            A. the files doesnrt exist
            B. wrong permissions,
                fopen() allows read permission
                to infile: line 33
                */
        fprintf(stderr, "Could not open %s.\nCheck spelling of infile.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        /*if it isnt opened:
            A. the files doesnrt exist
            B. wrong permissions,
        fopen() allows write permission
        to outfile: line 41
        */
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\nCheck spelling of outfile.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
/*Plan to use BITMAPFILEHEADER to create struct nameed bf
    Use fread() to create the struct from the infile
    Use infile to read 1 element the size of the struct named bf and start at location of pointer &bf
    */
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
/*Plan to use BITMAPINFOHEADER on bmp.h to create struct nameed bi
    Use fread() to create the struct from the infile
    Use infile to read 1 element the size of the struct named bf and start at location of pointer &bf
    */
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\nFix your pic!\n");
        return 4;
    }

/*New Structs for outfile*/
BITMAPFILEHEADER NEWbf = bf;
BITMAPINFOHEADER NEWbi = bi;

/*Variables for outfile*/

NEWbi.biWidth *= mult;
NEWbi.biHeight *= mult;
// determine padding for scanlines
int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
int NEWpadding = (4 - (NEWbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
NEWbi.biSizeImage = (sizeof(RGBTRIPLE) * NEWbi.biWidth + NEWpadding) * abs(NEWbi.biHeight);
NEWbf.bfSize = NEWbi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);




    // write outfile's BITMAPFILEHEADER
/*Use the outfile to write 1 element the size BITMAPFILEHEADER starting at &bf*/
    fwrite(&NEWbf, sizeof(BITMAPFILEHEADER), 1, outptr);

/*Write to the outfie 1 element the size BITMAPINFOHEADER starting from location of struct bi*/
    // write outfile's BITMAPINFOHEADER
    fwrite(&NEWbi, sizeof(BITMAPINFOHEADER), 1, outptr);



    // iterate over infile's scanlines
/*start at the first pixel and read across the width writing pixels into
    file with struct triple*/

    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int vertical = 0; vertical < mult; vertical++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int horizontal = 0; horizontal < mult; horizontal++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

            }

            //skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            //Add padding to outfile
            for (int k = 0; k < NEWpadding; k++)
            {
                fputc(0x00, outptr);
            }

            if (vertical < mult - 1)
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


