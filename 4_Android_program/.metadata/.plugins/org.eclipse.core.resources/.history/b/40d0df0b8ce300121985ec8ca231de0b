# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := AndroidFingerprint
#LOCAL_SRC_FILES := AndroidFingerprint.c
LOCAL_SRC_FILES := AndroidFingerprint.c\
				fingerprint_ver_1/fingerprint.c \
				fingerprint_ver_1/fooid.c \
				fingerprint_ver_1/harmonics.c \
				fingerprint_ver_1/regress.c \
				fingerprint_ver_1/s_fft.c \
				fingerprint_ver_1/spectrum.c \
				fingerprint_ver_1/common.c \
				fingerprint_ver_1/libresample/resample.c \
				fingerprint_ver_1/libresample/resamplesubs.c\
				fingerprint_ver_1/libresample/filterkit.c
LOCAL_LDLIBS    := -L$(SYSROOT)/usr/lib -llog	
LOCAL_CFLAGS 	:= -std=c99 
include $(BUILD_SHARED_LIBRARY)
