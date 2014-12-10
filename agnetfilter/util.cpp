#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

void WriteAGLog(LPCSTR cstr)
{
	return;	// chrome下，会出现183错误：创建已存在的文件。故此函数直接返回。
	char szFileFullPath[MAX_PATH*sizeof(char)];
	::GetModuleFileNameA(NULL, szFileFullPath, MAX_PATH*sizeof(char));

	string s = szFileFullPath;
	int len = strlen(szFileFullPath);
	char *cfilename = strrchr(szFileFullPath, '\\');
	//char szFileName[128]='\0';
	//strcpy(szFileName, szFileFullPath+begin);
	char log[128];
	memset(log, 0, 128*sizeof(char));
	strcpy(log, cfilename+1);
	int loglen = strlen(log);
	memset(log+loglen-3, 'l', sizeof(char));
	memset(log+loglen-2, 'o', sizeof(char));
	memset(log+loglen-1, 'g', sizeof(char));

	char prefix[MAX_PATH]; memset(prefix, 0, MAX_PATH);
	strcpy(prefix, "e:\\temp\\logs\\");
	char *logpath = strcat(prefix, log);

	//
	struct tm *local;
	time_t t;
	t=time(NULL);
	local = localtime(&t);

	//
	FILE *fp = fopen(logpath, "a+");
	if (fp)
	{
		fprintf(fp, "%2d:%2d:%2d\t%s\n", local->tm_hour, local->tm_min, local->tm_sec, cstr);
		fclose(fp);
		fp = NULL;
	}

}