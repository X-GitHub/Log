#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
//#include <windows.h>
#include "stm32f4xx.h"


#define _CRT_SECURE_NOWARNGINGS
#define MAX_FILE_LEN (u32)(1024 * 1024)


/* 获取当前系统的时间 */
static s8 *GetNowTime(void);

/* 设置路径 */
static void SetLogPath(s8 *InPath,s32 PathLen,s8 *OutFileName);

/* 获取文件的大小 */
static s32 GetFileSize(s8 *InFileName);

/* 写日志 */
void WriteLog(s8 *InFileName,s8 *InLogBuf,s32 InLogBufSize);







/* 获取当前系统的时间 */
static s8 *GetNowTime(void)
{
	struct tm *StrTime;
	time_t ttime;
	s8 *NowTimeBuf = (s8 *)malloc( 20u * sizeof(s8) );
	time(&ttime);
	StrTime = localtime(&ttime);
	sprintf((char*)NowTimeBuf,"%04d-%02d-%02d %02d:%02d:%02d",StrTime->tm_year + 1900,
		StrTime->tm_mon + 1,StrTime->tm_mday,StrTime->tm_hour,StrTime->tm_min,StrTime->tm_sec);
	printf("%s\n", NowTimeBuf);
	return NowTimeBuf;
}


/* 设置路径 */
static void SetLogPath(s8 *InPath,s32 PathLen,s8 *OutFileName)
{
	struct tm *StrTime;
	time_t ttime;
	time(&ttime);
	StrTime = localtime(&ttime);
	/* dengerous */
	//memcpy(OutFileName,InPath,PathLen);
	sprintf((char*)OutFileName, "%s%04d-%02d-%02d.txt",InPath, StrTime->tm_year + 1900,
		StrTime->tm_mon + 1,StrTime->tm_mday,StrTime->tm_hour,StrTime->tm_min,StrTime->tm_sec);
	printf("%s\n", OutFileName);
}


/* 获取文件的大小 */
static s32 GetFileSize1(s8 *InFileName)
{
	s32 Length = 0;

	if(InFileName != NULL)
	{
		FILE *Fp = NULL;

		Fp = fopen((char*)InFileName,"rb+");
		if(Fp != NULL)
		{
			fseek(Fp,0,SEEK_END);
			Length = ftell(Fp);
			fclose(Fp);
			Fp = NULL;
		}
	}

	return Length;
}


/* 写日志 */
void WriteLog(s8* FileName, s8* LogBuff, s32 LogBuffSize)
{
	if (NULL != FileName && NULL != LogBuff)
	{
		if (GetFileSize1(FileName) < 1024 * 1024)
		{
			FILE* fp = NULL;
			fp = fopen((char*)FileName, "a+");
			if (NULL != fp)
			{
				s8* TM = GetNowTime();
				fwrite(TM, 20, 1, fp);
				fwrite(LogBuff, LogBuffSize, 1, fp);
				if (NULL != TM)
				{
					free(TM);
					TM = NULL;
				}
			}
			fclose(fp);
			fp = NULL;
		}
		else
		{
			unlink((char*)FileName);
		}
	}

}





