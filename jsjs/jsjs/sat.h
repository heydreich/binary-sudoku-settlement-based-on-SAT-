#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 1        //�ж�Ϊ��
#define FALSE 0       //�ж�Ϊ��
#define OK 1          //����ִ�гɹ�
#define ERROR 0       //����ִ��ʧ��
#define INFEASTABLE -1     //�ṹ��δ����洢�ռ�
#define OVERFLOW -2       //������������䴢��ռ�ʧ��

typedef struct lNode {
	int l;         //�洢����
	int mark;      //��Ǹ������Ƿ�ɾ������ʼֵΪ1
	struct lNode* next;
}lNode, * plNode;               //�洢һ�����ֽڵ�

typedef struct cNode {
	int l_count;        //�洢һ���Ӿ�����ָ���
	int flag;           //��¼���Ӿ���Ϊflag����ɾ������ʼֵΪ0
	int mark;            //��Ǹ��Ӿ��Ƿ�ɾ�� ����ʼֵΪ1
	lNode* firstl;          //ָ���һ�����ֽڵ�
	struct cNode* next;        //ָ����һ���Ӿ�
}cNode, * pcNode;     //�Ӿ�ͷ�ڵ�

typedef struct iNode {
	cNode* p_cnode;       //�洢ָ�������ͷ����ָ��
	struct iNode* next;
}iNode, * piNode;       //��������ڽӵ�

typedef struct {
	iNode* firstz;       //�����ֵ�������
	iNode* firstf;       //�����ֵ�������
} index, * pindex;//����������Ķ���

typedef struct cnf {
	int varinum;       //��Ԫ����
	int claunum;        //�Ӿ����
	cNode* firstc;      //ָ���һ���Ӿ�ڵ�
	index* Index_List;    //������
}cnf, * pcnf;          //һ��cnf��ʽ

typedef struct SqList {
	int* elem;
	int length;
}SqList;              //һ��˳���ṹ���洢��

int createCNF(pcnf* L, char filename[80]);        //����CNFʽ
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

