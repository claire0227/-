#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cfg_op.h"

# define MaxLine 2048

int GetCfgItem(char *pFileName/*in*/,char *pKey/*in*/,char *pValue/*in out*/)
{
	int ret = 0;
	FILE *fp = NULL;
	char *pTemp = NULL;

	char *pBegin = NULL;
	char *pEnd = NULL;

	char lineBuf[MaxLine];
	
	fp = fopen(pFileName,"r");
	if(fp == NULL)
	{
		ret = -1;
		return ret;
	}
	while(!feof(fp))
	{
		//fgets(_Out_z_cap_(_MaxCount) char * _Buf, _In_ int _MaxCount, _Inout_ FILE * _File)
		fgets(lineBuf,MaxLine,fp);
		//printf("lineBuf%s",lineBuf);
		pTemp = strchr(lineBuf,'=');
		if(pTemp == NULL)
		{
			continue;
		}
		pTemp = strstr(lineBuf,pKey);
		if(pTemp == NULL)
		{
			continue;
		}
		pTemp = pTemp + strlen(pKey);
		pTemp  = strchr(pTemp,'=');
		if(pTemp == NULL)
		{
			continue;
		}
		pTemp = pTemp+1;
		printf("%s",pTemp);
		//ȥ���ַ���ǰ��ո�ĺ���
		while(1)
		{
			if(*pTemp==' ')
				pTemp++;
			else
			{
				pBegin = pTemp;
				if(*pBegin =='\n')
				{
					printf("������:%sû������\n",pKey);
					goto End;
				}
				break;
			}	
		}
		//��ȡ������
		while(1)
		{
           if((*pTemp==' '||*pTemp=='\n')) 
		   {
			   break;
		   }
		   else
			   pTemp++;
		}
		pEnd = pTemp;
        memcpy(pValue,pBegin,pEnd-pBegin);
	}
End:
	if(fp== NULL)
		fclose(fp);
	return ret;
}



//д�����ļ�
//ʵ������
//ѭ����ÿһ�У����key�������Ƿ���ڣ������޸���Ӧ��valueֵ
//�������ڣ������ļ�ĩβ��ӡ�key = value��
//�ѵ㣬����޸��ļ����е�ֵ,�Ȱ��ļ������ݻ����������޸�֮���ٴη����ļ���
int WriteCfgItem(char *pFileName/*in*/,char *pItemName/*in*/,char *pItemValue/*in out*/)
{

	int itag = 0;//���ֵ������Ƿ�Ϊ���޸ĵ����ݿ�
	int ret = 0;
	int length = 0;//�����ļ��ĳ���
	FILE	* fp = NULL;
	char lineBuf[MaxLine];
	char *pTemp = NULL,*pBegin = NULL,*pEnd=NULL;
	char filebuf[1024*8] = {0};//�ļ�������


	if(pFileName==NULL ||pItemName==NULL ||pItemValue==NULL)
	{
		ret=-1;
		printf("WriteCfgItem error\n");
		goto End;
	}
	fp = fopen(pFileName,"r+");
	if(fp == NULL)
	{
		ret = -2;
		printf("fopen() err.\n");
	}
	if(fp == NULL)//����ݴ��������ļ������ڵ�ʱ���½��ļ�
	{
		fp = fopen(pFileName,"w+t");
		if(fp == NULL)
		{
			ret = -3;
			printf("fopen() err.\n");
			goto End;
		}
	}

	fseek(fp,0L,SEEK_END);//���ļ�ָ���0λ�ÿ�ʼ���ƶ����ļ�ĩβ
	length = ftell(fp);//��ȡ�ļ��ĳ���
	fseek(fp,0L,SEEK_SET);//�����ƶ�����ͷλ��

	if(length > 1024*8)
	{
		ret = -3;
		printf("�ļ����ȳ��꣬��֧��\n");
		goto End;
	}

	//��ȡ����
	while(!feof(fp))//�����ļ�β
	{
		memset(lineBuf,0,sizeof(lineBuf));
		pTemp = fgets(lineBuf,MaxLine,fp);
		if(pTemp == NULL)
			break;
		//key�ؼ����Ƿ��ڱ���
		pTemp = strstr(lineBuf,pItemName);
		if(pTemp == NULL)
		{
			strcat(filebuf,lineBuf);
			continue;
		}
		else
		{
			sprintf(lineBuf,"%s=%s\n",pItemName,pItemValue);
			strcat(filebuf,lineBuf);
			itag =1;
		}

	}
	//��������׷��
	if(itag == 0)
	{
		fprintf(fp,"%s=%s\n",pItemName,pItemValue);
	}
	else//��key�ؼ��ִ��ڣ���Ҫ���½����ļ�
	{

		if(fp != NULL)
		{
			fclose(fp);
		}
		fp = fopen(pFileName,"w+t");
		if(fp == NULL)
		{
			ret = -4;
			printf("fopen() err.\n");
			goto End;
		}
		fputs(filebuf,fp);//����������д���ļ�

	}
End:
	if(fp != NULL)
	{
		fclose(fp);
	}
	return ret;
}
