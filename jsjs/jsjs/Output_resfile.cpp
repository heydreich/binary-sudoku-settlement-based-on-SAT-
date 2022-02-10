#include "sat.h"




int ResWrite1(int res, double time, SqList& An, char filename[80]) {   //输入求解结果，运行时间，储存答案的数组和cnf文件名    //将求解结果写入文件
	int i = 0;
	while (filename[i] != '\0') i++;
	filename[i - 3] = 'r';    //只改变文件的扩展名
	filename[i - 2] = 'e';
	filename[i - 1] = 's';
	FILE* fp;
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("打开文件失败\n");
		return ERROR;
	}
	fprintf(fp, "s %d\n", res);    //res是求解结果，1表示满足，0表示不满足，-1未定
	fprintf(fp, "v ");
	for (i = 1; i < An.length; i++) {
		if (An.elem[i] == -1)  fprintf(fp, "%5d", -i);
		else fprintf(fp, "%5d", i);
	}
	fprintf(fp, "\nt %f ms\n", time);
	fclose(fp);
	return OK; //输出一个res文件，其中用文字正负来表示答案
}

int ResWrite2(int res, double time, SqList& An, char filename[80]) {   //输入求解结果，运行时间，储存答案的数组和cnf文件名    //将求解结果写入文件
	int i = 0, j;
	while (filename[i] != '\0') i++;
	filename[i - 3] = 'r';    //只改变文件的扩展名
	filename[i - 2] = 'e';
	filename[i - 1] = 's';
	FILE* fp;
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("打开文件失败\n");
		return ERROR;
	}
	fprintf(fp, "s %d\n", res);    //res是求解结果，1表示满足，0表示不满足，-1未定
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
	return OK;//输出一个res文件，其中用0和1来表示答案
}
