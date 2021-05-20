class CCSMatrix
{
public:
	~CCSMatrix();
	CCSMatrix(const int InRows, const int InCols);
	CCSMatrix(const int InRows, const int InCols, const double *const *const Matrix);
	int SetVal(const double Val, const int IndRow, const int IndCol);			//установка нужного значения по указанному индексу
	int GetVal(const int IndRow, const int IndCol, double *const OutVal = 0);	//получение занчения матрицы по строке и столбцу
	int GetRows();
	int GetCols();
	int GetVals();
	double *GetArrVal();
	int *GetArrIndRow();
	int *GetArrIndCol();

	CCSMatrix &operator-=(CCSMatrix &ref);	//операция разности матриц
private:
	int Rows = 0;						//количество строк матрицы
	int Cols = 0;						//количество столбюцов матрицы
	int Vals = 0;						//количество ненулевых значений в матрице
	double *ArrVal;						//массив ненулевых значений
	int *ArrIndRow;						//массив индексов строк
	int *ArrIndCol = new int[1]{ 0 };	//массив индексации столбцов
	int SetAllVals(const int InRows, const int InCols, const int NewVals, double * const NewArrVal, int * const NewArrIndRow, int * const NewArrIndCol);	//сохранение готовых значений класса
	int GetNumValRow(const int IndRow, int *const StartIndRow = 0);																							//получение количества значений в строке
	int GetNumValCol(const int IndCol, int *const PrevIndCols = 0);																							//получение количества значений в столбце
	int MatrixToCCS(const double *const *const Matrix, const int MRows, const int MCols);																	//преобразование обычной матрицы в разреженную CCS
};
