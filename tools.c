#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"



/*******************************************************************************
*	输入str：数组首地址
*	输入len：数组长度
*	输出：数组首地址
*	功能：fgets进阶版，去除fgets读入的'\0'
********************************************************************************/
char *fgets_t(char*str,int len)
{
	stdin->_IO_read_ptr = stdin->_IO_read_end;//清空缓存区
	fgets(str,len,stdin);
	stdin->_IO_read_ptr = stdin->_IO_read_end;//清空缓存区

	for(int i=1;i<len;i++)
	{
		if(str[i]=='\n')
		{
			str[i] = '\0';
		}
	}
	return str;
}

/**************************************************
 @func:按任意键返回
**************************************************/
void press_anykey_return(void)
{
	BUFF_CLEAR;
	char ch = getchar();
}

/**************************************************
 @func:通过id比较大小，用于查找
**************************************************/
int compare_id(const void*s1,const void*s2)
{
	const Message* t1 = (Message*)s1;
	const Message* t2 = (Message*)s2;
	if(t1->id == t2->id)
	{
		return 0;	
	}
	else if(t1->id > t2->id)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

/**************************************************
 @func:查找id值对应的message，返回指针
**************************************************/
Message* find_id(int id)
{
	Message s = {.id = id};
	return query_list(list,&s,compare_id);
}

static FILE* fwp;	//写入文件句柄
static FILE* frp;	//读入文件句柄

/**************************************************
 @func:写入一个message数据
**************************************************/
void write_one_data(void* data)
{
	Message* mes = (Message*)data;
	int bool_buff[4]={mes->is_account,mes->is_tel,mes->is_email,mes->is_lock};
	fprintf(fwp,"%d ",mes->id);
	fprintf(fwp,"%s ",mes->addr);
	fprintf(fwp,"%s ",mes->note);
	fprintf(fwp,"%d %d %d %d ",bool_buff[0],bool_buff[1],bool_buff[2],bool_buff[3]);
	if(mes->is_account)
	{
		fprintf(fwp,"%s ",mes->account);
	}
	if(mes->is_account)
	{
		fprintf(fwp,"%s ",mes->password);
	}
	if(mes->is_email)
	{
		fprintf(fwp,"%s ",mes->email);
	}
	if(mes->is_tel)
	{
		fprintf(fwp,"%llu",mes->tel);
	}
	fprintf(fwp,"\n");
}


//读入文件
/**************************************************
 @func:读入文件信息
**************************************************/
void load_data(void)
{

	int cnt=0;
	int bool_buff[4];
	frp = fopen(FILE_PATH,"r");
	if(frp == NULL)
	{
		return;
	}
	fscanf(frp,"%d",&cnt);
	while(cnt--)
	{
		Message* mes = (Message* )malloc(sizeof(Message));
		fscanf(frp,"%d",&(mes->id));
		if(g_max_id < mes->id)
		{
			g_max_id = mes->id;
		}

		fscanf(frp,"%s",buffer);
		mes->addr = (char* )malloc(sizeof(char)*(strlen(buffer)+1));
		strcpy(mes->addr,buffer);
		
		
		fscanf(frp,"%s",buffer);
		mes->note = (char* )malloc(sizeof(char)*(strlen(buffer)+1));
		strcpy(mes->note,buffer);
		
		fscanf(frp,"%d%d%d%d",&bool_buff[0],&bool_buff[1],&bool_buff[2],&bool_buff[3]);
		mes->is_account = bool_buff[0];
		mes->is_tel = bool_buff[1];
		mes->is_email = bool_buff[2];
		mes->is_lock = bool_buff[3];
		
		if(mes->is_account)
		{
			fscanf(frp,"%s",buffer);
			mes->account = (char* )malloc(sizeof(char)*(strlen(buffer)+1));
			strcpy(mes->account,buffer);
			fgetc(frp);
		}
		if(mes->is_account)
		{
			fscanf(frp,"%s",buffer);
			mes->password = (char* )malloc(sizeof(char)*(strlen(buffer)+1));
			strcpy(mes->password,buffer);
			fgetc(frp);
		}
		if(mes->is_email)
		{
			fscanf(frp,"%s",buffer);
			mes->email = (char* )malloc(sizeof(char)*(strlen(buffer)+1));
			strcpy(mes->email,buffer);
			fgetc(frp);
		}
		if(mes->is_tel)
		{
			fscanf(frp,"%llu",&(mes->tel));
		}
		
		add_tail_list(list,mes);
	}
	fclose(frp);
}

//写入文件
/**************************************************
 @func:写入全部信息
**************************************************/
void write_data(void)
{
	fwp = fopen(FILE_PATH,"w");
	if(fwp == NULL)
	{
		return;
	}
	fprintf(fwp,"%d\n",size_list(list));
	show_list(list,write_one_data);
	fclose(fwp);
}

/**************************************************
 @func:释放内存依赖函数
**************************************************/
static void _release(void* message)
{
	Message* mes = (Message* )message;
	if(mes->addr)		free(mes->addr);
	if(mes->account)	free(mes->account);
	if(mes->password)	free(mes->password);
	if(mes->email)		free(mes->email);
	if(mes->note)		free(mes->note);
}

/**************************************************
 @func:释放内存
**************************************************/
void release(void)
{
	//遍历释放所有内存
	show_list(list,_release);
	//摧毁链表结构
	destroy_list(list);
}
