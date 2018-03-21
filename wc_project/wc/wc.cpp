#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<io.h>
#define N 100

char ch;
char token[N] = { '\0' };
int n = 0;
int num = 0;
char filesName[10][30] = {};
int file_num = 0;
FILE* fp;
int flag[7] = { 0 };//区分功能

int char_num = 0;
int word_num = 0;
int line_num = 0;
int note_num = 0;
int none_num = 0;

char stopWord[100] = {};
int stop_num=0;

char art[1000] = { '\0' };
char* sta = art;
char* word_list[100];

void get()
{
	ch = *sta;
	sta++;
}
void clearToken()
{
	for (int i = 0; i<N; i++)
		token[i] = '\0';
	n = 0;
}
bool isSpace(char a)
{
	if (a == ' ')
		return true;
	return false;
}
bool isNewline(char a)
{
	if (a == '\n')
		return true;
	return false;
}
bool isTab(char a)
{
	if (a == '\t')
		return true;
	return false;
}
bool isEnd(char a)
{
	if (a == EOF)
		return true;
	return false;
}
bool isComma(char a)
{
	if (a == ',')
		return true;
	return false;
}
bool isSemi(char a)
{
	if (a == ';')
		return true;
	return false;
}
bool isDivi(char a)
{
	if (a == '/')
		return true;
	return false;
}
bool isStar(char a)
{
	if (a == '*')
		return true;
	return false;
}
void catToken(char a)
{
	token[n] = a;
	n++;
}
void retract()
{
	sta--;
}

void none()//统计空行数
{
	int i,j = 0;
	for (i = 0;; i++)
	{
		if (art[i] == EOF)
			break;
		if (art[i] != '\n'&& art[i] != '\t'&& art[i] != ' ')
		{
			j++;
		}
		if (art[i] == '\n')
		{
			if (j <= 1)
				none_num++;
			j = 0;
		}
	}
}

int count()//统计单词数、行数、注释行数
{
	get();
	clearToken();
	while (isSpace(ch) || isNewline(ch) || isTab(ch) || isComma(ch))
	{
		if (isNewline(ch)) line_num++;
		get();
	}
	if (isStar(ch))
	{
		catToken(ch);
	}
	else if (isDivi(ch))
	{
		catToken(ch);
		get();
		if (isStar(ch))
		{
			note_num++;
			catToken(ch);
			do
			{
				do
				{
					get();
					if (isNewline(ch))
					{
						note_num++;
						line_num++;
					}

				} while (!isStar(ch));
				do
				{
					get();
					if (isNewline(ch))
					{
						note_num++;
						line_num++;
					}
					if (isDivi(ch))
					{
						catToken(ch);
						return 0;
					}
				} while (isStar(ch));
			} while (!isStar(ch));
		}
		if (isDivi(ch))
		{
			catToken(ch);
			do
			{
				get();
			} while (!isNewline(ch));
			note_num++;
		}
		if (isNewline(ch))
			line_num++;
	}
	else if (isEnd(ch))
		return 0;
	else
	{
		while (!(isSpace(ch) || isNewline(ch) || isTab(ch) || isComma(ch) || isDivi(ch)))
		{
			catToken(ch);
			get();
		}
		retract();
		if(strcmp(stopWord, "") == 0 || strcmp(token,stopWord)!=0)
		   word_num++;
	}
	return 0;
}

