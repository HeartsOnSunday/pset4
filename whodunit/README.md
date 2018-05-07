# Questions

## What's `stdint.h`?
C library for standardized intergers.
C does not requiresized for inegral data types.
Allows for the sizes of intergers to be defined inside the code.
This allows for portability between platforms.
Uses TYPEDEFS to define the EXACT WIDTH interger types.
Uses MACROS.
prevents errors by allowing standardized intergers to be defined.
TODO

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?
Aliases for C/C++ data types
Distinguish between a unit using 8 bits (1 Byte), 32 bits (4 Bytes or 1 DWORD or 1 Long) or 16 bits (2 bytes or 1 word).
Allocates the correct amount of bits to control the size of the data type.
Since C does not standardize the sizes of the data types its best practice to define these sizes yourself.
This keeps the code from using more memory than necessary and prevents the code from accesing areas of memory that it should not.


## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?
// 1 Byte == 8 bits
// 1 WORD == 2 Bytes == 16 bits
// 1 DWORD == 4 Bytes == 32 bits
// 1 LONG == 4 Bytes == 32 bits



TODO

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."
Must be 'B' 'M'
ASCII: B == 66 and M == 77
HEX: B == 42
HEX: M == 4D
clue.bmp starts as: 424d


TODO

## What's the difference between `bfSize` and `biSize`?
'bfSize' is the whole size of the BMP file. Includes BITMAPINFOHEADER and BITMAPFILEHEADER.
'biSize' is constant, always equal to 40 bytes, its the bitmapInfoHeader (the header).

TODO

## What does it mean if `biHeight` is negative?
The file is top-down, zero (the origin) is in the top left corner.
Use abs(biHeight) for the absolute value.

TODO

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?
WORD biBitCount; defines the color depth of the BMP.

TODO

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?
'NULL' indicated that the file does not exist or it cannot be accessed because the permissionsa are wrong.

TODO

## Why is the third argument to `fread` always `1` in our code?
The third argument in fread() indicates number of elements to read.
In copy.c fread() is reading one element at time.

TODO

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?
Padding will assign 1 to equal a total that is a multiple of 4 (bi.biWidth + padding = 4)

TODO

## What does `fseek` do?
//fseek reads the file looking for something specific. In copy.c it looks for padding and skips over it.

TODO

## What is `SEEK_CUR`?

Moves filepointer location to a specific location.
Will show the surrent location of the pointer

TODO
