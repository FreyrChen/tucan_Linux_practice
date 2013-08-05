#!/bin/sh

tar -zxvf ffmpeg-0.11.1.tar.gz
mv ffmpeg-0.11.1 ffmpeg
for i in `find diffs -type f`; do
	(cd ffmpeg && patch -p1 < ../$i)
done
