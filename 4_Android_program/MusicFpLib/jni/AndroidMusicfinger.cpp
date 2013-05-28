#include <android/log.h>
#include <string.h>
#include <jni.h>
#include "./cc_omusic_musicprint_Fingergen.h"
//#include "codegen/src/Codegen.h"
#include "./musicfingercode/Codegen.h"

//JNIEXPORT jstring JNICALL Java_edu_gvsu_masl_echoprint_Codegen_codegen
JNIEXPORT jstring JNICALL Java_cc_omusic_musicprint_Fingergen_codegen
  (JNIEnv *env, jobject thiz, jfloatArray pcmData, jint numSamples)
  {
	  // get the contents of the java array as native floats
	  float *data = (float *)env->GetFloatArrayElements(pcmData, 0);

		// invoke the codegen
		Codegen c = Codegen(data, (unsigned int)numSamples, 0);
		const char *code = c.getCodeString().c_str();
		
		// release the native array as we're done with them
		env->ReleaseFloatArrayElements(pcmData, data, 0); 
		// return the fingerprint string
		return env->NewStringUTF(code);
  }
