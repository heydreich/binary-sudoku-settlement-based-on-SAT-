#include "sat.h"
int write(char filename[80]) {   //�����̵ĳ�ʼ����д���ļ�
	int a[20], i = 0;
	printf("д�����̵ĳ�ʼ��������0Ϊ��β\n");
	scanf("%d", &a[0]);
	while (a[i] != 0) {
		i++;
		scanf("%d", &a[i]);
	}
	FILE* fp;
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("���ļ�ʧ��\n");
		return ERROR;
	}
	fprintf(fp, "ccccccBinary_Puzzle\n");
	fprintf(fp, "p cnf 36 %d\n", i + 2376);
	i = 0;
	while (a[i] != 0) { //����Ԫ��ֵ����cnf����Ϊ����
		fprintf(fp, "%d 0\n", a[i]);
		i++;
	}
	fclose(fp);
	return OK;
}


int WriteCNF(char filename[80]) {     //�����̵ĳ�ʼ����������Լ�������cnf��ʽ��д���ļ� 
	if (write(filename) != OK)  return FALSE;
	if (rule1(filename) != OK) return FALSE;
	if (rule2(filename) != OK) return FALSE;
	if (rule3(filename) != OK) return FALSE;
	return OK;
}