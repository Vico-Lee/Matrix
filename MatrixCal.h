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
	void Release();//�ͷž������ݣ���ʼ����ǩȡ��
	void ShowData();//��ʾ����ֵ
	void ShowStruct();//��ʾ����ṹ

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

	CMatrixCal Sub(CMatrixCal M1, CMatrixCal M2);//M=M1-M2 ͬ�;������
	void SubBy(CMatrixCal Matrix);//M = M-Matrix

	CMatrixCal Multiply(CMatrixCal M1, CMatrixCal M2);//M=M1*M2; ����˷�
	CMatrixCal Multiply(CMatrixCal M1, float p);//M=M1*p; �������
	void MultiBy(CMatrixCal M);//Matrix=Matrix*M;
	void MultiBy(float p);//Matrix=p*M;

	CMatrixCal Dot(CMatrixCal M1, CMatrixCal M2);//M=M1���M2; ͬ�;�����
	void DotBy(CMatrixCal M);//Matrix=Matrix���M;

	



	
};

