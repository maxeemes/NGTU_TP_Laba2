#include "CSMatrix.h"

CCSMatrix::CCSMatrix(const int InRows, const int InCols) : Rows(InRows), Cols(InCols)
{
	delete[] ArrIndCol;
	ArrIndCol = new int[InCols + 1]{ 0 }; //создание массива
										  //заполнение массива нулями
}

CCSMatrix::CCSMatrix(const int InRows, const int InCols, const double * const * const Matrix) : CCSMatrix(InRows, InCols)
{
	if (MatrixToCCS(Matrix, InRows, InCols) < 0)
	{
		delete this;
		CCSMatrix(InRows, InCols);
	}
}

int CCSMatrix::SetVal(const double Val, const int IndRow, const int IndCol)
{
	//проверка значения в матрице
	double OldVal;
	int ValInMatrix = GetVal(IndRow, IndCol, &OldVal);
	if (ValInMatrix < 0)
	{
		return ValInMatrix;
	}
	if (ValInMatrix >= 0 && OldVal == Val)
	{
		return 0;
	}
	//сохранение значения
	if (ValInMatrix == 0)
	{
		//сохранение нового ненулевого значения в матрице
		//обновление массива ArrIndCol
		for (int IndAICol = IndCol + 1; IndAICol <= Cols; IndAICol++)
		{
			ArrIndCol[IndAICol]++;
		}
		//перезапись массивов ArrVal и ArrIndRow
		int NewVals = Vals + 1;
		double *NewArrVal = new double[NewVals];
		int *NewArrIndRow = new int[NewVals];
		for (int IndAIRow = 0, NewIndAIRow = 0; NewIndAIRow < NewVals; IndAIRow++, NewIndAIRow++)
		{
			if (IndAIRow == NewIndAIRow && IndAIRow >= ArrIndCol[IndCol])
			{
				if ((IndAIRow < Vals && (ArrIndRow[IndAIRow] > IndRow || IndAIRow == ArrIndCol[IndCol + 1]) || IndAIRow == Vals))
				{
					NewArrVal[NewIndAIRow] = Val;
					NewArrIndRow[NewIndAIRow] = IndRow;
					NewIndAIRow++;
				}
			}
			if (IndAIRow < Vals)
			{
				NewArrVal[NewIndAIRow] = ArrVal[IndAIRow];
				NewArrIndRow[NewIndAIRow] = ArrIndRow[IndAIRow];
			}
		}
		Vals = NewVals;
		delete[] ArrVal;
		delete[] ArrIndRow;
		ArrVal = NewArrVal;
		ArrIndRow = NewArrIndRow;
		return 2;
	}
	else if (ValInMatrix == 1 && Val != 0)
	{
		//замена ненулевого значения в матрице (изменение 1 значения в массиве ArrVal)
		for (int IndAIRow = ArrIndCol[IndCol]; IndAIRow < ArrIndCol[IndCol + 1]; IndAIRow++)
		{
			if (ArrIndRow[IndAIRow] == IndRow)
			{
				ArrVal[IndAIRow] = Val;
				return 1;
			}
		}
	}
	else if (ValInMatrix == 1 && Val == 0)
	{
		//вставка нулевого значения вместо ненулевго
		//обновление массива ArrIndCol
		for (int IndAICol = IndCol + 1; IndAICol <= Cols; IndAICol++)
		{
			ArrIndCol[IndAICol]--;
		}
		//перезапись массивов ArrVal и ArrIndRow
		double *NewArrVal = new double[Vals - 1];
		double *NewArrIndRow = new double[Vals - 1];
		for (int IndAIRow = 0, NewIndAIRow = 0; IndAIRow < Vals; IndAIRow++, NewIndAIRow++)
		{
			if (IndAIRow == NewIndAIRow && IndAIRow >= ArrIndCol[IndCol])
			{
				if (ArrIndRow[IndAIRow] > IndRow || IndAIRow == ArrIndCol[IndCol + 1])
				{
					NewArrVal[NewIndAIRow] = Val;
					NewArrIndRow[NewIndAIRow] = IndRow;
					NewIndAIRow--;
				}
			}
			NewArrVal[NewIndAIRow] = ArrVal[IndAIRow];
			NewArrIndRow[NewIndAIRow] = ArrIndRow[IndAIRow];
		}
		return 3;
	}

	return -1;
}

int CCSMatrix::GetVal(const int IndRow, const int IndCol, double *const OutVal)
{
	//проверка значений индексов
	if (IndRow >= Rows || IndCol >= Cols) return -2;
	//проверка наличия ненулевых значений в матрице
	if (Vals == 0)
	{
		if (OutVal != 0) *OutVal = 0;
		return 0;
	}
	if (Vals > 0)
	{
		//получения количества значений в колонке
		int IndCols;
		int NumValCol = GetNumValCol(IndCol, &IndCols);
		if (NumValCol <= 0 || NumValCol > Cols)
		{
			if (OutVal != 0) *OutVal = 0;
			return 0;
		}
		//получение требуемого значения
		int IndAIRow = IndCols - NumValCol;
		while (IndAIRow < IndCols && ArrIndRow[IndAIRow] <= IndRow)
		{
			if (ArrIndRow[IndAIRow] == IndRow)
			{
				if (OutVal != 0) *OutVal = ArrVal[IndAIRow];
				return 1;
			}
			IndAIRow++;
		}
		if (OutVal != 0) *OutVal = 0;
		return 0;
	}
	return -1;
}

