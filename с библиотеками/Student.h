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
#include "either.h"
#define N 100
#define Nplus 20
#define Nchar 100000
typedef struct book {
	double ISBN;
	char author[N];
	char name[N];
	int all;
	int remains;
}book;
typedef struct student {
	char book[7];
	char surname[N];
	char name[N];
	char middlename[N];
	char fac[N];
	char spec[N];
}student;
typedef struct Nstudent
{
	char surname[N];
	char name[N];
	char middlename[N];
	char book[N];
	int Numb;
}Nstudent;
book* razbienie(FILE*, int*);
student* Srazbienie(FILE*, int*);
student* addstudent(student*, int*);
student* deletestudent(student*, int*);
student* deletestudNumb(student*, int*, int);
student* editstud(student*, int*);
student* lookstud(student*, int*);
student* Sbackup(student*, int*);
int Smadebackup(student*, int*);
void menustudent();
void printmenustudent();
void printtablestudent(student*, int);

book* razbienie(FILE* books, int* pn)							//Функция разбиения файла на строки
{
	int c, i = 0;
	char* massiv, * massivdlyact;
	massiv = (char*)malloc(N * sizeof(char));
	massivdlyact = (char*)malloc(Nchar * sizeof(char));
	book* allbooks;
	(*pn) = 0;

	while ((c = fgetc(books)) != EOF)
	{
		if (c == '\n')
		{
			massivdlyact[i] = '\0';
			++(*pn);
		}
		massivdlyact[i] = c;
		++i;
	}

	if (massivdlyact[0] == '\0')
	{
		printf("Пустой файл, пёс!\n");
		free(massiv);
		free(massivdlyact);
		return 0;
	}

	allbooks = (book*)malloc((*pn) * sizeof(book));

	for (int str = 0, i = 0, k = 0; str < (*pn);)
	{
		for (k = 0; massivdlyact[i] != ';'; ++i, ++k)			//ISBN
			massiv[k] = massivdlyact[i];
		++i;
		massiv[k] = '\0';
		allbooks[str].ISBN = DMYatoi(massiv);

		for (k = 0; massivdlyact[i] != ';'; ++i, ++k)			//Имя автора
			allbooks[str].author[k] = massivdlyact[i];
		++i;
		allbooks[str].author[k] = '\0';

		for (k = 0; massivdlyact[i] != ';'; ++i, ++k)			//Название книги
			allbooks[str].name[k] = massivdlyact[i];
		++i;
		allbooks[str].name[k] = '\0';

		for (k = 0; massivdlyact[i] != ';'; ++i, ++k)			//Количество книг
			massiv[k] = massivdlyact[i];
		++i;
		massiv[k] = '\0';
		allbooks[str].all = MYatoi(massiv);

		for (k = 0; massivdlyact[i] != '\n'; ++i, ++k)			//Оставшиеся книги
			massiv[k] = massivdlyact[i];
		++i;
		massiv[k] = '\0';
		allbooks[str].remains = MYatoi(massiv);

		++str;
	}

	free(massiv);
	free(massivdlyact);

	return allbooks;
}

