#include "sat.h"
int createCNF(pcnf* L, char filename[80]) { //输入要创建的链表名和输入的文件
	pcNode p;    //子句结点
	plNode q;    //文字节点
	piNode r;    //索引节点
	int i;
	*L = (cnf*)malloc(sizeof(struct cnf));
	p = (cNode*)malloc(sizeof(struct cNode));
	p->flag = 0;
	p->mark = 1;
	(*L)->firstc = p; 
	FILE* fp;
	int num = 0;
	int k = 0;       //记录每个子句文字个数
	int m = 0;             //记录子句的个数
	int flag;         //记录正负
	char c;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("打开文件失败\n");
		return 0;
	}
	fscanf(fp, "%c", &c);
	while (!feof(fp)) {
		if (c == 'c') {            //cnf文件注释部分
			while (c != '\n') {
				fscanf(fp, "%c", &c);
			}
			fscanf(fp, "%c", &c);
		}
		else if (c == 'p') {
			while (c != '\n') {
				while (c < '0' || c>'9') {
					fscanf(fp, "%c", &c);
				}
				while (c >= '0' && c <= '9') {        /*输出变元个数*/
					num = num * 10;
					num += c - '0';
					fscanf(fp, "%c", &c);
				}
				(*L)->varinum = num;
				(*L)->Index_List = (index*)malloc((num + 1) * sizeof(index));
				for (i = 0; i <= num; i++) {      /*利用数组将每个变元的索引链表创建*/
					(*L)->Index_List[i].firstf = NULL;
					(*L)->Index_List[i].firstz = NULL;
				}
				num = 0;
				while (c < '0' || c>'9') {
					fscanf(fp, "%c", &c);
				}
				while (c >= '0' && c <= '9') {        /*获取子句数目*/
					num = num * 10;
					num += c - '0';
					fscanf(fp, "%c", &c);
				}
				(*L)->claunum = num;
				num = 0;
			}
			fscanf(fp, "%c", &c);
		}
		else if ((c >= '0' && c <= '9') || (c == '-')) {
			q = (lNode*)malloc(sizeof(struct lNode));
			q->mark = 1;
			p->firstl = q;
			while (c != '\n') {
				while (c != '0') {
					while (c != ' ') {
						flag = 1;   /*flag用来记录正负*/
						while ((c >= '0' && c <= '9') || (c == '-')) {
							if (c == '-') {
								fscanf(fp, "%c", &c);
								flag = 0;
							}
							num = num * 10;
							num += c - '0';
							fscanf(fp, "%c", &c);
						}
						r = (iNode*)malloc(sizeof(struct iNode));
						r->p_cnode = p;
						if (flag == 0) {                    //为负的情况
							q->l = -num;
							r->next = (*L)->Index_List[num].firstf;
							(*L)->Index_List[num].firstf = r;
						}
						else {                    //为正的情况
							q->l = num;
							r->next = (*L)->Index_List[num].firstz;
							(*L)->Index_List[num].firstz = r;
						}
						num = 0;
						k++;
					}
					fscanf(fp, "%c", &c);
					if (c == '0') q->next = NULL;
					else {
						q->next = (lNode*)malloc(sizeof(struct lNode));
						q = q->next;
						q->mark = 1;
					}
				}
				fscanf(fp, "%c", &c);
			}
			fscanf(fp, "%c", &c);
			p->l_count = k;
			k = 0;
			m++;

			if (m < (*L)->claunum) {
				p->next = (cNode*)malloc(sizeof(struct cNode));
				p = p->next;
				p->flag = 0;
				p->mark = 1;
			}
			else p->next = NULL;
		}
		else fscanf(fp, "%c", &c);	//防止文件结尾有多个换行
	}
	fclose(fp);
	return OK; //将输入的cnf文件储存在链表中，并创建索引表，将与文字正相关的子句储存在对应数组的正链表中，负相关在负链表
}



int InitList(pcnf L, SqList& An) {//为存储答案的顺序表分配存储空间  //输入链表与储存答案的数组名
	An.elem = (int*)malloc((L->varinum + 1) * sizeof(int));//分配存储空间
	if (!An.elem) {
		return ERROR;//分配存储空间失败
	};
	An.length = L->varinum + 1;//初始化线性表的长度为0
	for (int i = 1; i < An.length; i++) {
		An.elem[i] = 0;                        //表示没有经过单子句简化赋值
	}
	return OK; //根据变元数目来创建数组大小
}

int showCNF(pcnf L) { //输入子句与文字的链表
	if (L->claunum == 0) {
		printf("cnf公式为空\n");
		return OK;
	}
	pcNode p = L->firstc;
	plNode q = p->firstl;
	printf("cnf公式变元数：%d  子句数：%d\n", L->varinum, L->claunum);
	int i = 1;
	int j;
	while (p) {
		if (p->mark == 0) p = p->next;
		else {
			printf("第%d句有%d个文字   ", i++, p->l_count);
			q = p->firstl;
			j = 1;
			while (q) {
				if (q->mark == 0)  q = q->next;
				else {
					printf("   %d   ", q->l);
					q = q->next;
				}
			}
			printf("\n");
			p = p->next;
		}

	}
	return OK; //将子句逐条打印并返回OK
}



