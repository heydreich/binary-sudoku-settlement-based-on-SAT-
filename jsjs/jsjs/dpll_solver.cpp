#include "sat.h"
int RemoveClause(pcnf L, int flag) {    //输入链表和dpll操作的变元        //找出一个变元，并删除
	pcNode p;    //子句头结点
	plNode q;    //文字节点
	piNode r;    //索引表节点
	if (flag > 0) {
		r = L->Index_List[flag].firstz;     // 删去子句
		while (r) {
			if (r->p_cnode->mark == 0)   r = r->next;  //子句因其它变元而删除，跳过
			else { 
				r->p_cnode->mark = 0;
				r->p_cnode->flag = flag; //记录因flag而删除
				L->claunum--;
				r = r->next;
			}
		}
		r = L->Index_List[flag].firstf; //删除文字
		while (r) {
			if (r->p_cnode->mark == 0)  r = r->next;
			else {
				q = r->p_cnode->firstl; //负索引表
				while (q) {
					if (q->mark == 0)  q = q->next;
					else {
						if (q->l == -flag) {
							q->mark = 0;
							r->p_cnode->l_count--;
							break; 
						}
						q = q->next;
					}
				}
				r = r->next;
			}
		}
	}
	else { //若flag为负
		r = L->Index_List[-flag].firstf;////// 先删去子句
		while (r) {
			if (r->p_cnode->mark == 0)   r = r->next;
			else {
				r->p_cnode->mark = 0;
				r->p_cnode->flag = flag;
				L->claunum--;
				r = r->next;
			}
		}
		r = L->Index_List[-flag].firstz; //删除文字
		while (r) {
			if (r->p_cnode->mark == 0)  r = r->next;
			else {
				q = r->p_cnode->firstl;
				while (q) {
					if (q->mark == 0)  q = q->next;
					else {
						if (q->l == -flag) {
							q->mark = 0;
							r->p_cnode->l_count--;
							break;
						}
						q = q->next;
					}
				}
				r = r->next;
			}
		}
	}


	L->varinum--;
	return OK;//删去flag相关的子句与相反变元，并返回OK
}

int AddClause(pcnf L, int flag) {    //输入链表和dpll操作的变元   //恢复前面因为flag而删除的元素
	pcNode p;    //子句头结点
	plNode q;    //文字节点
	piNode r;    //索引表节点
	if (flag > 0) {
		r = L->Index_List[flag].firstz;          //添加子句
		while (r) {
			if (r->p_cnode->mark == 1)  r = r->next;
			else {
				if (r->p_cnode->flag == flag) {
					r->p_cnode->mark = 1;
					r->p_cnode->flag = 0;
					L->claunum++;
				}
				r = r->next;
			}
		}
		r = L->Index_List[flag].firstf;      //添加文字
		while (r) {
			q = r->p_cnode->firstl;
			while (q) {
				if (q->mark == 0 && q->l == -flag) {
					q->mark = 1;
					r->p_cnode->l_count++;
					break;
				}
				q = q->next;
			}
			r = r->next;
		}
	}
	else {
		r = L->Index_List[-flag].firstf;          //添加子句
		while (r) {
			if (r->p_cnode->mark == 1)  r = r->next;
			else {
				if (r->p_cnode->flag == flag) {
					r->p_cnode->mark = 1;
					r->p_cnode->flag = 0;
					L->claunum++;
				}
				r = r->next;
			}
		}
		r = L->Index_List[-flag].firstz;      //添加文字
		while (r) {
			q = r->p_cnode->firstl;
			while (q) {
				if (q->mark == 0 && q->l == -flag) {
					q->mark = 1;
					r->p_cnode->l_count++;
					break;
				}
				q = q->next;
			}
			r = r->next;
		}
	}
	L->varinum++;             //变元数目加一
	return OK;//恢复flag相关的子句与相反变元，并返回OK
}

int EmptyClause(pcnf L) {        //查看是否有空句
	pcNode p = L->firstc;
	while (p) {
		if (p->l_count == 0 && p->mark == 1) return OK;
		p = p->next;
	}
	return FALSE;
}

