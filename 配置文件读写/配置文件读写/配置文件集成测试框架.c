#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cfg_op.h"

#define CFGNAME "c:/mycfg.ini"

void mymenu()
{
	printf("========================================\n");
	printf("1 ����д�����ļ�\n");
	printf("2 ���Զ������ļ�\n");
	printf("0 �˳�\n");
	printf("========================================\n");

}
//int GetCfgItem(char *pFileName/*in*/,char *pKey/*in*/,char *pValue/*in out*/,int *pValueLen/*out*/);
//int WriteCfgItem(char *pFileName/*in*/,char *pItemName/*in*/,char *pItemValue/*in out*/,int *ItemValueLen/*out*/);
//д���԰���
//��ȡ�����ļ�
int TGetCfg()
{
	int		ret = 0;
	char		Name[1024] = {0};
	char		value[1024] = {0};

	printf("\n�����key:");
	scanf("%s",Name);
	

	ret = GetCfgItem(CFGNAME,Name,value);
	if(ret !=0)
	{
	printf("func WriteCfgItem err: %d",ret);
	}
	printf("��������ǣ�%s = %s\n",Name,value);
	return ret;

}
//д�����ļ�
int TWriteCfg()
{
	int ret = 0;
	char Name[1024] = {0};
	char value[1024] = {0};

	printf("\n�����key:");
	scanf("%s",Name);
	
	printf("\n�����value:");
	scanf("%s",value);

	ret = WriteCfgItem(CFGNAME,Name,value);
	if(ret !=0)
	{
		printf("func WriteCfgItem err: %d",ret);
	}
	return ret;

}
void main()
{
	int choice;
	for(;;)
	{
		//��ʾһ���˵�

		mymenu();
		scanf("%d",&choice);
		switch(choice)
		{
		case 1://д������
			TWriteCfg();
			break;
		case 2://��������
			TGetCfg();
			break;
		case 0:
			exit(0);
		default:
			exit(0);

		}
	}
	printf("hello...\n");
	system("pause");
	return;
}