void menustudent()
{
	int i, n = 0, * pn = &n, actstud = 1;
	char* action = (char*)malloc(Nplus * sizeof(char));
	FILE* students = fopen("students.csv", "r");
	student* allstudents;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	allstudents = Srazbienie(students, pn);
	fclose(students);
	while (actstud != 0)
	{
		printmenustudent();

		printf("Каковы указания: ");
		scanstr(action);
		actstud = MYatoi(action);
		system("cls");

		switch (actstud)
		{
		case 0:
		{
			break; }
		case 1:
		{
			printf("\t\t\t\tПросмотр всех студентов\n");
			for (int i = 0; i < 127; ++i)
				printf("_");
			printf("\n");
			printf("Номер з|");
			printf("\tФамилия\t|");
			printf("\tИмя\t |");
			printf("\tОтчество\t|");
			printf("Факультет|");
			printf("\t\t\tСпециальность\t\t       |\n");
			for (int i = 0; i < 127; ++i)
				printf("_");
			printf("\n");
			for (i = 0; i < n; ++i)
				printtablestudent(allstudents, i);
			printf("Вот и все студенты, клацай для продолжения");
			logging("", "ViewAllStudent", 1);
			deleteconsole();
			break;
		}
		case 2:
		{
			printf("\tМеню добавления студентов\n");
			allstudents = addstudent(allstudents, pn);
			break;
		}
		case 3:
		{
			printf("\tМеню удаления студентов\n");
			allstudents = deletestudent(allstudents, pn);
			break;
		}
		case 4:
		{
			printf("\tРедактирование информации о студенте\n");
			allstudents = editstud(allstudents, pn);
			break;
		}
		case 5:
		{
			printf("\tПросмотр информации о студенте\n");
			allstudents = lookstud(allstudents, pn);
			break;
		}

		case 6:
		{
			printf("Создание бэкапа...\n");
			Smadebackup(allstudents, pn);
			break;
		}
		case 7:
		{
			printf("\tМеню отката библиотеки\n");
			allstudents = Sbackup(allstudents, pn);
			break;
		}
		default:
		{
			printf("ШУТНИК, ДА?! Я ДЛЯ ТЕБЯ ПРОСТО ШУТКА, СЕЙЧАС 3:41 НОЧИ И Я НЕ ГАМАЮ, А ТЕБЕ СМЕШНО, ДА?!, ЗАНОВО ДАВАЙ\nНу это, клацни куда нибудь\nПожалуйста\n");
			deleteconsole();
			break;
		}
		}
	}
	free(action);
	free(allstudents);
}

int Smadebackup(student* allstudents, int* pn)
{
	char backup_name[N];
	FILE* backupp;
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(backup_name, N, "students %m-%d-%Y %H-%M-%S.csv", timeinfo);

	backupp = fopen(backup_name, "w");
	if (backupp == 0)
	{
		printf("Что-то пошло не так при создании бэкапа\nКак ты это сделал?\nКлацай");
		logging("", "MadeBackUpStudent", 0);
		deleteconsole();
		return -1;
	}

	for (int i = 0; i < (*pn); ++i)
		fprintf(backupp, "%s;%s;%s;%s;%s;%s\n", allstudents[i].book, allstudents[i].surname,
			allstudents[i].name, allstudents[i].middlename, allstudents[i].fac, allstudents[i].spec);

	printf("Бэкап успешно создан, имя и расширение бэкапа: %s\nКлацай, продолжим", backup_name);
	logging("", "MadeBackUpStudent", 1);
	deleteconsole();
	fclose(backupp);
	return 1;
}

student* Sbackup(student* allstudents, int* pn)
{
	FILE* backupp, * bibl;
	char* datet = (char*)malloc(N * sizeof(char));
	char* namef = (char*)malloc(N * sizeof(char));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	strncpy(namef, "students ", 9);
	namef[9] = '\0';
	printf("Для восстановления введите дату сохранения в формате дд-мм-гггг чч-мм-сс\nПример: 04-06-2001 06-00-12\nДата сохранения: ");

	scanstr(datet);
	strcat(namef, datet);
	strcat(namef, ".csv");
	printf("%s\n", namef);
	backupp = fopen(namef, "r");
	if (backupp == 0)
	{
		printf("Вы не создавали резервного сохранения в это время\nПопробуй еще раз");
		logging("", "BackUpStudent", 0);
		deleteconsole();
		free(namef);
		free(datet);
		return allstudents;
	}
	free(allstudents);

	allstudents = Srazbienie(backupp, pn);
	fclose(backupp);

	bibl = fopen("students.csv", "w+");

	for (int i = 0; i < (*pn); ++i)
		fprintf(backupp, "%s;%s;%s;%s;%s;%s\n", allstudents[i].book, allstudents[i].surname,
			allstudents[i].name, allstudents[i].middlename, allstudents[i].fac, allstudents[i].spec);

	fclose(bibl);
	printf("Библиотека успешно восстановлена из файла %s\nКлацай", namef);
	logging("", "BackUpStudent", 1);
	deleteconsole();
	free(namef);
	free(datet);
	return allstudents;
}

