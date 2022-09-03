#ifndef TOOLS_H
#define TOOLS_H

#include "function.h"
#include "list.h"

//清空缓存区
#define BUFF_CLEAR stdin->_IO_read_ptr = stdin->_IO_read_end

#define FILE_PATH	"./source.txt"

//重写gets函数，更安全
char *fgets_t(char*str,int len);

//通过id比较大小，用于通过id查找
int compare_id(const void*s1,const void*s2);

//返回对应id的message结构体指针，用于修改信息
Message* find_id(int id);

//读入文件信息
void load_data(void);

//写入信息
void write_data(void);

//按任意键退出
void press_anykey_return(void);

//释放内存
void release(void);

#endif
