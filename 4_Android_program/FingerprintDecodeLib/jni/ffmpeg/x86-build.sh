#!/bin/bash

if [ "$NDK" = "" ]; then
	echo NDK variable not set, assuming ${HOME}/android-ndk/android-ndk-r8e
	export NDK=${HOME}/android-ndk/android-ndk-r8e
fi

SYSROOT=$NDK/platforms/android-14/arch-x86
WORKING_DIR=`pwd`
# Expand the prebuilt/* path into the correct one
TOOLCHAIN=`echo $NDK/toolchains/x86-4.6/prebuilt/linux-x86`
export PATH=$TOOLCHAIN/bin:$PATH

rm -rf build/ffmpeg
mkdir -p build/ffmpeg
cd ffmpeg

# Don't build any neon version for now
for version in x86; do

	DEST=$WORKING_DIR/build/ffmpeg
	FLAGS="--target-os=linux --cross-prefix=i686-linux-android- --arch=x86"
	FLAGS="$FLAGS --sysroot=$SYSROOT"
	FLAGS="$FLAGS --soname-prefix=/data/data/com.bambuser.broadcaster/lib/"
	FLAGS="$FLAGS --enable-shared --disable-symver"
	FLAGS="$FLAGS --enable-small --optimization-flags=-O2"
	FLAGS="$FLAGS --disable-everything"
	FLAGS="$FLAGS --enable-encoder=mpeg2video --enable-encoder=nellymoser"

	case "$version" in
		x86)
			EXTRA_CFLAGS=""
			EXTRA_LDFLAGS=""
			ABI="x86"
			;;
	esac
	DEST="$DEST/$ABI"
	FLAGS="$FLAGS --prefix=$DEST"

	mkdir -p $DEST
	echo $FLAGS --extra-cflags="$EXTRA_CFLAGS" --extra-ldflags="$EXTRA_LDFLAGS" > $DEST/info.txt
	./configure $FLAGS --extra-cflags="$EXTRA_CFLAGS" --extra-ldflags="$EXTRA_LDFLAGS" --extra-cflags='-mincoming-stack-boundary=4' | tee $DEST/configuration.txt
	[ $PIPESTATUS == 0 ] || exit 1
	make clean
	make -j4 || exit 1
	make install || exit 1

done

