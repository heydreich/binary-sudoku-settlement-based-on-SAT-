#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 1        //判断为真
#define FALSE 0       //判断为假
#define OK 1          //操作执行成功
#define ERROR 0       //操作执行失败
#define INFEASTABLE -1     //结构体未分配存储空间
#define OVERFLOW -2       //发生溢出，分配储存空间失败

typedef struct lNode {
	int l;         //存储文字
	int mark;      //标记该文字是否被删除，初始值为1
	struct lNode* next;
}lNode, * plNode;               //存储一个文字节点

typedef struct cNode {
	int l_count;        //存储一个子句的文字个数
	int flag;           //记录该子句因为flag而被删除，初始值为0
	int mark;            //标记该子句是否被删除 ，初始值为1
	lNode* firstl;          //指向第一个文字节点
	struct cNode* next;        //指向下一条子句
}cNode, * pcNode;     //子句头节点

typedef struct iNode {
	cNode* p_cnode;       //存储指向各文字头结点的指针
	struct iNode* next;
}iNode, * piNode;       //索引表的邻接点

typedef struct {
	iNode* firstz;       //正文字的索引点
	iNode* firstf;       //负文字的索引点
} index, * pindex;//对索引表结点的定义

typedef struct cnf {
	int varinum;       //变元个数
	int claunum;        //子句个数
	cNode* firstc;      //指向第一个子句节点
	index* Index_List;    //索引表
}cnf, * pcnf;          //一个cnf公式

typedef struct SqList {
	int* elem;
	int length;
}SqList;              //一个顺序表结构，存储答案

int createCNF(pcnf* L, char filename[80]);        //创建CNF式
int InitList(pcnf L, SqList& An);
int RemoveClause(pcnf L, int flag);
int AddClause(pcnf L, int flag);
int EmptyClause(pcnf L);
int Findl(pcnf L, SqList& An);
int DPLL(pcnf L, SqList& An, int now_l);
int check(pcnf L, SqList& An);
int rule1(char filename[80]);
int rule2(char filename[80]);
int rule3(char filename[80]);
int showCNF(pcnf L);
int WriteCNF(char filename[80]);
int ResWrite1(int res, double time, SqList& An, char filename[80]);
int ResWrite2(int res, double time, SqList& An, char filename[80]);

