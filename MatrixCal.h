#pragma once
class CMatrixCal
{
public:
	CMatrixCal(int m, int n);
	CMatrixCal();
	~CMatrixCal(void);

public:
	//基本功能
	float** init_floatmatrix(int m, int n);
	void releasedata(float** p,int m);
	CMatrixCal LoadMatrix(float** data,int width, int height);//把一个二维数组构建成矩阵
	void InitMatrix(int m, int n);//初始化矩阵，与第一构造函数等同。第二构造时需要初始化
	void Release();//释放矩阵数据，初始化标签取消
	void ShowData();//显示矩阵值
	void ShowStruct();//显示矩阵结构

	//矩阵参数
	int row_m;//行数
	int col_n;//列数
	float** data;//矩阵二维数据
	CString name;//矩阵名称
	BOOL IS_SQURE;//是否是方阵
	BOOL IS_INIT;//是否被初始化

	//矩阵自处理
	BOOL CheckSqure();//检查是否方阵
	void SetAllData(float num);//把所有值设成num
	void SetRowData(int row, float num);//把第row行（从0开始算起）（取值0~row-1）设成一个数值
	void SetColData(int col, float num);//把第col列（从0开始算起）（取值0~col-1）设成一个数值

	float Det_3D(CMatrixCal Matrix);//3阶行列式计算
	float Det_3D();
	float Det(CMatrixCal Matrix);//任意行列式计算
	float Det();
	CMatrixCal Det_Mij(CMatrixCal Matrix, int i, int j);//获取i行j列代数余子式
	CMatrixCal Det_Mij(int i, int j);//获取i行j列代数余子式
	CMatrixCal Transpose(CMatrixCal Matrix);//矩阵转置
	void Transpose();//矩阵自转置
	void ChangeName(CString str);//矩阵更新名称
	float Trace();//求迹运算
	float SumAll();//矩阵所有元素求和

	CMatrixCal AddRow(CMatrixCal M1, CMatrixCal M2);//把同列数矩阵M2矩阵，加到M1的下方
	void AddRowBy(CMatrixCal M);//把同列数矩阵M矩阵，加到原矩阵的下方

	//矩阵间运算
	void CopyMatrixData(CMatrixCal M);

	CMatrixCal Plus(CMatrixCal M1, CMatrixCal M2);//M=M1+M2 同型矩阵加法
	void PlusBy(CMatrixCal Matrix);//M = M+Matrix
	CMatrixCal Plus(CMatrixCal M1, float p);//M=M1+M2 同型矩阵加法
	void PlusBy(float p);//M = M+Matrix

	CMatrixCal Sub(CMatrixCal M1, CMatrixCal M2);//M=M1-M2 同型矩阵减法
	void SubBy(CMatrixCal Matrix);//M = M-Matrix

	CMatrixCal Multiply(CMatrixCal M1, CMatrixCal M2);//M=M1*M2; 矩阵乘法
	CMatrixCal Multiply(CMatrixCal M1, float p);//M=M1*p; 矩阵乘数
	void MultiBy(CMatrixCal M);//Matrix=Matrix*M;
	void MultiBy(float p);//Matrix=p*M;

	CMatrixCal Dot(CMatrixCal M1, CMatrixCal M2);//M=M1点乘M2; 同型矩阵点乘
	void DotBy(CMatrixCal M);//Matrix=Matrix点乘M;

	



	
};

