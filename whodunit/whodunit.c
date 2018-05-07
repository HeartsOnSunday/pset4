/*
Implement a program called whodunit that reveals Mr. Boddy’s drawing in such a way that you can recognize whodunit.
Implement your program in a file called whodunit.c in a directory called whodunit.
*/
// Copy BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

/*
Accept exactly two command-line arguments:
        the name of an input file to open for reading
        followed by the name of an output file to open for writing.
*/

int main(int argc, char *argv[])
{

/*
If your program is executed with fewer or more than two command-line arguments,
it should remind the user of correct usage, as with fprintf (to stderr),
and main should return 1.
*/

 // validate arguments and show usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: copy infile outfile\n"); //use fprintf with stderr to control the execition of an error message
        return 1; //if error return 1
    }

        //instantiate file names
        char *infile = argv[1];
        char *outfile = argv[2];



/*
If the input file cannot be opened for reading, your program should inform the user,
as with fprintf (to stderr),
main should return 2
*/


FILE *inptr = fopen(infile, "r");       //filepointer opens image for reading
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile); //if the file cannot be opened return error
        return 2;
    }

/*
If the output file cannot be opened for writing, your program should inform the user,
as with fprintf (to stderr),
and main should return 3.
*/

    FILE *outptr = fopen(outfile, "w"); //filepointer opens output file to write new image
    if (outptr == NULL)
    {
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

/*
If the input file is not a 24-bit uncompressed BMP 4.0, your program should inform the user,
as with fprintf (to stderr),
and main should return 4.
*/

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //int padding = (4 - (3 * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            //read over pixels in scanline and change color
            if (triple.rgbtRed == 0xff)
            {
                triple.rgbtRed = 0x00;
            }
            if (triple.rgbtGreen == 0xff && triple.rgbtBlue == 0xff)
            {
                triple.rgbtGreen = 0x00;
                triple.rgbtBlue = 0x00;
            }

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);
/*
Upon success, main should 0.
*/
    // success
    return 0;
}


