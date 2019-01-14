# Questions

## What's `stdint.h`?

A library that provides costumizable values for integers.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

More precision and efficiency in managing memory, smaller file size

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE is 1 byte long, WORD is 2 bytes long, and DWORD AND LONG are both 4 bytes long

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

ASCII: MB
decimal: 19778
hexadecimal: 4d42

## What's the difference between `bfSize` and `biSize`?

bfSize is the total size of the image file
biSize is the size of the info header

## What does it mean if `biHeight` is negative?

The image starts from the bottom left upwards, instead of from upper left downwards

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

because the file doesn't exist, or a file wasn't typed in the first place

## Why is the third argument to `fread` always `1` in our code?

Because we are reading 1 chunk of memory BITMAPFILEHEADER/BITMAPINFOHEADER - long at a time

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3 bytes

## What does `fseek` do?

used to move the pointer in order to rewind/fast-forward within a file

## What is `SEEK_CUR`?

argument to the fseek function, ut moves the file pointer position to the given location.

## Whodunit?

It was Professor Plum with the candlestick in the library
