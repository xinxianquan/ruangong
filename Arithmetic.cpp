
#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include<time.h>  
#include<string.h>
#include<ctype.h>


int main()
{
	int level_1(int n, int m);  //单运算符算术表达式产生函数
	int level_2(int n, int m);  //双运算符算术表达式产生函数
	void  answerschar(int m);   //获取键盘输入运算结果的函数
	void Grade(int m);          //统计成绩结果的函数

	FILE *fpan;
	char Filewirteanswers[] = "wirteanswers.txt";
	int n, m;
	char leve, gchar[10];
	while (1)
	{
		fpan = fopen(Filewirteanswers, "w");     //生成键盘输入运算结果的文本文件
		if (fpan == NULL)
		{
			printf("open anfile fail!");
		}
		printf("请输入出现的数值的最大值：");
		scanf("%d", &n);
		getchar();
		printf("\n请输入需要的题目数量：");
		scanf("%d", &m);
		getchar();
		printf("请选择题目难度：\n");
		printf("1[单运算符]\n");
		printf("2[双运算符]\n");
		printf("选着难度：");
		scanf("%c", &leve);
		getchar();
		switch (leve)
		{
		case'1':level_1(n, m);
			printf("\n请输入你的答案（每道题的答案用回车键作结束）：\n");
			printf("(提示：真分式书写方式：3'5/8)\n");
			for (int i = 0; i < m; i++)
			{
				scanf("%s", gchar);
				fprintf(fpan, "%s", gchar);
				fputc('\n', fpan);
			}
			fclose(fpan);
			answerschar(m);
			Grade(m);
			break;
		case'2':level_2(n, m);
			printf("\n请输入你的答案（每道题的答案用回车键作结束）：\n");
			printf("(提示：真分式书写方式：3'5/8)\n");
			for (int i = 0; i < m; i++)
			{
				scanf("%s", gchar);
				fprintf(fpan, "%s", gchar);
				fputc('\n', fpan);
			}
			fclose(fpan);
			answerschar(m);
			Grade(m);
			break;
		default:printf("error!"); break;
		}

		system("pause");    //程序运行完后停顿，输入任意键后，将屏幕清屏后继续运行程序
		system("cls");
	}
	return 0;
}


int level_1(int n, int m)
{
	void Answers(int num, FILE *fpanswers);
	void Exercises(int rdnum[], char rdchar[], int rd_num, int rd_char, FILE *fpexercises);

	char AFile[] = "Answers.txt";
	char EFile[] = "Exercises.txt";
	char YSF[] = { '+','-','*','/' };
	int rdnum[2], num;
	char rdchar[2];
	int rd_num = 2, rd_char = 1;
	FILE *fpanswers, *fpexercises;

	fpanswers = fopen(AFile, "w");      //生成算术表达式自动计算结果的文本文件
	if (fpanswers == NULL)
	{
		printf("open Afile fail!");
	}

	fpexercises = fopen(EFile, "w");    //生成算术表达式的文本文件
	if (fpexercises == NULL)
	{
		printf("open Efile fail!");
	}


	srand((int)time(0) * 200);         //以时间作为随机数的种子

	for (int j = 0; j < m; j++)
	{
		rdchar[0] = YSF[rand() % 4];     //随机生成运算符
		for (int i = 0; i < 2; i++)
		{
			rdnum[i] = rand() % n;       //生成随机数
			while (rdnum[i] == 0 || rdnum[i] < 0)
			{
				rdnum[i] = rand() % n;
			}
		}
		switch (rdchar[0])     //判断运算符然后计算结果
		{
		case '+':
			num = rdnum[1] + rdnum[0];
			Answers(num, fpanswers);
			Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises); break;
		case'-':
			if (rdnum[1] > rdnum[0])
			{
				num = rdnum[1];
				rdnum[1] = rdnum[0];
				rdnum[0] = num;
			}
			num = rdnum[0] - rdnum[1];
			Answers(num, fpanswers);
			Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises); break;
		case'*':
			num = rdnum[1] * rdnum[0];
			Answers(num, fpanswers);
			Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises); break;
		case'/':
			if (rdnum[0] % rdnum[1] == 0)
			{
				fprintf(fpanswers, "%d", rdnum[0] / rdnum[1]);
				fputc('\n', fpanswers);
				Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises); break;
			}
			else
			{
				if (rdnum[1] > rdnum[0])
				{

					fprintf(fpanswers, "%d", rdnum[0]);
					fputc('/', fpanswers);
					fprintf(fpanswers, "%d", rdnum[1]);
					fputc('\n', fpanswers);
				}
				else
				{
					num = rdnum[0] / rdnum[1];
					fprintf(fpanswers, "%d", num);
					fputc('\'', fpanswers);
					num = rdnum[0] % rdnum[1];
					fprintf(fpanswers, "%d", num);
					fputc('/', fpanswers);
					fprintf(fpanswers, "%d", rdnum[1]);
					fputc('\n', fpanswers);

				}
				Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises); break;
			}
		default:break;
		}
	}

	fclose(fpanswers);
	fclose(fpexercises);
	return 0;
}