student* lookstud(student* allstudents, int* pn)
{
	StudBook* allstudbook;
	char* str = (char*)malloc(N * sizeof(char));
	char* act = (char*)malloc(N * sizeof(char));
	int count = 0, enemy = 0, action, l = 0, first = 0, nbs = 0, * pnbs = &nbs;

	printf("Просмотр информации по:\n1. Номеру зачетной книжки\n2. Фамилии\nИтак, выбор: ");
	scanstr(str);
	action = MYatoi(str);

	switch (action)
	{
	case 1:
	{
		printf("Введите номер зачетной книги студента, информацию о котором хотите просмотреть: ");
		scanstr(str);
		if (str[0] > '9' || str[0] < '0' || str[1] < 'А' || str[1]>'Я' || str[2]>'9' || str[2] < '0' || str[3]>'9' || str[4] < '0' || str[4]>'9' || str[5] < '0' || str[5]>'9' || str[6] != '\0')
		{
			printf("Да, конечно, такой зачётки не может существовать\nКлацни для продолжения");
			logging("", "ViewStudent", 0);
			deleteconsole();
			free(str);
			free(act);
			return allstudents;
		}

		for (int i = 0; i < (*pn); ++i)
		{
			if (strcmp(allstudents[i].book, str) == 0)
			{
				++count;
				enemy = i;
			}
		}
		if (count == 0)
		{
			printf("Этого студента нет в нашей базе.\nКлац...");
			logging("", "ViewStudent", 0);
			deleteconsole();
			free(str);
			free(act);
			return allstudents;
		}
		break;
	}
	case 2:
	{
		printf("Введите фамилию студента, информацию о котором хотите просмотреть: ");
		scanstr(str);

		for (int i = 0; i < (*pn); ++i)
			if (strcmp(allstudents[i].surname, str) == 0)
			{
				if (first == 0)
				{
					++first;
					printf("Информация о студентах *%s*\n", allstudents[i].surname);
				}
				++l;
				printf("%d. %s\n", l, allstudents[i].book);
			}
		if (first == 0)
		{
			printf("Этого студента нет в нашей базе.\nКлац...");
			logging("", "ViewStudent", 0);
			deleteconsole();
			free(str);
			free(act);
			return allstudents;
		}

		printf("Информацию о каком студенте желаете просмотреть: ");
		scanstr(act);
		action = (MYatoi(act));
		if (MYatoi(act) > l || MYatoi(act) < 1)
		{
			printf("СЕРЬЁЗНО?! НЕ СМОГ НАЖАТЬ ВСЕГО ПАРУ ЦИФР?!\nЗАНОВО!");
			logging("", "ViewStudent", 0);
			deleteconsole();
			free(str);
			free(act);
			return allstudents;
		}
		l = 0;
		for (int i = 0; i < (*pn); ++i)
		{
			if (strcmp(allstudents[i].surname, str) == 0)
			{
				++l;
				if (l == action)
					enemy = i;
			}
		}
		break;
	}
	default:
	{
		printf("СЕРЬЁЗНО?! НЕ СМОГ НАЖАТЬ ВСЕГО ОДНУ ЦИФРУ?!\nЗАНОВО!");
		logging("", "ViewStudent", 0);
		deleteconsole();
		free(str);
		free(act);
		return allstudents;
		break;
	}
	}
	system("cls");
	printf("\tИнформация о студенте %s\n", allstudents[enemy].book);
	printf("Фамилия: %s\nИмя: %s\nОтчество: %s\nФакультет: %s\nСпециальность: %s\n",
		allstudents[enemy].surname, allstudents[enemy].name, allstudents[enemy].middlename,
		allstudents[enemy].fac, allstudents[enemy].spec);

	count = 0;
	allstudbook = SBrazbienie(pnbs);
	for (int i = 0; i < nbs; ++i)
		if (strcmp(allstudents[enemy].book, allstudbook[i].book) == 0)
			count++;
	if (count == 0)
	{
		printf("Студент не брал книг/сдал все книги\nКлацни для продолжения");
	}
	else
	{
		FILE* books = fopen("books.csv", "r");
		book* allbooks = 0;
		int nb = 0, * pnb = &nb, coun = 0;
		if (books == 0)
		{
			printf("Доступ к файлу с книгами нарушен!\nКлац");
			logging("", "ViewStudent", 0);
			free(allstudbook);
			free(str);
			free(act);
			deleteconsole();
			return allstudents;

		}
		allbooks = razbienie(books, pnb);
		printf("Студент должен сдать %d книг:\n", count);
		for (int i = 0; i < nbs; ++i)
			if (strcmp(allstudents[enemy].book, allstudbook[i].book) == 0)
				for (int z = 0; z < nb; ++z)
					if (allbooks[z].ISBN == allstudbook[i].ISBN)
					{
						coun++;
						printf("%d. ", coun);

						if (allbooks[z].ISBN < 10)
							for (int i = 0; i < 9; ++i)
								printf("0");
						else if (allbooks[z].ISBN < 100)
							for (int i = 0; i < 8; ++i)
								printf("0");
						else if (allbooks[z].ISBN < 1000)
							for (int i = 0; i < 7; ++i)
								printf("0");
						else if (allbooks[z].ISBN < 10000)
							for (int i = 0; i < 6; ++i)
								printf("0");
						else if (allbooks[z].ISBN < 100000)
							for (int i = 0; i < 5; ++i)
								printf("0");
						else if (allbooks[z].ISBN < 1000000)
							for (int i = 0; i < 4; ++i)
								printf("0");
						else if (allbooks[z].ISBN < 10000000)
							for (int i = 0; i < 3; ++i)
								printf("0");
						else if (allbooks[z].ISBN < 100000000)
							for (int i = 0; i < 2; ++i)
								printf("0");
						else if (allbooks[z].ISBN < 1000000000)
							for (int i = 0; i < 1; ++i)
								printf("0");
						printf("%.0lf-%s *%s* - дата сдачи: %s\n", allbooks[z].ISBN, allbooks[z].author, allbooks[z].name, allstudbook[i].date);
					}
		free(allbooks);
	}
	printf("Клацай");
	logging("", "ViewStudent", 1);
	free(allstudbook);
	free(str);
	free(act);
	deleteconsole();
	return allstudents;
}

