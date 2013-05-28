# Copyright (C) 2010 The Android Open Source Project
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

LOCAL_MODULE    :=musicprint-jni

LOCAL_SRC_FILES :=AndroidMusic.cpp \
				/musicfingercode/Codegen.cpp \
				/musicfingercode/Whitening.cpp \
				/musicfingercode/SubbandAnalysis.cpp \
				/musicfingercode/MatrixUtility.cpp \
				/musicfingercode/Fingerprint.cpp \
				/musicfingercode/Base64.cpp \
				/musicfingercode/AudioStreamInput.cpp \
				/musicfingercode/AudioBufferInput.cpp
					
LOCAL_LDLIBS    := -llog\
					-lz					
LOCAL_C_INCLUDES :=/home/tusion/code/4_Android_program/MusicFpLib/jni_musicprint/musicfingercode \
			/home/tusion/android_app_dev/boost_1_53_0				

#LOCAL_C_INCLUDES :=/Users/alex/Desktop/GVSU/MASLEchoPrint/jni/codegen/src \
#					/Users/alex/Desktop/GVSU/MASLEchoPrint/jni/boost_1_47_0				
include $(BUILD_SHARED_LIBRARY)