int main(char argc, char* argv[])
{

	if (argc<3)
		printf("请在控制台输入正确命令!\n");
	else
	{
		if (strcmp(argv[0], "wc.exe") != 0)
			printf("可执行文件名输入错误!\n");
		else
		{
			for (int i = 1; i<argc; i++)
			{
				if (strcmp(argv[i], "-c") == 0)
				{
					flag[0] = 1;
				}
				else if (strcmp(argv[i], "-w") == 0)
				{
					flag[1] = 1;
				}
				else if (strcmp(argv[i], "-l") == 0)
				{
					flag[2] = 1;
				}
				else if (strcmp(argv[i], "-o") == 0)
				{
					flag[3] = 1;
				}
				else if (strcmp(argv[i], "-s") == 0)
				{
					flag[4] = 1;
				}
				else if (strcmp(argv[i], "-a") == 0)
				{
					flag[5] = 1;
				}
				else if (strcmp(argv[i], "-e") == 0)
				{
					flag[6] = 1;
				}
			}
		}
	}

	if (flag[4] == 1)
	{
		_finddata_t sFind;
		long lResult = 0;
		lResult = _findfirst("*.c", &sFind);
		if (lResult == -1) {
			printf("没有找到文件。");
			return 0;
		}

		int i=0,len;
		do {
			len = strlen(sFind.name);
			strcpy_s(filesName[i], len + 1, sFind.name);//将所有读到的保存到filesname
			file_num++;
			i++;
		} while (_findnext(lResult, &sFind) != -1);
	
		for (int j = 0; j < file_num; j++)
		{
			fopen_s(&fp, filesName[j], "r");
			if (fp == NULL)
				printf("error!\n");
			int i = 0;
			do//获取文件内容
			{
				ch = fgetc(fp);
				art[i++] = ch;
			} while (ch != EOF);
			fclose(fp);
			char_num = i;

			if (flag[6] == 1)//获取停用词
			{
				fopen_s(&fp, "stopList.txt", "a");
				fgets(stopWord, 20, fp);
				fclose(fp);
			}
			do//核心统计
			{
				count();
			} while (!isEnd(ch));
			none();
	
			if (flag[0] == 1)
				printf("%s,字符数: %d \n", filesName[j], char_num);
			if (flag[1] == 1)
				printf("%s,单词数: %d \n", filesName[j], word_num);
			if (flag[2] == 1)
				printf("%s,总行数: %d \n", filesName[j], line_num);
			if (flag[3] == 1)
			{
				fopen_s(&fp, argv[argc - 1], "a");
				if (flag[0] == 1)
					fprintf(fp, "%s,字符数: %d \n", filesName[j], char_num);
				if (flag[1] == 1)
					fprintf(fp,"%s,单词数: %d \n", filesName[j], word_num);
				if (flag[2] == 1)
					fprintf(fp,"%s,总行数: %d \n", filesName[j], line_num);
				if (flag[5] == 1)
					fprintf(fp, "%s,代码行/空行/注释行: %d/%d/%d \n", filesName[j], line_num - note_num - none_num, none_num, note_num);
				fclose(fp);
			}
			if (flag[5] == 1)
				printf("%s,代码行/空行/注释行: %d/%d/%d \n", filesName[j], line_num - note_num - none_num, none_num, note_num);
			strcpy_s(stopWord,1,"");
			for (int i = 0; i < 1000; i++)
				art[i] = '\0';
			sta = art;
			char_num = 0;
			word_num = 0;
			line_num = 0;
		    note_num = 0;
			none_num = 0;
		}
	}

	else
	{
		fopen_s(&fp, "file.c", "r");
		if (fp == NULL)
			printf("error!\n");
		int i = 0;
		do
		{
			ch = fgetc(fp);
			art[i++] = ch;
		} while (ch != EOF);
		fclose(fp);
		char_num = i;

		if (flag[6] == 1)
		{
			fopen_s(&fp, "stopList.txt", "r");
			fgets(stopWord, 20, fp);
			fclose(fp);
		}
		do
		{
			count();
		} while (!isEnd(ch));
		none();

		if (flag[0] == 1)
			printf("file.c,字符数: %d \n", char_num);
		if (flag[1] == 1)
			printf("file.c,单词数: %d \n", word_num);
		if (flag[2] == 1)
			printf("file.c,总行数: %d \n", line_num);
		if (flag[3] == 1)
		{
			fopen_s(&fp, argv[argc - 1], "w");
			if (flag[0] == 1)
				fprintf(fp, "file.c,字符数: %d \n", char_num);
			if (flag[1] == 1)
				fprintf(fp, "file.c,单词数: %d \n", word_num);
			if (flag[2] == 1)
				fprintf(fp, "file.c,总行数: %d \n", line_num);
			if (flag[5] == 1)
				fprintf(fp, "file.c,代码行/空行/注释行: %d/%d/%d \n", line_num - note_num - none_num, none_num, note_num);
			fclose(fp);
		}
		if (flag[5] == 1)
			printf("file.c,代码行/空行/注释行: %d/%d/%d \n", line_num - note_num - none_num, none_num, note_num);
	}
	printf("\n");
	system("pause");
	return 0;
}