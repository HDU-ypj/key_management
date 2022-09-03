#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "function.h"
#include "tools.h"

//定义全局的用于获取字符串输入的缓冲区
char buffer[BUFFER_MAX];

List* list;				//链表结构
bool vip = false;		//定义超级管理员
int g_max_id = 999;		//最大的id值，自动生成id号

/**************************************************
 @func:获取网站地址值
 @mes:传入结构体指针
**************************************************/
void get_addr(Message* mes)
{
	if(mes == NULL)	return;
	printf("please input addr:");
	fgets_t(buffer,BUFFER_MAX);
	if(mes->addr == NULL)
	{
		mes->addr = (char* )malloc(sizeof(char)*(strlen(buffer)+1));
	}
	strcpy(mes->addr,buffer);
}


/**************************************************
 @func:获取登录账户
**************************************************/
void get_account(Message* mes)
{
	if(mes == NULL)	return;
	printf("是否存在帐号登录操作y/n:");
	char ch;
	BUFF_CLEAR;
	ch = getchar();
	if(ch == 'y' || ch == 'Y')
	{
		printf("please input account:");
		fgets_t(buffer,BUFFER_MAX);
		if(mes->account == NULL)
		{
			mes->account = (char* )malloc(sizeof(char)*(strlen(buffer)+1));
		}
		strcpy(mes->account,buffer);
		mes->is_account = true;
	}
	else
	{
		mes->is_account = false;
		mes->account = NULL;
	}
}

/**************************************************
 @func:获取登录账户密码
 @mes:传入结构体指针
**************************************************/
void get_password(Message* mes)
{
	if(mes == NULL)	return;
	if(mes->is_account == false)	return;	
	printf("please input passward:");
	fgets_t(buffer,BUFFER_MAX);
	if(mes->password == NULL)
	{
		mes->password = (char* )malloc(sizeof(char)*(strlen(buffer)+1));
	}
	strcpy(mes->password,buffer);
}

/**************************************************
 @func:获取登录账户绑定邮箱
**************************************************/
void get_email(Message* mes)
{
	if(mes == NULL)	return;
	if(mes->is_account == false)	return;
	char ch;
	printf("是否绑定了邮箱y/n:");
	BUFF_CLEAR;
	ch = getchar();
	if(ch == 'y'||ch == 'Y')
	{
		printf("please input email:");
		fgets_t(buffer,BUFFER_MAX);
		if(mes->email == NULL)
		{
			mes->email = (char* )malloc(sizeof(char)*(strlen(buffer)+1));
		}
		strcpy(mes->email,buffer);
		mes->is_email = true;
	}
	else
	{
		mes->is_email = false;
		mes->email = NULL;
	}
}
/**************************************************
 @func:获取登录账户绑定手机号
**************************************************/
void get_tel(Message* mes)
{
	if(mes == NULL)	return;
	if(mes->is_account == false)	return;
	char ch;
	printf("是否绑定了手机号y/n:");
	BUFF_CLEAR;
	ch = getchar();
	if(ch == 'y' || ch == 'Y')
	{
		printf("please input tel:");
		//获取输入的tel值
		uint64_t tel;
		while(scanf("%llu",&tel) != 1)
		{
			BUFF_CLEAR;
		}
		//将缓存读入地址
		mes->tel = tel;
		//设置标志位
		mes->is_tel = true;
	}
	else
	{
		mes->is_tel = false;
		mes->tel = 0;
	}
}

/**************************************************
 @func:添加备注
**************************************************/
void get_note(Message* mes)
{
	if(mes == NULL)	return;
	printf("please input note:");
	fgets_t(buffer,BUFFER_MAX);
	if(mes->note == NULL)
	{
		mes->note = (char* )malloc(sizeof(char)*(strlen(buffer)+1));
	}
	else
	{
		mes->note = realloc(mes->note,sizeof(char)*(strlen(buffer)+1));
	}
	strcpy(mes->note,buffer);
}


/**************************************************
 @func:设置是否可见
**************************************************/
void get_islock(Message* mes)
{
	if(mes == NULL)	return;
	printf("please input is_lock y/n:");
	char ch;
	BUFF_CLEAR;
	ch = getchar();
	if(ch == 'y' || ch == 'Y')
	{
		mes->is_lock = true;
	}
	else
	{
		mes->is_lock = false;
	}
}

/**************************************************
 @func:初始化
**************************************************/
void sys_init(void)
{
	list = create_list();	//创建链表
	load_data();			//加载文件
}

/**************************************************
 @func:创建一个信息
**************************************************/
Message* create_mes(void)
{
	Message* mes = (Message* )malloc(sizeof(Message));
	if(mes == NULL)	exit(0);
	
	mes->id = ++g_max_id;
	mes->addr = NULL;
	mes->password = NULL;
	mes->email = NULL;
	mes->account = NULL;
	mes->tel = 0;
	mes->note = NULL;

	mes->is_tel = false;
	mes->is_email = false;
	mes->is_account = false;

	get_addr(mes);		//获取网址
	get_account(mes);	//获取帐号
	get_password(mes);	//获取密码
	get_email(mes);		//获取绑定邮箱
	get_tel(mes);		//获取绑定手机号
	get_note(mes);		//获取备注
	get_islock(mes);	//是否可见

	return mes;
}

/**************************************************
 @func:获取输入一个id
**************************************************/
static int get_input_id(void)
{
	printf("请输入需要修改的id：");
	int id;
	while(scanf("%d",&id) != 1)
	{
		BUFF_CLEAR;	
	}
	return id;
}

/**************************************************
 @func:插入一个信息到链表
**************************************************/
void insert_mes(void)
{
	void* node = create_mes();
	add_head_list(list,node);
}

