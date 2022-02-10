#include "sat.h"
int createCNF(pcnf* L, char filename[80]) { //����Ҫ��������������������ļ�
	pcNode p;    //�Ӿ���
	plNode q;    //���ֽڵ�
	piNode r;    //�����ڵ�
	int i;
	*L = (cnf*)malloc(sizeof(struct cnf));
	p = (cNode*)malloc(sizeof(struct cNode));
	p->flag = 0;
	p->mark = 1;
	(*L)->firstc = p; 
	FILE* fp;
	int num = 0;
	int k = 0;       //��¼ÿ���Ӿ����ָ���
	int m = 0;             //��¼�Ӿ�ĸ���
	int flag;         //��¼����
	char c;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("���ļ�ʧ��\n");
		return 0;
	}
	fscanf(fp, "%c", &c);
	while (!feof(fp)) {
		if (c == 'c') {            //cnf�ļ�ע�Ͳ���
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
				while (c >= '0' && c <= '9') {        /*�����Ԫ����*/
					num = num * 10;
					num += c - '0';
					fscanf(fp, "%c", &c);
				}
				(*L)->varinum = num;
				(*L)->Index_List = (index*)malloc((num + 1) * sizeof(index));
				for (i = 0; i <= num; i++) {      /*�������齫ÿ����Ԫ������������*/
					(*L)->Index_List[i].firstf = NULL;
					(*L)->Index_List[i].firstz = NULL;
				}
				num = 0;
				while (c < '0' || c>'9') {
					fscanf(fp, "%c", &c);
				}
				while (c >= '0' && c <= '9') {        /*��ȡ�Ӿ���Ŀ*/
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
						flag = 1;   /*flag������¼����*/
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
						if (flag == 0) {                    //Ϊ�������
							q->l = -num;
							r->next = (*L)->Index_List[num].firstf;
							(*L)->Index_List[num].firstf = r;
						}
						else {                    //Ϊ�������
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
		else fscanf(fp, "%c", &c);	//��ֹ�ļ���β�ж������
	}
	fclose(fp);
	return OK; //�������cnf�ļ������������У�������������������������ص��Ӿ䴢���ڶ�Ӧ������������У�������ڸ�����
}



int InitList(pcnf L, SqList& An) {//Ϊ�洢�𰸵�˳������洢�ռ�  //���������봢��𰸵�������
	An.elem = (int*)malloc((L->varinum + 1) * sizeof(int));//����洢�ռ�
	if (!An.elem) {
		return ERROR;//����洢�ռ�ʧ��
	};
	An.length = L->varinum + 1;//��ʼ�����Ա�ĳ���Ϊ0
	for (int i = 1; i < An.length; i++) {
		An.elem[i] = 0;                        //��ʾû�о������Ӿ�򻯸�ֵ
	}
	return OK; //���ݱ�Ԫ��Ŀ�����������С
}

int showCNF(pcnf L) { //�����Ӿ������ֵ�����
	if (L->claunum == 0) {
		printf("cnf��ʽΪ��\n");
		return OK;
	}
	pcNode p = L->firstc;
	plNode q = p->firstl;
	printf("cnf��ʽ��Ԫ����%d  �Ӿ�����%d\n", L->varinum, L->claunum);
	int i = 1;
	int j;
	while (p) {
		if (p->mark == 0) p = p->next;
		else {
			printf("��%d����%d������   ", i++, p->l_count);
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
	return OK; //���Ӿ�������ӡ������OK
}



