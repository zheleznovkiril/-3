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
#include "Students.h"
#include "common.h"
#include "either.h"
#define N 100
#define Nplus 20
#define Nchar 100000

typedef struct Nauthor
{
	char author[N];
	int quan;
}Nauthor;

book* printbook(book*, int*);
book* editbook(book*, int*);
book* givegetbook(book*, int*, char);
book* addbook(book*, int*);
book* deletebook(book*, int*);
book* deletebookNumb(book*, int*, int);
book* backup(book*, int*);
int madebackup(book*, int*);
void printtablebook(book*, int);
void printmenubook();
void menubook();
void BookShellSort(book*, int*);
void BookSwap(book*, int, int);

void menubook()
{
	int n = 0, * pn = &n, actbook = 1;
	char* action = (char*)malloc(Nplus * sizeof(char));
	FILE* books = fopen("books.csv", "r");
	book* allbooks;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	allbooks = razbienie(books, pn);
	fclose(books);
	while (actbook != 0)
	{
		printmenubook();

		printf("Каковы указания: ");
		scanstr(action);
		actbook = MYatoi(action);
		system("cls");

		switch (actbook)
		{
		case 0:
		{
			break; }
		case 1:
		{
			printf("\t\t\t\tПросмотр всех книг, отсортированных по ISBN\n");
			for (int i = 0; i < 108; ++i)
				printf("_");
			printf("\n");
			printf("    ISBN   |");
			printf("        Автор        |");
			printf("                  Название книги                   |");
			printf("Всего книг|");
			printf(" Осталось |\n");
			for (int i = 0; i < 108; ++i)
				printf("_");
			printf("\n");
			BookShellSort(allbooks, pn);
			printf("Вот и все книги, клацай для продолжения");
			logging("", "ViewAllBook", 1);
			deleteconsole();
			break;
		}
		case 2:
		{
			printf("\tМеню добавления книг\n");
			allbooks = addbook(allbooks, pn);
			break;
		}
		case 3:
		{
			printf("\tМеню удаления книг\n");
			allbooks = deletebook(allbooks, pn);
			break;
		}
		case 4:
		{
			printf("Создание бэкапа...\n");
			madebackup(allbooks, pn);
			break;
		}
		case 5:
		{
			printf("\tМеню отката библиотеки\n");
			allbooks = backup(allbooks, pn);
			break;
		}
		case 6:
		{
			printf("\tМеню просмотра книги\n");
			printbook(allbooks, pn);
			break;
		}
		case 7:
		{
			printf("\tРедактирование информации о книге\n");
			allbooks = editbook(allbooks, pn);
			break;
		}
		case 8:
		{
			printf("\tВыдача книги\n");
			allbooks = givegetbook(allbooks, pn, '-');
			break;
		}
		case 9:
		{
			printf("\tВозращение книги книги\n");
			allbooks = givegetbook(allbooks, pn, '+');
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
	free(allbooks);
}

book* givegetbook(book* allbooks, int* pn, char doing)
{
	FILE* editbook, * editstudbook, * editstud;
	student* allstudents = 0;
	StudBook* allstudbook = 0, * copy = 0;
	char* str = (char*)malloc(N * sizeof(char));
	double ISBN;
	int count = 0, enemy, enemys, enemye, ns = 0, * pns = &ns, counts = 0, nsb = 0, * pnsb = &nsb, counte = 0;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("Введите ISBN книги: ");
	scanstr(str);
	ISBN = DMYatoi(str);
	if (ISBN < 1 || ISBN>9999999999)
	{
		printf("ТАКОГО ИСЭБЭЭНА НЕ МОЖЕТ СУЩЕСТВОВАТЬ \nЗАНОВО!");
		if (doing == '+')
			logging("", "GetBook", 0);
		if (doing == '-')
			logging("", "GiveBook", 0);
		deleteconsole();
		free(str);
		return allbooks;
	}

	for (int i = 0; i < (*pn); ++i)
		if (allbooks[i].ISBN == ISBN)
		{
			count++;
			enemy = i;
		}

	if (count == 0)
	{
		printf("Книга не найдена\nКлацни, чтобы продолжить");
		if (doing == '+')
			logging("", "GetBook", 0);
		if (doing == '-')
			logging("", "GiveBook", 0);
		deleteconsole();
		free(str);
		return allbooks;
	}

	if (doing == '-')
		if (allbooks[enemy].remains == 0)
		{
			char* day = (char*)malloc(3 * sizeof(char));
			char* month = (char*)malloc(3 * sizeof(char));
			char* year = (char*)malloc(5 * sizeof(char));
			char* day2 = (char*)malloc(3 * sizeof(char));
			char* month2 = (char*)malloc(3 * sizeof(char));
			char* year2 = (char*)malloc(5 * sizeof(char));
			StudBook* check = 0;

			int first = 0, k = 0;
			check = SBrazbienie(pnsb);

			free(str);
			printf("Извините, но книги *%s* закончились\n", allbooks[enemy].name);

			for (int i = 0; i < nsb; ++i)
			{
				if (allbooks[enemy].ISBN == check[i].ISBN)
				{
					k = 0;
					if (first == 0)
					{
						for (int l = 0; l < 2; ++l)
						{
							day[l] = check[i].date[k];
							++k;
						}
						++k;
						day[2] = '\0';
						for (int l = 0; l < 2; ++l)
						{
							month[l] = check[i].date[k];
							++k;
						}
						++k;
						month[2] = '\0';
						for (int l = 0; l < 4; ++l)
						{
							year[l] = check[i].date[k];
							++k;
						}
						++k;
						year[4] = '\0';
						++first;
					}
					else
					{
						for (int l = 0; l < 2; ++l)
						{
							day2[l] = check[i].date[k];
							++k;
						}
						++k;
						day2[2] = '\0';
						for (int l = 0; l < 2; ++l)
						{
							month2[l] = check[i].date[k];
							++k;
						}
						++k;
						month2[2] = '\0';
						for (int l = 0; l < 4; ++l)
						{
							year2[l] = check[i].date[k];
							++k;
						}
						++k;
						year2[4] = '\0';
						++first;
						if (MYatoi(year2) < MYatoi(year))
						{
							strcpy(year, year2);
							strcpy(month, month2);
							strcpy(day, day2);
						}
						else if (MYatoi(year2) == MYatoi(year))
						{
							if (MYatoi(month2) < MYatoi(month))
							{
								strcpy(year, year2);
								strcpy(month, month2);
								strcpy(day, day2);
							}
							else if (MYatoi(month2) == MYatoi(month))
							{
								if (MYatoi(day2) < MYatoi(day))
								{
									strcpy(year, year2);
									strcpy(month, month2);
									strcpy(day, day2);
								}
							}
						}
					}
				}
			}

			if (first == 0)
			{
				printf("По каким-то причинам книг нет, но и студенты их не брали\n");
				logging("", "GiveBook", 0);
				deleteconsole();
				free(check);
				free(day);
				free(day2);
				free(month);
				free(month2);
				free(year);
				free(year2);
				return allbooks;
			}
			printf("Ближайшая дата возврата: %s.%s.%s", day, month, year);
			logging("", "GiveBook", 0);
			deleteconsole();
			free(check);
			free(day);
			free(day2);
			free(month);
			free(month2);
			free(year);
			free(year2);
			return allbooks;
		}
	if (doing == '+')
		if (allbooks[enemy].remains == allbooks[enemy].all)
		{
			free(str);
			printf("Где-то обман\nВсе книги *%s* на месте\nКлацай для продолжения", allbooks[enemy].name);
			logging("", "GetBook", 0);
			deleteconsole();
			return allbooks;
		}
	editbook = fopen("books.csv", "r+");
	if (editbook == 0)
	{
		printf("Проблема с открытием файла с книгами\n");
		if (doing == '+')
			logging("", "GetBook", 0);
		if (doing == '-')
			logging("", "GiveBook", 0);
		free(str);
		deleteconsole();
		return allbooks;
	}

	editstud = fopen("students.csv", "r");
	if (editstud == 0)
	{
		printf("Проблема с открытием файла с студентами\n");
		if (doing == '+')
			logging("", "GetBook", 0);
		if (doing == '-')
			logging("", "GiveBook", 0);
		free(str);
		deleteconsole();
		fclose(editbook);
		return allbooks;
	}
	allstudents = Srazbienie(editstud, pns);
	if (allstudents == 0)
	{
		printf("Некому выдавать книги, сначала добавьте студента в библиотеку\n");
		if (doing == '+')
			logging("", "GetBook", 0);
		if (doing == '-')
			logging("", "GiveBook", 0);
		free(str);
		deleteconsole();
		fclose(editbook);
		return allbooks;
	}
	printf("Введите номер зачетной книжки студента: ");
	scanstr(str);
	if (str[0] > '9' || str[0] < '0' || str[1] < 'А' || str[1]>'Я' || str[2]>'9' || str[2] < '0' || str[3]>'9' || str[4] < '0' || str[4]>'9' || str[5] < '0' || str[5]>'9' || str[6] != '\0')
	{
		printf("Да, конечно, такой зачётки не может существовать\nКлацни для продолжения");
		if (doing == '+')
			logging("", "GetBook", 0);
		if (doing == '-')
			logging("", "GiveBook", 0);
		deleteconsole();
		free(str);
		free(allstudents);
		fclose(editbook);
		return allbooks;
	}
	for (int i = 0; i < ns; ++i)
		if (strcmp(str, allstudents[i].book) == 0)
		{
			enemys = i;
			counts++;
			break;
		}
	if (counts == 0)
	{
		printf("Студент не найден\nКлацни, чтобы продолжить");
		if (doing == '+')
			logging("", "GetBook", 0);
		if (doing == '-')
			logging("", "GiveBook", 0);
		deleteconsole();
		free(allstudents);
		free(str);
		fclose(editbook);
		return allbooks;
	}

	allstudbook = SBrazbienie(pnsb);

	if (doing == '-')
	{
		printf("Введите дату, когда студент должен сдать книгу (дд.мм.гггг): ");
		scanstr(str);
		if ((str[0] == '3' && str[1] > '1') || (str[0] != '3' && str[1] > '9') || (str[0] == '0' && str[1] == '0') || str[2] != '.' || (str[3] == '0' && str[4] == '0') || (str[3] == '1' && str[4] > '2') || (str[3] == '0' && str[4] > '9') || str[3] > '1' || str[5] != '.' || str[6] != '2' || str[7] != '0' || str[8] > '9' || str[8] < '0' || str[9]>'9' || str[9] < '0' || str[10] != '\0')
		{
			printf("Дата некорректна!\n");
			logging("", "GiveBook", 0);
			deleteconsole();
			free(allstudbook);
			free(allstudents);
			free(str);
			fclose(editbook);
			return allbooks;
		}
		if (allstudbook != 0)
		{
			nsb++;
			copy = (StudBook*)malloc(nsb * sizeof(StudBook));
			for (int i = 0; i < (nsb - 1); ++i)
				copy[i] = allstudbook[i];
			free(allstudbook);
		}
		else
		{
			printf("Файл с студентами и книгами повреждён!\n");
			logging("", "GiveBook", 0);
			deleteconsole();
			free(allstudbook);
			free(allstudents);
			free(str);
			fclose(editbook);
			return allbooks;
		}
		strcpy(copy[nsb - 1].book, allstudents[enemys].book);
		copy[nsb - 1].ISBN = allbooks[enemy].ISBN;
		strcpy(copy[nsb - 1].date, str);
	}
	if (doing == '+')
	{
		for (int i = 0; i < nsb; ++i)
			if (strcmp(allstudents[enemys].book, allstudbook[i].book) == 0)
				if (allbooks[enemy].ISBN == allstudbook[i].ISBN)
				{
					counte++;
					enemye = i;
					break;
				}
		if (counte == 0)
		{
			printf("Этот студент не брал эту книгу!\n");
			logging("", "GetBook", 0);
			deleteconsole();
			free(allstudbook);
			free(allstudents);
			free(str);
			fclose(editbook);
			return allbooks;
		}
		nsb--;
		allstudbook[enemye] = allstudbook[nsb];
		copy = (StudBook*)malloc(nsb * sizeof(StudBook));
		for (int i = 0; i < nsb; ++i)
			copy[i] = allstudbook[i];
		free(allstudbook);
	}

	editstudbook = fopen("student_books.csv", "w");
	if (editstudbook == 0)
	{
		printf("Помни, что эту ошибку вызвать невозможно\nИ если ты это сделал, то как\n");
		if (doing == '+')
			logging("", "GetBook", 0);
		if (doing == '-')
			logging("", "GiveBook", 0);
		deleteconsole();
		free(allstudbook);
		free(allstudents);
		free(str);
		fclose(editbook);
		return allbooks;
	}
	for (int i = 0; i < nsb; ++i)
		fprintf(editstudbook, "%.0lf;%s;%s\n", copy[i].ISBN, copy[i].book, copy[i].date);
	fclose(editstudbook);

	if (doing == '+')
		(allbooks[enemy].remains)++;
	else if (doing == '-')
		(allbooks[enemy].remains)--;

	for (int i = 0; i < (*pn); ++i)
		fprintf(editbook, "%.0lf;%s;%s;%d;%d\n", allbooks[i].ISBN, allbooks[i].author, allbooks[i].name, allbooks[i].all, allbooks[i].remains);

	if (doing == '-')
		printf("Книга *%s* успешно выдана студенту %s\nДоступно теперь: %d\nКлацай для продолжения", allbooks[enemy].name, allstudents[enemys].book, allbooks[enemy].remains);
	else if (doing == '+')
		printf("Книга *%s* успешно принята от студента %s\nДоступно теперь: %d\nКлацай для продолжения", allbooks[enemy].name, allstudents[enemys].book, allbooks[enemy].remains);
	if (doing == '+')
		logging("", "GetBook", 1);
	if (doing == '-')
		logging("", "GiveBook", 1);
	deleteconsole();
	free(allstudents);
	free(str);
	fclose(editbook);
	return allbooks;
}

book* editbook(book* allbooks, int* pn)
{
	FILE* edit;
	char* str = (char*)malloc(N * sizeof(char));
	double ISBN;
	int count = 0, enemy, action, quan;
	edit = fopen("books.csv", "r+");
	if (edit == 0)
	{
		printf("\nОшибка открытия файла с книгами");
		logging("", "EditBook", 0);
		deleteconsole();
		free(str);
		return allbooks;
	}
	printf("Введите ISBN книги, информацию которой необходимо изменить: ");
	scanstr(str);
	ISBN = DMYatoi(str);
	if (ISBN < 1 || ISBN>9999999999)
	{
		printf("Да, конечно, такого ISBN не может существовать\nЗАНОВО!");
		logging("", "EditBook", 0);
		deleteconsole();
		free(str);
		return allbooks;
	}
	for (int i = 0; i < (*pn); ++i)
	{
		if (ISBN == allbooks[i].ISBN)
		{
			++count;
			enemy = i;
		}
	}
	if (count == 0)
	{
		printf("А где книга? А нету, братан. ЗАНОВО!\n");
		logging("", "EditBook", 0);
		deleteconsole();
		free(str);
		return allbooks;
	}
	system("cls");

	printf("\tРедактирование книги (ISBN ");
	if (allbooks[enemy].ISBN < 10)
		for (int i = 0; i < 9; ++i)
			printf("0");
	else if (allbooks[enemy].ISBN < 100)
		for (int i = 0; i < 8; ++i)
			printf("0");
	else if (allbooks[enemy].ISBN < 1000)
		for (int i = 0; i < 7; ++i)
			printf("0");
	else if (allbooks[enemy].ISBN < 10000)
		for (int i = 0; i < 6; ++i)
			printf("0");
	else if (allbooks[enemy].ISBN < 100000)
		for (int i = 0; i < 5; ++i)
			printf("0");
	else if (allbooks[enemy].ISBN < 1000000)
		for (int i = 0; i < 4; ++i)
			printf("0");
	else if (allbooks[enemy].ISBN < 10000000)
		for (int i = 0; i < 3; ++i)
			printf("0");
	else if (allbooks[enemy].ISBN < 100000000)
		for (int i = 0; i < 2; ++i)
			printf("0");
	else if (allbooks[enemy].ISBN < 1000000000)
		for (int i = 0; i < 1; ++i)
			printf("0");
	printf("%.0lf)\n", allbooks[enemy].ISBN);
	printf("Автор: %s\nНазвание: %s\nКоличество книг: %d\nКоличество доступных книг: %d\n",
		allbooks[enemy].author, allbooks[enemy].name, allbooks[enemy].all, allbooks[enemy].remains);
	printf("Что желаете изменить?\n1. Автора \n2. Название \n3. Количество книг\n4. Количество доступных книг\nИтак, выбор: ");

	scanstr(str);
	action = MYatoi(str);
	switch (action)
	{
	case 1:
	{
		printf("Введите нового автора: ");
		scanstr(str);
		strcpy(allbooks[enemy].author, str);
		printf("Автор изменён!");
		logging("", "EditBook_Author", 1);
		break;
	}
	case 2:
	{
		printf("Введите новое название: ");
		scanstr(str);
		strcpy(allbooks[enemy].name, str);
		printf("Название изменёно!");
		logging("", "EditBook_NameBook", 1);
		break;
	}
	case 3:
	{
		printf("Введите новое количество книг: ");
		scanstr(str);
		quan = MYatoi(str);
		if (quan < 0)
		{
			printf("ГЫГЫГЫ, как смешно\nЗАНОВО!");
			logging("", "EditBook", 0);
			deleteconsole();
			free(str);
			return allbooks;
		}
		if (DMYatoi(str) > 30000)
		{
			printf("Наша библиотека не позволяет вместить более 30000 одинаковых книг\nЗАНОВО!");
			logging("", "EditBook", 0);
			deleteconsole();
			free(str);
			return allbooks;
		}
		if (quan >= allbooks[enemy].all)
		{
			allbooks[enemy].remains = (allbooks[enemy].remains + (quan - allbooks[enemy].all));
			allbooks[enemy].all = quan;
		}
		else if ((allbooks[enemy].remains - (allbooks[enemy].all - quan)) >= 0)
		{
			allbooks[enemy].remains = (allbooks[enemy].remains - (allbooks[enemy].all - quan));
			allbooks[enemy].all = quan;
		}
		else
		{
			printf("При этой операции количество доступных книг станет меньше нуля. ЗАНОВО, ВОРЮГА!");
			logging("", "EditBook", 0);
			deleteconsole();
			free(str);
			return allbooks;
		}

		printf("Количество книг изменёно!");
		logging("", "EditBook_Quantity", 1);
		break;
	}
	case 4:
	{
		printf("Введите новое количество доступных книг: ");

		scanstr(str);
		quan = MYatoi(str);
		if (quan < 0)
		{
			printf("ГЫГЫГЫ, как смешно\nЗАНОВО!");
			logging("", "EditBook", 0);
			deleteconsole();
			free(str);
			return allbooks;
		}
		if (quan > allbooks[enemy].all)
		{
			printf("Вы не можете написать больше книг, чем всего в библиотеке\nКлацай");
			logging("", "EditBook", 0);
			deleteconsole();
			free(str);
			return allbooks;
		}
		allbooks[enemy].remains = quan;
		printf("Количество доступных книг изменёно!");
		logging("", "EditBook_AvailableQuantity", 1);
		break;
	}
	default:
	{
		printf("Ты серьёзно не смог ввести всего одну цифру?!\nЗАНОВО!");
		logging("", "EditBook", 0);
		deleteconsole();
		free(str);
		return allbooks;
		break;
	}
	}

	for (int i = 0; i < (*pn); ++i)
		fprintf(edit, "%.0lf;%s;%s;%d;%d\n", allbooks[i].ISBN, allbooks[i].author, allbooks[i].name, allbooks[i].all, allbooks[i].remains);

	fclose(edit);
	free(str);
	deleteconsole();
	return allbooks;
}

book* printbook(book* allbooks, int* pn)
{
	StudBook* allstudbook;
	int actbook, count = 0, enemy, nbs = 0, * pnbs = &nbs;
	char* action = (char*)malloc(Nplus * sizeof(char));
	double ISBN;
	printf("Посмотреть информацию:\n1. По ISBN\n2. По автору\n3. По названию\n");
	printf("Итак, выбор: ");
	scanstr(action);
	printf("%s", action);
	actbook = MYatoi(action);
	system("cls");

	switch (actbook)
	{
	case 1:
	{
		printf("Просмотр информации по ISBN\nВведите ISBN: ");
		scanstr(action);
		ISBN = DMYatoi(action);
		for (int i = 0; i < (*pn); ++i)
			if (ISBN == allbooks[i].ISBN)
			{
				++count;
				enemy = i;
			}
		if (count == 0 || ISBN > 9999999999 || ISBN <= 0)
		{
			printf("А где книга? А нету, братан. ЗАНОВО!\n");
			logging("", "ViewBook", 0);
			deleteconsole();
			free(action);
			return allbooks;
		}
		break;
	}
	case 2:
	{
		int first = 0, area = 1, k = 0, actdel, n;
		Nauthor* author = (Nauthor*)malloc(area * sizeof(Nauthor));
		printf("	Просмотр информации книги по автору\n");
		for (int i = 0, l = 0; i < (*pn); ++i)
		{
			if (first == 0)
			{
				++first;
				strcpy(author[l].author, allbooks[i].author);
				author[l].quan = 1;
				++l;
			}
			else
			{
				for (int z = 0; z < l; ++z)
				{
					if (strcmp(allbooks[i].author, author[z].author) != 0)
						k = 0;
					else k = 1;

					if (k == 1)
					{
						++(author[z].quan);
						break;
					}
					else if (k == 0 && z == (l - 1))
					{
						++area; ++z; ++l;
						author = (Nauthor*)realloc(author, area * sizeof(Nauthor));
						strcpy(author[z].author, allbooks[i].author);
						author[z].quan = 1;
						break;
					}
				}
			}
		}
		for (int i = 0; i < area; ++i)
			printf("%d. %s (*%d* книги)\n", (i + 1), author[i].author, author[i].quan);
		printf("Книга какого автора интересует: ");
		scanstr(action);
		actdel = MYatoi(action) - 1;
		if (actdel >= area || actdel < 0)
		{
			printf("Ха-ха-ха, заново, Петросян\nКлацнуть не забудь\n");
			logging("", "ViewBook", 0);
			deleteconsole();
			free(action);
			free(author);
			return allbooks;
		}
		system("cls");
		printf("	Просмотр книг автора *%s*\n", author[actdel].author);

		for (int i = 0, l = 0; i < (*pn); ++i)
			if (strcmp(author[actdel].author, allbooks[i].author) == 0)
			{
				printf("%d. %s(%d/%d)\n", (l + 1), allbooks[i].name, allbooks[i].remains, allbooks[i].all);
				++l; n = l;
			}
		area = n;
		printf("Каков выбор: ");
		scanstr(action);
		enemy = MYatoi(action) - 1;
		if (enemy >= area || enemy < 0)
		{
			printf("Ха-ха-ха, заново, Петросян\nКлацнуть не забудь\n");
			logging("", "ViewBook", 0);
			deleteconsole();
			free(action);
			free(author);
			return allbooks;
		}
		for (int i = 0, l = -1;; ++i)
		{
			if (strcmp(author[actdel].author, allbooks[i].author) == 0)
				++l;
			if (l == enemy)
			{
				enemy = i;
				break;
			}
		}

		free(author);
		break;
	}
	case 3:
	{
		printf("	Просмотр по названию\nВведите название без ошибок: ");
		enemy = -1;
		scanstr(action);
		for (int i = 0; i < (*pn); ++i)
			if (strcmp(action, allbooks[i].name) == 0)
			{
				enemy = i;
				break;
			}
		if (enemy == -1)
		{
			printf("Такой книги нет в библиотеке/Неправильно введено название книги\nПопробуйте снова");
			logging("", "ViewBook", 0);
			deleteconsole();
			return allbooks;
		}

		break;
	}
	default:
	{
		printf("Ха-ха-ха, заново, Петросян\nКлацнуть не забудь\n");
		logging("", "ViewBook", 0);
		deleteconsole();
		free(action);
		return allbooks;
	}
	}
	system("cls");

	printf("ISBN книги: ");
	if (allbooks[enemy].ISBN < 10)
		for (int i = 0; i < 9; ++i)
			printf("0");
	else if (allbooks[enemy].ISBN < 100)
		for (int i = 0; i < 8; ++i)
			printf("0");
	else if (allbooks[enemy].ISBN < 1000)
		for (int i = 0; i < 7; ++i)
			printf("0");
	else if (allbooks[enemy].ISBN < 10000)
		for (int i = 0; i < 6; ++i)
			printf("0");
	else if (allbooks[enemy].ISBN < 100000)
		for (int i = 0; i < 5; ++i)
			printf("0");
	else if (allbooks[enemy].ISBN < 1000000)
		for (int i = 0; i < 4; ++i)
			printf("0");
	else if (allbooks[enemy].ISBN < 10000000)
		for (int i = 0; i < 3; ++i)
			printf("0");
	else if (allbooks[enemy].ISBN < 100000000)
		for (int i = 0; i < 2; ++i)
			printf("0");
	else if (allbooks[enemy].ISBN < 1000000000)
		for (int i = 0; i < 1; ++i)
			printf("0");
	printf("%.0lf\n", allbooks[enemy].ISBN);

	printf("Автор: %s\n", allbooks[enemy].author);
	printf("Название: %s\n", allbooks[enemy].name);
	printf("Всего в библиотеке: %d\n", allbooks[enemy].all);
	printf("Доступно: %d\n", allbooks[enemy].remains);


	count = 0;
	allstudbook = SBrazbienie(pnbs);
	for (int i = 0; i < nbs; ++i)
		if (allbooks[enemy].ISBN == allstudbook[i].ISBN)
			count++;
	if (count == 0)
	{
		printf("Все студенты сдали эту книгу\n");
	}
	else
	{
		FILE* students = fopen("students.csv", "r");
		student* allstudents = 0;
		int ns = 0, * pns = &ns, coun = 0;
		if (students == 0)
		{
			printf("Доступ к файлу с студентами нарушен!\nКлац");
			logging("", "ViewBook", 0);
			free(allstudbook);
			free(action);
			deleteconsole();
			return allbooks;
		}
		allstudents = Srazbienie(students, pns);
		printf("%d студентов брали эту книгу:\n", count);
		for (int i = 0; i < nbs; ++i)
			if (allbooks[enemy].ISBN == allstudbook[i].ISBN)
				for (int z = 0; z < ns; ++z)
					if (strcmp(allstudents[z].book, allstudbook[i].book) == 0)
					{
						coun++;
						printf("%d. %s-%s %s %s с факультета %s специальности %s - дата сдачи: %s\n",
							coun, allstudents[z].book, allstudents[z].surname, allstudents[z].name,
							allstudents[z].middlename, allstudents[z].fac, allstudents[z].spec, allstudbook[i].date);
					}
		free(allstudents);
	}


	printf("Клацни для продолжения");
	deleteconsole();
	logging("", "ViewBook", 1);
	free(action);
	return allbooks;
}

void BookShellSort(book* allbooks, int* pn)
{
	int step, i, j;
	book* copy = (book*)malloc((*pn) * sizeof(book));
	for (int l = 0; l < (*pn); ++l)
		copy[l] = allbooks[l];
	for (step = (*pn) / 2; step > 0; step /= 2)
		for (i = step; i < (*pn); i++)
			for (j = i - step; j >= 0 && copy[j].ISBN > copy[j + step].ISBN; j -= step)
				BookSwap(copy, j, j + step);
	for (int k = 0; k < (*pn); ++k)
		printtablebook(copy, k);
	free(copy);
}

void BookSwap(book* copy, int i, int j)
{
	book temp;
	temp = copy[i];
	copy[i] = copy[j];
	copy[j] = temp;
}

book* backup(book* allbooks, int* pn)
{
	FILE* backupp, * bibl;
	char* datet = (char*)malloc(N * sizeof(char));
	char* namef = (char*)malloc(N * sizeof(char));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	strncpy(namef, "books ", 6);
	namef[6] = '\0';
	printf("Для восстановления введите дату сохранения в формате дд-мм-гггг чч-мм-сс\nПример: 04-06-2001 06-00-12\nДата сохранения: ");

	scanstr(datet);
	strcat(namef, datet);
	strcat(namef, ".csv");

	backupp = fopen(namef, "r");
	if (backupp == 0)
	{
		printf("Вы не создавали резервного сохранения в это время\nПопробуй еще раз");
		logging("", "BackUpBook", 0);
		deleteconsole();
		free(namef);
		free(datet);
		return allbooks;
	}
	free(allbooks);

	allbooks = razbienie(backupp, pn);
	fclose(backupp);

	bibl = fopen("books.csv", "w+");

	for (int i = 0; i < (*pn); ++i)
		fprintf(bibl, "%.0lf;%s;%s;%d;%d\n", allbooks[i].ISBN, allbooks[i].author, allbooks[i].name, allbooks[i].all, allbooks[i].remains);

	fclose(bibl);
	printf("Библиотека успешно восстановлена из файла %s\nКлацай", namef);
	logging("", "BackUpBook", 1);
	deleteconsole();
	free(namef);
	free(datet);
	return allbooks;
}

int madebackup(book* allbooks, int* pn)
{
	char backup_name[N];
	FILE* backupp;
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(backup_name, N, "books %m-%d-%Y %H-%M-%S.csv", timeinfo);

	backupp = fopen(backup_name, "w");
	if (backupp == 0)
	{
		printf("Что-то пошло не так при создании бэкапа\nКак ты это сделал?\nКлацай");
		logging("", "MadeBackUpBook", 0);
		deleteconsole();
		return -1;
	}

	for (int i = 0; i < (*pn); ++i)
		fprintf(backupp, "%.0lf;%s;%s;%d;%d\n", allbooks[i].ISBN, allbooks[i].author, allbooks[i].name, allbooks[i].all, allbooks[i].remains);

	printf("Бэкап успешно создан, имя и расширение бэкапа: %s\nКлацай, продолжим", backup_name);
	logging("", "MadeBackUpBook", 0);
	deleteconsole();
	fclose(backupp);
	return 1;
}

void printtablebook(book* allbooks, int n)
{
	int l = 0;
	printf("|");
	if (allbooks[n].ISBN < 10)
		for (int i = 0; i < 9; ++i)
			printf("0");
	else if (allbooks[n].ISBN < 100)
		for (int i = 0; i < 8; ++i)
			printf("0");
	else if (allbooks[n].ISBN < 1000)
		for (int i = 0; i < 7; ++i)
			printf("0");
	else if (allbooks[n].ISBN < 10000)
		for (int i = 0; i < 6; ++i)
			printf("0");
	else if (allbooks[n].ISBN < 100000)
		for (int i = 0; i < 5; ++i)
			printf("0");
	else if (allbooks[n].ISBN < 1000000)
		for (int i = 0; i < 4; ++i)
			printf("0");
	else if (allbooks[n].ISBN < 10000000)
		for (int i = 0; i < 3; ++i)
			printf("0");
	else if (allbooks[n].ISBN < 100000000)
		for (int i = 0; i < 2; ++i)
			printf("0");
	else if (allbooks[n].ISBN < 1000000000)
		for (int i = 0; i < 1; ++i)
			printf("0");
	printf("%.0lf", allbooks[n].ISBN);
	printf("|");

	printf("%s", allbooks[n].author);
	for (int i = 0; allbooks[n].author[i] != '\0'; ++i)
		l = i;
	l = 20 - l;
	for (int i = 0; i < l; ++i)
		printf(" ");
	printf("|");

	printf("%s", allbooks[n].name);
	for (int i = 0; allbooks[n].name[i] != '\0'; ++i)
		l = i;
	l = 50 - l;
	for (int i = 0; i < l; ++i)
		printf(" ");
	printf("|");

	printf("%d", allbooks[n].all);
	if (allbooks[n].all < 10)
		for (int i = 0; i < 9; ++i)
			printf(" ");
	else if (allbooks[n].all < 100)
		for (int i = 0; i < 8; ++i)
			printf(" ");
	else if (allbooks[n].all < 1000)
		for (int i = 0; i < 7; ++i)
			printf(" ");
	else if (allbooks[n].all < 10000)
		for (int i = 0; i < 6; ++i)
			printf(" ");
	else if (allbooks[n].all < 100000)
		for (int i = 0; i < 5; ++i)
			printf(" ");
	else if (allbooks[n].all < 1000000)
		for (int i = 0; i < 4; ++i)
			printf(" ");
	else if (allbooks[n].all < 10000000)
		for (int i = 0; i < 3; ++i)
			printf(" ");
	else if (allbooks[n].all < 100000000)
		for (int i = 0; i < 2; ++i)
			printf(" ");
	else if (allbooks[n].all < 1000000000)
		for (int i = 0; i < 1; ++i)
			printf(" ");
	printf("|");

	printf("%d", allbooks[n].remains);
	if (allbooks[n].remains < 10)
		for (int i = 0; i < 9; ++i)
			printf(" ");
	else if (allbooks[n].remains < 100)
		for (int i = 0; i < 8; ++i)
			printf(" ");
	else if (allbooks[n].remains < 1000)
		for (int i = 0; i < 7; ++i)
			printf(" ");
	else if (allbooks[n].remains < 10000)
		for (int i = 0; i < 6; ++i)
			printf(" ");
	else if (allbooks[n].remains < 100000)
		for (int i = 0; i < 5; ++i)
			printf(" ");
	else if (allbooks[n].remains < 1000000)
		for (int i = 0; i < 4; ++i)
			printf(" ");
	else if (allbooks[n].remains < 10000000)
		for (int i = 0; i < 3; ++i)
			printf(" ");
	else if (allbooks[n].remains < 100000000)
		for (int i = 0; i < 2; ++i)
			printf(" ");
	else if (allbooks[n].remains < 1000000000)
		for (int i = 0; i < 1; ++i)
			printf(" ");
	printf("|\n");
	for (int i = 0; i < 108; ++i)
		printf("_");
	printf("\n");
}

void printmenubook()
{
	printf("\tМеню книг\n");
	printf("1. Просмотр всех книг\n");
	printf("2. Добавить книгу\n");
	printf("3. Удалить книгу\n");
	printf("4. Создать резервное сохранение\n");
	printf("5. Восстановить библиотеку из резервного сохранения\n");
	printf("6. Узнать информацию о книге\n");
	printf("7. Редактировать информацию о книге\n");
	printf("8. Выдать книгу студенту\n");
	printf("9. Принять книгу от студента\n");
	printf("0. Выход\n");
}

book* addbook(book* allbooks, int* pn)
{
	int i = 0, n = *pn, count = 0;
	char* digits = (char*)malloc(Nplus * sizeof(char));
	book newbook;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	printf("Введите ISBN книги: ");
	scanstr(digits);
	(newbook.ISBN) = DMYatoi(digits);
	for (i = 0; i < n; ++i)
		if (allbooks[i].ISBN == newbook.ISBN)
		{
			printf("Ну это, существует уже такой ISBN\nКлацни\n");
			logging("", "AddBook", 0);
			deleteconsole();
			free(digits);
			return allbooks;
		}
	if (newbook.ISBN <= 0 || newbook.ISBN > 9999999999)
	{
		printf("УМНИК, ДА?! ВВЁЛ НЕВОЗМОЖНЫЙ ИСЭБЭЭН И ДОВОЛЕН?! ЗАНОВО!\n");
		logging("", "AddBook", 0);
		deleteconsole();
		free(digits);
		return allbooks;
	}
	printf("Введите имя автора книги: ");
	scanstr(newbook.author);
	for (i = 0; i < n; ++i)
		if (strcmp(allbooks[i].author, newbook.author) == 0)
			count++;
	if (count != 0)
		printf("О, книга этого автора уже есть в нашей библиотеке!\n");
	else
		printf("Это новый автор!\n");

	printf("Введите название книги: ");
	scanstr(newbook.name);
	for (i = 0; i < n; ++i)
		if (strcmp(allbooks[i].name, newbook.name) == 0)
		{
			printf("Книга с таким названием уже есть, придумай что-нибудь своё!\nКлацни\n");
			logging("", "AddBook", 0);
			deleteconsole();
			free(digits);
			return allbooks;
		}

	printf("Введите сколько книг имеется: ");
	scanstr(digits);
	newbook.all = MYatoi(digits);
	if (newbook.all == -1)
	{
		printf("ГЫГЫГЫ ПОЧЕМУ БЫ НЕ ВВЕСТИ БУКАВЫ ВМЕСТО ЦИФР\nЗАНОВО");
		logging("", "AddBook", 0);
		deleteconsole();
		free(digits);
		return allbooks;
	}
	if (DMYatoi(digits) > 30000)
	{
		printf("Наша библиотека не позволяет вместить более 30000 книг\nЗАНОВО!");
		logging("", "AddBook", 0);
		deleteconsole();
		free(digits);
		return allbooks;
	}

	newbook.remains = newbook.all;
	FILE* books = fopen("books.csv", "w+");
	(*pn)++;
	allbooks = (book*)realloc(allbooks, ((*pn) * sizeof(book)));

	allbooks[(*pn) - 1] = newbook;

	for (i = 0; i < (*pn); ++i)
		fprintf(books, "%.0lf;%s;%s;%d;%d\n", allbooks[i].ISBN, allbooks[i].author, allbooks[i].name, allbooks[i].all, allbooks[i].remains);
	fclose(books);
	printf("Книга добавлена\nКлацни, и мы продолжим\n");
	logging("", "AddBook", 1);
	deleteconsole();
	free(digits);
	return allbooks;
}

book* deletebook(book* allbooks, int* pn)
{
	StudBook* allstudbook;
	int actbook, enemy, count = 0, nbs = 0, * pnbs = &nbs;
	double ISBN;
	char* action = (char*)malloc(Nplus * sizeof(char));
	printf("Удалить книгу по:\n1. ISBN\n2. Автору\n3. Названию\nИтак, выбор: ");
	scanstr(action);
	actbook = MYatoi(action);
	system("cls");
	switch (actbook)
	{
	case 1:
	{
		int actisbn;
		printf("	Удаление книги по ISBN\n1. Ввести ISBN вручную\n2. Выбрать из *%d* книг\n", *pn);
		printf("Каковы указания: ");
		scanstr(action);
		actisbn = MYatoi(action);

		switch (actisbn)
		{
		case 1:
		{
			printf("	Удаляем вручную...\nЦель: ");
			scanstr(action);
			ISBN = DMYatoi(action);
			for (int i = 0; i < (*pn); ++i)
				if (ISBN == allbooks[i].ISBN)
				{
					++count;
					enemy = i;
				}
			if (count == 0 || ISBN > 9999999999 || ISBN <= 0)
			{
				printf("А где книга? А нету, братан. ЗАНОВО!\n");
				logging("", "DeleteBook", 0);
				deleteconsole();
				free(action);
				return allbooks;
			}
			break;
		}
		case 2:
		{
			printf("	Удаляем на выбор\n");
			for (int i = 0; i < (*pn); ++i)
				printf("%d. %.0lf (%d/%d)\n", i + 1, allbooks[i].ISBN, allbooks[i].remains, allbooks[i].all);
			printf("Цель: ");
			scanstr(action);
			enemy = MYatoi(action) - 1;
			if (enemy < 0 || enemy >((*pn) - 1))
			{
				printf("Серьёзно?! Тебе надо было ввести лишь несколько циферек и ты не смог? ЗАНОВО!\n");
				logging("", "DeleteBook", 0);
				deleteconsole();
				free(action);
				return allbooks;
			}
			break;
		}
		default:
		{
			printf("Ха-ха-ха, заново, Петросян\nКлацнуть не забудь\n");
			logging("", "DeleteBook", 0);
			deleteconsole();
			free(action);
			return allbooks;
		}
		}
		break;
	}
	case 2:
	{
		int first = 0, area = 1, k = 0, actdel, n;
		Nauthor* author = (Nauthor*)malloc(area * sizeof(Nauthor));
		printf("	Удаление книги по автору\n");
		for (int i = 0, l = 0; i < (*pn); ++i)
		{
			if (first == 0)
			{
				++first;
				strcpy(author[l].author, allbooks[i].author);
				author[l].quan = 1;
				++l;
			}
			else
			{
				for (int z = 0; z < l; ++z)
				{
					if (strcmp(allbooks[i].author, author[z].author) != 0)
						k = 0;
					else k = 1;

					if (k == 1)
					{
						++(author[z].quan);
						break;
					}
					else if (k == 0 && z == (l - 1))
					{
						++area; ++z; ++l;
						author = (Nauthor*)realloc(author, area * sizeof(Nauthor));
						strcpy(author[z].author, allbooks[i].author);
						author[z].quan = 1;
						break;
					}
				}
			}
		}
		for (int i = 0; i < area; ++i)
			printf("%d. %s (*%d* книги)\n", (i + 1), author[i].author, author[i].quan);
		printf("Книгу какого автора удалить: ");
		scanstr(action);
		actdel = MYatoi(action) - 1;
		if (actdel >= area || actdel < 0)
		{
			printf("Ха-ха-ха, заново, Петросян\nКлацнуть не забудь\n");
			logging("", "DeleteBook", 0);
			deleteconsole();
			free(action);
			free(author);
			return allbooks;
		}
		system("cls");
		printf("	Удаление книг автора *%s*\n", author[actdel].author);

		for (int i = 0, l = 0; i < (*pn); ++i)
			if (strcmp(author[actdel].author, allbooks[i].author) == 0)
			{
				printf("%d. %s(%d/%d)\n", (l + 1), allbooks[i].name, allbooks[i].remains, allbooks[i].all);
				++l; n = l;
			}
		area = n;
		printf("Каков выбор: ");
		scanstr(action);
		enemy = MYatoi(action) - 1;
		if (enemy >= area || enemy < 0)
		{
			printf("Ха-ха-ха, заново, Петросян\nКлацнуть не забудь\n");
			logging("", "DeleteBook", 0);
			deleteconsole();
			free(action);
			free(author);
			return allbooks;
		}
		for (int i = 0, l = -1;; ++i)
		{
			if (strcmp(author[actdel].author, allbooks[i].author) == 0)
				++l;
			if (l == enemy)
			{
				enemy = i;
				break;
			}
		}

		free(author);
		break;
	}
	case 3:
	{
		printf("	Удаление по названию\nВведите название без ошибок: ");
		enemy = -1;
		scanstr(action);
		for (int i = 0; i < (*pn); ++i)
			if (strcmp(action, allbooks[i].name) == 0)
			{
				enemy = i;
				break;
			}
		if (enemy == -1)
		{
			printf("Такой книги нет в библиотеке/Неправильно введено название книги\nПопробуйте снова");
			logging("", "DeleteBook", 0);
			deleteconsole();
			free(action);
			return allbooks;
		}

		break;
	}
	default:
	{
		printf("Ха-ха-ха, заново, Петросян\nКлацнуть не забудь\n");
		logging("", "DeleteBook", 0);
		deleteconsole();
		free(action);
		return allbooks;
	}
	}

	count = 0;
	allstudbook = SBrazbienie(pnbs);
	for (int i = 0; i < (*pn); ++i)
		if (allstudbook[i].ISBN == allbooks[enemy].ISBN)
			++count;
	if (count != 0)
	{
		printf("Эта книга сейчас есть у студентов\nВы не можете удалить книгу, которую не вернули в библиотеку\nКлац");
		logging("", "DeleteBook", 0);
		deleteconsole();
		free(action);
		free(allstudbook);
		return allbooks;
	}

	allbooks = deletebookNumb(allbooks, pn, enemy);

	printf("Книга удалена из базы!\nКлацни для продожения\n");
	logging("", "DeleteBook", 1);
	deleteconsole();
	free(action);

	return allbooks;
}

book* deletebookNumb(book* allbooks, int* pn, int enemy)
{
	book* copy = (book*)malloc(((*pn) - 1) * sizeof(book));
	FILE* books = fopen("books.csv", "w+");

	allbooks[enemy] = allbooks[((*pn) - 1)];
	(*pn)--;
	for (int i = 0; i < (*pn); ++i)
		copy[i] = allbooks[i];

	for (int i = 0; i < enemy; ++i)
		fprintf(books, "%.0lf;%s;%s;%d;%d\n", copy[i].ISBN, copy[i].author, copy[i].name, copy[i].all, copy[i].remains);

	fclose(books);
	free(allbooks);

	return copy;
}