student* editstud(student* allstudents, int* pn)
{
	FILE* students;
	char* str = (char*)malloc(N * sizeof(char));
	int count = 0, enemy, action;
	
	printf("Введите номер зачетной книги студента, информацию о котором необходимо изменить: ");
	scanstr(str);
	if (str[6] != '\0' || str[0] > '9' || str[0] < '0' || str[1] < 'А' || str[1]>'Я' || str[2]>'9' || str[2] < '0' || str[3]>'9' || str[4] < '0' || str[4]>'9' || str[5] < '0' || str[5]>'9')
	{
		printf("Да, конечно, такой зачётки не может существовать\nКлацни для продолжения");
		logging("", "EditStudent", 0);
		deleteconsole();
		free(str);
		return allstudents;
	}

	for (int i = 0; i < (*pn); ++i)
	{
		if (strcmp(allstudents[i].book, str) == 0)
		{
			++count;
			enemy = i;
		}
	}
	if (count == 0)
	{
		printf("Этот студент не брал книгу.\nКлац...");
		logging("", "EditStudent", 0);
		deleteconsole();
		free(str);
		return allstudents;
	}
	system("cls");

	printf("\tРедактирование информации о студенте %s\n", allstudents[enemy].book);
	printf("Фамилия: %s\nИмя: %s\nОтчество: %s\nФакультет: %s\nСпециальность: %s\n",
		allstudents[enemy].surname, allstudents[enemy].name, allstudents[enemy].middlename,
		allstudents[enemy].fac, allstudents[enemy].spec);
	printf("Что желаете изменить?\n1. Фамилию \n2. Имя \n3. Отчество\n4. Факультет\n5. Специальность\nИтак, выбор: ");
	scanstr(str);
	action = MYatoi(str);
	switch (action)
	{
	case 1:
	{
		printf("Введите измененную фамилию: ");
		scanstr(str);
		strcpy(allstudents[enemy].surname, str);
		printf("Фамилия изменена!");
		logging("", "EditStudent_Surname", 1);
		break;
	}
	case 2:
	{
		printf("Введите измененное имя: ");
		scanstr(str);
		strcpy(allstudents[enemy].name, str);
		printf("Имя изменено!");
		logging("", "EditStudent_Name", 1);
		break;
	}
	case 3:
	{
		printf("Введите измененное отчество: ");
		scanstr(str);
		strcpy(allstudents[enemy].middlename, str);
		printf("Отчество изменено!");
		logging("", "EditStudent_Middlename", 1);
		break;
	}
	case 4:
	{
		printf("Введите измененный факультет: ");
		scanstr(str);
		strcpy(allstudents[enemy].fac, str);
		printf("Факультет изменен!");
		logging("", "EditStudent_Faculty", 1);
		break;
	}
	case 5:
	{
		printf("Введите измененную специальность: ");
		scanstr(str);
		strcpy(allstudents[enemy].spec, str);
		printf("Специальность изменена!");
		logging("", "EditStudent_Specialty", 1);
		break;
	}
	default:
	{
		printf("СЕРЬЁЗНО?! НЕ СМОГ НАЖАТЬ ВСЕГО ОДНУ ЦИФРУ?!\nЗАНОВО!");
		logging("", "EditStudent", 0);
		deleteconsole();
		free(str);
		return allstudents;
		break;
	}
	}
	students = fopen("students.csv", "w+");
	if (students == 0)
	{
		printf("\nОшибка открытия файла");
		logging("", "EditStudent", 0);
		deleteconsole();
		free(str);
		return allstudents;
	}

	for (int i = 0; i < (*pn); ++i)
		fprintf(students, "%s;%s;%s;%s;%s;%s\n", allstudents[i].book, allstudents[i].surname,
			allstudents[i].name, allstudents[i].middlename, allstudents[i].fac, allstudents[i].spec);

	fclose(students);
	free(str);
	deleteconsole();
	return allstudents;
}