int level_2(int n, int m)
{
	void Answers(int num, FILE *fpanswers);
	void Exercises(int rdnum[], char rdchar[], int rd_num, int rd_char, FILE *fpexercises);

	char EFile[] = "Exercises.txt";
	char AFile[] = "Answers.txt";
	char YSF[] = { '+','-','*','/' };
	int rdnum[3], num;
	char rdchar[2];
	int rd_num = 3, rd_char = 2;
	FILE *fpanswers, *fpexercises;

	fpanswers = fopen(AFile, "w");       //生成算术表达式自动计算结果的文本文件
	if (fpanswers == NULL)
	{
		printf("open Afile fail!");
	}

	fpexercises = fopen(EFile, "w");     //生成算是表达式的文本文件
	if (fpexercises == NULL)
	{
		printf("open Efile fail!");
	}

	srand((int)time(0) * 200);       //设置随机数种子

	for (int j = 0; j < m; j++)
	{
		for (int i = 0; i < 2; i++)
		{
			rdchar[i] = YSF[rand() % 4];     //随机生成运算符
		}

		for (int i = 0; i < 3; i++)
		{
			rdnum[i] = rand() % n;       //生成随机数
			while (rdnum[i] == 0)
			{
				rdnum[i] = rand() % n;
			}
		}

		switch (rdchar[0])        //判断运算符然后计算表达式的度结果
		{
		case'+':
			switch (rdchar[1])
			{
			case'+':num = rdnum[2] + rdnum[1] + rdnum[0];
				Answers(num, fpanswers);
				Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
				break;
			case'-':if (rdnum[0] + rdnum[1] < rdnum[2])
			{
				num = rdnum[2];
				rdnum[2] = rdnum[0];
				rdnum[0] = num;
			}
					num = rdnum[0] + rdnum[1] - rdnum[2];
					Answers(num, fpanswers);
					Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
					break;
			case'*':num = rdnum[0] + rdnum[1] * rdnum[2];
				Answers(num, fpanswers);
				Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
				break;
			case'/':
				if (rdnum[1] % rdnum[2] == 0)
				{
					num = rdnum[0] + rdnum[1] / rdnum[2];
					fprintf(fpanswers, "%d", num);
					fputc('\n', fpanswers);
					Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
					break;
				}
				else
				{
					if (rdnum[1] > rdnum[2])
					{
						num = rdnum[0] + rdnum[1] / rdnum[2];
						fprintf(fpanswers, "%d", num);
						fputc('\'', fpanswers);
						num = rdnum[1] % rdnum[2];
						fprintf(fpanswers, "%d", num);
						fputc('/', fpanswers);
						fprintf(fpanswers, "%d", rdnum[2]);
						fputc('\n', fpanswers);
					}
					else
					{
						fprintf(fpanswers, "%d", rdnum[0]);
						fputc('\'', fpanswers);
						fprintf(fpanswers, "%d", rdnum[1]);
						fputc('/', fpanswers);
						fprintf(fpanswers, "%d", rdnum[2]);
						fputc('\n', fpanswers);
					}
					Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
					break;
				}
			default:printf("error!"); break;
			}
			break;
		case'-':
			switch (rdchar[1])
			{
			case'+':
				if ((rdnum[0] - rdnum[1] + rdnum[2]) < 0)
				{
					num = rdnum[1];
					rdnum[1] = rdnum[2];
					rdnum[2] = num;
				}
				num = rdnum[0] - rdnum[1] + rdnum[2];
				Answers(num, fpanswers);
				Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
				break;
			case'-':
				if ((rdnum[0] - rdnum[1] - rdnum[2]) < 0)
				{
					if (rdnum[0] - (rdnum[1] - rdnum[2]) < 0)
					{
						num = rdnum[1];
						rdnum[1] = rdnum[0];
						rdnum[0] = num;
					}
					num = rdnum[0] - (rdnum[1] - rdnum[2]);
					Answers(num, fpanswers);
					for (int i = 0; i < rd_num; i++)
					{
						fprintf(fpexercises, "%d", rdnum[i]);
						fputc(' ', fpexercises);
						printf("%d", rdnum[i]);
						if (rd_char > i)
						{
							fprintf(fpexercises, "%c", rdchar[i]);
							fputc(' ', fpexercises);
							printf("%c", rdchar[i]);
							if (i == 0)
							{
								fputs("( ", fpexercises);
								printf("(");
							}
						}
					}
					printf(")=\n");
					fputs(") =\n", fpexercises);
					break;
				}
				num = rdnum[0] - rdnum[1] - rdnum[2];
				Answers(num, fpanswers);
				Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
				break;
			case'*':
				if ((rdnum[0] - (rdnum[1] * rdnum[2])) < 0)
				{
					if (rdnum[0] < rdnum[1])
					{
						num = rdnum[1];
						rdnum[1] = rdnum[0];
						rdnum[0] = num;
					}

					num = (rdnum[0] - rdnum[1]) * rdnum[2];
					Answers(num, fpanswers);
					for (int i = 0; i < rd_num; i++)
					{
						if (i == 0)
						{
							fputs("( ", fpexercises);
							printf("(");
						}
						fprintf(fpexercises, "%d", rdnum[i]);
						fputc(' ', fpexercises);
						printf("%d", rdnum[i]);
						if (i == 1)
						{
							fputs(") ", fpexercises);
							printf(")");
						}
						if (rd_char > i)
						{
							fprintf(fpexercises, "%c", rdchar[i]);
							fputc(' ', fpexercises);
							printf("%c", rdchar[i]);
						}
					}
					printf("=\n");
					fputs("=\n", fpexercises);
					break;
				}
				num = rdnum[0] - rdnum[1] * rdnum[2];
				Answers(num, fpanswers);
				Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
				break;
			case'/':
				if ((rdnum[0] - (rdnum[1] / rdnum[2])) < 0)
				{
					if (rdnum[0] < rdnum[1])
					{
						num = rdnum[1];
						rdnum[1] = rdnum[0];
						rdnum[0] = num;
					}
					num = rdnum[0] - rdnum[1];
					if (num %rdnum[2] == 0)
					{
						fprintf(fpanswers, "%d", num / rdnum[2]);
						fputc('\n', fpanswers);
					}
					else
					{
						if (num < rdnum[2])
						{
							fprintf(fpanswers, "%d", num);
							fputc('/', fpanswers);
							fprintf(fpanswers, "%d", rdnum[2]);
							fputc('\n', fpanswers);
						}
						else
						{
							fprintf(fpanswers, "%d", num / rdnum[2]);
							fputc('\'', fpanswers);
							fprintf(fpanswers, "%d", num%rdnum[2]);
							fputc('/', fpanswers);
							fprintf(fpanswers, "%d", rdnum[2]);
							fputc('\n', fpanswers);
						}
					}
					for (int i = 0; i < rd_num; i++)
					{
						if (i == 0)
						{
							fputs("( ", fpexercises);
							printf("(");
						}
						fprintf(fpexercises, "%d", rdnum[i]);
						fputc(' ', fpexercises);
						printf("%d", rdnum[i]);
						if (i == 1)
						{
							fputs(") ", fpexercises);
							printf(")");
						}
						if (rd_char > i)
						{
							fprintf(fpexercises, "%c", rdchar[i]);
							fputc(' ', fpexercises);
							printf("%c", rdchar[i]);
						}
					}
					printf("=\n");
					fputs("=\n", fpexercises);
					break;
				}
				else
				{
					if (rdnum[1] % rdnum[2] == 0)
					{
						num = rdnum[1] / rdnum[2];
						fprintf(fpanswers, "%d", rdnum[0] - num);
						fputc('\n', fpanswers);
					}
					else
					{
						num = rdnum[1] / rdnum[2];
						if (rdnum[0] - num - 1 == 0)
						{
							num = rdnum[2] - (rdnum[1] % rdnum[2]);
							fprintf(fpanswers, "%d", num);
							fputc('/', fpanswers);
							fprintf(fpanswers, "%d", rdnum[2]);
							fputc('\n', fpanswers);
						}
						else
						{
							fprintf(fpanswers, "%d", rdnum[0] - num - 1);
							fputc('\'', fpanswers);
							num = rdnum[2] - (rdnum[1] % rdnum[2]);
							fprintf(fpanswers, "%d", num);
							fputc('/', fpanswers);
							fprintf(fpanswers, "%d", rdnum[2]);
							fputc('\n', fpanswers);
						}
					}
					Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
					break;
				}
			default:printf("error!"); break;
			}
			break;
		case'*':
			switch (rdchar[1])
			{
			case'+':num = rdnum[0] * rdnum[1] + rdnum[2];
				Answers(num, fpanswers);
				Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
				break;
			case'-':
				if ((rdnum[0] * rdnum[1] - rdnum[2]) < 0)
				{
					if (rdnum[1] < rdnum[2])
					{
						num = rdnum[2];
						rdnum[2] = rdnum[1];
						rdnum[1] = num;
					}

					num = rdnum[0] * (rdnum[1] - rdnum[2]);
					for (int i = 0; i < rd_num; i++)
					{
						fprintf(fpexercises, "%d", rdnum[i]);
						fputc(' ', fpexercises);
						printf("%d", rdnum[i]);
						if (rd_char > i)
						{
							fprintf(fpexercises, "%c", rdchar[i]);
							fputc(' ', fpexercises);
							printf("%c", rdchar[i]);
							if (i == 0)
							{
								fputs("( ", fpexercises);
								printf("(");
							}
						}
					}
					printf(")=\n");
					fputs(") =\n", fpexercises);
					Answers(num, fpanswers);
					break;
				}
				num = rdnum[0] * rdnum[1] - rdnum[2];
				Answers(num, fpanswers);
				Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
				break;
			case'*':num = rdnum[0] * rdnum[1] * rdnum[2];
				Answers(num, fpanswers);
				Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
				break;
			case'/':
				num = rdnum[0] * rdnum[1];
				if (num%rdnum[2] == 0)
				{
					num = rdnum[0] * rdnum[1] / rdnum[2];
					Answers(num, fpanswers);
					Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
					break;
				}
				else
				{
					if (num < rdnum[2])
					{
						fprintf(fpanswers, "%d", num);
						fputc('/', fpanswers);
						fprintf(fpanswers, "%d", rdnum[2]);
						fputc('\n', fpanswers);
						Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
						break;
					}
					num = num / rdnum[2];
					fprintf(fpanswers, "%d", num);
					fputc('\'', fpanswers);
					num = num % rdnum[2];
					fprintf(fpanswers, "%d", num);
					fputc('/', fpanswers);
					fprintf(fpanswers, "%d", rdnum[2]);
					fputc('\n', fpanswers);
					Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
					break;
				}
			default:break;
			}
			break;
		case'/':
			switch (rdchar[1])
			{
			case'+':
				num = (rdnum[0] / rdnum[1]) + rdnum[2];
				fprintf(fpanswers, "%d", num);
				if (rdnum[0] % rdnum[1] != 0)
				{
					if (rdnum[0] > rdnum[1])
					{
						fputc('\'', fpanswers);
						num = rdnum[0] % rdnum[1];
						fprintf(fpanswers, "%d", num);
						fputc('/', fpanswers);
						fprintf(fpanswers, "%d", rdnum[1]);
						fputc('\n', fpanswers);
						Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
						break;
					}
					else
					{
						fputc('\'', fpanswers);
						fprintf(fpanswers, "%d", rdnum[0]);
						fputc('/', fpanswers);
						fprintf(fpanswers, "%d", rdnum[1]);
						fputc('\n', fpanswers);
						Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
						break;
					}
				}
				fputc('\n', fpanswers);
				Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
				break;

			case'-':
				if ((rdnum[0] / rdnum[1]) - rdnum[2] < 0)
				{
					if (rdnum[1] < rdnum[2])
					{
						num = rdnum[2];
						rdnum[2] = rdnum[1];
						rdnum[1] = num;
					}
					num = rdnum[0] / (rdnum[1] - rdnum[2]);
					if (rdnum[0] % (rdnum[1] - rdnum[2]) == 0)
					{
						fprintf(fpanswers, "%d", num);
						fputc('\n', fpanswers);
					}
					else
					{
						if (rdnum[0] < (rdnum[1] - rdnum[2]))
						{
							fprintf(fpanswers, "%d", rdnum[0]);
							fputc('/', fpanswers);
							fprintf(fpanswers, "%d", rdnum[1] - rdnum[2]);
							fputc('\n', fpanswers);
						}
						else
						{
							fprintf(fpanswers, "%d", num);
							fputc('\'', fpanswers);
							num = rdnum[0] % (rdnum[1] - rdnum[2]);
							fprintf(fpanswers, "%d", num);
							fputc('/', fpanswers);
							fprintf(fpanswers, "%d", rdnum[1] - rdnum[2]);
							fputc('\n', fpanswers);
						}
					}
					for (int i = 0; i < rd_num; i++)
					{
						fprintf(fpexercises, "%d", rdnum[i]);
						fputc(' ', fpexercises);
						printf("%d", rdnum[i]);
						if (rd_char > i)
						{
							fprintf(fpexercises, "%c", rdchar[i]);
							fputc(' ', fpexercises);
							printf("%c", rdchar[i]);
							if (i == 0)
							{
								fputs("( ", fpexercises);
								printf("(");
							}
						}
					}
					printf(")=\n");
					fputs(") =\n", fpexercises);
					break;

				}
				else
				{
					num = (rdnum[0] / rdnum[1]) - rdnum[2];
					if ((rdnum[0] % rdnum[1]) == 0)
					{
						fprintf(fpanswers, "%d", num);
						fputc('\n', fpanswers);
						Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
						break;
					}
					else
					{
						if (num == 0)
						{
							num = rdnum[0] % rdnum[1];
							fprintf(fpanswers, "%d", num);
							fputc('/', fpanswers);
							fprintf(fpanswers, "%d", rdnum[1]);
							fputc('\n', fpanswers);
							Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
							break;
						}
						else
						{
							fprintf(fpanswers, "%d", num);
							fputc('\'', fpanswers);
							num = rdnum[0] % rdnum[1];
							fprintf(fpanswers, "%d", num);
							fputc('/', fpanswers);
							fprintf(fpanswers, "%d", rdnum[1]);
							fputc('\n', fpanswers);
							Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
							break;
						}
					}
				}
				break;
			case'*':
				if ((rdnum[0] * rdnum[2]) % rdnum[1] == 0)
				{
					num = (rdnum[0] * rdnum[2]) / rdnum[1];
					fprintf(fpanswers, "%d", num);
					fputc('\n', fpanswers);
				}
				else
				{
					if ((rdnum[0] * rdnum[2]) < rdnum[1])
					{
						fprintf(fpanswers, "%d", rdnum[0] * rdnum[2]);
						fputc('/', fpanswers);
						fprintf(fpanswers, "%d", rdnum[1]);
						fputc('\n', fpanswers);
					}
					else
					{
						num = (rdnum[0] * rdnum[2]) / rdnum[1];
						fprintf(fpanswers, "%d", num);
						fputc('\'', fpanswers);
						num = (rdnum[0] * rdnum[2]) % rdnum[1];
						fprintf(fpanswers, "%d", num);
						fputc('/', fpanswers);
						fprintf(fpanswers, "%d", rdnum[1]);
						fputc('\n', fpanswers);
					}
				}
				Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
				break;
			case'/':
				if (rdnum[0] % (rdnum[1] * rdnum[2]) == 0)
				{
					num = rdnum[0] / (rdnum[1] * rdnum[2]);
					fprintf(fpanswers, "%d", num);
					fputc('\n', fpanswers);
				}
				else
				{
					if (rdnum[0] < (rdnum[1] * rdnum[2]))
					{
						fprintf(fpanswers, "%d", rdnum[0]);
						fputc('/', fpanswers);
						fprintf(fpanswers, "%d", rdnum[1] * rdnum[2]);
						fputc('\n', fpanswers);
					}
					else
					{
						num = rdnum[0] / (rdnum[1] * rdnum[2]);
						fprintf(fpanswers, "%d", num);
						fputc('\'', fpanswers);
						num = rdnum[0] % (rdnum[1] * rdnum[2]);
						fprintf(fpanswers, "%d", num);
						fputc('/', fpanswers);
						fprintf(fpanswers, "%d", rdnum[1] * rdnum[2]);
						fputc('\n', fpanswers);
					}
				}
				Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
				break;
			default:printf("error!"); break;
			}
			break;
		default:printf("error!"); break;
		}

	}

	fclose(fpanswers);
	fclose(fpexercises);
	return 0;
}

