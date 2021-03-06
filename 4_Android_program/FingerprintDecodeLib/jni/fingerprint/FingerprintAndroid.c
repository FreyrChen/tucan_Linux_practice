#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jni.h>
//#include <dlfcn.h>

#include "../ffmpeg/libavcodec/avcodec.h"
#include "../ffmpeg/libavformat/avformat.h"
#include "../ffmpeg/libavutil/avutil.h"
#include "../ffmpeg/libswscale/swscale.h"
//#include <libswscale/swscale.h>

//#include "cc_omusic_Fingerprint_decoder_jni_FingerprintWraper.h"

#include <android/log.h>
#define  LOG_TAG    "FingprintAndroid.c"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

//jbyteArray Java_cc_omusic_fingerprintjni_FingerprintWraper_fingerprint
//JNIEXPORT jbyteArray JNICALL Java_cc_omusic_fingerprintjni_FingerprintWraper_fingerprint
//(JNIEnv *env, jobject thiz, jobject DecoderObj, jint sampleRate, jint numChannels)


/*
 * Class:     cc_omusic_Fingerprint_decoder_jni_FingerprintWraper
 * Method:    getVersionOfDecoder
 * Signature: (V)Ljava/lang/String;
 */


jstring Java_cc_omusic_FingerprintDecoderLib_FingerprintWraper_getVersionOfDecoder
(JNIEnv *env, jobject thiz)
{

	//printf(" this ffmpeg version: %d \n", avcodec_version() );
	LOGD("go into jni function\n");
	char str[30];
	/*
	void *filehandle = dlopen("/data/data/cc.omusic.FingerprintDecodeApp/lib/libaccodec.so",RTLD_LAZY);
	if( filehandle)
	{
		LOGD("file open success!");
	}
	else
	{
		LOGD("failed to open file!");
	}
	*/
	unsigned int version = avcodec_version();
	LOGD("verison: %d", version );

	//av_register_all();
	//sprintf(str, "%d", avcodec_version());
	//sprintf(str, "%s", "string use sprint");
	//return (*env)->NewStringUTF(env,str);
	return (*env)->NewStringUTF(env,"hello from fingerprint jni");
}