student* deletestudent(student* allstudents, int* pn)
{
	StudBook* allstudbook;
	int enemy, count = 0, nbs = 0, * pnbs = &nbs;
	char* action = (char*)malloc(Nplus * sizeof(char));
	printf("Удаление студента по номеру зачётной книжки\nВведите номер зачётной книжки: ");
	scanstr(action);
	if (action[6] != '\0' || action[0] > '9' || action[0] < '0' || action[1] < 'А' || action[1]>'Я' || action[2]>'9' || action[2] < '0' || action[3]>'9' || action[4] < '0' || action[4]>'9' || action[5] < '0' || action[5]>'9')
	{
		printf("Да, конечно, такой зачётки не может существовать\nКлацни для продолжения");
		logging("", "DeleteStudent", 0);
		deleteconsole();
		free(action);
		return allstudents;
	}
	for (int i = 0; i < (*pn); ++i)
		if (strcmp(action, allstudents[i].book) == 0)
		{
			++count;
			enemy = i;
		}
	if (count == 0)
	{
		printf("Этот студент не брал у нас книгу\nКлац");
		logging("", "DeleteStudent", 0);
		deleteconsole();
		free(action);
		return allstudents;
	}
	count = 0;
	allstudbook = SBrazbienie(pnbs);
	for (int i = 0; i < (*pn); ++i)
		if (strcmp(action, allstudbook[i].book) == 0)
			++count;
	if (count != 0)
	{
		printf("Этот студент брал у нас книгу\nВы не можете удалить студента, который не вернул книги\nКлац");
		logging("", "DeleteStudent", 0);
		deleteconsole();
		free(action);
		return allstudents;
	}
	allstudents = deletestudNumb(allstudents, pn, enemy);

	printf("Студент удалён из базы!\nКлацни для продожения\n");
	logging("", "DeleteStudent", 1);
	deleteconsole();
	free(action);

	return allstudents;
}

