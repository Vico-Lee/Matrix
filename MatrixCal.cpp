#include "stdafx.h"
#include "MatrixCal.h"
//#include "math.h"


CMatrixCal::CMatrixCal(int m, int n)
{
	name = "普通矩阵";
	row_m = m;
	col_n = n;
	data =new float*[m];   
    for(int i=0;i<m;++i)  
	{
		data[i]=new float[n];
		for(int j=0;j<n;j++)
		{
			data[i][j] = 0;
		}
	}  
	IS_INIT = TRUE;
	if(m == n)
	{
		IS_SQURE = TRUE;
	}
	else
	{
		IS_SQURE = FALSE;
	}
}
CMatrixCal::CMatrixCal(float** resoure,int m, int n)
{
	name = "普通矩阵";
	row_m = m;
	col_n = n;
	data =new float*[m];   
    for(int i=0;i<m;++i)  
	{
		data[i]=new float[n];
		for(int j=0;j<n;j++)
		{
			data[i][j] = resoure[i][j];
		}
	}  
	IS_INIT = TRUE;
	if(m == n)
	{
		IS_SQURE = TRUE;
	}
	else
	{
		IS_SQURE = FALSE;
	}
}
CMatrixCal::CMatrixCal(int m,int n,CString style)//初始化各种形状的模板矩阵
{
	if(style == "circle" && m==n)
	{
		float R = (m-1)/2.0;
		name = "圆形模板矩阵";
		row_m = m;
		col_n = n;
		data =new float*[m];   
		for(int i=0;i<m;++i)  
		{
			data[i]=new float[n];
			for(int j=0;j<n;j++)
			{
				if(((float)(i-R)*(float)(i-R)+(float)(j-R)*(float)(j-R))<=(R*R))
				{
					data[i][j] = 1;
				}
				else
				{
					data[i][j] = 0;
				}
			}
		}  
		IS_INIT = TRUE;
		if(m == n)
		{
			IS_SQURE = TRUE;
		}
		else
		{
			IS_SQURE = FALSE;
		}
	}
	else
	{
		name = "普通矩阵";
		row_m = m;
		col_n = n;
		data =new float*[m];   
		for(int i=0;i<m;++i)  
		{
			data[i]=new float[n];
			for(int j=0;j<n;j++)
			{
				data[i][j] = 0;
			}
		}  
		IS_INIT = TRUE;
		if(m == n)
		{
			IS_SQURE = TRUE;
		}
		else
		{
			IS_SQURE = FALSE;
		}
	}
}
CMatrixCal::CMatrixCal()
{
	IS_INIT = FALSE;
}

