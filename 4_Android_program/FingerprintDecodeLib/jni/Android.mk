#include $(call all-subdir-makefiles)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libavcodec
LOCAL_SRC_FILES := build/ffmpeg/$(TARGET_ARCH_ABI)/lib/$(LOCAL_MODULE).a
LOCAL_CFLAGS := -I$(LOCAL_MODULE)
LOCAL_EXPORT_C_CFLAGS :=-I$(LOCAL_MODULE)
LOCAL_EXPORT_C_LDLIBS :=-llog
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/build/ffmpeg/$(TARGET_ARCH_ABI)/include
include $(PREBUILT_STAITC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libavformat
LOCAL_SRC_FILES := build/ffmpeg/$(TARGET_ARCH_ABI)/lib/$(LOCAL_MODULE).a
LOCAL_CFLAGS := -I$(LOCAL_MODULE)
LOCAL_EXPORT_C_CFLAGS :=-I$(LOCAL_MODULE)
LOCAL_EXPORT_C_LDLIBS :=-llog
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/build/ffmpeg/$(TARGET_ARCH_ABI)/include
include $(PREBUILT_STAITC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libavutil
LOCAL_SRC_FILES := build/ffmpeg/$(TARGET_ARCH_ABI)/lib/$(LOCAL_MODULE).a
LOCAL_CFLAGS := -I$(LOCAL_MODULE)
LOCAL_EXPORT_C_CFLAGS :=-I$(LOCAL_MODULE)
LOCAL_EXPORT_C_LDLIBS :=-llog
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/build/ffmpeg/$(TARGET_ARCH_ABI)/include
include $(PREBUILT_STAITC_LIBRARY)

#clear all the variabre of make file register
include $(CLEAR_VARS)

#module name to be generate
LOCAL_MODULE := Fingerprint

LOCAL_CFLAGS := 
LOCAL_CFLAGES := -I$(LOCAL_PATH)/ffmpeg/build/ffmpeg/$(TARGET_ARCH_ABI)/lib 

#source files
LOCAL_SRC_FILES := $(LOCAL_PATH)/fingerprint/FingerprintAndroid.c

LOCAL_SHARED_LIBRARIES := libavcodec libavformat libavutil
#LOCAL_STATIC_LIBRARIES := libavcodec libavformat libavutil 
LOCAL_C_INCLUDES := $(LOCAL_PATH)/ffmpeg/build/ffmpeg/$(TARGET_ARCH_ABI)/include

LOCAL_LDLIBS := -L/home/tusion/android-ndk/android-ndk-r8e/platforms/android-14/arch-arm/usr/lib/ \
				-L$(LOCAL_PATH)/../ffmpeg/build/ffmpeg/$(TARGET_ARCH_ABI)/lib \
				-llog \
				-lz \
				-ldl \
				-lm \
				-lgcc 
LOCAL_STATIC_LIBRARIES := avcodec avformat avutil 
#LOCAL_LDLIBS += -llog -lm -lz -ldl -lgcc -lbz2
#include $(PREBUILD_SHARED_LIBRARY)
include $(BUILD_SHARED_LIBRARY)