student* deletestudNumb(student* allstudents, int* pn, int enemy)
{
	student* copy = (student*)malloc(((*pn) - 1) * sizeof(student));
	FILE* students = fopen("students.csv", "w+");

	allstudents[enemy] = allstudents[((*pn) - 1)];
	(*pn)--;
	for (int i = 0; i < (*pn); ++i)
		copy[i] = allstudents[i];

	for (int i = 0; i < enemy; ++i)
		fprintf(students, "%s;%s;%s;%s;%s;%s\n", copy[i].book, copy[i].surname, copy[i].name,
			copy[i].middlename, copy[i].fac, copy[i].spec);

	fclose(students);
	free(allstudents);

	return copy;
}

student* addstudent(student* allstudents, int* pn)
{
	int i = 0, n = *pn, count = 0;
	char* letters = (char*)malloc(Nplus * sizeof(char));
	student newstudent;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	printf("Введите номер зачётки: ");
	scanstr(newstudent.book);

	if (newstudent.book[6] != '\0' || newstudent.book[0] > '9' || newstudent.book[0] < '0' || newstudent.book[1] < 'А' || newstudent.book[1]>'Я' || newstudent.book[2]>'9' || newstudent.book[2] < '0' || newstudent.book[3]>'9' || newstudent.book[4] < '0' || newstudent.book[4]>'9' || newstudent.book[5] < '0' || newstudent.book[5]>'9')
	{
		printf("Да, конечно, такой зачётки не может существовать\nКлацни для продолжения");
		logging("", "AddStudent", 0);
		deleteconsole();
		free(letters);
		return allstudents;
	}
	for (i = 0; i < n; ++i)
		if (strcmp(allstudents[i].book, newstudent.book) == 0)
		{
			printf("Такой номер зачётки уже занят\nКлацни для продолжения");
			logging("", "AddStudent", 0);
			deleteconsole();
			free(letters);
			return allstudents;
		}

	printf("Введите фамилию студента: ");
	scanstr(newstudent.surname);
	for (i = 0; i < n; ++i)
		if (strcmp(allstudents[i].surname, newstudent.surname) == 0)
			count++;
	if (count != 0)
		printf("У нас уже брали книги %d студента с фамилией %s!\n", count, newstudent.surname);
	count = 0;

	printf("Введите имя студента: ");
	scanstr(newstudent.name);
	for (i = 0; i < n; ++i)
		if ((strcmp(allstudents[i].surname, newstudent.surname) == 0) && (strcmp(allstudents[i].name, newstudent.name) == 0))
			count++;
	if (count != 0)
		printf("У нас уже брали книги %d студента с ФИ %s %s\n", count, newstudent.surname, newstudent.name);
	count = 0;

	printf("Введите отчество студента: ");
	scanstr(newstudent.middlename);
	for (i = 0; i < n; ++i)
		if ((strcmp(allstudents[i].surname, newstudent.surname) == 0) && (strcmp(allstudents[i].name, newstudent.name) == 0) && (strcmp(allstudents[i].middlename, newstudent.middlename) == 0))
			count++;
	if (count != 0)
		printf("У нас уже брали книги %d студента с ФИО %s %s %s\n", count, newstudent.surname, newstudent.name, newstudent.middlename);
	count = 0;

	printf("Введите факультет, на котором обучается студент: ");
	scanstr(newstudent.fac);
	for (i = 0; i < n; ++i)
		if ((strcmp(allstudents[i].surname, newstudent.surname) == 0) && (strcmp(allstudents[i].name, newstudent.name) == 0) && (strcmp(allstudents[i].middlename, newstudent.middlename) == 0) && (strcmp(allstudents[i].fac, newstudent.fac) == 0))
			count++;
	if (count != 0)
		printf("У нас уже брали книги %d студента с ФИО %s %s %s с факультета %s\n",
			count, newstudent.surname, newstudent.name, newstudent.middlename, newstudent.fac);
	count = 0;

	printf("Введите специальность, на которой обучается студент: ");
	scanstr(newstudent.spec);
	for (i = 0; i < n; ++i)
		if ((strcmp(allstudents[i].surname, newstudent.surname) == 0) && (strcmp(allstudents[i].name, newstudent.name) == 0) && (strcmp(allstudents[i].middlename, newstudent.middlename) == 0) && (strcmp(allstudents[i].fac, newstudent.fac) == 0) && (strcmp(allstudents[i].spec, newstudent.spec) == 0))
			count++;
	if (count != 0)
	{
		printf("У нас уже брали книги %d студента с ФИО %s %s %s с факультета %s кафедры %s\n",
			count, newstudent.surname, newstudent.name, newstudent.middlename, newstudent.fac, newstudent.spec);
		printf("Вы уверены, что ввели номер зачётной книжки верно?\n");
	}

	printf("Добавить студента?\n1. Да\n2. Нет\nИтак, выбор: ");
	scanstr(letters);
	count = MYatoi(letters);
	switch (count)
	{
	case 1:
	{
		logging("", "AddStudent", 1);
		break;
	}
	case 2:
	{
		printf("Студент не был добавлен\n");
		logging("", "AddStudent", 0);
		deleteconsole();
		free(letters);
		return allstudents;
		break;
	}
	default:
		printf("ГЫГЫГЫ ПОЧЕМУ БЫ НЕ ВВЕСТИ ЧТО-ТО ДРУГОЕ, А НЕ 1 ИЛИ 2!!!\nЗАНОВО!");
		logging("", "AddStudent", 0);
		deleteconsole();
		free(letters);
		return allstudents;
		break;
	}
	FILE* students = fopen("students.csv", "w+");
	(*pn)++;
	allstudents = (student*)realloc(allstudents, ((*pn) * sizeof(student)));

	allstudents[(*pn) - 1] = newstudent;

	for (i = 0; i < (*pn); ++i)
		fprintf(students, "%s;%s;%s;%s;%s;%s\n", allstudents[i].book, allstudents[i].surname,
			allstudents[i].name, allstudents[i].middlename, allstudents[i].fac, allstudents[i].spec);
	fclose(students);
	printf("Студент добавлен\nКлацни, и мы продолжим\n");
	deleteconsole();
	free(letters);
	return allstudents;
}

