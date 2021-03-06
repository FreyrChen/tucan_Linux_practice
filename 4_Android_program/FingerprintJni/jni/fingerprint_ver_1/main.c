#include <stdio.h>
#include <stdlib.h>

#include "main.h"

#include "fooid.h"
#include "sndfile.h"

int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        printf("Usage: ./test filename.wav\n");
        return 0;
    }

    SF_INFO * sfinfo = malloc(sizeof(*sfinfo));
	//use sndfile.c read wav file 
    SNDFILE * file = sf_open(argv[1], SFM_READ, sfinfo);

	//print wav file's channel & sample rate
    print_file_info(sfinfo);

	//initial t_fooid struct, reasample wav file to 8000hz.
    t_fooid * fooid = fp_init(sfinfo->samplerate, sfinfo->channels);

    short * data = malloc(sizeof(short) * sfinfo->channels * sfinfo->samplerate);

    int centiseconds = 0;

    while (1)
    {
		//return the number of  items read, every loop read 1s data from wav file
        sf_count_t items_read = sf_read_short(file, data, sfinfo->channels * sfinfo->samplerate);

        if (items_read == 0)
        {
            break;
        }

		//1/100 seconds
        centiseconds += 100 * sfinfo->channels * sfinfo->samplerate / items_read;
		printf("centiseconds=%d, items_read=%d \n", centiseconds, items_read ); 
		
        int result = fp_feed_short(fooid, data, items_read);

        if (result < 0)
        {
            printf("Error!\n");
            break;
        }
    }
	//fp_size == 424
    unsigned char * buffer =  malloc(fp_getsize(fooid));

    int result = fp_calculate(fooid, centiseconds, buffer);

    if (result < 0)
    {
        printf("Failed to calculate fingerprint\n");
    }
    else
    {
        int i;
        for (i = 0; i < fp_getsize(fooid); i++)
        {
            if (!(i % 32))
            {
                printf("\n");
            }

            printf("%02x ", (int) buffer[i]);
        }

        printf("\n");
    }

	//printf("[main]fp: length=%d, avg_fit=%d, avg_dom=%d \n", 
	//		&(fooid->fp.length), fooid->fp.avg_fit, fooid->fp.avg_dom );
	
    free(buffer);
    fp_free(fooid);
    free(data);
    free(sfinfo);

    return 0;
}