/**************************************************
 @func:删除一个信息
**************************************************/
void del_mes(void)
{
	int id;
	printf("请输入需要删除的网站ID号:");
	while(scanf("%d",&id) !=1)
	{
		BUFF_CLEAR;
	}
	Message mes={.id = id};
	Message* res = del_value_list(list,&mes,compare_id);
	if(res == NULL)	printf("不存在该ID号\n");
	else free(res);
}

/**************************************************
 @func:改变网址
**************************************************/
void modify_mes_addr(void)
{
	int id = get_input_id();
	Message* res = find_id(id);
	if(res == NULL)	printf("没有该ID\n");
	get_addr(res);
}

/**************************************************
 @func:改变帐号
**************************************************/
void modify_mes_account(void)
{
	int id = get_input_id();
	Message* res = find_id(id);
	if(res == NULL)	printf("没有该ID\n");
	get_account(res);
}

/**************************************************
 @func:改变密码
**************************************************/
void modify_mes_password(void)
{
	int id = get_input_id();
	Message* res = find_id(id);
	if(res == NULL)	printf("没有该ID\n");
	get_password(res);
}

/**************************************************
 @func:改变绑定电话
**************************************************/
void modify_mes_tel(void)
{
	int id = get_input_id();
	Message* res = find_id(id);
	if(res == NULL)	printf("没有该ID\n");
	get_tel(res);
}

/**************************************************
 @func:改变绑定email
**************************************************/
void modify_mes_email(void)
{
	int id = get_input_id();
	Message* res = find_id(id);
	if(res == NULL)	printf("没有该ID\n");
	get_email(res);
}

/**************************************************
 @func:修改备注
**************************************************/
void modify_mes_notice(void)
{
	int id = get_input_id();
	Message* res = find_id(id);
	if(res == NULL)	printf("没有该ID\n");
	get_note(res);
}

/**************************************************
 @func:改变可见状态
**************************************************/
void modify_mes_islock(void)
{
	int id = get_input_id();
	Message* res = find_id(id);
	if(res == NULL)	printf("没有该ID\n");
	get_islock(res);
}

/**************************************************
 @func:设置超级管理员权限
**************************************************/
void set_vip(void)
{
	printf("修改后权限 1：vip 0:游客:");
	int a;
	while(scanf("%d",&a) != 1)
	{
		BUFF_CLEAR;
	}
	vip = (a==0?false:true);
}

/**************************************************
 @func:显示所有的帐号信息
**************************************************/
void show_person_mes(void* message)
{
	Message* mes = (Message* )message;
	if(mes == NULL)	return;
	if(true == mes->is_lock && false == vip)	return;
	
	printf("--------------------------------------------------------\n");
	printf("ID: %d\n",mes->id);
	printf("addr: %s\n",mes->addr);
	if(mes->is_account)	printf("account: %s\n",mes->account);
	if(mes->is_account)	printf("password: %s\n",mes->password);
	if(mes->is_email)	printf("email: %s\n",mes->email);
	if(mes->is_tel)		printf("tel: %llu\n",mes->tel);
	printf("note: %s\n",mes->note);
}

/**************************************************
 @func:遍历打印所有的信息
**************************************************/
void show_all_mes(void)
{
	show_list(list,show_person_mes);
}

static FILE* fwp; 

void _export(void* message)
{
	Message* mes = (Message* )message;
	if(mes == NULL)	return;
	fprintf(fwp,"网址：%s ",mes->addr);
	if(mes->is_account)	fprintf(fwp,"帐号: %s ",mes->account);
	if(mes->is_account)	fprintf(fwp,"密码: %s ",mes->password);
	if(mes->is_email)	fprintf(fwp,"绑定邮箱: %s ",mes->email);
	if(mes->is_tel)		fprintf(fwp,"绑定电话: %llu ",mes->tel);
	fprintf(fwp,"备注: %s\n",mes->note);
}
/**************************************************
 @func:导出所有可见网站到文件
**************************************************/
void export(void)
{
	fwp = fopen("export.txt","w");
	show_list(list,_export);
	fclose(fwp);
}
/**************************************************
 @func:显示主界面
**************************************************/
void show_interface(void)
{
	printf("welcome to use ypj account management system\n");
	printf("	0、退出系统\n");
	printf("	1、插入一个信息\n");
	printf("	2、删除一个信息\n");
	printf("	3、修改网址\n");
	printf("	4、修改帐号\n");
	printf("	5、修改密码\n");
	printf("	6、修改绑定手机号\n");
	printf("	7、修改绑定邮箱\n");
	printf("	8、修改超级管理员权限\n");
	printf("	9、修改网站可见性\n");
	printf("	10、显示所有的信息\n");
	printf("	11、修改备注\n");
	printf("	12、导出所有可见的网址\n");
	printf("	13、搜索(功能开发中)\n");
	printf("请输入你的选择：");
}


/**************************************************
 @func:死循环运行程序
**************************************************/
void sys_run(void)
{
	int ch;
	system("clear");
	sys_init();
	while(1)
	{
		show_interface();
		while(scanf("%d",&ch) != 1)
		{
			BUFF_CLEAR;
		}
		if(ch == 0)	break;
		switch(ch)
		{
			case 1:insert_mes();break;
			case 2:del_mes();break;
			case 3:modify_mes_addr();break;
			case 4:modify_mes_account();break;
			case 5:modify_mes_password();break;
			case 6:modify_mes_tel();break;
			case 7:modify_mes_email();break;
			case 8:set_vip();break;
			case 9:modify_mes_islock();break;
			case 10:show_all_mes();break;
			case 11:modify_mes_notice();break;
			case 12:export();break;
			
			default:break;
		}
		printf("按任意键继续……");
		press_anykey_return();
		system("clear");
	}
	//写入文件
	write_data();
	//释放内存
	release();
}

