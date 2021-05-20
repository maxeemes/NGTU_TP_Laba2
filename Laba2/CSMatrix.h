class CCSMatrix
{
public:
	~CCSMatrix();
	CCSMatrix(const int InRows, const int InCols);
	CCSMatrix(const int InRows, const int InCols, const double *const *const Matrix);
	int SetVal(const double Val, const int IndRow, const int IndCol);			//��������� ������� �������� �� ���������� �������
	int GetVal(const int IndRow, const int IndCol, double *const OutVal = 0);	//��������� �������� ������� �� ������ � �������
	int GetRows();
	int GetCols();
	int GetVals();
	double *GetArrVal();
	int *GetArrIndRow();
	int *GetArrIndCol();

	CCSMatrix &operator-=(CCSMatrix &ref);	//�������� �������� ������
private:
	int Rows = 0;						//���������� ����� �������
	int Cols = 0;						//���������� ��������� �������
	int Vals = 0;						//���������� ��������� �������� � �������
	double *ArrVal;						//������ ��������� ��������
	int *ArrIndRow;						//������ �������� �����
	int *ArrIndCol = new int[1]{ 0 };	//������ ���������� ��������
	int SetAllVals(const int InRows, const int InCols, const int NewVals, double * const NewArrVal, int * const NewArrIndRow, int * const NewArrIndCol);	//���������� ������� �������� ������
	int GetNumValRow(const int IndRow, int *const StartIndRow = 0);																							//��������� ���������� �������� � ������
	int GetNumValCol(const int IndCol, int *const PrevIndCols = 0);																							//��������� ���������� �������� � �������
	int MatrixToCCS(const double *const *const Matrix, const int MRows, const int MCols);																	//�������������� ������� ������� � ����������� CCS
};
