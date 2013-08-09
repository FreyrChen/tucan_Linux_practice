
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#include <jni.h>
#include <android/log.h>
#define  LOG_TAG    "AndroidFingerprint"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


jstring Java_cc_omusic_fingerprintdecoderapp_MainActivity_hello
(JNIEnv *env, jobject thiz)
{

	//printf(" this ffmpeg version: %d \n", avcodec_version() );
	LOGD("go into jni function\n");
	//char str[30];

	//sprintf(str, "%s", "string use sprint");
	//return (*env)->NewStringUTF(env,str);
	return (*env)->NewStringUTF(env,"hello from fingerprint jni");
}
