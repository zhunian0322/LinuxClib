/*
 * linklist_test.c
 *
 *  Created on: Nov 3, 2017
 *      Author: gino
 */


#include <stdio.h>
#include <string.h>

#include "../inc/zn_data_linklist.h"

typedef struct {
	LinkNode next;
	char name[64];
	int age;
} TESTDATA;

void linkNode_print(LinkNode *data) {
	if (data == NULL) return;

	TESTDATA * p = (TESTDATA *) data;
	printf("name is %s\t\t age is %d\n", p->name, p->age);

}

bool linkNode_compare(LinkNode *a, LinkNode *b) {
	if(a == NULL || b == NULL)
		return false;

	TESTDATA * p1 = (TESTDATA *)a;
	TESTDATA * p2 = (TESTDATA *)b;

	if((strcmp(p1->name,p2->name) == 0) && (p1->age == p2->age))
		return true;

	return false;
}



int main() {

	TESTDATA p1,p2,p3,p4,p5,p6;
	strcpy(p1.name,"xiaoming");
	strcpy(p2.name,"xiaohong");
	strcpy(p3.name,"xiaohua");
	strcpy(p4.name,"xiaolu");
	strcpy(p5.name,"xiaomi");
	strcpy(p6.name,"xiaowang");

	p1.age = 1;
	p2.age = 2;
	p3.age = 3;
	p4.age = 4;
	p5.age = 5;
	p6.age = 6;


	LLink *list = zn_data_linklistInit();
	zn_data_linklistInsert(list,0,(LinkNode *)&p1);
	zn_data_linklistPushFront(list,(LinkNode *)&p2);
	zn_data_linklistPushBack(list,(LinkNode *)&p3);
	zn_data_linklistInsert(list,3,(LinkNode *)&p4);
	zn_data_linklistInsert(list,-1,(LinkNode *)&p5);
	zn_data_linklistInsert(list,1024,(LinkNode *)&p6);

	zn_data_linklistForeach(list,linkNode_print);

	printf("\n=====================================================\n");

	TESTDATA *t = (TESTDATA *)zn_data_linklistPopFront(list);
	linkNode_print((LinkNode *)t);

	t = (TESTDATA *)zn_data_linklistPopBack(list);
	linkNode_print((LinkNode *)t);

	t = (TESTDATA *)zn_data_linklistRemoveByPos(list,3);
	linkNode_print((LinkNode *)t);

	zn_data_linklistRemoveByCompare(list,(LinkNode *)&p3,linkNode_compare);
	printf("\n=====================================================\n");
	zn_data_linklistForeach(list,linkNode_print);

	printf("List length is %d\n",zn_data_linklistGetListLen(list));

	zn_data_linklistDestory(list);
}
