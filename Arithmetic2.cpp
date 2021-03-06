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
	void rcommad(int m);   //实现参数r的函数
	void ncommad(int n);    //实现参数n的函数
	char ch[2];
	int num;
	while (1)
	{
		printf("test.cpp>");
		scanf("%s",ch);
		getchar();
		if (strcmp(ch,"-n")==0)
		{
			printf("请输入参数n的值：");
			scanf("%d", &num);
			getchar();
			ncommad(num);
		}
		else if(strcmp(ch,"-r")==0)
		{
			printf("请输入参数r的值：");
			scanf("%d", &num);
			getchar();
			rcommad(num);
		}
		system("pause");    //程序运行完后停顿，输入任意键后，将屏幕清屏后继续运行程序
		system("cls");
	}
	return 0;
}


void rcommad(int m)
{
	void generatearithmetic(int n, int m);
	int n;
	char ch[10];
	printf("test.cpp>");
	scanf("%s", &ch);
	getchar();
	if (strcmp(ch, "-n") == 0)
	{
		printf("请输入参数n的值：");
		scanf("%d", &n);
		getchar();
		generatearithmetic(n, m);
	}
	else
	{
		printf("error!参数n没有赋值，请输入需要产生的题目数量\n");
		rcommad(m);
	}

}

void ncommad(int n)
{
	void generatearithmetic(int n, int m);
	int m;
	char ch[10];
	printf("test.cpp>");
	scanf("%s", &ch);
	getchar();
	if (strcmp(ch, "-r") == 0)
	{
		printf("请输入参数r的值：");
		scanf("%d", &m);
		getchar();
		generatearithmetic(n, m);
	}
	else
	{
		printf("error!参数r没有赋值，请输入题目中数值（自然数、真分数和真分数分母）的范围\n");
		ncommad(n);
	}

}

void generatearithmetic(int n,int m)  //生成表达式的函数
{
	void level_1(int n, int m,int nm);  //单运算符算术表达式产生函数
	void level_2(int n, int m);  //双运算符算术表达式产生函数
	void  answerschar(int m);   //获取键盘输入运算结果的函数
	void Grade(int m);          //统计成绩结果的函数

	FILE *fpan;
	char Filewirteanswers[] = "wirteanswers.txt";
	char gchar[10];
	int nm;

	fpan = fopen(Filewirteanswers, "w");     //生成键盘输入运算结果的文本文件
	if (fpan == NULL)
	{
		printf("open anfile fail!");
	}
	nm = n / 2;
	if (n%2==0)
	{
		   
			level_1(n/2,m,nm);
			level_2(n/2,m);
			printf("\n请输入你的答案（每道题的答案用回车键作结束）：\n");
			printf("(提示：真分式书写方式：3'5/8)\n");
			for (int i = 0; i < n; i++)
			{
				scanf("%s", gchar);
				fprintf(fpan, "%s", gchar);
				fputc('\n', fpan);
			}
			fclose(fpan);
			answerschar(n);
			Grade(n);
	}
	else
	{
		level_1((n / 2)+1, m,nm);
		level_2(n / 2, m);
		printf("\n请输入你的答案（每道题的答案用回车键作结束）：\n");
		printf("(提示：真分式书写方式：3'5/8)\n");
		for (int i = 0; i < n; i++)
		{
			scanf("%s", gchar);
			fprintf(fpan, "%s", gchar);
			fputc('\n', fpan);
		}
		fclose(fpan);
		answerschar(n);
		Grade(n);
	}

}


void level_1(int n, int m,int nm) //产生单运算符的表达式
{
	void Answers(int num, FILE *fpanswers);
	void Exercises(int rdnum[], char rdchar[], int rd_num, int rd_char,FILE *fpexercises);
	void ncommad(int n);

	char AFile[] = "Answers.txt";
	char EFile[] = "Exercises.txt";
	char YSF[] = { '+','-','*','/' };
	int rdnum[2], num;
	char rdchar[2];
	int rd_num = 2, rd_char = 1;
	FILE *fpanswers,*fpexercises;

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

	if (m!=1)
	{
		for (int j = 0; j < n; j++)
		{
			rdchar[0] = YSF[rand() % 4];     //随机生成运算符
			for (int i = 0; i < 2; i++)
			{
				rdnum[i] = rand() % m;       //生成随机数
				while (rdnum[i] == 0 || rdnum[i] < 0)
				{
					rdnum[i] = rand() % m;
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
	}
	else
	{
		printf("r该参数没有实际意义！请从新输入！\n");
	    ncommad(n+nm);
	}
	fclose(fpanswers);
	fclose(fpexercises);
}

void level_2(int n, int m)  //产生双运算符的表达式
{
	void Answers(int num, FILE *fpanswers);
	void Exercises(int rdnum[], char rdchar[], int rd_num, int rd_char, FILE *fpexercises);
	void ncommad(int n);

	char EFile[] = "Exercises.txt";
	char AFile[] = "Answers.txt";
	char YSF[] = { '+','-','*','/' };
	int rdnum[3], num;
	char rdchar[2];
	int rd_num = 3, rd_char = 2;
	FILE *fpanswers, *fpexercises;

	fpanswers = fopen(AFile, "a");       //生成算术表达式自动计算结果的文本文件
	if (fpanswers == NULL)
	{
		printf("open Afile fail!");
	}

	fpexercises = fopen(EFile, "a");     //生成算是表达式的文本文件
	if (fpexercises == NULL)
	{
		printf("open Efile fail!");
	}

	srand((int)time(0) * 200);       //设置随机数种子

	for (int j = 0; j < n; j++)
		{
			for (int i = 0; i < 2; i++)
			{
				rdchar[i] = YSF[rand() % 4];     //随机生成运算符
			}

			for (int i = 0; i < 3; i++)
			{
				rdnum[i] = rand() % m;       //生成随机数
				while (rdnum[i] == 0)
				{
					rdnum[i] = rand() % m;
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
						else
						{
							fprintf(fpanswers, "%d", num / rdnum[2]);
							fputc('\'', fpanswers);
							fprintf(fpanswers, "%d", num % rdnum[2]);
							fputc('/', fpanswers);
							fprintf(fpanswers, "%d", rdnum[2]);
							fputc('\n', fpanswers);
							Exercises(rdnum, rdchar, rd_num, rd_char, fpexercises);
							break;
						}
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
							fprintf(fpanswers, "%d", (rdnum[0] * rdnum[2]) / rdnum[1]);
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
	for (int j=0;j<m;j++)     //将生成的答案输出到屏幕
	{
		if(!feof(fpA))
		{
			fgets(ch, 20, fpA);
			printf("%s",ch);
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