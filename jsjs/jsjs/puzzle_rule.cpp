#include "sat.h"
int rule1(char filename[80]) { //�����ļ���
	FILE* fp;
	fp = fopen(filename, "a+");
	if (fp == NULL) {
		printf("���ļ�ʧ��\n");
		return 0;
	}
	
	
	int i, j, k;                 //Լ��1��ÿһ�У�ÿһ�У�û������������0��������1 
	for (i = 1; i <= 6; i++) {             //ÿһ�� ���� 
		for (j = 1; j <= 4; j++) {
			for (k = 0; k <= 2; k++) {
				fprintf(fp, "%d ", (i - 1) * 6 + j + k);
			}
			fprintf(fp, "0\n");
			for (k = 0; k <= 2; k++) {
				fprintf(fp, "%d ", -((i - 1) * 6 + j + k));
			}
			fprintf(fp, "0\n");
		}
	}
	for (j = 1; j <= 6; j++) {            //ÿһ�п��� 
		for (i = 1; i <= 4; i++) {
			for (k = 0; k <= 2; k++) {
				for (k = 0; k <= 2; k++) {
					fprintf(fp, "%d ", (i - 1) * 6 + j + k * 6);
				}
				fprintf(fp, "0\n");
				for (k = 0; k <= 2; k++) {
					fprintf(fp, "%d ", -((i - 1) * 6 + j + k * 6));
				}
				fprintf(fp, "0\n");
			}
		}
	}
	fclose(fp);
	return OK;  //��������û������������1��0���Ӿ䴢����cnf�ļ��У���Ϊ����
} //��ʱ���Ӿ���Ϊ96������ԪΪ1~36 

int rule2(char filename[80]) {      //Լ��2��ÿһ�� ��ÿһ�е�0��1��Ŀ��ȣ�=3����������4����Ԫ����ȫΪ0����ȫΪ1 
	FILE* fp;
	fp = fopen(filename, "a+");
	if (fp == NULL) {
		printf("���ļ�ʧ��\n");
		return 0;
	}
	int i, j, k, w;
	int n;
	for (n = 0; n <= 5; n++) {       //������        
		for (i = 1; i <= 3; i++) {
			for (j = 2; j <= 4; j++) {
				for (k = 3; k <= 5; k++) {
					for (w = 4; w <= 6; w++) {
						if (i < j && j < k && k < w) {
							fprintf(fp, "%d %d %d %d 0\n", i + 6 * n, j + 6 * n, k + 6 * n, w + 6 * n);
							fprintf(fp, "%d %d %d %d 0\n", -(i + 6 * n), -(j + 6 * n), -(k + 6 * n), -(w + 6 * n));
						}

					}
				}

			}
		}
	}
	for (n = 0; n <= 5; n++) {       //������       
		for (i = 1; i <= 13; i = i + 6) {
			for (j = 7; j <= 19; j = j + 6) {
				for (k = 13; k <= 25; k = k + 6) {
					for (w = 19; w <= 31; w = w + 6) {
						if (i < j && j < k && k < w) {
							fprintf(fp, "%d %d %d %d 0\n", i + n, j + n, k + n, w + n);
							fprintf(fp, "%d %d %d %d 0\n", -(i + n), -(j + n), -(k + n), -(w + n));
						}

					}
				}

			}
		}
	}
	fclose(fp);
	return OK; //����ÿ��ÿ��1��0��Ŀ��ͬ���Ӿ���cnf�ļ���
}

