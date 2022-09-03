#include "list.h"
#include <stdlib.h>

//创建节点
static Node* create_node(void* ptr)
{
	Node* node = (Node* )malloc(sizeof(Node));
	node->next = node;
	node->prev = node;
	node->ptr = ptr;
	return node;
}

//在两个节点之间插入一个节点
static void _add_list(Node* prev,Node* next,void* ptr)
{
	Node* node = create_node(ptr);
	node->next = next;
	node->prev = prev;
	prev->next = node;
	next->prev = node;
}

//根据位置访问节点
static Node* _index_list(List* list,size_t index)
{
	if(index >= list->size)	return NULL;
	if(index < list->size/2)
	{
		Node* n = list->head->next;
		while(index--)	n = n->next;	
		return n;
	}
	else
	{
		Node* n = list->head->prev;
		while(++index <list->size)	n = n->prev;
		return n;
	}
}

//删除节点,将节点数据传回去
static void* _del_list(Node* node)
{
	node->next->prev = node->prev;
	node->prev->next = node->next;
	void* ptr = node->ptr;
	free(node);
	return ptr;
}
//创建链表,带头节点
List* create_list(void)
{
	List* list = (List* )malloc(sizeof(List));
	list->head = create_node(NULL);
	list->size = 0;
	return list;
}

//数量
size_t size_list(List* list)
{
	return list->size;
}

//头添加
void add_head_list(List* list,void* ptr)
{
	_add_list(list->head,list->head->next,ptr);
	list->size++;
}

//尾添加
void add_tail_list(List* list,void* ptr)
{
	_add_list(list->head->prev,list->head,ptr);
	list->size++;
}

//插入
bool insert_list(List* list,size_t index,void* ptr)
{
	Node* node = _index_list(list,index);
	if(node == NULL)	return false;

	_add_list(node->prev,node,ptr);
	list->size++;
	return true;
}

//按位置删除
void* del_index_list(List* list,size_t index)
{
	Node* node = _index_list(list,index);
	if(node == NULL)	return NULL;

	list->size--;
	return _del_list(node);
}

//按值删除
void* del_value_list(List* list,void* ptr,int (*compare)(const void*,const void*))
{
	for(Node* n=list->head->next; list->head!=n; n=n->next)
	{
		if(0 == compare(ptr,n->ptr))
		{
			list->size--;
			return _del_list(n);
		}
	}
	return NULL;
}


//查询
void* query_list(List* list,void* ptr,Compare cmp)
{
	for(Node* node=list->head->next; node!=list->head; node = node->next)	
	{
		if(0 == cmp(ptr,node->ptr))	return node->ptr;
	}
	return NULL;
}

//访问
void* access_list(List* list,size_t index)
{
	Node* node = _index_list(list,index);
	if(node == NULL)	return NULL;

	return node->ptr;
}

//排序
void sort_list(List* list,Compare cmp)
{
	for(Node* i=list->head->next; i->next!=list->head; i=i->next)
	{
		for(Node* j=i->next; j!=list->head; j=j->next)
		{
			if(cmp(i->ptr,j->ptr)>0)
			{
				void* temp = i->ptr;
				i->ptr = j->ptr;
				j->ptr = temp;
			}
		}
	}
}

//清空 使用此函数则数据必须存放在堆内存中
void clear_list(List* list)
{
	Node* node = list->head->next;
	while(node!=list->head)
	{
		Node* temp = node;
		node = node->next;
		free(temp->ptr);
		free(temp);
	}
	list->head->next = list->head;
	list->head->prev = list->head;
	list->size = 0;
}

//销毁	使用此函数则数据必须存放在堆内存中
void destroy_list(List* list)
{
	clear_list(list);
	free(list->head);
	free(list);
}

//遍历 show是回调函数，由调用者提供
void show_list(List* list,void (*show)(void*))
{
	for(Node* node = list->head->next; node!=list->head; node=node->next)
	{
		show(node->ptr);
	}
}
