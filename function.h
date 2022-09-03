#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdint.h>
#include <stdbool.h>

#include "list.h"

#define BUFFER_MAX	50

typedef struct Message
{
	int id;				//信息的id值
	char* addr;			//存放网站的地址
	char* account;		//帐号
	char* password;		//密码
	char* email;		//绑定邮箱
	char* note;			//注释
	uint64_t tel;		//绑定电话号
	bool is_lock;		//是否可见
	bool is_email;		//是否绑定邮箱
	bool is_tel;		//是否绑定电话号
	bool is_account;	//是否有帐号登录操作
}Message;

extern List* list;			//链表结构
extern int g_max_id;		//最大id值
extern char buffer[BUFFER_MAX];//输入字符串缓冲区
void sys_run(void);			//代码主体

#endif