int CCSMatrix::GetRows()
{
	return Rows;
}

int CCSMatrix::GetCols()
{
	return Cols;
}

int CCSMatrix::GetVals()
{
	return Vals;
}

double * CCSMatrix::GetArrVal()
{
	double *OutArrVal = new double[Vals];
	for (int IndArrVal = 0; IndArrVal < Vals; IndArrVal++)
	{
		OutArrVal[IndArrVal] = ArrVal[IndArrVal];
	}
	return OutArrVal;
}

int * CCSMatrix::GetArrIndRow()
{
	int *OutArrIndRow = new int[Vals];
	for (int IndArrIndRow = 0; IndArrIndRow < Vals; IndArrIndRow++)
	{
		OutArrIndRow[IndArrIndRow] = ArrIndRow[IndArrIndRow];
	}
	return OutArrIndRow;
}

int * CCSMatrix::GetArrIndCol()
{
	int *OutArrIndCol = new int[Cols + 1];
	for (int IndArrIndCol = 0; IndArrIndCol <= Cols; IndArrIndCol++)
	{
		OutArrIndCol[IndArrIndCol] = ArrIndCol[IndArrIndCol];
	}
	return OutArrIndCol;
}

CCSMatrix & CCSMatrix::operator-=(CCSMatrix & ref)
{
	if (this->Rows != ref.Rows || Cols != ref.Cols) return *this;
	for (int IndCol = 0; IndCol <= Cols; IndCol++)
	{
		for (int IndVal = ref.ArrIndCol[IndCol]; IndVal < ref.ArrIndCol[IndCol + 1]; IndVal++)
		{
			double OldVal;
			if (GetVal(ref.ArrIndRow[IndVal], IndCol, &OldVal) < 0)
			{
				return *this;
			}
			double NewVal = OldVal - ref.ArrVal[IndVal];
			if (SetVal(NewVal, ref.ArrIndRow[IndVal], IndCol) < 0)
			{
				return *this;
			}
		}
	}
	return *this;
}

int CCSMatrix::SetAllVals(const int InRows, const int InCols, const int NewVals, double * const NewArrVal, int * const NewArrIndRow, int * const NewArrIndCol)
{
	if (NewArrIndCol[InCols] == NewVals)
	{
		//delete this;
		CCSMatrix(InRows, InCols);
		delete[] ArrIndCol;
		Vals = NewVals;
		ArrVal = NewArrVal;
		ArrIndRow = NewArrIndRow;
		ArrIndCol = NewArrIndCol;
		return 1;
	}
	return -1;
}

int CCSMatrix::GetNumValRow(const int IndRow, int *const StartIndRow)
{
	//проверка корректности индекса строки
	if (IndRow < 0 || IndRow >= Rows) return -1;
	//получение количества значений
	int NumValRow = 0;
	int IndAIRow = 0;
	while (IndAIRow < Vals)
	{
		if (ArrIndRow[IndAIRow] == IndRow)
		{
			NumValRow++;
			if (NumValRow == 1 && StartIndRow != 0)
			{
				*StartIndRow = IndAIRow;
			}
		}
		IndAIRow++;
	}
	return NumValRow;
}

int CCSMatrix::GetNumValCol(const int IndCol, int *const IndCols)
{
	//проверка корректности индекса столбца
	if (IndCol < 0 || IndCol >= Cols) return -1;
	//получение количества значений
	if (IndCols != 0) *IndCols = ArrIndCol[IndCol + 1];
	return ArrIndCol[IndCol + 1] - ArrIndCol[IndCol];
}

int CCSMatrix::MatrixToCCS(const double *const *const Matrix, const int MRows, const int MCols)
{
	if (MRows != Rows || MCols != Cols) return -2;
	//поиск и сохранение ненулевых значений
	//подсчет ненулевых значений и заполнение массива индексации столбцов
	int NewVals = 0;
	int *NewArrIndCol = new int[Cols + 1]{ 0 };
	for (int IndCol = 0; IndCol < MCols; IndCol++)
	{
		for (int IndRow = 0; IndRow < MRows; IndRow++)
		{
			if (Matrix[IndCol][IndRow] != 0)
			{
				NewVals++;
			}
		}
		NewArrIndCol[IndCol + 1] = NewVals;
	}
	//сохранение ненулевых значений в массив значений и индексов строк
	double *NewArrVal = new double[NewVals];
	int *NewArrIndRow = new int[NewVals];
	for (int IndCol = 0, IndVal = 0; IndCol < MCols; IndCol++)
	{
		int IndRow = 0;
		while (NewArrIndCol[IndCol + 1] > IndVal)
		{
			if (Matrix[IndCol][IndRow] != 0)
			{
				NewArrVal[IndVal] = Matrix[IndCol][IndRow];
				NewArrIndRow[IndVal] = IndRow;
				IndVal++;
			}
			IndRow++;
		}
	}
	//сохранение новых значений в массивы класса
	return SetAllVals(MRows, MCols, NewVals, NewArrVal, NewArrIndRow, NewArrIndCol);
}


CCSMatrix::~CCSMatrix()
{
	if (Vals > 0)
	{
		delete[] ArrVal;
		delete[] ArrIndRow;
	}
	delete[] ArrIndCol;
	Rows = 0;
	Cols = 0;
	Vals = 0;
}
