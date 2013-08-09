#!/bin/bash

if [ "$NDK" = "" ]; then
	echo NDK variable not set, assuming ${HOME}/android-ndk/android-ndk-r8e
	export NDK=${HOME}/android-ndk/android-ndk-r8e
fi

SYSROOT=$NDK/platforms/android-14/arch-arm
WORKING_DIR=`pwd`
# Expand the prebuilt/* path into the correct one
#TOOLCHAIN=`echo $NDK/toolchains/arm-linux-androideabi-4.6/prebuilt/*-x86`
TOOLCHAIN=$NDK/toolchains/arm-linux-androideabi-4.6/prebuilt/linux-x86
export PATH=$TOOLCHAIN/bin:$PATH

rm -rf build/ffmpeg
mkdir -p build/ffmpeg
#cd ffmpeg

# Don't build any neon version for now
for version in armv5te armv7a; do

	DEST=$WORKING_DIR/build/ffmpeg
	FLAGS="--target-os=linux --cross-prefix=arm-linux-androideabi- --arch=arm"
	FLAGS="$FLAGS --sysroot=$SYSROOT"
	#FLAGS="$FLAGS --soname-prefix=/data/data/com.bambuser.broadcaster/lib/"
	FLAGS="$FLAGS --soname-prefix=/data/data/cc.omusic.FingerprintDecodeApp/lib/"
	#FLAGS="$FLAGS --soname-prefix=/data/data/cc.omusic.FingerprintDecodeLib/lib/"
	FLAGS="$FLAGS --enable-shared --disable-symver"
	FLAGS="$FLAGS --enable-small --optimization-flags=-O2"
	FLAGS="$FLAGS --disable-everything"
	FLAGS="$FLAGS --enable-cross-compile \
	  --disable-doc \
	  --disable-ffplay \
	  --disable-ffmpeg \
	  --disable-ffprobe \
	  --disable-ffserver \
	  --disable-avdevice \
	  --disable-avresample \
	  --disable-avfilter \
	  --disable-encoders \
	  --disable-muxers \
	  --disable-filters \
	  --disable-devices \

	  --disable-everything \
	  --disable-decoders \
	  --enable-decoder=mp2 \
	  --enable-decoder=mp3 \
	  --enable-decoder=aac \
	  --enable-decoder=aac_latm \
	  --enable-decoder=wmalossless\
	  --enable-decoder=wmapro \
	  --enable-decoder=wmav1 \
	  --enable-decoder=wmav2 \
	  --enable-decoder=wmavoice \


	  --disable-protocols  \
	  --enable-protocol=file \

	  --disable-parsers \
	  --enable-parser=aac \
	  --enable-parser=aac_latm \
	  --enable-parser=mpegaudio \

	  --disable-demuxers \
	  --enable-demuxer=aac \
	  --enable-demuxer=mp3 \
	  --enable-demuxer=ogg \
	  --enable-demuxer=asf \
	  --enable-demuxer=xwma \
	  --enable-demuxer=flv\

	  --disable-bsfs \
	  --disable-network \
	  --disable-swscale  \
	  --disable-demuxer=sbg \
	  --disable-demuxer=dts \
	  --disable-parser=dca \
	  --disable-decoder=dca "

	case "$version" in
		neon)
			EXTRA_CFLAGS="-march=armv7-a -mfloat-abi=softfp -mfpu=neon"
			EXTRA_LDFLAGS="-Wl,--fix-cortex-a8"
			# Runtime choosing neon vs non-neon requires
			# renamed files
			ABI="armeabi-v7a"
			;;
		armv7a)
			EXTRA_CFLAGS="-march=armv7-a -mfloat-abi=softfp"
			EXTRA_LDFLAGS=""
			ABI="armeabi-v7a"
			;;
		*)
			EXTRA_CFLAGS=""
			EXTRA_LDFLAGS=""
			ABI="armeabi"
			;;
	esac
	DEST="$DEST/$ABI"
	FLAGS="$FLAGS --prefix=$DEST"

	mkdir -p $DEST
	echo $FLAGS --extra-cflags="$EXTRA_CFLAGS" --extra-ldflags="$EXTRA_LDFLAGS" > $DEST/info.txt
	./configure $FLAGS --extra-cflags="$EXTRA_CFLAGS" --extra-ldflags="$EXTRA_LDFLAGS" | tee $DEST/configuration.txt
	[ $PIPESTATUS == 0 ] || exit 1
	make clean
	make -j4 || exit 1
	make install || exit 1

done