void Answers(int num, FILE *fpanswers)   //将自动计算出的结果写进answers文本文件
{
	fprintf(fpanswers, "%d", num);
	fputs("\n", fpanswers);
}

void Exercises(int rdnum[], char rdchar[], int rd_num, int rd_char, FILE  *fpexercises)    //将生成的算术表达式写进exercises文本文件
{
	for (int i = 0; i < rd_num; i++)
	{
		fprintf(fpexercises, "%d", rdnum[i]);
		fputc(' ', fpexercises);
		printf("%d", rdnum[i]);
		if (rd_char > i)
		{
			fprintf(fpexercises, "%c", rdchar[i]);
			fputc(' ', fpexercises);
			printf("%c", rdchar[i]);
		}
	}
	printf("=\n");
	fputs("=\n", fpexercises);
}

void Grade(int m)   //将成绩写入Grade文本文件
{
	FILE *fpG, *fpG1, *fpG2, *fpA;
	char FileGrade[] = "Grade.txt";
	char FileGrade1[] = "correctGrade.txt";
	char FileGrade2[] = "wrongGrade.txt";
	char FileAnswers[] = "Answers.txt";
	char grade, ch[20];

	fpG1 = fopen(FileGrade1, "r");   //对存储答对的题号和总数的文本文件经行读操作
	if (fpG1 == NULL)
	{
		printf("open Grade1file fail!");
	}

	fpG2 = fopen(FileGrade2, "r");   //对存储答错的题号和总数的文本文件经行读操作
	if (fpG2 == NULL)
	{
		printf("open Grade2file fail!");
	}

	fpG = fopen(FileGrade, "w");     //生成存储最终成绩的Grade文件
	if (fpG == NULL)
	{
		printf("open Gradefile fail!");

	}

	while (!feof(fpG1))       //将答对的题号和总数写如Grade文件
	{
		grade = fgetc(fpG1);
		fprintf(fpG, "%c", grade);
		printf("%c", grade);
	}
	fputc('\n', fpG);
	printf("\n");
	while (!feof(fpG2))     //将答错的题号和总数写如Grade文件
	{
		grade = fgetc(fpG2);
		fprintf(fpG, "%c", grade);
		printf("%c", grade);
	}
	fputc('\n', fpG);
	printf("\n");

	fclose(fpG);
	fclose(fpG1);
	fclose(fpG2);

	fpA = fopen(FileAnswers, "r");     //对存储生成的答案的文件进行读操作
	if (fpA == NULL)
	{
		printf("open Answersfile fail!");
	}
	printf("标准答案为：\n");
	for (int j = 0; j < m; j++)     //将生成的答案输出到屏幕
	{
		if (!feof(fpA))
		{
			fgets(ch, 20, fpA);
			printf("%s", ch);
		}
	}
	fclose(fpA);
}

