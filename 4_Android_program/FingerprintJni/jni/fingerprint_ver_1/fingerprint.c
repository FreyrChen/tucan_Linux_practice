#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "fooid.h"
//#include "sndfile.h"


#define SAMPLERRATE 44100
#define CHANNELS 	2 		//should consider nano, reduce time cost.
// in resample sub array 44100*2/2048 =43
// so SUB_SECONDS max is 20
#define SUB_SECONDS  1

//pcm array is input wav file's data 441000Hz
//num_samples is number of sample data pcm array
int fingerprint( short pcm[], unsigned int num_samples,
							unsigned char buffer[] )
{

	int samplerrate = SAMPLERRATE;
	int channels = CHANNELS;

	 

	//initial t_fooid struct, reasample wav file to 8000hz.
    t_fooid * fooid = fp_init( samplerrate, channels );
//    LOGD("fp_init() complete\n");



    int centiseconds = 0;
	int offset = 0;
	int len = (int)(channels * samplerrate / SUB_SECONDS); // every chip is 1s/SUB_SECONDS
	int result;
//    short * data = malloc(sizeof(short) * channels * samplerrate );
    short * data = malloc(sizeof(short) * len );

    while ( offset < num_samples )
    {
		//return the number of  items read, every loop read 1s data from wav file
		memcpy( data, pcm + offset, sizeof( short ) *len);
		offset += len;


		//1/100 seconds
		//int items_read = channels *  samplerrate;
        centiseconds += (int)((len * 100 )/(channels * samplerrate))  ;
		printf("num_samples=%d, SUB_SECONDS=%d, centiseconds:%d, items_read=%d \n",
				num_samples, SUB_SECONDS,centiseconds, len );
        //LOGD("ready to fp_short() ... \n");
		//printf("fingerprint: data size(len)=%d",len);
		result = fp_feed_short( fooid, data, len );
//		result = fp_feed_float( fooid, data, len );
		//LOGD("fp_feed_short() offset=%d, result=%d \n", offset, result);
        if (result < 0)
        {
            //printf("fp_feed_float() Error!\n");
            break;
        }
    }


	//fp_size == 424
    //unsigned char * buffer =  malloc(fp_getsize(fooid));
 //   LOGD("fp_calculate() centiseconds=%d\n", centiseconds);
    result = fp_calculate(fooid, centiseconds, buffer);
 //   LOGE("fp_calculate result= %d\n", result);
//    LOGD("fp_calculate() complete\n");
    fp_free(fooid);
    free(data);
 //   LOGD("free complete\n");

    /*
    if (result < 0)
       {
    		LOGE("Failed to calculate fingerprint\n");
       }
       else
       {
           int i;
           for (i = 0; i < 424; i++)
           {
               LOGE("%02x ", (int) buffer[i]);
           }

           LOGE("\n");
       }
	*/
    if (result <0 )
	{
		return 0;
	}
	else
    {
		return 1 ;
    }


	//return NULL;
}
