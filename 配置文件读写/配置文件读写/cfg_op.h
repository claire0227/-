#ifndef __CFG_OP_H__
#define __CFG_OP_H__

#ifdef  __cplusplus
extern "C" 
#endif
//��ȡ������
int GetCfgItem(char *pFileName/*in*/,char *pKey/*in*/,char *pValue/*in out*/);
//д������
int WriteCfgItem(char *pFileName/*in*/,char *pItemName/*in*/,char *pItemValue/*in out*/);

#ifdef  __cplusplus

#endif

#endif

