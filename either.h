#pragma once
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
#define N 100
#define Nplus 20
#define Nchar 100000
typedef struct user {
	char login[N];
	char password[N];
	int book;
	int student;
}user;
user* auth(user*);
user USER;
typedef struct StudBook {
	double ISBN;
	char book[7];
	char date[11];
}StudBook;
StudBook* SBrazbienie(int*);
typedef struct log {
	char date[20];
	char user[N];
	char step[N];
	char progress[Nplus];
}log;
int logging(const char*, const char*, int);
int valid();

int valid()
{
	int c;
	double validate, semic, str;
	char* mas = (char*)malloc(Nchar * sizeof(char));
	FILE* val;
	val = fopen("books.csv", "r");
	if (val == 0)
	{
		printf("Файл с книгами повреждён\nВосстановите файл, прежде чем начать\n");
		free(mas);
		return 0;
	}
	semic = 0;
	str = 0;

	while ((c = fgetc(val)) != EOF)
	{
		if (c == '\n')
			++str;
		if (c == ';')
			++semic;
	}
	if (str != 0 && semic != 0) {
		validate = (semic / str);
		if (validate != 4)
		{
			printf("Файл с книгами повреждён\nВосстановите файл, прежде чем начать\n");
			free(mas);
			return 0;
		}
	}
	fclose(val);

	val = fopen("students.csv", "r");
	if (val == 0)
	{
		printf("Файл со студентами повреждён\nВосстановите файл, прежде чем начать\n");
		free(mas);
		return 0;
	}
	semic = 0;
	str = 0;
	while ((c = fgetc(val)) != EOF)
	{
		if (c == '\n')
			++str;
		if (c == ';')
			++semic;
	}
	if (str != 0 && semic != 0)
	{
		validate = (semic / str);
		if (validate != 5)
		{
			printf("Файл со студентами повреждён\nВосстановите файл, прежде чем начать\n");
			free(mas);
			return 0;
		}
	}

	fclose(val);
	val = fopen("users.csv", "r");
	if (val == 0)
	{
		printf("Файл с пользователями повреждён\nВосстановите файл, прежде чем начать\n");
		free(mas);
		return 0;
	}
	semic = 0;
	str = 0;
	while ((c = fgetc(val)) != EOF)
	{
		if (c == '\n')
			++str;
		if (c == ';')
			++semic;
	}
	if (str != 0 && semic != 0)
	{
		validate = (semic / str);
		if (validate != 3)
		{
			printf("Файл с пользователями повреждён\nВосстановите файл, прежде чем начать\n");
			free(mas);
			return 0;
		}
	}

	fclose(val);
	val = fopen("student_books.csv", "r");
	if (val == 0)
	{
		printf("Файл с должниками повреждён\nВосстановите файл, прежде чем начать\n");
		free(mas);
		return 0;
	}
	semic = 0;
	str = 0;
	while ((c = fgetc(val)) != EOF)
	{
		if (c == '\n')
			++str;
		if (c == ';')
			++semic;
	}
	if (str != 0 && semic != 0) {
		validate = (semic / str);
		if (validate != 2)
		{
			printf("Файл с должниками повреждён\nВосстановите файл, прежде чем начать\n");
			free(mas);
			return 0;
		}
	}
	fclose(val);

	val = fopen("logging.log", "r");
	if (val == 0)
	{
		printf("Файл с логированием повреждён\nВосстановите файл, прежде чем начать\n");
		free(mas);
		return 0;
	}
	semic = 0;
	str = 0;
	while ((c = fgetc(val)) != EOF)
	{
		if (c == '\n')
			++str;
		if (c == ';')
			++semic;
	}
	if (str != 0 && semic != 0)
	{
		validate = (semic / str);
		if (validate != 3)
		{
			printf("Файл с логированием повреждён\nВосстановите файл, прежде чем начать\n");
			free(mas);
			return 0;
		}
	}

	fclose(val);
	return 1;
}

int logging(const char errorlogin[], const char action[], int success)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int c;
	FILE* logger = fopen("logging.log", "r+");
	log logg;
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if (logger == 0)
	{
		printf("Повреждён файл о изменениях пользователя");
		deleteconsole();
		return 0;
	}
	while ((c = fgetc(logger)) != EOF);

	strftime(logg.date, 20, "%d.%m.%Y %H:%M:%S", timeinfo);	//date

	if (errorlogin[0] == '\0')
		strcpy(logg.user, USER.login);						//user
	else
		strcpy(logg.user, errorlogin);

	strcpy(logg.step, action);								//Действие

	if (success == 1)											//Успех
		strcpy(logg.progress, "Success!");
	else
		strcpy(logg.progress, "Failure!");


	fprintf(logger, "%s;%s;%s;%s\n", logg.date, logg.user, logg.step, logg.progress);

	fclose(logger);

	return 1;
}

