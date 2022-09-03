#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdbool.h>

//定义了函数指针类型，新类型名叫Compare
//定义函数指针变量Compare cmp
//cmp即为函数指针变量
typedef int (*Compare)(const void*, const void*);

// 通用链表节点结构
typedef struct Node{
	void* ptr;
	struct Node* prev;
	struct Node* next;
}Node;

// 通用链表结构
typedef struct List{
	Node* head;
	size_t size;
}List;

//创建链表
List* create_list(void);

//头添加
void add_head_list(List* list,void* ptr);

//尾添加
void add_tail_list(List* list,void* ptr);

//插入
bool insert_list(List* list,size_t index,void* ptr);

//按位置删除
void* del_index_list(List* list,size_t index);

//按值删除
void* del_value_list(List* list,void* ptr,int (*compare)(const void*,const void*));

//查询
void* query_list(List* list,void* ptr,Compare cmp);

//访问
void* access_list(List* list,size_t index);

//排序
void sort_list(List* list,Compare cmp);

//清空
void clear_list(List* list);

//销毁
void destroy_list(List* list);

//遍历
void show_list(List* list,void (*show)(void*));

//数量
size_t size_list(List* list);


#endif
