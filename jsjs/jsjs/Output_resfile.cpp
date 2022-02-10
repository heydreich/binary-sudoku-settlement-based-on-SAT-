#include "sat.h"




int ResWrite1(int res, double time, SqList& An, char filename[80]) {   //���������������ʱ�䣬����𰸵������cnf�ļ���    //�������д���ļ�
	int i = 0;
	while (filename[i] != '\0') i++;
	filename[i - 3] = 'r';    //ֻ�ı��ļ�����չ��
	filename[i - 2] = 'e';
	filename[i - 1] = 's';
	FILE* fp;
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("���ļ�ʧ��\n");
		return ERROR;
	}
	fprintf(fp, "s %d\n", res);    //res���������1��ʾ���㣬0��ʾ�����㣬-1δ��
	fprintf(fp, "v ");
	for (i = 1; i < An.length; i++) {
		if (An.elem[i] == -1)  fprintf(fp, "%5d", -i);
		else fprintf(fp, "%5d", i);
	}
	fprintf(fp, "\nt %f ms\n", time);
	fclose(fp);
	return OK; //���һ��res�ļ���������������������ʾ��
}

int ResWrite2(int res, double time, SqList& An, char filename[80]) {   //���������������ʱ�䣬����𰸵������cnf�ļ���    //�������д���ļ�
	int i = 0, j;
	while (filename[i] != '\0') i++;
	filename[i - 3] = 'r';    //ֻ�ı��ļ�����չ��
	filename[i - 2] = 'e';
	filename[i - 1] = 's';
	FILE* fp;
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("���ļ�ʧ��\n");
		return ERROR;
	}
	fprintf(fp, "s %d\n", res);    //res���������1��ʾ���㣬0��ʾ�����㣬-1δ��
	fprintf(fp, "v \n");
	for (i = 0; i < 6; i++) {
		fprintf(fp, "----------------------------\n  ");
		for (j = 1; j <= 6; j++) {
			if (An.elem[6 * i + j] == 1) fprintf(fp, "1  ");
			else fprintf(fp, "0  ");
			if (j != 6) fprintf(fp, "   ");
			else fprintf(fp, "\n");
		}
	}
	fprintf(fp, "----------------------------\n");
	fprintf(fp, "\nt %f ms\n", time);
	fclose(fp);
	return OK;//���һ��res�ļ���������0��1����ʾ��
}