int Findl(pcnf L, SqList& An) { //输入链表和存储答案的数组
	pcNode p;
	plNode q;
	int i;
	int flag = 0;
	p = L->firstc;
	while (p) {
		if (p->mark == 1 && p->l_count == 1) {      //寻找单子句
			q = p->firstl;
			while (q) {
				if (q->mark == 1) {
					if (q->l > 0) 	An.elem[q->l] = 1;
					else    An.elem[-(q->l)] = -1;
					return q->l;
				}
				else q = q->next;
			}
		}
		else p = p->next;
	}
	//单子句不存在，就寻找出现次数最多的那个变元
	int* a = (int*)malloc((2 * An.length - 1) * sizeof(int));     //构建数组a，存储各变元出现的次数
	for (i = 0; i < 2 * An.length - 1; i++) {
		a[i] = 0;
	}
	p = L->firstc;
	while (p) {                //记录各变元出现的次数
		if (p->mark == 0) p = p->next;
		else {
			q = p->firstl;
			while (q) {
				if (q->mark == 0) q = q->next;
				else {
					if (q->l > 0) a[2 * (q->l) - 1]++;
					else if (q->l < 0)    a[2 * (-(q->l))]++;
					q = q->next;
				}
			}
			p = p->next;
		}
	}
	for (i = 1; i < 2 * An.length - 1; i++) {    //找出出现次数的最大值
		if (a[i] > flag)  flag = a[i];
	}
	for (i = 1; i < 2 * An.length - 1; i++) {  //找到变元
		if (a[i] == flag)  break;
	}
	free(a);
	if (i % 2) {
		An.elem[(i + 1) / 2] = 1;
		return ((i + 1) / 2);
	}
	else {
		An.elem[i / 2] = -1;
		return (-(i / 2)); //返回次数最多的变元，若为负则返回负
	}
}


int DPLL(pcnf L, SqList& An, int now_l) { //输入链表，储存答案的数组，要dpll操作的变元
	int next_l;
	if (L->claunum == 0) return OK;       //cnf公式为空，化简成功
	else {
		if (EmptyClause(L) == OK) {       //有空子句说明失败，进行返回
			if (AddClause(L, now_l) != OK)  printf("恢复失败\n"); //恢复因now_1而删除的子句和文字
			if (now_l > 0) An.elem[now_l] = 0;  //使数组储存的值变为原始值
			else An.elem[-now_l] = 0;
			return FALSE; //递归返回
		}
		else {
			next_l = Findl(L, An);   //寻找出现最多的文字进行操作
			if (next_l == 0) return FALSE;   
			if (RemoveClause(L, next_l) != OK)  printf("删除失败\n");  //dpll删除操作新得到的文字

			if (DPLL(L, An, next_l) == OK)  return OK;  //递归操作，进入下一层分支
			else { //到达最底层分支且不成功时
				if (AddClause(L, next_l) != OK) printf("恢复失败\n");  //恢复
				if (RemoveClause(L, -next_l) != OK) printf("删除失败\n"); //进入另一条分支，即此文字为原来相反的情况下
				if (DPLL(L, An, -next_l) == OK) { //若成功
					if (next_l > 0) An.elem[next_l] = -1;
					else  An.elem[-next_l] = 1;
					return OK;  
				}
				else { //若失败，则又返回上一层，由上一层进入另一条分支
					if (AddClause(L, -next_l) != OK) printf("恢复失败\n");
					if (next_l > 0) An.elem[next_l] = 0;
					else An.elem[-next_l] = 0;
					return FALSE;
				}
			}
		}
	}
}

int check(pcnf L, SqList& An) {    //输入链表和储存答案的变元   //检验答案是否正确
	int flag;
	pcNode p;
	plNode q;
	p = L->firstc;
	while (p) {
		flag = 0;
		q = p->firstl;
		while (q) { 
			if (((q->l > 0) && (An.elem[q->l] == 1)) || ((q->l < 0) && (An.elem[-(q->l)] == -1 ))) {
				flag = 1;//若子句有一个变元正确则正确
				break;
			}
			else q = q->next;
		}
		if (flag == 0) break;//此条子句错误
		p = p->next;
	}
	if (flag == 0)  return FALSE;
	else return TRUE; //返回检查的结果
}

