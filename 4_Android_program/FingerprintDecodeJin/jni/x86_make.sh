#!/bin/sh

#gcc -o main main.c   -lz  -lm
#gcc -o main main.c -lavutil -lavformat -lavcodec -lz -lavutil -lm

gcc -Wall -std=c99 -g FingerprintX86.c ./libfooid/libfooid.a  -o FingerprintX86 \
	-lavformat -lavcodec  -lavutil -lva -lz -lavutil -lm  -lpthread -lbz2  \
	-L ./libfooid/libfooid.a ./libfooid/libresample/libresample.a \
	|| exit 1

echo '=========== run application ======== '
#./FingerprintX86 ./libfooid/test.wav  || exit 1
./FingerprintX86 ~/music_fp/test_music/test.mp3  || exit 1
#./FingerprintX86 ~/music_fp/test_music/1490278.mp3  || exit 1
#./FingerprintX86 ~/music_fp/test_music/311067.aac  || exit 1
#./FingerprintX86 ~/music_fp/test_music/2755785.mp3  || exit 1

#ls -hl ./

#gcc -Wall -g FingerprintX86.c -o FingerprintX86 -lavformat -lavcodec  -lavutil -lva -lz -lavutil -lm -lpthread  -lbz2
#gcc -o main main.c  -lavformat -lavcodec -lz  -lm
