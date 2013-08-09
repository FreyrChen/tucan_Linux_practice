#!/bin/sh

export PREBUILT=/home/tusion/android-ndk/android-ndk-r8e/toolchains/arm-linux-androideabi-4.6
export PLATFORM=/home/tusion/android-ndk/android-ndk-r8e/platforms/android-14/arch-arm
#export TMPDIR=/home/work/tmp
WORKING_DIR=`pwd`

./configure \
--target-os=linux \
--arch=arm \
--disable-symver \
--disable-debug \
--disable-stripping \
--disable-yasm \
--disable-asm \
--enable-gpl \
--enable-version3 \
--enable-nonfree \
--disable-doc \
--enable-static \
--disable-shared \
--enable-cross-compile \
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
#--enable-protocol=file \
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
--enable-swscale  \
--prefix=$WORKING_DIR/ffmpeg \
--cc=$PREBUILT/prebuilt/linux-x86/bin/arm-linux-androideabi-gcc \
--cross-prefix=$PREBUILT/prebuilt/linux-x86/bin/arm-linux-androideabi- \
--nm=$PREBUILT/prebuilt/linux-x86/bin/arm-linux-androideabi-nm \
--extra-cflags="-fPIC -DANDROID -I$PLATFORM/usr/include" \
--extra-ldflags="-L$PLATFORM/usr/lib -nostdlib"
