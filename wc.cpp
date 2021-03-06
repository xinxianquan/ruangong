#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

using namespace std;

int main()
{
	int countchar(FILE*fp);
	int countword(FILE*fp);
	int countline(FILE*fp);
	void rows(FILE*fp);

	FILE *ft;
	int num = 0;
	char  ch, fpname[20] = {};

	while (1)
	{
		printf("wc.exe>");
		scanf("%s\n", &fpname);      //导入文件
		ft = fopen(fpname, "r");    //利用函数fopen对文件fpname进行读操作，并用指针指向fpname
		if (ft == NULL)                //对所导入的文件进行打开判断，失败退出程序
		{
			printf("文件打开失败！\n");
			exit(0);
		}
		ch = getchar();
		if (ch == '>') { printf(">wc.exe:"); } //输入字符'>'进行判断文件导入完成并进入操作命令行
		ch = getchar();
		while (ch != NULL)
		{


			if (ch == '-')
			{
				switch (getchar())        //用switch语句进行命令选择
				{
				case'c':num = countchar(ft);
					rewind(ft);            //当调用完子函数时需将文件指针重新指向文件fpname的开头
					printf("[charnum] %d %s\n", num, fpname); break;
				case'w':num = countword(ft);
					rewind(ft);
					printf("[wordnum] %d %s\n", num, fpname); break;
				case'l':num = countline(ft);
					rewind(ft);
					printf("[linenum] %d %s\n", num, fpname); break;
				case'a':rows(ft); rewind(ft); break;
				default:printf("error!"); break;
				}
				printf(">wc.exe:");
			}
			ch = getchar();
			if (ch == 'e') { fclose(ft); break; }  //若输入字符'e'则关闭所打开的文件，跳出命令选着循环，导入新的文件
		}

	}
	return 0;
}


int countchar(FILE*fp)//计算字符数的子函数
{
	char ch;
	int charnum = 0;
	ch = fgetc(fp);
	while (!feof(fp)) //判断文件是否已结束
	{
		if (ch == '\n')
		{
			ch = fgetc(fp);
		}
		else
		{
			charnum++;
			ch = fgetc(fp);
		}
	}
	return charnum;
}

int countword(FILE*fp)  //计算单词数的子函数
{
	char ch;
	int wordnum = 0;
	ch = fgetc(fp);
	while (!feof(fp))
	{
		if ((unsigned char)isalpha(ch) || (int)ch == '_')//判断获取的字符是否是字母或者是下划线
		{
			ch = fgetc(fp);
			while ((unsigned char)isalnum(ch) || (int)ch == '_')//判断获取的字符是否是字母或者是下划线或者是数字
			{
				ch = fgetc(fp);
			}
			wordnum++;
		}
		ch = fgetc(fp);
	}
	return wordnum;
}

int countline(FILE*fp)  //计算行数的子函数
{
	char ch;
	int linenum = 0;
	ch = fgetc(fp);
	while (!feof(fp))
	{
		if (ch == '\n')   //当读取到换行符时，若下一个获得的字符不是换行符或者不为空时表时已读完此行
		{
			ch = fgetc(fp);
			if (ch != NULL && ch != '\n')
				linenum++;
		}
		ch = fgetc(fp);
	}
	return linenum;
}

void rows(FILE*fp)  //代码行、空行、注释行计算函数
{
	int zsline = 0, dmline = 0, kline = 0;
	char ch;
	ch = fgetc(fp);
	while (!feof(fp))
	{
		if (ch == '/')   //若连续出现两个‘/’符时表示此行为注释行
		{
			ch = fgetc(fp);
			if (ch == '/')
			{
				while (!feof(fp))
				{
					if (ch == '\n') { zsline++; break; }
					ch = fgetc(fp);
				}

			}

		}

		else if (ch == '{' || ch == '}')  //当已读取到字符‘{’、‘}’时，若下一个字符为空格或这是换行符时表示此行为空行
		{
			ch = fgetc(fp);
			if (ch == ' ' || ch == '\n')
			{
				while (!feof(fp))
				{
					if (ch == '\n') { kline++; break; }
					ch = fgetc(fp);
				}
			}
			else if (ch == '/')  //当当已读取到字符‘{’、‘}’时，若下一个字符为‘/’时表示为注释行
			{
				while (!feof(fp))
				{
					if (ch == '\n') { zsline++; break; }
					ch = fgetc(fp);
				}
			}
		}

		else if (ch == ' ' || ch == '\n')
		{
			while (!feof(fp))
			{
				if (ch == '\n') { kline++; break; }
				ch = fgetc(fp);
			}
		}  //当此行都是空格或换行符时表示是空行

		else
		{
			while (!feof(fp))      //当此行有多个不为空符或换行符或‘{’、‘}’符时表示为代码行
			{
				if (ch == '\n')
				{
					ch = fgetc(fp);
					if (ch != NULL && ch != '\n') { dmline++; break; }
				}
				ch = fgetc(fp);
			}
		}
		ch = fgetc(fp);
	}
	printf("[dmlinenum] %d\n", dmline); //显示结果
	printf("[zslinenum] %d\n", zsline);
	printf("[klinenum] %d\n", kline);
}
