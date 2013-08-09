#include <stdio.h>
#include <stdlib.h>

#include "./libavcodec/avcodec.h"
#include "./libavformat/avformat.h"
#include "./libavutil/avutil.h"
#include "./libswscale/swscale.h"


int main(char arg,char *argv[])
{
	char *filename = argv[1];

	printf(" this ffmpeg version: %d \n", avcodec_version() );


	av_register_all();	//注册所有可解码类型
	printf(" av_register run success!\n" );
	
	AVFormatContext *pInFmtCtx=NULL;	//文件格式
	AVCodecContext *pInCodecCtx=NULL;	//编码格式 
	if (av_open_input_file(&pInFmtCtx, filename, NULL, 0, NULL)!=0)	//获取文件格式
		printf("av_open_input_file error\n");
	if (av_find_stream_info(pInFmtCtx) < 0)	//获取文件内音视频流的信息
		printf("av_find_stream_info error\n");

	unsigned int j;
	// Find the first audio stream
	int audioStream = -1;
	for (j=0; j<pInFmtCtx->nb_streams; j++)	//找到音频对应的stream
	{
		if (pInFmtCtx->streams[j]->codec->codec_type == CODEC_TYPE_AUDIO)
		{
			audioStream = j;
			break;
		}
	}
	if (audioStream == -1)
	{
		printf("input file has no audio stream\n");
		return 0; // Didn't find a audio stream
	}
	printf("audio stream num: %d\n",audioStream);
	pInCodecCtx = pInFmtCtx->streams[audioStream]->codec; //音频的编码上下文
	AVCodec *pInCodec = NULL;

	pInCodec = avcodec_find_decoder(pInCodecCtx->codec_id); //根据编码ID找到用于解码的结构体
	if (pInCodec == NULL)
	{
		printf("error no Codec found\n");
		return -1 ; // Codec not found
	}

	if(avcodec_open(pInCodecCtx, pInCodec)<0)//将两者结合以便在下面的解码函数中调用pInCodec中的对应解码函数
	{
		printf("error avcodec_open failed.\n");
		return -1; // Could not open codec

	}

	static AVPacket packet;

	printf(" bit_rate = %d \r\n", pInCodecCtx->bit_rate);
	printf(" sample_rate = %d \r\n", pInCodecCtx->sample_rate);
	printf(" channels = %d \r\n", pInCodecCtx->channels);
	printf(" code_name = %s \r\n", pInCodecCtx->codec->name);
	printf(" block_align = %d\n",pInCodecCtx->block_align);

	uint8_t *pktdata;
	int pktsize;
	int out_size = AVCODEC_MAX_AUDIO_FRAME_SIZE*100;
	uint8_t * inbuf = (uint8_t *)malloc(out_size);
	FILE* pcm;
	pcm = fopen("result.pcm","wb");
	long start = clock();
	while (av_read_frame(pInFmtCtx, &packet) >= 0)//pInFmtCtx中调用对应格式的packet获取函数
	{
		if(packet.stream_index==audioStream)//如果是音频
		{
			pktdata = packet.data;
			pktsize = packet.size;
			while(pktsize>0)
			{
				out_size = AVCODEC_MAX_AUDIO_FRAME_SIZE*100;
				//解码
				int len = avcodec_decode_audio2(pInCodecCtx, (short*)inbuf, &out_size, pktdata, pktsize);
				if (len < 0)
				{
					printf("Error while decoding.\n");
					break;
				}
				if(out_size > 0)
				{
					fwrite(inbuf,1,out_size,pcm);//pcm记录
					fflush(pcm);
				}
				pktsize -= len;
				pktdata += len;
			}
		} 
		av_free_packet(&packet);
	}
	long end = clock();
	printf("cost time :%f\n",(double) ((end-start)/(double)CLOCKS_PER_SEC) );
	free(inbuf);
	fclose(pcm);
	if (pInCodecCtx!=NULL)
	{
		avcodec_close(pInCodecCtx);
	}
	av_close_input_file(pInFmtCtx);


	return 0;

}
