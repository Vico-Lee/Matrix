#pragma once
class CMatrixCal
{
public:
	CMatrixCal(int m, int n);
	CMatrixCal(float**,int m, int n);//�����ݳ�ʼ������
	CMatrixCal(int m,int n,CString style);//��ʼ��������״��ģ�����
	CMatrixCal();
	~CMatrixCal(void);

public:
	//////////////////////////////////////////////////////////////////////////////��������
	float** init_floatmatrix(int m, int n);
	void releasedata(float** p,int m);
	CMatrixCal LoadMatrix(float** data,int width, int height);//��һ����ά���鹹���ɾ���
	void InitMatrix(int m, int n);//��ʼ���������һ���캯����ͬ���ڶ�����ʱ��Ҫ��ʼ��
	void InitMatrix(int m, int n,CString style);//��ʼ���������һ���캯����ͬ���ڶ�����ʱ��Ҫ��ʼ��
	void Release();//�ͷž������ݣ���ʼ����ǩȡ��
	void ShowDataShort();//��ʾ����ֵ
	void ShowData();//��ʾ����ֵ
	void ShowRowData(int Row);//��ʾ�����Row�У���1���㣩ֵ
	void ShowColData(int Col);//��ʾ�����Col�У���1���㣩ֵ
	void ShowData(int Row, int Col);//��ʾ�����Row�У���1���㣩��Col�У���1���㣩ֵ
	void ShowStruct();//��ʾ����ṹ
	void ShowMaxMin();//��ʾ����ֵ
	void ShowMaxMin_Row(int Row);//��ʾ�����Row�У���1���㣩��ֵ
	void ShowMaxMin_Col(int Col);//��ʾ�����Col�У���1���㣩��ֵ

	//�������
	int row_m;//����
	int col_n;//����
	float** data;//�����ά����
	CString name;//��������
	BOOL IS_SQURE;//�Ƿ��Ƿ���
	BOOL IS_INIT;//�Ƿ񱻳�ʼ��

	//////////////////////////////////////////////////////////////////////////////�����Դ���: ���漰������������������¾���Ĵ���
	//��ֵ����
	BOOL CheckSqure();//����Ƿ���
	void SetAllData(float num);//������ֵ���num
	void SetRowData(int row, float num);//�ѵ�row�У���1��ʼ���𣩣�ȡֵ1~row�����һ����ֵnum
	void SetColData(int col, float num);//�ѵ�col�У���1��ʼ���𣩣�ȡֵ1~col�����һ����ֵnum
	CMatrixCal SeletctPartMatrixByRowCol(CMatrixCal M, int row_begin,int row_end,int col_begin,int col_end);//��M�����д�row_begin��row_end�С�col_begin��col_end����ȡ�����������µľ��󣨴�1��ʼ����
	//����ʽ����
	float Det_3D(CMatrixCal Matrix);//3������ʽ����
	float Det_3D();
	float Det(CMatrixCal Matrix);//��������ʽ����
	float Det();//////////////////////////���Ϻ��ʵ�ʲ�������/////////////////////////////////�漰������Det_3D()��Det_Mij
	CMatrixCal Det_Mij(CMatrixCal Matrix, int i, int j);//��ȡi��j�д�������ʽ
	CMatrixCal Det_Mij(int i, int j);//��ȡi��j�д�������ʽ
	//��������
	CMatrixCal Transpose(CMatrixCal Matrix);//����ת��
	void Transpose();//������ת��
	void ChangeName(CString str);//�����������
	float Trace();//������
	float SumAll();//��������Ԫ�����
	float SumRow(int row);//�Ե�row����ͣ�row��1��ʼ���㣻
	float SumCol(int col);//�Ե�col����ͣ�col��1��ʼ���㣻
	CMatrixCal SumRow_toCol(CMatrixCal M);//����������ͣ���������������
	void SumRow_toCol();//����������ͣ���������������
	CMatrixCal SumCol_toRow(CMatrixCal M);//����������ͣ���������������
	void SumCol_toRow();//����������ͣ���������������
	CMatrixCal OppositeMatrix(CMatrixCal Matrix);//ȡM = -Matrix��ȡ�෴����
	void OppositeMatrix();//ȡM = -M��ȡ�෴����
	float Max_ofAll();//ȡ������������ֵ
	float Min_ofAll();//ȡ�����������Сֵ
	float Max_ofRow(int Row);//ȡ�����Row�У���1���㣩�����ֵ
	float Min_ofRow(int Row);//ȡ�����Row�У���1���㣩����Сֵ
	float Max_ofCol(int Col);//ȡ�����Col�У���1���㣩�����ֵ
	float Min_ofCol(int Col);//ȡ�����Col�У���1���㣩����Сֵ

	void Segmente_toBinary(float t);//��������ֵ>tʱ����ֵΪ1������Ϊ0
	void Check_LargetValue(float t);//��������ֵ>tʱ����ֵΪ0�����಻��
	//�������д���
	CMatrixCal AddRow(CMatrixCal M1, CMatrixCal M2);//��ͬ��������M2���󣬼ӵ�M1���·�
	void AddRowBy(CMatrixCal M);//��ͬ��������M���󣬼ӵ�ԭ������·�

	//////////////////////////////////////////////////////////////////////////////��������㣺�����漰�������������
	
	void CopyMatrixData(CMatrixCal M);//��һ���������ֵ��������ǰ����

	//�������㷨��
	CMatrixCal Plus(CMatrixCal M1, CMatrixCal M2);//M=M1+M2 ͬ�;���ӷ�
	void PlusBy(CMatrixCal Matrix);//M = M+Matrix
	CMatrixCal Plus(CMatrixCal M1, float p);//M=M1+M2 ͬ�;���ӷ�
	void PlusBy(float p);//M = M+Matrix
	CMatrixCal Plus_MatrixByColV(CMatrixCal M1, CMatrixCal V);//M=M1+V,V����������
	void Plus_MatrixByColV(CMatrixCal V);//M = M+V;V��������
	CMatrixCal Plus_MatrixByRowV(CMatrixCal M1, CMatrixCal V);//M=M1+V,V����������
	void Plus_MatrixByRowV(CMatrixCal V);//M = M+V;V��������


	CMatrixCal Sub(CMatrixCal M1, CMatrixCal M2);//M=M1-M2 ͬ�;������
	void SubBy(CMatrixCal Matrix);//M = M-Matrix

	CMatrixCal Multiply(CMatrixCal M1, CMatrixCal M2);//M=M1*M2; ����˷�
	CMatrixCal Multiply(CMatrixCal M1, float p);//M=M1*p; �������
	void MultiBy(CMatrixCal M);//Matrix=Matrix*M;
	void MultiBy(float p);//Matrix=p*M;

	CMatrixCal Dot(CMatrixCal M1, CMatrixCal M2);//M=M1���M2; ͬ�;�����
	void DotBy(CMatrixCal M);//Matrix=Matrix���M;

	


	//���ӹ���
	double gaussrand(double,double);//���ɵ����˹����
	double randomUniform(double dMinValue,double dMaxValue);//���ȷֲ�
};

