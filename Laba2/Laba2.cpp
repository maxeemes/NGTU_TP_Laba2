// Laba2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <ctime>
#include "CSMatrix.h"
#include "ConsoleTextStyle.h"
//#include <sstream>
#include <string>
using namespace std;
/*
1.2.Лабораторная работа №2  Разреженные матрицы
Задача 8. Даны две разреженные структурно симметричные матрицы. Из одной матрицы вычесть другую и результат занести в разреженную матрицу CCS.

*/

int ReadConsoleNum(const string Text = "", const int Color = 7);
double **SimmetricMatrixGenerate(CCSMatrix *InCCSMatrix);//генерация матрицы заданного размера
int CCSMatrixToConsole(CCSMatrix *InCCSMatrix, string MatrixName = "Имя матрицы");


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	bool IsExit = false;

	do
	{
		AddConsoleTextColor("_____________________________________________________________________________", 14);
		AddConsoleTextColor("Лабораторная работа 2", 224);
		AddConsoleTextColor("Задача 8", 224);
		AddConsoleTextColor(
			string("Даны две разреженные структурно симметричные матрицы. Из одной матрицы вычесть\n") +
			string("другую и результат занести в разреженную матрицу CCS.\n") +
			string("_____________________________________________________________________________"), 14);
		AddConsoleTextColor("Генерация симметричных матриц", 224);
		int Size = ReadConsoleNum("Введите количество строк/столбцов матрицы...", 14);
		if (Size > 0)
		{
			AddConsoleTextColor("Генерация...", 14);
			//создание массивов матриц
			double **Matrix1 = SimmetricMatrixGenerate(new CCSMatrix(Size, Size));
			Sleep(1000);
			double **Matrix2 = SimmetricMatrixGenerate(new CCSMatrix(Size, Size));
			//вывод матриц
			AddConsoleTextColor("РЕЗУЛЬТАТ:", 14);
			AddConsoleTextColor("1 МАТРИЦА:", 14);
			DoubleSMatrixToConsole(Matrix1, Size, Size);
			AddConsoleTextColor("2 МАТРИЦА:", 14);
			DoubleSMatrixToConsole(Matrix2, Size, Size);
			//перенос матриц в массивы CCS
			AddConsoleTextColor("Перенос матриц в массивы CCS...", 14);
			CCSMatrix *CCSMatrix1 = new CCSMatrix(Size, Size, Matrix1);
			CCSMatrix *CCSMatrix2 = new CCSMatrix(Size, Size, Matrix2);
			//вывод матриц на консоль
			CCSMatrixToConsole(CCSMatrix1, "Матрица 1");
			CCSMatrixToConsole(CCSMatrix2, "Матрица 2");
			//операция вычитания матриц
			AddConsoleTextColor("Вычитание 2 матрицы из 1...", 14);
			*CCSMatrix1 -= *CCSMatrix2;
			//вывод получившейся матрицы
			CCSMatrixToConsole(CCSMatrix1, "Результат вычитания:");
			//очистка выделенной памяти
			delete CCSMatrix1;
			delete CCSMatrix2;
		}
		else
		{
			IsExit = ReadConsoleNum("Ошибка ввода размера матрицы, для выхода введите 1 или любую цифру для продолжения...", 14) == 1;
		}
		IsExit = ReadConsoleNum("Для выхода введите 1 или любую цифру для продолжения...", 14) == 1;
	} while (IsExit == false);

	return 0;
}

int ReadConsoleNum(const string Text, const int Color)
{
	if (!Text.empty())
	{
		AddConsoleTextColor(Text, Color);
	}
	int Num;
	cin >> Num;
	if (Num >= 0)
	{
		return Num;
	}
	return -1;
}

double ** SimmetricMatrixGenerate(CCSMatrix * InCCSMatrix)
{
	int Size = InCCSMatrix->GetRows();
	if (Size > 0 && Size == InCCSMatrix->GetCols())
	{
		double **Matrix = new double*[Size]; // Создаем массив указателей
		srand(time(nullptr));
		for (int IndRow = 0; IndRow < Size; IndRow++)
		{
			Matrix[IndRow] = new double[Size]; // Создаем элементы
			for (int IndCol = 0; IndCol < Size; IndCol++)
			{
				Matrix[IndRow][IndCol] = 0;
			}
		}
		//наполнение массива
		for (int IndRow = 0; IndRow < Size; IndRow++)
		{
			int IndCol = IndRow;
			while (IndCol < Size)
			{
				IndCol += rand() % 10;
				if (IndCol < Size)
				{
					double NewVal = rand() % 10000 / 100.0;
					Matrix[IndRow][IndCol] = NewVal;
					Matrix[IndCol][IndRow] = NewVal;
				}
			}
		}
		return Matrix;
	}
	return nullptr;
}

int CCSMatrixToConsole(CCSMatrix * InCCSMatrix, string MatrixName)
{
	AddConsoleTextColor(MatrixName, 224);
	AddConsoleTextColor("Размер матрицы: " + to_string(InCCSMatrix->GetCols()) + "x" + to_string(InCCSMatrix->GetRows()), 14);
	AddConsoleTextColor("Количество ненулевых значений: " + to_string(InCCSMatrix->GetVals()), 14);
	double *ArrVal = InCCSMatrix->GetArrVal();
	int *ArrIndRow = InCCSMatrix->GetArrIndRow(), *ArrIndCol = InCCSMatrix->GetArrIndCol();
	string TextArrVal = "", TextArrIndRow = "", TextArrIndCol = "";
	for (int IndArrVal = 0; IndArrVal < InCCSMatrix->GetVals(); IndArrVal++)
	{
		if (IndArrVal > 0)
		{
			TextArrVal += ", ";
			TextArrIndRow += ", ";
		}
		TextArrVal += to_string(ArrVal[IndArrVal]);
		TextArrIndRow += to_string(ArrIndRow[IndArrVal]);
	}
	AddConsoleTextColor("Массив ненулевых значений матрицы: " + TextArrVal, 14);
	AddConsoleTextColor("Массив индексов строк матрицы: " + TextArrIndRow, 14);
	//вывод 3 массива
	for (int IndArrCol = 0; IndArrCol <= InCCSMatrix->GetCols(); IndArrCol++)
	{
		if (IndArrCol > 0)
		{
			TextArrIndCol += ", ";
		}
		TextArrIndCol += to_string(ArrIndCol[IndArrCol]);
	}
	AddConsoleTextColor("Массив индексов строк колонок: " + TextArrIndCol, 14);
	return 0;
}
