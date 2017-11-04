/** 
* @file zn_data_linklist.h
* @brief 基于 linux  封装链表
* @author zhunian0322@163.com
* @date 09:52 2017/11/04
* @version 1
*/

#ifndef ZN_DATA_LINKLIST_H_
#define ZN_DATA_LINKLIST_H_

#include <stdbool.h>

/** 链表节点 */
typedef struct __LinkNode{
	struct __LinkNode *next;  /**< 链表的下一个节点 */
}LinkNode;

/** 链表头 */
typedef void* LLink;

/** 打印回调 */
typedef void(*TYPE_PRINT)(LinkNode *);

/** 比较回调 */
typedef bool(*TYPE_COMPARE)(LinkNode *,LinkNode *);

/** 
 *  @breif	初始化链表结构  
 *  @return 返回 void * 类型指针， 链表头
 */
LLink zn_data_linklistInit();

/** 
 *  @breif	在链表指定位置插入元素  
 *  @param[in] head  链表头
 *  @param[in] pos   偏移位置
 *  @param[in] data  插入的元素
 */
void zn_data_linklistInsert(LLink *head,int pos, LinkNode *data);

/** 
 *  @breif	在链表头插入元素  
 *  @param[in] head  链表头
 *  @param[in] data  插入的元素
 */
void zn_data_linklistPushFront(LLink *head, LinkNode *data);

/** 
 *  @breif	在链尾头插入元素  
 *  @param[in] head  链表头
 *  @param[in] data  插入的元素
 */
void zn_data_linklistPushBack(LLink *head, LinkNode *data);

/** 
 *  @breif	删除指定位置的元素  
 *  @param[in] head  链表头
 *  @param[in] pos   偏移位置
 *  @return 返回删除的元素，失败返回 NULL
 */
LinkNode *zn_data_linklistRemoveByPos(LLink *head, int pos);

/** 
 *  @breif	删除指定元素  
 *  @param[in] head  链表头
 *  @param[in] data  要删除的数据(用作对比)
 *  @param[in] compare 比较函数
 */
void zn_data_linklistRemoveByCompare(LLink *head, LinkNode *data, TYPE_COMPARE compare);

/** 
 *  @breif	删除头部元素  
 *  @param[in] head  链表头
 *  @return 返回删除的元素，失败返回 NULL
 */
LinkNode *zn_data_linklistPopFront(LLink *head);

/** 
 *  @breif	删除尾部元素  
 *  @param[in] head  链表头
 *  @return 返回删除的元素，失败返回 NULL
 */
LinkNode *zn_data_linklistPopBack(LLink *head);

/** 
 *  @breif	获取链表长度  
 *  @param[in] head  链表头
 *  @return 返回链表长度
 */
int zn_data_linklistGetListLen(LLink *head);

/** 
 *  @breif	销毁链表
 *  @param[in] head  链表头
 */
void zn_data_linklistDestory(LLink *head);

/** 
 *  @breif	遍历链表  
 *  @param[in] head  链表头
 *  @param[in] print 打印函数
 */
void zn_data_linklistForeach(LLink *head, TYPE_PRINT print);

#endif /* ZN_DATA_LINKLIST_H_ */
