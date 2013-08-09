#!/bin/sh
echo '================ ndk-build clean ================'
~/android-ndk/android-ndk-r8e/ndk-build clean

echo '================ ndk-build ================'
~/android-ndk/android-ndk-r8e/ndk-build

echo '================ list  ================'
ls -lh ../libs/armeabi/