student* Srazbienie(FILE* students, int* pn)							//Функция разбиения файла на строки
{
	int c, i = 0;
	char* massiv, * massivdlyact;
	massiv = (char*)malloc(N * sizeof(char));
	massivdlyact = (char*)malloc(Nchar * sizeof(char));
	student* allstudents;
	(*pn) = 0;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	while ((c = fgetc(students)) != EOF)
	{
		if (c == '\n')
		{
			massivdlyact[i] = '\0';
			++(*pn);
		}
		massivdlyact[i] = c;
		++i;
	}

	if (massivdlyact[0] < '0')
	{
		printf("Пустой файл, пёс!\n");
		free(massiv);
		free(massivdlyact);
		return 0;
	}

	allstudents = (student*)malloc((*pn) * sizeof(student));

	for (int str = 0, i = 0, k = 0; str < (*pn);)
	{
		for (k = 0; massivdlyact[i] != ';'; ++i, ++k)			//Зачетка
			allstudents[str].book[k] = massivdlyact[i];
		++i;
		allstudents[str].book[k] = '\0';

		for (k = 0; massivdlyact[i] != ';'; ++i, ++k)			//Фамилия
			allstudents[str].surname[k] = massivdlyact[i];
		++i;
		allstudents[str].surname[k] = '\0';

		for (k = 0; massivdlyact[i] != ';'; ++i, ++k)			//Имя
			allstudents[str].name[k] = massivdlyact[i];
		++i;
		allstudents[str].name[k] = '\0';

		for (k = 0; massivdlyact[i] != ';'; ++i, ++k)			//Отчество
			allstudents[str].middlename[k] = massivdlyact[i];
		++i;
		allstudents[str].middlename[k] = '\0';

		for (k = 0; massivdlyact[i] != ';'; ++i, ++k)			//Факультет
			allstudents[str].fac[k] = massivdlyact[i];
		++i;
		allstudents[str].fac[k] = '\0';

		for (k = 0; massivdlyact[i] != '\n'; ++i, ++k)			//Специальность
			allstudents[str].spec[k] = massivdlyact[i];
		++i;
		allstudents[str].spec[k] = '\0';

		++str;
	}

	free(massiv);
	free(massivdlyact);

	return allstudents;
}

