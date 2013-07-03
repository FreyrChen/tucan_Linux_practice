#include <stdio.h>
#include <stdlib.h>

#include "main.h"

//#include "fooid.h"
#include "./libsndfile/sndfile.h"
#include "fingerprint.h"

#define SECONDS 100 
#define FPSIZE	424 

int main(int argc, char ** argv)
{
    int i;

    if (argc < 2)
    {
        printf("Usage: ./%s filename.wav\n", argv[0] );
        return 0;
    }

    SF_INFO * sfinfo = malloc(sizeof(*sfinfo));
	//use sndfile.c read wav file 
    SNDFILE * file = sf_open(argv[1], SFM_READ, sfinfo);
	//print wav file's channel & sample rate
    print_file_info(sfinfo);

	int num_samples = SECONDS * sfinfo->channels * sfinfo->samplerate;
	float *pcm = malloc( sizeof(float) * num_samples );
	/*
	short * data = malloc(sizeof(short) * num_samples );
    //return the number of  items read, every loop read 1s data from wav file
	sf_count_t items_read = sf_read_short(file, data, num_samples );
	//printf(" input file num of sample:%d, items_read:%d\n", num_samples, items_read );

	for( i=0; i< num_samples; i++ )
	{
		pcm[i] = data[i] / 32767.0f;  // in fp_feed_short(), transe short to float
	}
	*/
	sf_count_t items_read = sf_read_float(file, pcm, num_samples );
	unsigned char * buffer = fingerprint( pcm, num_samples );


	for (i = 0; i < FPSIZE; i++)
    {
            if (!(i % 32))
            {
                printf("\n");
            }

            printf("%02x ", (int) buffer[i]);
    }

	//print( "avg_fit: %d, avg_dom: %d i\n", fi->fp.avg_fit, fp.avg_dom);
	printf("\n");
    

    free(buffer);

    return 0;
}
