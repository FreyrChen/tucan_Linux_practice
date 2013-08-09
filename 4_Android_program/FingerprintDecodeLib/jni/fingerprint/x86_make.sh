#!/bin/sh

#gcc -o main main.c   -lz  -lm
#gcc -o main main.c -lavutil -lavformat -lavcodec -lz -lavutil -lm
gcc -Wall -g FingerprintX86.c -o FingerprintX86 -lavformat -lavcodec  -lavutil -lva -lz -lavutil -lm -lpthread  -lbz2
#gcc -o main main.c  -lavformat -lavcodec -lz  -lm