int rule3(char filename[80]) {       //�����ļ���         //Լ������û�����У�������ͬ 
	FILE* fp;
	fp = fopen(filename, "a+");
	if (fp == NULL) {
		printf("���ļ�ʧ��\n");
		return 0;
	}
	int i, j, k, w, r, s, t;
	for (i = 1; i <= 6; i++) {              //������ 
		for (k = 1; k <= 6 - i; k++) {
			for (w = 0; w <= 6; w++) {     //����м���Ϊ��
				if (w == 0) {
					for (j = 1; j <= 6; j++) {
						fprintf(fp, "%d %d ", (i - 1) * 6 + j, (i - 1) * 6 + j + 6 * k);
					}
					fprintf(fp, "0\n");
				}
				else if (w == 1) {            //һ��Ϊ�� 
					for (r = 1; r <= 6; r++) {       //��ǵ�ǰ���ĸ���Ϊ��
						for (j = 1; j <= 6; j++) {
							if (j == r) fprintf(fp, "%d %d ", -((i - 1) * 6 + j), -((i - 1) * 6 + j + 6 * k));
							else fprintf(fp, "%d %d ", (i - 1) * 6 + j, (i - 1) * 6 + j + 6 * k);
						}
						fprintf(fp, "0\n");
					}
				}
				else if (w == 2) {  //����Ϊ�� 
					for (r = 1; r <= 6; r++) {
						for (s = r + 1; s <= 6; s++) {
							for (j = 1; j <= 6; j++) {
								if (j == r || j == s)  fprintf(fp, "%d %d ", -((i - 1) * 6 + j), -((i - 1) * 6 + j + 6 * k));
								else fprintf(fp, "%d %d ", (i - 1) * 6 + j, (i - 1) * 6 + j + 6 * k);
							}
							fprintf(fp, "0\n");
						}
					}
				}
				else if (w == 3) {  //����Ϊ�� 
					for (r = 1; r < 6; r++) {
						for (s = r + 1; s <= 6; s++) {
							for (t = s + 1; t <= 6; t++) {
								for (j = 1; j <= 6; j++) {
									if (j == r || j == s || j == t) fprintf(fp, "%d %d ", -((i - 1) * 6 + j), -((i - 1) * 6 + j + 6 * k));
									else fprintf(fp, "%d %d ", (i - 1) * 6 + j, (i - 1) * 6 + j + 6 * k);
								}
								fprintf(fp, "0\n");
							}
						}
					}
				}
				else if (w == 4) {           //�ĸ�Ϊ�� 
					for (r = 1; r <= 6; r++) {
						for (s = r + 1; s <= 6; s++) {
							for (j = 1; j <= 6; j++) {
								if (j == r || j == s)  fprintf(fp, "%d %d ", (i - 1) * 6 + j, (i - 1) * 6 + j + 6 * k);
								else fprintf(fp, "%d %d ", -((i - 1) * 6 + j), -((i - 1) * 6 + j + 6 * k));
							}
							fprintf(fp, "0\n");
						}
					}
				}
				else if (w == 5) {
					for (r = 1; r <= 6; r++) {       //��ǵ�ǰ���ĸ���Ϊ��
						for (j = 1; j <= 6; j++) {
							if (j == r) fprintf(fp, "%d %d ", (i - 1) * 6 + j, (i - 1) * 6 + j + 6 * k);
							else fprintf(fp, "%d %d ", -((i - 1) * 6 + j), -((i - 1) * 6 + j + 6 * k));
						}
						fprintf(fp, "0\n");
					}
				}
				else if (w == 6) {       //����Ϊ�� 
					for (j = 1; j <= 6; j++) {
						fprintf(fp, "%d %d ", -((i - 1) * 6 + j), -((i - 1) * 6 + j + 6 * k));
					}
					fprintf(fp, "0\n");
				}
			}

		}
	}

	for (i = 1; i <= 6; i++) {   //������ 
		for (k = i + 1; k <= 6; k++) {
			for (w = 0; w <= 6; w++) {
				if (w == 0) {
					for (j = 1; j <= 6; j++) {
						fprintf(fp, "%d %d ", i + (j - 1) * 6, k + (j - 1) * 6);
					}
					fprintf(fp, "0\n");
				}
				else if (w == 1) {
					for (r = 1; r <= 6; r++) {       //��ǵ�ǰ���ĸ���Ϊ��
						for (j = 1; j <= 6; j++) {
							if (j == r) fprintf(fp, "%d %d ", -(i + (j - 1) * 6), -(k + (j - 1) * 6));
							else fprintf(fp, "%d %d ", i + (j - 1) * 6, k + (j - 1) * 6);
						}
						fprintf(fp, "0\n");
					}
				}
				else if (w == 2) {
					for (r = 1; r <= 6; r++) {
						for (s = r + 1; s <= 6; s++) {
							for (j = 1; j <= 6; j++) {
								if (j == r || j == s)  fprintf(fp, "%d %d ", -(i + (j - 1) * 6), -(k + (j - 1) * 6));
								else fprintf(fp, "%d %d ", i + (j - 1) * 6, k + (j - 1) * 6);
							}
							fprintf(fp, "0\n");
						}
					}
				}
				else if (w == 3) {  //����Ϊ�� 
					for (r = 1; r < 6; r++) {
						for (s = r + 1; s <= 6; s++) {
							for (t = s + 1; t <= 6; t++) {
								for (j = 1; j <= 6; j++) {
									if (j == r || j == s || j == t) fprintf(fp, "%d %d ", -(i + (j - 1) * 6), -(k + (j - 1) * 6));
									else fprintf(fp, "%d %d ", i + (j - 1) * 6, k + (j - 1) * 6);
								}
								fprintf(fp, "0\n");
							}
						}
					}
				}
				else if (w == 4) {           //�ĸ�Ϊ�� 
					for (r = 1; r <= 6; r++) {
						for (s = r + 1; s <= 6; s++) {
							for (j = 1; j <= 6; j++) {
								if (j == r || j == s)  fprintf(fp, "%d %d ", i + (j - 1) * 6, k + (j - 1) * 6);
								else fprintf(fp, "%d %d ", -(i + (j - 1) * 6), -(k + (j - 1) * 6));
							}
							fprintf(fp, "0\n");
						}
					}
				}
				else if (w == 5) {
					for (r = 1; r <= 6; r++) {       //��ǵ�ǰ���ĸ���Ϊ��
						for (j = 1; j <= 6; j++) {
							if (j == r) fprintf(fp, "%d %d ", i + (j - 1) * 6, k + (j - 1) * 6);
							else fprintf(fp, "%d %d ", -(i + (j - 1) * 6), -(k + (j - 1) * 6));
						}
						fprintf(fp, "0\n");
					}
				}
				else if (w == 6) {       //����Ϊ�� 
					for (j = 1; j <= 6; j++) {
						fprintf(fp, "%d %d ", -(i + (j - 1) * 6), -(k + (j - 1) * 6));
					}
					fprintf(fp, "0\n");
				}
			}
		}
	}
	fclose(fp);
	return OK; //����������֮�䣬������֮�以����ͬ���Ӿ䴢����cnf�ļ���
}

