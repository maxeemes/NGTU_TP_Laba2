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
1.2.������������ ������ �2  ����������� �������
������ 8. ���� ��� ����������� ���������� ������������ �������. �� ����� ������� ������� ������ � ��������� ������� � ����������� ������� CCS.

*/

int ReadConsoleNum(const string Text = "", const int Color = 7);
double **SimmetricMatrixGenerate(CCSMatrix *InCCSMatrix);//��������� ������� ��������� �������
int CCSMatrixToConsole(CCSMatrix *InCCSMatrix, string MatrixName = "��� �������");


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	bool IsExit = false;

	do
	{
		AddConsoleTextColor("_____________________________________________________________________________", 14);
		AddConsoleTextColor("������������ ������ 2", 224);
		AddConsoleTextColor("������ 8", 224);
		AddConsoleTextColor(
			string("���� ��� ����������� ���������� ������������ �������. �� ����� ������� �������\n") +
			string("������ � ��������� ������� � ����������� ������� CCS.\n") +
			string("_____________________________________________________________________________"), 14);
		AddConsoleTextColor("��������� ������������ ������", 224);
		int Size = ReadConsoleNum("������� ���������� �����/�������� �������...", 14);
		if (Size > 0)
		{
			AddConsoleTextColor("���������...", 14);
			//�������� �������� ������
			double **Matrix1 = SimmetricMatrixGenerate(new CCSMatrix(Size, Size));
			Sleep(1000);
			double **Matrix2 = SimmetricMatrixGenerate(new CCSMatrix(Size, Size));
			//����� ������
			AddConsoleTextColor("���������:", 14);
			AddConsoleTextColor("1 �������:", 14);
			DoubleSMatrixToConsole(Matrix1, Size, Size);
			AddConsoleTextColor("2 �������:", 14);
			DoubleSMatrixToConsole(Matrix2, Size, Size);
			//������� ������ � ������� CCS
			AddConsoleTextColor("������� ������ � ������� CCS...", 14);
			CCSMatrix *CCSMatrix1 = new CCSMatrix(Size, Size, Matrix1);
			CCSMatrix *CCSMatrix2 = new CCSMatrix(Size, Size, Matrix2);
			//����� ������ �� �������
			CCSMatrixToConsole(CCSMatrix1, "������� 1");
			CCSMatrixToConsole(CCSMatrix2, "������� 2");
			//�������� ��������� ������
			AddConsoleTextColor("��������� 2 ������� �� 1...", 14);
			*CCSMatrix1 -= *CCSMatrix2;
			//����� ������������ �������
			CCSMatrixToConsole(CCSMatrix1, "��������� ���������:");
			//������� ���������� ������
			delete CCSMatrix1;
			delete CCSMatrix2;
		}
		else
		{
			IsExit = ReadConsoleNum("������ ����� ������� �������, ��� ������ ������� 1 ��� ����� ����� ��� �����������...", 14) == 1;
		}
		IsExit = ReadConsoleNum("��� ������ ������� 1 ��� ����� ����� ��� �����������...", 14) == 1;
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
		double **Matrix = new double*[Size]; // ������� ������ ����������
		srand(time(nullptr));
		for (int IndRow = 0; IndRow < Size; IndRow++)
		{
			Matrix[IndRow] = new double[Size]; // ������� ��������
			for (int IndCol = 0; IndCol < Size; IndCol++)
			{
				Matrix[IndRow][IndCol] = 0;
			}
		}
		//���������� �������
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
	AddConsoleTextColor("������ �������: " + to_string(InCCSMatrix->GetCols()) + "x" + to_string(InCCSMatrix->GetRows()), 14);
	AddConsoleTextColor("���������� ��������� ��������: " + to_string(InCCSMatrix->GetVals()), 14);
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
	AddConsoleTextColor("������ ��������� �������� �������: " + TextArrVal, 14);
	AddConsoleTextColor("������ �������� ����� �������: " + TextArrIndRow, 14);
	//����� 3 �������
	for (int IndArrCol = 0; IndArrCol <= InCCSMatrix->GetCols(); IndArrCol++)
	{
		if (IndArrCol > 0)
		{
			TextArrIndCol += ", ";
		}
		TextArrIndCol += to_string(ArrIndCol[IndArrCol]);
	}
	AddConsoleTextColor("������ �������� ����� �������: " + TextArrIndCol, 14);
	return 0;
}