StudBook* SBrazbienie(int* pn)							//Функция разбиения файла на строки
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int c, i = 0;
	char* massiv, * massivdlyact;
	massiv = (char*)malloc(N * sizeof(char));
	massivdlyact = (char*)malloc(Nchar * sizeof(char));
	FILE* STUDBOOK = fopen("student_books.csv", "r");
	StudBook* allbookstud;
	(*pn) = 0;
	if (STUDBOOK == 0)
	{

		printf("Файл с данными о пользователях повреждён!\nВосстановите файл и продолжайте");
		deleteconsole();
		free(massiv);
		free(massivdlyact);
		return 0;
	}

	while ((c = fgetc(STUDBOOK)) != EOF)
	{
		if (c == '\n')
		{
			massivdlyact[i] = '\0';
			++(*pn);
		}
		massivdlyact[i] = c;
		++i;
	}

	allbookstud = (StudBook*)malloc((*pn) * sizeof(StudBook));

	for (int str = 0, i = 0, k = 0; str < (*pn);)
	{
		for (k = 0; massivdlyact[i] != ';'; ++i, ++k)			//ISBN
			massiv[k] = massivdlyact[i];
		++i;
		massiv[k] = '\0';
		allbookstud[str].ISBN = DMYatoi(massiv);

		for (k = 0; massivdlyact[i] != ';'; ++i, ++k)			//Номер зк
			allbookstud[str].book[k] = massivdlyact[i];
		++i;
		allbookstud[str].book[k] = '\0';

		for (k = 0; massivdlyact[i] != '\n'; ++i, ++k)			//DATE
			allbookstud[str].date[k] = massivdlyact[i];
		++i;
		allbookstud[str].date[k] = '\0';

		++str;
	}
	fclose(STUDBOOK);
	free(massiv);
	free(massivdlyact);

	return allbookstud;
}

user* auth(user* PUSER)
{
	int c, i = 0, n, count = 0;
	char* massiv, * massivdlyact;
	massiv = (char*)malloc(N * sizeof(char));
	massivdlyact = (char*)malloc(Nchar * sizeof(char));
	user* allusers;
	FILE* users = fopen("users.csv", "r");
	if (users == 0)
	{
		printf("Файл с данными о пользователях повреждён!\nВосстановите файл и продолжайте");
		deleteconsole();
		free(massiv);
		free(massivdlyact);
		return 0;
	}
	n = 0;

	while ((c = fgetc(users)) != EOF)
	{
		if (c == '\n')
		{
			massivdlyact[i] = '\0';
			++n;
		}
		massivdlyact[i] = c;
		++i;
	}

	if (massivdlyact[0] == '\n')
	{
		printf("Пустой файл, пёс!\n");
		free(massiv);
		free(massivdlyact);
		fclose(users);
		deleteconsole();
		return 0;
	}

	allusers = (user*)malloc(n * sizeof(user));

	for (int str = 0, i = 0, k = 0; str < n;)
	{
		for (k = 0; massivdlyact[i] != ';'; ++i, ++k)			//Login
			allusers[str].login[k] = massivdlyact[i];
		++i;
		allusers[str].login[k] = '\0';

		for (k = 0; massivdlyact[i] != ';'; ++i, ++k)			//Password
			allusers[str].password[k] = massivdlyact[i];
		++i;
		allusers[str].password[k] = '\0';

		for (k = 0; massivdlyact[i] != ';'; ++i, ++k)			//bookwatch
			massiv[k] = massivdlyact[i];
		++i;
		massiv[k] = '\0';
		for (int z = 0; massiv[z] != '\0'; ++z)
			allusers[str].book = MYatoi(massiv);

		for (k = 0; massivdlyact[i] != '\n'; ++i, ++k)			//studentwatch
			massiv[k] = massivdlyact[i];
		++i;
		massiv[k] = '\0';
		for (int z = 0; massiv[z] != '\0'; ++z)
			allusers[str].student = MYatoi(massiv);

		++str;
	}

	printf("Если хотите выйти из программы, введите *exit* при введении логина или пароля\nВведите логин: ");
	scanstr(massiv);
	if (strcmp(massiv, "exit") == 0)
		return 0;
	for (i = 0; i < n; ++i)
		if (strcmp(massiv, allusers[i].login) == 0)
		{
			count++;
			break;
		}
	if (count == 0)
	{
		printf("Пользователь с логином %s не найден!\nКлацни повтори попытку", massiv);
		logging(massiv, "Authentication", 0);
		free(massiv);
		free(massivdlyact);
		free(allusers);
		fclose(users);
		deleteconsole();
		PUSER->book = -1;
		return PUSER;
	}
	printf("Введите пароль: ");
	scanstr(massiv);
	if (strcmp(massiv, "exit") == 0)
		return 0;
	if (strcmp(massiv, allusers[i].password) == 0)
	{
		(*PUSER) = allusers[i];
		printf("Вы авторизовались под логином %s\nКлацни для продолжения", PUSER->login);
		logging(USER.login, "Authentication", 1);
		free(massiv);
		free(massivdlyact);
		free(allusers);
		fclose(users);
		deleteconsole();
		return PUSER;
	}
	printf("Вы ввели неверный пароль\nКлацни и повтори попытку");
	logging(massiv, "Authentication", 0);
	PUSER->book = -1;
	free(massiv);
	free(allusers);
	free(massivdlyact);
	deleteconsole();
	return PUSER;
}