#include "sat.h"
int write(char filename[80]) {   //将棋盘的初始条件写入文件
	int a[20], i = 0;
	printf("写入棋盘的初始条件，以0为结尾\n");
	scanf("%d", &a[0]);
	while (a[i] != 0) {
		i++;
		scanf("%d", &a[i]);
	}
	FILE* fp;
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("打开文件失败\n");
		return ERROR;
	}
	fprintf(fp, "ccccccBinary_Puzzle\n");
	fprintf(fp, "p cnf 36 %d\n", i + 2376);
	i = 0;
	while (a[i] != 0) { //将变元的值输入cnf中作为条件
		fprintf(fp, "%d 0\n", a[i]);
		i++;
	}
	fclose(fp);
	return OK;
}


int WriteCNF(char filename[80]) {     //将棋盘的初始条件的三个约束，变成cnf公式，写入文件 
	if (write(filename) != OK)  return FALSE;
	if (rule1(filename) != OK) return FALSE;
	if (rule2(filename) != OK) return FALSE;
	if (rule3(filename) != OK) return FALSE;
	return OK;
}