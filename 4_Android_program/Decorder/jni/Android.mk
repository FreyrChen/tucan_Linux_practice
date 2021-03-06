LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
 
#LOCAL_MODULE    := gdx-audio
LOCAL_MODULE    := music-decoder
LOCAL_C_INCLUDES := vorbis 
 
LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%) -O2 -Wall -D__ANDROID__ -DFIXED_POINT -D_ARM_ASSEM_ -D__ANDROID__ -DMPG123_NO_CONFIGURE -DOPT_GENERIC -DHAVE_STRERROR -DMPG123_NO_LARGENAME -DASMALIGN_BYTE
LOCAL_CPPFLAGS := $(LOCAL_C_INCLUDES:%=-I%) -O2 -Wall -D__ANDROID__ -DFIXED_POINT -D_ARM_ASSEM_ -D__ANDROID__ -DMPG123_NO_CONFIGURE -DOPT_GENERIC -DHAVE_STRERROR -DMPG123_NO_LARGENAME -DASMALIGN_BYTE
LOCAL_LDLIBS := -lm
LOCAL_ARM_MODE  := arm
 
LOCAL_SRC_FILES := cc_omusic_decorder_AudioTools.cpp\
	cc_omusic_decorder_Mpg123Decoder.cpp\
	cc_omusic_decorder_VorbisDecoder.cpp\
	libmpg123/compat.c\
	libmpg123/dct64.c\
	libmpg123/equalizer.c\
	libmpg123/format.c\
	libmpg123/frame.c\
	libmpg123/icy.c\
	libmpg123/icy2utf8.c\
	libmpg123/id3.c\
	libmpg123/index.c\
	libmpg123/layer1.c\
	libmpg123/layer2.c\
	libmpg123/layer3.c\
	libmpg123/libmpg123.c\
	libmpg123/ntom.c\
	libmpg123/optimize.c\
	libmpg123/parse.c\
	libmpg123/readers.c\
	libmpg123/stringbuf.c\
	libmpg123/synth.c\
	libmpg123/synth_8bit.c\
	libmpg123/synth_arm.S\
	libmpg123/synth_real.c\
	libmpg123/synth_s32.c\
	libmpg123/tabinit.c\
	vorbis/bitwise.c\
	vorbis/block.c\
	vorbis/codebook.c\
	vorbis/floor0.c\
	vorbis/floor1.c\
	vorbis/framing.c\
	vorbis/info.c\
	vorbis/mapping0.c\
	vorbis/mdct.c\
	vorbis/registry.c\
	vorbis/res012.c\
	vorbis/sharedbook.c\
	vorbis/synthesis.c\
	vorbis/vorbisfile.c\
	vorbis/window.c
	
include $(BUILD_SHARED_LIBRARY)
