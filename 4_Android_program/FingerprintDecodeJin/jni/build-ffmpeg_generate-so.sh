#!/bin/sh
echo'==============================================='
echo 'into ffmpeg dir to build libs'

cd ffmpeg-0-11-1

echo 'make clean'
sudo rm -rf ffmpeg
sudo make clean

echo 'configure ffmepg for android'
export PREBUILT=/home/tusion/android-ndk/android-ndk-r8e/toolchains/arm-linux-androideabi-4.6
export PLATFORM=/home/tusion/android-ndk/android-ndk-r8e/platforms/android-14/arch-arm
#export TMPDIR=/home/work/tmp
WORKING_DIR=`pwd`

#must enable file protocol, to open local files.
#the default for .wav files is use pcm_s16le.
./configure \
--target-os=linux \
--arch=arm \
--enable-static \
--disable-shared \
--enable-cross-compile \
--disable-ffplay \
--disable-ffmpeg \
--disable-ffprobe \
--disable-ffserver \
--disable-avdevice \
--disable-devices \
--enable-avfilter \
--disable-encoders \
--disable-muxers \
--disable-symver \
--disable-debug \
--disable-stripping \
--enable-gpl \
--enable-version3 \
--enable-nonfree \
--disable-doc \
--disable-everything \
--disable-decoders \
--enable-decoder=pcm_s16be \
--enable-decoder=pcm_s16le \
--enable-decoder=pcm_s16le_planar \
--enable-decoder=pcm_u16be \
--enable-decoder=pcm_u16le \
--enable-decoder=wavpack \
--enable-decoder=mp2 \
--enable-decoder=mp3 \
--enable-decoder=aac \
--enable-decoder=aac_latm \
--enable-decoder=wmapro \
--enable-decoder=wmav1 \
--enable-decoder=wmav2 \
--enable-decoder=wmavoice \
--enable-decoder=vorbis \
--enable-decoder=libvorbis \
--disable-protocols \
--enable-protocol=file \
--disable-parsers \
--enable-parser=aac \
--enable-parser=aac_latm \
--enable-parser=mpegaudio \
--enable-parser=vorbis \
--enable-parser=ac3 \
--disable-demuxers \
--enable-demuxer=aac \
--enable-demuxer=mp3 \
--enable-demuxer=pcm_s16be \
--enable-demuxer=pcm_s16le \
--enable-demuxer=pcm_u16be \
--enable-demuxer=pcm_u16le \
--enable-demuxer=wav \
--enable-demuxer=flv \
--enable-demuxer=flac \
--enable-demuxer=ogg \
--enable-demuxer=flv \
--enable-demuxer=asf \
--disable-bsfs \
--disable-network \
--disable-yasm \
--disable-asm \
--prefix=$WORKING_DIR/ffmpeg \
--cc=$PREBUILT/prebuilt/linux-x86/bin/arm-linux-androideabi-gcc \
--cross-prefix=$PREBUILT/prebuilt/linux-x86/bin/arm-linux-androideabi- \
--nm=$PREBUILT/prebuilt/linux-x86/bin/arm-linux-androideabi-nm \
--extra-cflags="-fPIC -DANDROID -I$PLATFORM/usr/include" \
--extra-ldflags="-L$PLATFORM/usr/lib -nostdlib"

make 
make install

#copy libs and head file to jni folder
echo 'copy libs and head file to jni folder'
sudo rm -fr ../*.a
sudo cp -rf ./ffmpeg/lib/* ../
sudo cp -rf ./ffmpeg/include/* ../

cd ..
echo '================ ndk-build clean ================'
~/android-ndk/android-ndk-r8e/ndk-build clean

echo '================ ndk-build ================'
~/android-ndk/android-ndk-r8e/ndk-build

echo '================ list  ================'
ls -lh ../libs/armeabi/

