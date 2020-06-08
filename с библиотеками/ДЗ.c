#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include "Books.h"
#include "common.h"
#include "Students.h"
#include "either.h"
#define N 100
#define Nplus 20
#define Nchar 100000

int main()
{
	int act = -1, doing = -1;
	char* mas = (char*)malloc(N * sizeof(char));
	user * PUSER = &USER;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (valid() == 0)
		return 0;

	while (PUSER != 0)
	{
		PUSER = auth(PUSER);
		if (PUSER != 0)
		{
			doing = -1;
			if (USER.book == 0 && USER.student == 0)
			{
				printf("У вас нет прав доступа\nКлац!");
				logging("", "Exit", 1);
				deleteconsole();
			}
			if (USER.book == 1 && USER.student == 0)
			{
				menubook();
				logging("", "Exit", 1);
			}
			if (USER.book == 0 && USER.student == 1)
			{
				menustudent();
				logging("", "Exit", 1);
			}
			if (USER.book == 1 && USER.student == 1)
			{
				while (doing != 0)
				{
					printf("\tГлавное меню\n1. Меню книг\n2. Меню студентов\n0. Выход\nВаш выбор: ");
					scanstr(mas);
					doing = MYatoi(mas);
					switch (doing)
					{
					case 0:
					{
						doing = 0;
						printf("Вы вышли, клацните");
						logging("", "Exit", 1);
						deleteconsole();
						break;
					}
					case 1:
					{
						system("cls");
						menubook();
						break;
					}
					case 2:
					{
						system("cls");
						menustudent();
						break;
					}
					default:
					{
						printf("ГЫГЫГЫ, КАК СМЕШНО, ПИШЁВ ВОН ОТСЮДА");
						return 0;
						break;
					}
					}
				}
			}
		}
		else
		{
			printf("Спасибо за использование!");
			free(mas);
			return 0;
		}
	}
}