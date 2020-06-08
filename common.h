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
#define N 100
#define Nplus 20
#define Nchar 100000
void deleteconsole();
int scanstr(char*);
int MYatoi(char*);
float FMYatoi(char*);
double DMYatoi(char*);
int power(int, int);
float Fpower(int, int);
double Dpower(int, int);

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