void  answerschar(int m)
{
	FILE *fpG1, *fpG2, *fpA, *fpan;
	char FileGrade1[] = "correctGrade.txt";
	char FileGrade2[] = "wrongGrade.txt";
	char FileAnswers[] = "Answers.txt";
	char Fileanch[] = "wirteanswers.txt";
	char gch[10], anch[10];
	int wrongnum = 0, correctnum = 0;

	fpan = fopen(Fileanch, "r");
	if (fpan == NULL)
	{
		printf("open anfile fail!");
	}

	fpG1 = fopen(FileGrade1, "w");     //生成存储答对的题号和总数的文件
	if (fpG1 == NULL)
	{
		printf("open Grade1file fail!");
	}

	fpG2 = fopen(FileGrade2, "w");  //生成存储答错的题号和总数的文件
	if (fpG2 == NULL)
	{
		printf("open Grade2file fail!");
	}


	fpA = fopen(FileAnswers, "r");
	if (fpA == NULL)
	{
		printf("open Answersfile fail!");
	}

	fputs("correct(", fpG1);
	fputs("wrong(", fpG2);
	for (int i = 0; i < m; i++)        //对存储键盘输入的答案的文件进行读操作
	{
		if (!feof(fpan))
		{
			fgets(gch, 10, fpan);
		}

		if (!feof(fpA))              //对存储自动生成的答案的文件进行读操作
		{
			fgets(anch, 10, fpA);
		}

		if (strcmp(anch, gch) == 0)   //比较键盘输入的答案和生成的答案是否一致
		{
			correctnum++;
			fprintf(fpG1, "%d", i + 1);   //答案一致，写入题号并答对总数加一
			fputc(',', fpG1);
		}
		else
		{
			wrongnum++;
			fprintf(fpG2, "%d", i + 1);   //答案不一致，写入题号并答错总数加一
			fputc(',', fpG2);
		}

	}
	fputc(')', fpG1);
	fputc(')', fpG2);
	fprintf(fpG1, "%d", correctnum);
	fprintf(fpG2, "%d", wrongnum);

	fclose(fpA);
	fclose(fpan);
	fclose(fpG1);
	fclose(fpG2);

}