void printmenustudent()
{
	printf("\tМеню студентов\n");
	printf("1. Показать всех студентов\n");
	printf("2. Добавить студента\n");
	printf("3. Удалить студента\n");
	printf("4. Редактировать информацию о студенте\n");
	printf("5. Посмотреть информацию о студенте\n");
	printf("6. Создать резервное сохранение\n");
	printf("7. Восстановить библиотеку из резервного сохранения\n");
	printf("0. Выход\n");
}

void printtablestudent(student* allstudents, int n)
{
	int l = 0;

	printf("%s", allstudents[n].book);
	for (int i = 0; allstudents[n].book[i] != '\0'; ++i)
		l = i;
	l = 6 - l;
	for (int i = 0; i < l; ++i)
		printf(" ");
	printf("|");

	printf("%s", allstudents[n].surname);
	for (int i = 0; allstudents[n].surname[i] != '\0'; ++i)
		l = i;
	l = 15 - l;
	for (int i = 0; i < l; ++i)
		printf(" ");
	printf("|");

	printf("%s", allstudents[n].name);
	for (int i = 0; allstudents[n].name[i] != '\0'; ++i)
		l = i;
	l = 15 - l;
	for (int i = 0; i < l; ++i)
		printf(" ");
	printf("|");

	printf("%s", allstudents[n].middlename);
	for (int i = 0; allstudents[n].middlename[i] != '\0'; ++i)
		l = i;
	l = 21 - l;
	for (int i = 0; i < l; ++i)
		printf(" ");
	printf("|");

	printf("%s", allstudents[n].fac);
	for (int i = 0; allstudents[n].fac[i] != '\0'; ++i)
		l = i;
	l = 8 - l;
	for (int i = 0; i < l; ++i)
		printf(" ");
	printf("|");

	printf("%s", allstudents[n].spec);
	for (int i = 0; allstudents[n].spec[i] != '\0'; ++i)
		l = i;
	l = 50 - l;
	for (int i = 0; i < l; ++i)
		printf(" ");
	printf("|\n");
	for (int i = 0; i < 127; ++i)
		printf("_");
	printf("\n");
}
