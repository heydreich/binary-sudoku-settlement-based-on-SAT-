#include "sat.h"
int RemoveClause(pcnf L, int flag) {    //���������dpll�����ı�Ԫ        //�ҳ�һ����Ԫ����ɾ��
	pcNode p;    //�Ӿ�ͷ���
	plNode q;    //���ֽڵ�
	piNode r;    //������ڵ�
	if (flag > 0) {
		r = L->Index_List[flag].firstz;     // ɾȥ�Ӿ�
		while (r) {
			if (r->p_cnode->mark == 0)   r = r->next;  //�Ӿ���������Ԫ��ɾ��������
			else { 
				r->p_cnode->mark = 0;
				r->p_cnode->flag = flag; //��¼��flag��ɾ��
				L->claunum--;
				r = r->next;
			}
		}
		r = L->Index_List[flag].firstf; //ɾ������
		while (r) {
			if (r->p_cnode->mark == 0)  r = r->next;
			else {
				q = r->p_cnode->firstl; //��������
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
	else { //��flagΪ��
		r = L->Index_List[-flag].firstf;////// ��ɾȥ�Ӿ�
		while (r) {
			if (r->p_cnode->mark == 0)   r = r->next;
			else {
				r->p_cnode->mark = 0;
				r->p_cnode->flag = flag;
				L->claunum--;
				r = r->next;
			}
		}
		r = L->Index_List[-flag].firstz; //ɾ������
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
	return OK;//ɾȥflag��ص��Ӿ����෴��Ԫ��������OK
}

int AddClause(pcnf L, int flag) {    //���������dpll�����ı�Ԫ   //�ָ�ǰ����Ϊflag��ɾ����Ԫ��
	pcNode p;    //�Ӿ�ͷ���
	plNode q;    //���ֽڵ�
	piNode r;    //������ڵ�
	if (flag > 0) {
		r = L->Index_List[flag].firstz;          //����Ӿ�
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
		r = L->Index_List[flag].firstf;      //�������
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
		r = L->Index_List[-flag].firstf;          //����Ӿ�
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
		r = L->Index_List[-flag].firstz;      //�������
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
	L->varinum++;             //��Ԫ��Ŀ��һ
	return OK;//�ָ�flag��ص��Ӿ����෴��Ԫ��������OK
}

int EmptyClause(pcnf L) {        //�鿴�Ƿ��пվ�
	pcNode p = L->firstc;
	while (p) {
		if (p->l_count == 0 && p->mark == 1) return OK;
		p = p->next;
	}
	return FALSE;
}

int Findl(pcnf L, SqList& An) { //��������ʹ洢�𰸵�����
	pcNode p;
	plNode q;
	int i;
	int flag = 0;
	p = L->firstc;
	while (p) {
		if (p->mark == 1 && p->l_count == 1) {      //Ѱ�ҵ��Ӿ�
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
	//���Ӿ䲻���ڣ���Ѱ�ҳ��ִ��������Ǹ���Ԫ
	int* a = (int*)malloc((2 * An.length - 1) * sizeof(int));     //��������a���洢����Ԫ���ֵĴ���
	for (i = 0; i < 2 * An.length - 1; i++) {
		a[i] = 0;
	}
	p = L->firstc;
	while (p) {                //��¼����Ԫ���ֵĴ���
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
	for (i = 1; i < 2 * An.length - 1; i++) {    //�ҳ����ִ��������ֵ
		if (a[i] > flag)  flag = a[i];
	}
	for (i = 1; i < 2 * An.length - 1; i++) {  //�ҵ���Ԫ
		if (a[i] == flag)  break;
	}
	free(a);
	if (i % 2) {
		An.elem[(i + 1) / 2] = 1;
		return ((i + 1) / 2);
	}
	else {
		An.elem[i / 2] = -1;
		return (-(i / 2)); //���ش������ı�Ԫ����Ϊ���򷵻ظ�
	}
}


int DPLL(pcnf L, SqList& An, int now_l) { //������������𰸵����飬Ҫdpll�����ı�Ԫ
	int next_l;
	if (L->claunum == 0) return OK;       //cnf��ʽΪ�գ�����ɹ�
	else {
		if (EmptyClause(L) == OK) {       //�п��Ӿ�˵��ʧ�ܣ����з���
			if (AddClause(L, now_l) != OK)  printf("�ָ�ʧ��\n"); //�ָ���now_1��ɾ�����Ӿ������
			if (now_l > 0) An.elem[now_l] = 0;  //ʹ���鴢���ֵ��Ϊԭʼֵ
			else An.elem[-now_l] = 0;
			return FALSE; //�ݹ鷵��
		}
		else {
			next_l = Findl(L, An);   //Ѱ�ҳ����������ֽ��в���
			if (next_l == 0) return FALSE;   
			if (RemoveClause(L, next_l) != OK)  printf("ɾ��ʧ��\n");  //dpllɾ�������µõ�������

			if (DPLL(L, An, next_l) == OK)  return OK;  //�ݹ������������һ���֧
			else { //������ײ��֧�Ҳ��ɹ�ʱ
				if (AddClause(L, next_l) != OK) printf("�ָ�ʧ��\n");  //�ָ�
				if (RemoveClause(L, -next_l) != OK) printf("ɾ��ʧ��\n"); //������һ����֧����������Ϊԭ���෴�������
				if (DPLL(L, An, -next_l) == OK) { //���ɹ�
					if (next_l > 0) An.elem[next_l] = -1;
					else  An.elem[-next_l] = 1;
					return OK;  
				}
				else { //��ʧ�ܣ����ַ�����һ�㣬����һ�������һ����֧
					if (AddClause(L, -next_l) != OK) printf("�ָ�ʧ��\n");
					if (next_l > 0) An.elem[next_l] = 0;
					else An.elem[-next_l] = 0;
					return FALSE;
				}
			}
		}
	}
}

int check(pcnf L, SqList& An) {    //��������ʹ���𰸵ı�Ԫ   //������Ƿ���ȷ
	int flag;
	pcNode p;
	plNode q;
	p = L->firstc;
	while (p) {
		flag = 0;
		q = p->firstl;
		while (q) { 
			if (((q->l > 0) && (An.elem[q->l] == 1)) || ((q->l < 0) && (An.elem[-(q->l)] == -1 ))) {
				flag = 1;//���Ӿ���һ����Ԫ��ȷ����ȷ
				break;
			}
			else q = q->next;
		}
		if (flag == 0) break;//�����Ӿ����
		p = p->next;
	}
	if (flag == 0)  return FALSE;
	else return TRUE; //���ؼ��Ľ��
}

