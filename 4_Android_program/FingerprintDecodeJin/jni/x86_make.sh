#!/bin/sh

#gcc -o main main.c   -lz  -lm
#gcc -o main main.c -lavutil -lavformat -lavcodec -lz -lavutil -lm

gcc -Wall -std=c99 -g FingerprintX86.c -o FingerprintX86 \
	-lavformat -lavcodec  -lavutil -lva -lz -lavutil -lm  -lpthread -lbz2 \
	|| exit 1

echo '=========== run application ======== '
./FingerprintX86 ~/music_fp/test_music/test.mp3  || exit 1


#gcc -Wall -g FingerprintX86.c -o FingerprintX86 -lavformat -lavcodec  -lavutil -lva -lz -lavutil -lm -lpthread  -lbz2
#gcc -o main main.c  -lavformat -lavcodec -lz  -lm
