#!/bin/sh

#gcc -o main main.c   -lz  -lm
#gcc -o main main.c -lavutil -lavformat -lavcodec -lz -lavutil -lm
gcc -Wall -g main.c -o main  -lavformat -lavcodec  -lavutil -lva -lz -lavutil -lm -lpthread

#gcc -o main main.c  -lavformat -lavcodec -lz  -lm
