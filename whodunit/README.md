# Questions

## What's `stdint.h`?
//library for standardized Intergers
//uses typedef

TODO

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?
//distinguish between a unit using 8 bits (1 Byte), 32 bits (4 Bytes or 1 DWORD or 1 Long) oe 16 bits (2 bytes or 1 word).

TODO

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?
// 1 Byte == 8 bits
// 1 DWORD == 4 Bytes == 32 bits
// 1 LONG == 4 Bytes == 32 bits
// 1 WORD == 2 Bytes == 16 bits


TODO

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."
//Must be B M
ASCII: B == 66 and M == 77
HEX: B == 42
HEX: M == 4D


TODO

## What's the difference between `bfSize` and `biSize`?
//bfSize is the whole size of bf and includes headerfile
//biSize is constant, always equal to 40 bytes, its the bitmapInfoHeader

TODO

## What does it mean if `biHeight` is negative?
//top-down, zero is in the top left corner

TODO

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?
//

TODO

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

TODO

## Why is the third argument to `fread` always `1` in our code?

TODO

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

TODO

## What does `fseek` do?

TODO

## What is `SEEK_CUR`?

TODO