CMatrixCal::~CMatrixCal(void)
{
	//if(data != NULL)
	//{
	//	for(int i = 0; i < row_m; i++) //分级释放堆上的数组内存
	//	{
	//		delete []data[i];
	//		data[i] = NULL;
	//	}
	//	delete []data;
	//	data = NULL;
	//}
}
void CMatrixCal::InitMatrix(int m, int n)
{
	name = "普通矩阵";
	row_m = m;
	col_n = n;
	data =new float*[m];   
    for(int i=0;i<m;++i)  
	{
		data[i]=new float[n];
		for(int j=0;j<n;j++)
		{
			data[i][j] = 0;
		}
	}  
	IS_INIT = TRUE;
	if(m == n)
	{
		IS_SQURE = TRUE;
	}
	else
	{
		IS_SQURE = FALSE;
	}
}
float** CMatrixCal::init_floatmatrix(int m, int n)
{
	float** res =new float*[m];   
	for(int i=0;i<m;++i)  
	{
		res[i]=new float[n];
		for(int j=0;j<n;j++)
		{
			res[i][j] = 0;
		}
	}  
	return res;
}
void CMatrixCal::releasedata(float**p,int m)
{
	for(int i = 0; i < m; i++) //分级释放堆上的数组内存
    {
        delete []p[i];
	}
	delete []p;
	p=NULL;
}
void CMatrixCal::Release()
{
	if(IS_INIT)
	{
		for(int i = 0; i < row_m; i++) //分级释放堆上的数组内存
		{
		   delete []data[i];
		   data[i]=NULL;
		}
		delete []data;
		data = NULL;
		IS_INIT = FALSE;
	}
}
BOOL CMatrixCal::CheckSqure()//检查是否方阵
{
	if(IS_INIT)
	{
		if(row_m == col_n)
		{
			IS_SQURE = TRUE;
		}
		else
		{
			IS_SQURE = FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}
void CMatrixCal::SetAllData(float num)//把所有值设成num
{
	for(int m =0;m<row_m;m++)
	{
		for(int n=0;n<col_n;n++)
		{
			data[m][n] = num;
		}
	}
}
//把第row行（从1开始算起）（取值1~row）设成一个数值
void CMatrixCal::SetRowData(int row, float num)//把第row行（从1开始算起）（取值1~row）设成一个数值
{
	if(row<=0 || row> row_m)
	{
		CString str;
		str.Format("行数设置为：%d\n可取值范围为：1~ %d",row,row_m);
		AfxMessageBox(str);
		return;
	}
	for(int n=0;n<col_n;n++)
	{
		data[row-1][n] = num;
	}
}
//把第col列（从1开始算起）（取值1~col）设成一个数值
void CMatrixCal::SetColData(int col, float num)//把第col列（从1开始算起）（取值1~col）设成一个数值
{
	if(col<=0 || col> col_n)
	{
		CString str;
		str.Format("列数设置为：%d\n可取值范围为：1 - %d",col,col_n);
		AfxMessageBox(str);
		return;
	}
	for(int m=0;m<row_m;m++)
	{
		data[m][col-1] = num;
	}
}
//把M矩阵中从row_begin到row_end行、col_begin到col_end列提取出来，生成新的矩阵（从1开始算起）
CMatrixCal CMatrixCal::SeletctPartMatrixByRowCol(CMatrixCal M, int row_begin,int row_end,int col_begin,int col_end)
{
	
	if(col_begin<=0 || row_begin<=0)
	{
		CString str;
		str.Format("起始行：%d 起始列：%d，不能小于0",row_begin,col_begin);
		AfxMessageBox(str);
		CMatrixCal M_error(1,1);
		M_error.ChangeName("错误矩阵");
		return M_error;
	}
	else if(col_end>M.col_n || row_end>M.row_m)
	{
		CString str;
		str.Format("终止行：%d 终止列：%d，原矩阵行数：%d,原矩阵列数：%d，超出范围",row_end,col_end,M.row_m,M.col_n);
		AfxMessageBox(str);
		CMatrixCal M_error(1,1);
		M_error.ChangeName("错误矩阵");
		return M_error;
	}
	else if((col_end - col_begin)<0 || (row_end - row_begin)<0)
	{
		CString str;
		str.Format("起始行：%d,终止行：%d,起始列：%d,终止列：%d,超出范围",row_begin,row_end,col_begin,col_end);
		AfxMessageBox(str);
		CMatrixCal M_error(1,1);
		M_error.ChangeName("错误矩阵");
		return M_error;
	}
	int row_new = row_end - row_begin + 1;
	int col_new = col_end - col_begin + 1;
	CMatrixCal M_new(row_new,col_new);
	for(int m=0;m<row_new;m++)
	{
		for(int n=0;n<col_new;n++)
		{
			M_new.data[m][n] = M.data[row_begin-1+m][col_begin-1+n];
		}
	}
	return M_new;
}
float CMatrixCal::Det_3D(CMatrixCal Matrix)
{
	float res;
	if(!Matrix.IS_SQURE)
	{
		AfxMessageBox("矩阵不是方阵，无法计算行列式");
		return -996699;
	}
	else if(Matrix.row_m != 3)
	{
		AfxMessageBox("矩阵不是三阶矩阵");
		return -996699;
	}
	else
	{
		res = Matrix.data[0][0]*Matrix.data[1][1]*Matrix.data[2][2]
			+Matrix.data[0][1]*Matrix.data[1][2]*Matrix.data[2][0]
			+Matrix.data[0][2]*Matrix.data[1][0]*Matrix.data[2][1]
			-Matrix.data[0][2]*Matrix.data[1][1]*Matrix.data[2][0]
			-Matrix.data[0][1]*Matrix.data[1][0]*Matrix.data[2][2]
			-Matrix.data[0][0]*Matrix.data[1][2]*Matrix.data[2][1];
		return res;
	}	
}
float CMatrixCal::Det_3D()
{
	float res;
	if(!IS_SQURE)
	{
		AfxMessageBox("矩阵不是方阵，无法计算行列式");
		return -996699;
	}
	else if(row_m != 3)
	{
		AfxMessageBox("矩阵不是三阶矩阵");
		return -996699;
	}
	else
	{
		res = data[0][0]*data[1][1]*data[2][2]
			+data[0][1]*data[1][2]*data[2][0]
			+data[0][2]*data[1][0]*data[2][1]
			-data[0][2]*data[1][1]*data[2][0]
			-data[0][1]*data[1][0]*data[2][2]
			-data[0][0]*data[1][2]*data[2][1];
		return res;
	}	
}
float CMatrixCal::Det(CMatrixCal Matrix)
{
	float res = 0;
	if(Matrix.row_m == 3)
	{
		res = Det_3D(Matrix);
	}
	else
	{
		for(int i=0;i<Matrix.row_m;i++)
		{
			int j=0;
			int index = i+j;
			float aij;
			if (index %2==0)
			{
				aij = Matrix.data[i][j];
			}
			else
			{
				aij = -Matrix.data[i][j];
			}
			CMatrixCal Mij = Matrix.Det_Mij(Matrix,i,j);
			res = res+aij*Det(Mij);
			Mij.Release();
		}
	}
	return res;
}
float CMatrixCal::Det()
{
	if(!IS_SQURE)
	{
		AfxMessageBox("矩阵不是方阵，无法计算行列式");
		return -996699;
	}
	float res = 0;
	if(row_m == 2)
	{
		res = data[0][0]*data[1][1] - data[0][1]*data[1][0];
	}
	if(row_m == 3)
	{
		res = Det_3D();
	}
	else
	{
		for(int i=0;i<row_m;i++)
		{
			int j=0;
			int index = i+j;
			float aij;
			if (index %2==0)
			{
				aij = data[i][j];
			}
			else
			{
				aij = -data[i][j];
			}
			CMatrixCal Mij = Det_Mij(i,j);
			res = res+aij*Det(Mij);
			Mij.Release();
		}
	}
	return res;
}
CMatrixCal CMatrixCal::Det_Mij(CMatrixCal Matrix, int i, int j)//获取代数余子式
{
	int m = Matrix.row_m-1;
	int n = Matrix.col_n-1;
	CMatrixCal Mij(m,n);

	//int row = 0, col = 0;

	for(int row=0;row<m;row++)
	{
		for(int col=0;col<n;col++)
		{
			if(row<i && col<j)
			{
				Mij.data[row][col] = Matrix.data[row][col];
			}
			else if(row>=i && col<j)
			{
				Mij. data[row][col] = Matrix.data[row+1][col];
			}
			else if(row<i && col>=j)
			{
				Mij. data[row][col] = Matrix.data[row][col+1];
			}
			else if(row>=i && col>=j)
			{
				Mij. data[row][col] = Matrix.data[row+1][col+1];
			}
		}
	}
	return Mij;
}
CMatrixCal CMatrixCal::Det_Mij(int i, int j)//获取代数余子式
{
	int m = row_m-1;
	int n = col_n-1;
	CMatrixCal Mij(m,n);

	//int row = 0, col = 0;

	for(int row=0;row<m;row++)
	{
		for(int col=0;col<n;col++)
		{
			if(row<i && col<j)
			{
				Mij.data[row][col] = data[row][col];
			}
			else if(row>=i && col<j)
			{
				Mij. data[row][col] = data[row+1][col];
			}
			else if(row<i && col>=j)
			{
				Mij. data[row][col] = data[row][col+1];
			}
			else if(row>=i && col>=j)
			{
				Mij. data[row][col] = data[row+1][col+1];
			}
		}
	}
	return Mij;
}

float CMatrixCal::Trace()
{
	float res =0;
	if(!IS_SQURE)
	{
		AfxMessageBox("矩阵不是方阵，无法计算行列式");
		return -996699;
	}
	else
	{
		for(int i=0;i<row_m;i++)
		{
			res = res+data[i][i];
		}
		return res;
	}
}
CMatrixCal CMatrixCal::Transpose(CMatrixCal Matrix)//矩阵转置
{
	CMatrixCal MT(Matrix.col_n,Matrix.row_m);
	for(int m=0;m<Matrix.col_n;m++)
	{
		for(int n=0;n<Matrix.row_m;n++)
		{
			MT.data[m][n] = Matrix.data[n][m];
		}
	}
	return MT;
}
void CMatrixCal::Transpose()
{
	int m_new = col_n;
	int n_new = row_m;
	float** temp = init_floatmatrix(m_new,n_new);
	for(int m=0;m<m_new;m++)
	{
		for(int n=0;n<n_new;n++)
		{
			temp[m][n] = data[n][m];
		}
	}
	releasedata(data,row_m);
	data = temp;
	row_m = m_new;
	col_n = n_new;
}
void CMatrixCal::ChangeName(CString str)
{
	name = str;
}
CMatrixCal CMatrixCal::LoadMatrix(float** data,int width, int height)
{
	CMatrixCal Matrix(height,width);
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			Matrix.data[i][j] = data[i][j];
		}
	}
	return Matrix;
}
void CMatrixCal::ShowData()
{
	CString str;
	for(int i=0;i<row_m;i++)
	{
		for(int j=0;j<col_n;j++)
		{
			CString temp;
			temp.Format("%.3f	",data[i][j]);
			str = str+temp;
		}
		str = str+"\n";
	}
	str+=name;
	AfxMessageBox(str);
}
void CMatrixCal::ShowStruct()//显示矩阵结构
{
	CString str;
	str.Format("矩阵行数：%d\n矩阵列数：%d\n",row_m,col_n);
	str+=name;
	AfxMessageBox(str);
}
void CMatrixCal::CopyMatrixData(CMatrixCal M)
{
	if(row_m != M.row_m || col_n != M.col_n)
	{
		CString str;
		str.Format("矩阵构型不同（赋值）：M:%d行%d列，操作矩阵：%d行%d列。",row_m,col_n,M.row_m,M.col_n);
		AfxMessageBox(str);
	}
	else
	{
		for(int m=0;m<row_m;m++)
		{
			for(int n=0;n<col_n;n++)
			{
				data[m][n] = M.data[m][n];
			}
		}
	}
}
CMatrixCal CMatrixCal::Plus(CMatrixCal M1, CMatrixCal M2)//M1+M2
{
	CMatrixCal M(M1.row_m,M1.col_n);
	if(M1.row_m != M2.row_m || M1.col_n != M2.col_n)
	{
		CString str;
		str.Format("矩阵构型不同（加法）：M1:%d行%d列，M2：%d行%d列。",M1.row_m,M1.col_n,M2.row_m,M2.col_n);
		AfxMessageBox(str);
	}
	else
	{
		for(int m=0;m<M.row_m;m++)
		{
			for(int n=0;n<M.col_n;n++)
			{
				M.data[m][n] = M1.data[m][n]+M2.data[m][n];
			}
		}
	}
	return M;
}
void CMatrixCal::PlusBy(CMatrixCal Matrix)//M+Matrix
{
	if(row_m != Matrix.row_m || col_n != Matrix.col_n)
	{
		CString str;
		str.Format("矩阵构型不同（加法）：M:%d行%d列，操作矩阵：%d行%d列。",row_m,col_n,Matrix.row_m,Matrix.col_n);
		AfxMessageBox(str);
	}
	else
	{
		for(int m=0;m<row_m;m++)
		{
			for(int n=0;n<col_n;n++)
			{
				data[m][n] = data[m][n]+Matrix.data[m][n];
			}
		}
	}
}
CMatrixCal CMatrixCal::Plus(CMatrixCal M1, float p)//M=M1+M2 同型矩阵加
{
	CMatrixCal M(M1.row_m,M1.col_n);
	for(int m=0;m<M.row_m;m++)
	{
		for(int n=0;n<M.col_n;n++)
		{
			M.data[m][n] = M1.data[m][n]+p;
		}
	}
	return M;
}
void CMatrixCal::PlusBy(float p)//M = M+Matrix
{
	for(int m=0;m<row_m;m++)
	{
		for(int n=0;n<col_n;n++)
		{
			data[m][n] = data[m][n]+p;
		}
	}
}
CMatrixCal CMatrixCal::Multiply(CMatrixCal M1, CMatrixCal M2)//M=M1*M2
{
	CMatrixCal M(M1.row_m,M2.col_n);
	if(M1.col_n != M2.row_m)
	{
		CString str;
		str.Format("矩阵构型不同（乘法）：M1:%d行%d列，M2：%d行%d列。",M1.row_m,M1.col_n,M2.row_m,M2.col_n);
		AfxMessageBox(str);
	}
	else
	{
		for(int m=0;m<M.row_m;m++)
		{
			for(int n=0;n<M.col_n;n++)
			{
				M.data[m][n] = 0;
				for(int k=0;k<M1.col_n;k++)
				{
					M.data[m][n] = M.data[m][n]+ M1.data[m][k]*M2.data[k][n];
				}
			}
		}
	}
	return M;
}
CMatrixCal Multiply(CMatrixCal M1, float p)//M=M1*p
{
	CMatrixCal M(M1.row_m,M1.col_n);
	for(int m=0;m<M.row_m;m++)
	{
		for(int n=0;n<M.col_n;n++)
		{
			M.data[m][n] = 0;
			for(int k=0;k<M1.col_n;k++)
			{
				M.data[m][n] = M.data[m][n]+ M1.data[m][k]*p;
			}
		}
	}
	return M;
}
void CMatrixCal::MultiBy(CMatrixCal M)//Matrix=Matrix*M;
{
	if(col_n != M.row_m)
	{
		CString str;
		str.Format("矩阵构型不同（乘法）：M:%d行%d列，操作矩阵：%d行%d列。",row_m,col_n,M.row_m,M.col_n);
		AfxMessageBox(str);
	}
	else
	{
		int m_new = row_m;
		int n_new = M.col_n;
		float** temp = init_floatmatrix(m_new,n_new);
		for(int m=0;m<m_new;m++)
		{
			for(int n=0;n<n_new;n++)
			{
				temp[m][n] = 0;
				for(int k=0;k<col_n;k++)
				{
					temp[m][n] = temp[m][n]+ data[m][k]*M.data[k][n];
				}
			}
		}
		releasedata(data,row_m);
		data = temp;
		row_m = m_new;
		col_n = n_new;
	}
}
void CMatrixCal::MultiBy(float p)//Matrix=p*M;
{	
	for(int m=0;m<row_m;m++)
	{
		for(int n=0;n<col_n;n++)
		{
			data[m][n] = p*data[m][n];
		}
	}
}
CMatrixCal CMatrixCal::Dot(CMatrixCal M1, CMatrixCal M2)//M=M1点乘M2;
{
	CMatrixCal M(M1.row_m,M1.col_n);
	if(M1.row_m != M2.row_m || M1.col_n != M2.col_n)
	{
		CString str;
		str.Format("矩阵构型不同（点乘）：M1:%d行%d列，M2：%d行%d列。",M1.row_m,M1.col_n,M2.row_m,M2.col_n);
		AfxMessageBox(str);
	}
	else
	{
		for(int m=0;m<M.row_m;m++)
		{
			for(int n=0;n<M.col_n;n++)
			{
				M.data[m][n] = M1.data[m][n]*M2.data[m][n];
			}
		}
	}
	return M;
}
void CMatrixCal::DotBy(CMatrixCal M)//Matrix=Matrix点乘M
{
	if(row_m != M.row_m || col_n != M.col_n)
	{
		CString str;
		str.Format("矩阵构型不同（点乘）：M:%d行%d列，操作矩阵：%d行%d列。",row_m,col_n,M.row_m,M.col_n);
		AfxMessageBox(str);
	}
	else
	{
		for(int m=0;m<row_m;m++)
		{
			for(int n=0;n<col_n;n++)
			{
				data[m][n] = data[m][n]*M.data[m][n];
			}
		}
	}
}
CMatrixCal CMatrixCal::Sub(CMatrixCal M1, CMatrixCal M2)//M=M1-M2
{
	CMatrixCal M(M1.row_m,M1.col_n);
	if(M1.row_m != M2.row_m || M1.col_n != M2.col_n)
	{
		CString str;
		str.Format("矩阵构型不同（减法）：M1:%d行%d列，M2：%d行%d列。",M1.row_m,M1.col_n,M2.row_m,M2.col_n);
		AfxMessageBox(str);
	}
	else
	{
		for(int m=0;m<M.row_m;m++)
		{
			for(int n=0;n<M.col_n;n++)
			{
				M.data[m][n] = M1.data[m][n]-M2.data[m][n];
			}
		}
	}
	return M;
}
void CMatrixCal::SubBy(CMatrixCal Matrix)//M = M-Matrix
{
	if(row_m != Matrix.row_m || col_n != Matrix.col_n)
	{
		CString str;
		str.Format("矩阵构型不同（减法）：M:%d行%d列，加矩阵：%d行%d列。",row_m,col_n,Matrix.row_m,Matrix.col_n);
		AfxMessageBox(str);
	}
	else
	{
		for(int m=0;m<row_m;m++)
		{
			for(int n=0;n<col_n;n++)
			{
				data[m][n] = data[m][n]-Matrix.data[m][n];
			}
		}
	}
}
float CMatrixCal::SumAll()
{
	float res = 0;
	for(int m=0;m<row_m;m++)
	{
		for(int n=0;n<col_n;n++)
		{
			res = res+data[m][n];
		}
	}
	return res;
}
CMatrixCal CMatrixCal::AddRow(CMatrixCal M1, CMatrixCal M2)//把同列数矩阵M2矩阵，加到M1的下方
{
	CMatrixCal M(M1.row_m+M2.row_m,M1.col_n);
	if(M1.col_n != M2.col_n)
	{
		CString str;
		str.Format("矩阵构型不同（按行叠加）：M1:%d列，M2：%d列。",M1.col_n,M2.col_n);
		AfxMessageBox(str);
	}
	else
	{
		for(int m=0;m<M1.row_m;m++)
		{
			for(int n=0;n<M1.col_n;n++)
			{
				M.data[m][n] = M1.data[m][n];
			}
		}
		for(int m=0;m<M2.row_m;m++)
		{
			for(int n=0;n<M2.col_n;n++)
			{
				M.data[m+M1.row_m][n] = M1.data[m][n];
			}
		}
	}
	return M;
}
void CMatrixCal::AddRowBy(CMatrixCal M)//把同列数矩阵M矩阵，加到原矩阵的下方
{
	if(col_n != M.col_n)
	{
		CString str;
		str.Format("矩阵构型不同（按行叠加）：M1:%d列，M2：%d列。",col_n,M.col_n);
		AfxMessageBox(str);
	}
	else
	{
		int m_new = row_m + M.row_m;
		int n_new = col_n;
		float** temp = init_floatmatrix(m_new,n_new);

		for(int m=0;m<row_m;m++)
		{
			for(int n=0;n<col_n;n++)
			{
				temp[m][n] = data[m][n];
			}
		}
		for(int m=0;m<M.row_m;m++)
		{
			for(int n=0;n<M.col_n;n++)
			{
				temp[m+row_m][n] = M.data[m][n];
			}
		}
		releasedata(data,row_m);
		data = temp;
		row_m = m_new;
		col_n = n_new;
	}
}