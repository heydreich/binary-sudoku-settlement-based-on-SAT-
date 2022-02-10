#include "sat.h"




int main(int argc, char** argv) {
	pcnf L;
	SqList An;
	clock_t start, end;              ///记录时间
	double duration;
	char filename[80];
	//三个功能选择 
	int op = 1;
	int op_1 = 1;
	int op_2 = 1;
	int tag = -1;
	while (op) {//两大模块sat和puzzle 
		system("cls");	printf("\n\n");
		printf("         主菜单 \n");
		printf("------------------------------------------------------\n");
		printf("    	  1. sat       2. puzzle\n");
		printf("          0. Exit                   \n");
		printf("------------------------------------------------------\n");
		printf("    请选择你的操作[0~2]:");
		scanf("%d", &op);
		switch (op) {  //演示系统的功能选择 
		case 1:
			op_1 = 1;
			while (op_1) {//sat部分系统 
				system("cls");	printf("\n\n");
				printf("     Menu for Linear Table On Sequence Structure    \n");
				printf("----------------------------------------------------\n");
				printf("       1. 创建CNF         2. 解析子句               \n");
				printf("       3. DPLL            4. 检查                  \n");
				printf("       5. 打印答案        6. 输出Res文件             \n");
				printf("       0. Exit                                      \n");
				printf("----------------------------------------------------\n");
				printf("     请选择你的操作[0~6]:");
				scanf("%d", &op_1);
				switch (op_1) {
				case 1:
					printf("请输入选择的文件名\n");
					scanf("%s", filename);
					if (createCNF(&L, filename) == OK) printf("cnf公式创建成功\n");
					else {
						printf("cnf公式创建失败\n");
						getchar(); getchar();
						break;
					}
					if (InitList(L, An) == OK) printf("分配结果存储空间成功\n");
					else {
						printf("分配结果存储空间失败\n");
						getchar(); getchar();
						break;
					}
					getchar(); getchar();
					break;
				
				
				case 2:
					printf("\n--------解析子句功能待实现！\n");
					if (showCNF(L) == OK) printf("cnf公式打印成功\n");
					else printf("打印失败\n");
					getchar(); getchar();
					break;


				case 3:
					start = clock();
					if (DPLL(L, An, 1) == OK) {
						tag = 1;
						printf("求解成功\n");
					}
					else {
						tag = 0;
						printf("求解失败\n");
					}
					end = clock();
					duration = ((double)(end - start)) / CLK_TCK * 1000;
					printf("运行时间为：%f毫秒\n", duration);
					getchar(); getchar();
					break;
				case 4:
					if (check(L, An) == TRUE) printf("------------答案合理\n");
					else printf("---------答案不合理\n");
					getchar(); getchar();
					break;
				case 5:
					for (int i = 1; i < An.length; i++) {
						if (An.elem[i] == -1)  printf("%5d", -i);
						else printf("%5d", i);
						if (i % 10 == 0)  printf("\n");
					}
					getchar(); getchar();
					break;
				case 6:
					if (ResWrite1(tag, duration, An, filename) == OK) printf("结果写入成功\n");
					else printf("结果写入失败\n");
					getchar(); getchar();
					break;
				case 0:
					break;
				}
			}
			//getchar();getchar();
			break;
		case 2:
			op_2 = 1;
			while (op_2) {//puzzle部分系统 
				system("cls");	printf("\n\n");
				printf("        puzzle系统    \n");
				printf("----------------------------------------------------\n");
				printf("       1. 输入初始条件          2. 创建CNF             \n");
				printf("       3. DPLL                  4. 检查                  \n");
				printf("       5. 打印答案              6. 输出Res文件             \n");
				printf("       0. Exit                                      \n");
				printf("----------------------------------------------------\n");
				printf("     请选择操作[0~6]:");
				scanf("%d", &op_2);
				switch (op_2) {
				case 1:
					printf("请输入创建的文件名\n");
					scanf("%s", filename);
					if (WriteCNF(filename) == OK)  printf("棋局文件写入成功\n");
					else printf("棋局文件写入失败\n");
					getchar(); getchar();
					break;
				case 2:
					if (createCNF(&L, filename) == OK) printf("cnf公式创建成功\n");
					else {
						printf("cnf公式创建失败\n");
						getchar(); getchar();
						break;
					}
					if (InitList(L, An) == OK) printf("分配结果存储空间成功\n");
					else {
						printf("分配结果存储空间失败\n");
						getchar(); getchar();
						break;
					}
					getchar(); getchar();
					break;
				case 3:
					start = clock();
					if (DPLL(L, An, 1) == OK) {
						tag = 1;
						printf("求解成功\n");
					}
					else {
						tag = 0;
						printf("求解失败\n");
					}
					end = clock();
					duration = ((double)(end - start)) / CLK_TCK * 1000;
					printf("运行时间为：%f毫秒\n", duration);
					getchar(); getchar();
					break;
				case 4:
					if (check(L, An) == TRUE) printf("------------答案合理\n");
					else printf("----------答案不合理\n");
					getchar(); getchar();
					break;
				case 5:
					for (int i = 1; i < An.length; i++) {
						if (An.elem[i] == -1)  printf("0 ");
						else printf("1 ");
						if (i % 6 == 0)  printf("\n");
					}
					getchar(); getchar();
					break;
				case 6:
					if (ResWrite2(tag, duration, An, filename) == OK) printf("结果写入成功\n");
					else printf("结果写入失败\n");
					getchar(); getchar();
					break;
				case 0:
					break;
				}
			}
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
	return 0;
}
