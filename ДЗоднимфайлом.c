#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#define N 100
#define Nplus 20
#define Nchar 100000
  
//Объявление общих функций
void deleteconsole();
int scanstr(char*);
int MYatoi(char*);
float FMYatoi(char*);
double DMYatoi(char*);
int power(int , int);
float Fpower(int, int);
double Dpower(int , int);
//Конец об общ функций

//Объявление для функций студента
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
//Конец объявлений для студента

//Объявление для функций книг
typedef struct book {
	double ISBN;
	char author[N];
	char name[N];
	int all;
	int remains;
}book;
typedef struct Nauthor
{
	char author[N];
	int quan;
}Nauthor;
book* razbienie(FILE*, int*);
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
//Конец объявлений для функций книг

//Объявление авторизации
typedef struct user {
	char login[N];
	char password[N];
	int book;
	int student;
}user;
user* auth(user*);
user USER;
//Конец авторизации

//Объявление объединения книг и студентов
typedef struct StudBook {
	double ISBN;
	char book[7];
	char date[11];
}StudBook;
StudBook* SBrazbienie(int*);
//конец

//лог
typedef struct log {
	char date[20];
	char user[N];
	char step[N];
	char progress[Nplus];
}log;
int logging(const char *, const char *, int);
//лог

//проверка на валидность
int valid();
//вал

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


//лог
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
//лог

//Объединение
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
//конец об

//Функции авторизации
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
//Конец авторизации

//Книжные функции
void menubook()
{
	int i, c, n = 0, * pn = &n, actbook = 1;
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
	FILE* editbook,* editstudbook,* editstud;
	student* allstudents = 0;
	StudBook* allstudbook = 0, *copy = 0;
	char* str = (char*)malloc(N * sizeof(char));
	double ISBN;
	int count = 0, enemy, enemys, enemye, ns = 0, * pns = &ns, counts = 0, nsb = 0, *pnsb=&nsb, counte=0;
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
	if(editstud == 0)
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
		if ((str[0] == '3' && str[1] > '1') || (str[0] != '3' && str[1] > '9') ||(str[0] == '0' && str[1] == '0') ||str[2] != '.' || (str[3] == '0' && str[4] == '0') ||(str[3]=='1' &&str[4]>'2')|| (str[3] == '0' && str[4] > '9')||str[3]>'1' || str[5] != '.' || str[6] != '2' || str[7] != '0' || str[8] > '9' || str[8] < '0' || str[9]>'9' || str[9] < '0' || str[10] != '\0')
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
			for (int i = 0; i < (nsb-1); ++i)
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
		strcpy(copy[nsb-1].book, allstudents[enemys].book);
		copy[nsb-1].ISBN = allbooks[enemy].ISBN;
		strcpy(copy[nsb-1].date, str);
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
	if(editstudbook==0)
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

	if(doing=='+')
		(allbooks[enemy].remains)++;
	else if(doing=='-')
		(allbooks[enemy].remains)--;

	for (int i = 0; i < (*pn); ++i)
		fprintf(editbook, "%.0lf;%s;%s;%d;%d\n", allbooks[i].ISBN, allbooks[i].author, allbooks[i].name, allbooks[i].all, allbooks[i].remains);

	if (doing == '-')
		printf("Книга *%s* успешно выдана студенту %s\nДоступно теперь: %d\nКлацай для продолжения", allbooks[enemy].name,allstudents[enemys].book, allbooks[enemy].remains);
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
	int actbook, count = 0, enemy, nbs=0,*pnbs=&nbs;
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

	bibl = fopen("books", "w+");

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
	int actbook, enemy, count = 0, nbs = 0, *pnbs=&nbs;
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
//Конец книжных функций

//Функции студента
void menustudent()
{
	int i, c, n = 0, * pn = &n, actstud = 1;
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
	FILE* students;
	char* str = (char*)malloc(N * sizeof(char));
	char* act = (char*)malloc(N * sizeof(char));
	int count = 0, enemy = 0, action, quan, l = 0, first = 0, nbs = 0, *pnbs = &nbs;

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
		int nb = 0, * pnb = &nb, coun=0;
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
			for(int z =0;z<nb;++z)
				if (allbooks[z].ISBN == allstudbook[i].ISBN)
				{
					coun++;
					printf("%d. ",
						coun, allbooks[z].ISBN, allbooks[z].author, allbooks[z].name, allstudbook[i].date);

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
	double ISBN;
	int count = 0, enemy, action, quan;
	students = fopen("students.csv", "w+");
	if (students == 0)
	{
		printf("\nОшибка открытия файла");
		logging("", "EditStudent", 0);
		deleteconsole();
		free(str);
		return allstudents;
	}
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
	int actstudent, enemy, count = 0, nbs = 0, * pnbs = &nbs;
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
//Конец функций студента

//Общие функции
int MYatoi(char* massiv)								//Функция переводит массив символов в число
{
	int p = 0, l, i = 0;

	while (massiv[i] != '\0')
	{
		if (massiv[i] < '0' || massiv[i]>'9')
			return -1;
		++i;
	}
	for (l = 0; massiv[l] != '\0'; ++l)
	{
		--i;
		p = p + (massiv[l] - '0') * power(10, i);
	}
	return p;
}

float FMYatoi(char* massiv)
{
	int l, i = 0;
	float p = 0;
	while (massiv[i] != '\0')
	{
		if (massiv[i] < '0' || massiv[i]>'9')
			return -1;
		++i;
	}
	for (l = 0; massiv[l] != '\0'; ++l)
	{
		--i;
		p = p + (massiv[l] - '0') * Fpower(10, i);
	}
	return p;
}

double DMYatoi(char* massiv)
{
	int l, i = 0;
	double p = 0;
	while (massiv[i] != '\0')
	{
		if (massiv[i] < '0' || massiv[i]>'9')
			return -1;
		++i;
	}
	for (l = 0; massiv[l] != '\0'; ++l)
	{
		--i;
		p = p + (massiv[l] - '0') * Dpower(10, i);
	}
	return p;
}

int power(int x, int n)								//Возведение числа x в степень n
{
	int i, p;
	p = 1;

	if (n > 0)
		for (i = 1; i <= n; ++i)
			p = p * x;
	return p;
}

float Fpower(int x, int n)								//Возведение числа x в степень n double
{
	int i;
	float p;
	p = 1;

	if (n > 0)
		for (i = 1; i <= n; ++i)
			p = p * x;
	return p;
}

double Dpower(int x, int n)								//Возведение числа x в степень n double
{
	int i;
	double p;
	p = 1;

	if (n > 0)
		for (i = 1; i <= n; ++i)
			p = p * x;
	return p;
}

int scanstr(char* str)
{

	char c = getchar();

	while (c == ' ' || c == '\t' || c == '\n')
	{
		c = getchar();
	}
	str[0] = c;


	int i;
	for (i = 0; str[i] != '\n'; ++i)
	{

		str[i + 1] = getchar();

	}
	str[i] = '\0';
	return 1;
}

void deleteconsole()
{
	_getch();
	system("cls");
}
//Конец общих функций
