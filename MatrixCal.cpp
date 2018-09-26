#include "stdafx.h"
#include "MatrixCal.h"
//#include "math.h"


CMatrixCal::CMatrixCal(int m, int n)
{
	name = "��ͨ����";
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
CMatrixCal::CMatrixCal()
{
	IS_INIT = FALSE;
}

CMatrixCal::~CMatrixCal(void)
{
	//for(int i = 0; i < row_m; i++) //�ּ��ͷŶ��ϵ������ڴ�
 //   {
 //       delete []data[i];
	//}
}
void CMatrixCal::InitMatrix(int m, int n)
{
	name = "��ͨ����";
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
	for(int i = 0; i < m; i++) //�ּ��ͷŶ��ϵ������ڴ�
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
		for(int i = 0; i < row_m; i++) //�ּ��ͷŶ��ϵ������ڴ�
		{
		   delete []data[i];
		}
		delete []data;
		data = NULL;
		IS_INIT = FALSE;
	}
}
BOOL CMatrixCal::CheckSqure()//����Ƿ���
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
void CMatrixCal::SetAllData(float num)//������ֵ���num
{
	for(int m =0;m<row_m;m++)
	{
		for(int n=0;n<col_n;n++)
		{
			data[m][n] = num;
		}
	}
}
//�ѵ�row�У���1��ʼ���𣩣�ȡֵ0~row-1�����һ����ֵ
void CMatrixCal::SetRowData(int row, float num)//�ѵ�row�У���1��ʼ���𣩣�ȡֵ0~row-1�����һ����ֵ
{
	if(row<=0 || row> row_m)
	{
		CString str;
		str.Format("��������Ϊ��%d\n��ȡֵ��ΧΪ��1~ %d",row,row_m);
		AfxMessageBox(str);
		return;
	}
	for(int n=0;n<col_n;n++)
	{
		data[row-1][n] = num;
	}
}
//�ѵ�col�У���1��ʼ���𣩣�ȡֵ0~col-1�����һ����ֵ
void CMatrixCal::SetColData(int col, float num)//�ѵ�col�У���1��ʼ���𣩣�ȡֵ0~col-1�����һ����ֵ
{
	if(col<=0 || col> col_n)
	{
		CString str;
		str.Format("��������Ϊ��%d\n��ȡֵ��ΧΪ��1 - %d",col,col_n);
		AfxMessageBox(str);
		return;
	}
	for(int m=0;m<row_m;m++)
	{
		data[m][col-1] = num;
	}
}
float CMatrixCal::Det_3D(CMatrixCal Matrix)
{
	float res;
	if(!Matrix.IS_SQURE)
	{
		AfxMessageBox("�����Ƿ����޷���������ʽ");
		return -996699;
	}
	else if(Matrix.row_m != 3)
	{
		AfxMessageBox("���������׾���");
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
		AfxMessageBox("�����Ƿ����޷���������ʽ");
		return -996699;
	}
	else if(row_m != 3)
	{
		AfxMessageBox("���������׾���");
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
	float res = 0;
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
CMatrixCal CMatrixCal::Det_Mij(CMatrixCal Matrix, int i, int j)//��ȡ��������ʽ
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
CMatrixCal CMatrixCal::Det_Mij(int i, int j)//��ȡ��������ʽ
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
		AfxMessageBox("�����Ƿ����޷���������ʽ");
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
CMatrixCal CMatrixCal::Transpose(CMatrixCal Matrix)//����ת��
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
void CMatrixCal::ShowStruct()//��ʾ����ṹ
{
	CString str;
	str.Format("����������%d\n����������%d\n",row_m,col_n);
	str+=name;
	AfxMessageBox(str);
}
void CMatrixCal::CopyMatrixData(CMatrixCal M)
{
	if(row_m != M.row_m || col_n != M.col_n)
	{
		CString str;
		str.Format("�����Ͳ�ͬ����ֵ����M:%d��%d�У���������%d��%d�С�",row_m,col_n,M.row_m,M.col_n);
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
		str.Format("�����Ͳ�ͬ���ӷ�����M1:%d��%d�У�M2��%d��%d�С�",M1.row_m,M1.col_n,M2.row_m,M2.col_n);
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
		str.Format("�����Ͳ�ͬ���ӷ�����M:%d��%d�У���������%d��%d�С�",row_m,col_n,Matrix.row_m,Matrix.col_n);
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
CMatrixCal CMatrixCal::Plus(CMatrixCal M1, float p)//M=M1+M2 ͬ�;����
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
		str.Format("�����Ͳ�ͬ���˷�����M1:%d��%d�У�M2��%d��%d�С�",M1.row_m,M1.col_n,M2.row_m,M2.col_n);
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
		str.Format("�����Ͳ�ͬ���˷�����M:%d��%d�У���������%d��%d�С�",row_m,col_n,M.row_m,M.col_n);
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
CMatrixCal CMatrixCal::Dot(CMatrixCal M1, CMatrixCal M2)//M=M1���M2;
{
	CMatrixCal M(M1.row_m,M1.col_n);
	if(M1.row_m != M2.row_m || M1.col_n != M2.col_n)
	{
		CString str;
		str.Format("�����Ͳ�ͬ����ˣ���M1:%d��%d�У�M2��%d��%d�С�",M1.row_m,M1.col_n,M2.row_m,M2.col_n);
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
void CMatrixCal::DotBy(CMatrixCal M)//Matrix=Matrix���M
{
	if(row_m != M.row_m || col_n != M.col_n)
	{
		CString str;
		str.Format("�����Ͳ�ͬ����ˣ���M:%d��%d�У���������%d��%d�С�",row_m,col_n,M.row_m,M.col_n);
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
		str.Format("�����Ͳ�ͬ����������M1:%d��%d�У�M2��%d��%d�С�",M1.row_m,M1.col_n,M2.row_m,M2.col_n);
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
		str.Format("�����Ͳ�ͬ����������M:%d��%d�У��Ӿ���%d��%d�С�",row_m,col_n,Matrix.row_m,Matrix.col_n);
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
CMatrixCal CMatrixCal::AddRow(CMatrixCal M1, CMatrixCal M2)//��ͬ��������M2���󣬼ӵ�M1���·�
{
	CMatrixCal M(M1.row_m+M2.row_m,M1.col_n);
	if(M1.col_n != M2.col_n)
	{
		CString str;
		str.Format("�����Ͳ�ͬ�����е��ӣ���M1:%d�У�M2��%d�С�",M1.col_n,M2.col_n);
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
void CMatrixCal::AddRowBy(CMatrixCal M)//��ͬ��������M���󣬼ӵ�ԭ������·�
{
	if(col_n != M.col_n)
	{
		CString str;
		str.Format("�����Ͳ�ͬ�����е��ӣ���M1:%d�У�M2��%d�С�",col_n,M.col_n);
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