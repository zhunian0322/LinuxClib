/** 
* @file zn_data_linklist.c
* @brief 基于 linux  封装链表
* @author zhunian0322@163.com
* @date 09:52 2017/11/04
* @version 1
*/


#include <stdio.h>
#include <stdlib.h>

#include "../inc/zn_data_linklist.h"

typedef struct __LinkList {
	LinkNode header;
	int size;
} LinkList;

LLink zn_data_linklistInit() {
	LinkList * list = (LinkList *) malloc(sizeof(LinkList));

	if (list == NULL) return NULL;

	list->header.next = NULL;
	list->size = 0;

	return list;
}

void zn_data_linklistInsert(LLink *head, int pos, LinkNode *data) {
	if (head == NULL || data == NULL) return;

	LinkList *temp = (LinkList *) head;
	if (pos < 0 || pos > temp->size) pos = temp->size;

	LinkNode *pCurrent = &(temp->header);

	for (int i = 0; i < pos; ++i) {
		pCurrent = pCurrent->next;
	}

	data->next = pCurrent->next;
	pCurrent->next = data;
	temp->size++;

}

void zn_data_linklistPushFront(LLink *head, LinkNode *data) {
	if (head == NULL || data == NULL) return;

	zn_data_linklistInsert(head, 0, data);
}

void zn_data_linklistPushBack(LLink *head, LinkNode *data) {
	if (head == NULL || data == NULL) return;

	zn_data_linklistInsert(head, -1, data);
}

LinkNode *zn_data_linklistRemoveByPos(LLink *head, int pos) {
	if (head == NULL) return NULL;

	LinkList *temp = (LinkList *) head;
	if (pos < 0 || pos >= temp->size) return NULL;

	LinkNode *pCurrent = &(temp->header);
	for (int i = 0; i < pos; i++)
		pCurrent = pCurrent->next;

	LinkNode *DelNode = pCurrent->next;
	pCurrent->next = DelNode->next;
	temp->size--;

	return DelNode;
}

void zn_data_linklistRemoveByCompare(LLink *head, LinkNode *data,
        TYPE_COMPARE compare) {

	if (head == NULL || data == NULL || compare == NULL) return;

	LinkList *temp = (LinkList *) head;
	if (temp->size == 0) return;

	LinkNode *pPrev = &(temp->header);
	LinkNode *pCurrent = temp->header.next;

	while (pCurrent) {
		if (compare(pCurrent, data)) {
			pPrev->next = pCurrent->next;
			temp->size--;
			break;
		}

		pPrev = pCurrent;
		pCurrent = pCurrent->next;
	}

}

LinkNode *zn_data_linklistPopFront(LLink *head) {
	if (head == NULL) return NULL;

	return zn_data_linklistRemoveByPos(head, 0);
}

LinkNode *zn_data_linklistPopBack(LLink *head) {
	if (head == NULL) return NULL;

	return zn_data_linklistRemoveByPos(head, ((LinkList *) head)->size - 1);
}

int zn_data_linklistGetListLen(LLink *head) {
	if(head == NULL)
		return 0;

	return ((LinkList *)head)->size;
}

void zn_data_linklistDestory(LLink *head) {
	if(head == NULL)
		return;

	free(head);
	head = NULL;
}

void zn_data_linklistForeach(LLink *head, TYPE_PRINT print) {
	if(head == NULL || print == NULL)
		return;

	LinkList *temp = (LinkList *)head;
	LinkNode *pCurrent = temp->header.next;
	for(int i = 0; i < temp->size; ++i){
		print(pCurrent);
		pCurrent = pCurrent->next;
	}

}
