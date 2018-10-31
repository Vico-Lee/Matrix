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
CMatrixCal::CMatrixCal(float** resoure,int m, int n)
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

//��ʼ��������״��ģ�����:"circle"Բ��01��ֵģ�壻"norm"���ȳ�ʼ��0-0.1��"Gauss"��ֵΪ0����׼��Ϊ1
CMatrixCal::CMatrixCal(int m,int n,CString style)
{
	if(style == "circle" && m==n)
	{
		float R = (m-1)/2.0;
		name = "Բ��ģ�����";
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
	else if(style == "norm")
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
				data[i][j] = randomUniform(0.0,1.0)*0.1;
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
	else if(style == "gauss")
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
				data[i][j] = gaussrand(0,1)*0.01;
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
}
CMatrixCal::CMatrixCal()
{
	IS_INIT = FALSE;
}

CMatrixCal::~CMatrixCal(void)
{
	//if(data != NULL)
	//{
	//	for(int i = 0; i < row_m; i++) //�ּ��ͷŶ��ϵ������ڴ�
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

//��ʼ��������״��ģ�����:"circle"Բ��01��ֵģ�壻"norm"���ȳ�ʼ��0-0.1��"Gauss"��ֵΪ0����׼��Ϊ1
void CMatrixCal::InitMatrix(int m, int n,CString style)//��ʼ���������һ���캯����ͬ���ڶ�����ʱ��Ҫ��ʼ��
{
	if(style == "circle" && m==n)
	{
		float R = (m-1)/2.0;
		name = "Բ��ģ�����";
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
	else if(style == "norm")
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
				data[i][j] = randomUniform(0.0,1.0)*0.01;
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
	else if(style == "gauss")
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
				data[i][j] = gaussrand(0,1)*0.01;
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
		p[i] = NULL;
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
		   data[i]=NULL;
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
		return IS_SQURE;
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
//�ѵ�row�У���1��ʼ���𣩣�ȡֵ1~row�����һ����ֵ
void CMatrixCal::SetRowData(int row, float num)//�ѵ�row�У���1��ʼ���𣩣�ȡֵ1~row�����һ����ֵ
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
//�ѵ�col�У���1��ʼ���𣩣�ȡֵ1~col�����һ����ֵ
void CMatrixCal::SetColData(int col, float num)//�ѵ�col�У���1��ʼ���𣩣�ȡֵ1~col�����һ����ֵ
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
//��M�����д�row_begin��row_end�С�col_begin��col_end����ȡ�����������µľ��󣨴�1��ʼ����
CMatrixCal CMatrixCal::SeletctPartMatrixByRowCol(CMatrixCal M, int row_begin,int row_end,int col_begin,int col_end)
{
	
	if(col_begin<=0 || row_begin<=0)
	{
		CString str;
		str.Format("��ʼ�У�%d ��ʼ�У�%d������С��0",row_begin,col_begin);
		AfxMessageBox(str);
		CMatrixCal M_error(1,1);
		M_error.ChangeName("�������");
		return M_error;
	}
	else if(col_end>M.col_n || row_end>M.row_m)
	{
		CString str;
		str.Format("��ֹ�У�%d ��ֹ�У�%d��ԭ����������%d,ԭ����������%d��������Χ",row_end,col_end,M.row_m,M.col_n);
		AfxMessageBox(str);
		CMatrixCal M_error(1,1);
		M_error.ChangeName("�������");
		return M_error;
	}
	else if((col_end - col_begin)<0 || (row_end - row_begin)<0)
	{
		CString str;
		str.Format("��ʼ�У�%d,��ֹ�У�%d,��ʼ�У�%d,��ֹ�У�%d,������Χ",row_begin,row_end,col_begin,col_end);
		AfxMessageBox(str);
		CMatrixCal M_error(1,1);
		M_error.ChangeName("�������");
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
	if(!IS_SQURE)
	{
		AfxMessageBox("�����Ƿ����޷���������ʽ");
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
	str = name+"\n";
	for(int i=0;i<row_m;i++)
	{
		for(int j=0;j<col_n;j++)
		{
			CString temp;
			temp.Format("%.8f	",data[i][j]);
			str = str+temp;
		}
		str = str+"\n";
	}
	AfxMessageBox(str);
}
void CMatrixCal::ShowDataShort()
{
	CString str;
	str = name+"\n";
	for(int i=0;i<row_m;i++)
	{
		for(int j=0;j<col_n;j++)
		{
			CString temp;
			temp.Format("%.1f	",data[i][j]);
			str = str+temp;
		}
		str = str+"\n";
	}
	AfxMessageBox(str);
}

//��ʾ����ֵ
void CMatrixCal::ShowMaxMin()
{
	float max,min;
	max = Max_ofAll();
	min = Min_ofAll();
	CString str;
	str = name;
	CString temp;
	temp.Format("\n�������ֵ��%f   ������Сֵ��%f",max,min);
	str += temp;
	AfxMessageBox(str);
}

//��ʾ�����Row�У���1���㣩��ֵ
void CMatrixCal::ShowMaxMin_Row(int Row)
{
	if(Row < 1 || Row > row_m)
	{
		CString str;
		str.Format("������ʾ�м�ֵ��ȡֵ��Χ��%d-%d��,��ǰ��Χ��%d",1,row_m,Row);
		AfxMessageBox(str);
		return;
	}
	float max,min;
	max = Max_ofRow(Row);
	min = Min_ofRow(Row);

	CString str;
	str = name;
	CString temp;
	temp.Format("\n�����%d�У����ֵ��%f   ������Сֵ��%f",Row,max,min);
	str += temp;
	AfxMessageBox(str);
}
//��ʾ�����Col�У���1���㣩��ֵ
void CMatrixCal::ShowMaxMin_Col(int Col)
{
	if(Col < 1 || Col > col_n)
	{
		CString str;
		str.Format("������ʾ�м�ֵ��ȡֵ��Χ��%d-%d��,��ǰ��Χ��%d",1,col_n,Col);
		AfxMessageBox(str);
		return;
	}
	float max,min;
	max = Max_ofCol(Col);
	min = Min_ofCol(Col);

	CString str;
	str = name;
	CString temp;
	temp.Format("\n�����%d�У����ֵ��%f   ������Сֵ��%f",Col,max,min);
	str += temp;
	AfxMessageBox(str);
}
//��ʾ�����Row�У���1���㣩ֵ
void CMatrixCal::ShowRowData(int Row)
{
	if(Row < 1 || Row > row_m)
	{
		CString str;
		str.Format("������ʾ�����ݣ�ȡֵ��Χ��%d-%d��,��ǰ��Χ��%d",1,row_m,Row);
		AfxMessageBox(str);
		return;
	}
	CString str;
	str = name;
	CString temp;
	temp.Format("\n��%d������\n",Row);
	str += temp;
	for(int n=0;n<col_n;n++)
	{
		temp.Format("M%d%d: %.8f ",Row, n+1, data[Row-1][n]);
		str = str+temp;
	}
	AfxMessageBox(str);
}

//��ʾ�����Col�У���1���㣩ֵ
void CMatrixCal::ShowColData(int Col)
{
	if(Col < 1 || Col > col_n)
	{
		CString str;
		str.Format("������ʾ�����ݣ�ȡֵ��Χ��%d-%d��,��ǰ��Χ��%d",1,col_n,Col);
		AfxMessageBox(str);
		return;
	}
	CString str;
	str = name;
	CString temp;
	temp.Format("\n��%d������\n",Col);
	str += temp;
	for(int m=0;m<row_m;m++)
	{
		temp.Format("M%d%d:%.8f | ", m+1, Col, data[m][Col-1]);
		str = str+temp;
	}
	AfxMessageBox(str);
}

//��ʾ�����Row�У���1���㣩��Col�У���1���㣩ֵ
void CMatrixCal::ShowData(int Row, int Col)
{
	if(Col < 1 || Col > col_n || Row < 1 || Row > row_m)
	{
		CString str;
		str.Format("������ʾ�����ݣ���ȡֵ��Χ��%d-%d��,��ȡֵ��Χ��%d-%d��,��ǰ��Χ��%d-%d",1,row_m,1,col_n,Row,Col);
		AfxMessageBox(str);
		return;
	}
	CString str;
	str = name;
	CString temp;
	temp.Format("\n��%d�е�%d������: %f",Row,Col,data[Row-1][Col-1]);
	str += temp;
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

//M1+M2
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
//M=M1+V,V����������
CMatrixCal CMatrixCal::Plus_MatrixByColV(CMatrixCal M1, CMatrixCal V)
{
	CMatrixCal M(M1.row_m,M1.col_n);
	if(M1.row_m != V.row_m || V.col_n != 1)
	{
		CString str;
		str.Format("�����Ͳ�ͬ������+����������M1:%d��%d�У�V��%d��%d�С�",M1.row_m,M1.col_n,V.row_m,V.col_n);
		AfxMessageBox(str);
	}
	else
	{
		for(int m=0;m<M.row_m;m++)
		{
			for(int n=0;n<M.col_n;n++)
			{
				M.data[m][n] = M1.data[m][n]+V.data[m][0];
			}
		}
	}
	return M;
}

//M = M+V;V��������
void CMatrixCal::Plus_MatrixByColV(CMatrixCal V)
{
	if(row_m != V.row_m || V.col_n != 1)
	{
		CString str;
		str.Format("�����Ͳ�ͬ������+������������ǰ����:%d��%d�У�V��%d��%d�С�",row_m,col_n,V.row_m,V.col_n);
		AfxMessageBox(str);
	}
	else
	{
		for(int m=0;m<row_m;m++)
		{
			for(int n=0;n<col_n;n++)
			{
				data[m][n] = data[m][n]+V.data[m][0];
			}
		}
	}
}

//M=M1+V,V����������
CMatrixCal CMatrixCal::Plus_MatrixByRowV(CMatrixCal M1, CMatrixCal V)
{
	CMatrixCal M(M1.row_m,M1.col_n);
	if(M1.col_n != V.col_n || V.row_m != 1)
	{
		CString str;
		str.Format("�����Ͳ�ͬ������+����������M1:%d��%d�У�V��%d��%d�С�",M1.row_m,M1.col_n,V.row_m,V.col_n);
		AfxMessageBox(str);
	}
	else
	{
		for(int m=0;m<M.row_m;m++)
		{
			for(int n=0;n<M.col_n;n++)
			{
				M.data[m][n] = M1.data[m][n]+V.data[0][n];
			}
		}
	}
	return M;
}

//M = M+V;V��������
void CMatrixCal::Plus_MatrixByRowV(CMatrixCal V)
{
	if(col_n != V.col_n || V.row_m != 1)
	{
		CString str;
		str.Format("�����Ͳ�ͬ������+������������ǰ����:%d��%d�У�V��%d��%d�С�",row_m,col_n,V.row_m,V.col_n);
		AfxMessageBox(str);
	}
	else
	{
		for(int m=0;m<row_m;m++)
		{
			for(int n=0;n<col_n;n++)
			{
				data[m][n] = data[m][n]+V.data[0][n];
			}
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

//M=M1-M2
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

//M = M-Matrix
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

//��������Ԫ�����
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

//�Ե�row����ͣ�row��1��ʼ���㣻
float CMatrixCal::SumRow(int row)
{
	if(row < 1 || row > row_m)
	{
		CString str;
		str.Format("���������ͣ�ȡֵ��Χ��%d-%d��,��ǰ��Χ��%d",1,row_m,row);
		AfxMessageBox(str);
		return -996699;
	}
	float res = 0;
	for(int n=0;n<col_n;n++)
	{
		res = res+data[row-1][n];
	}
	return res;
}

//�Ե�col����ͣ�col��1��ʼ���㣻
float CMatrixCal::SumCol(int col)
{
	if(col < 1 || col > col_n)
	{
		CString str;
		str.Format("���������ͣ�ȡֵ��Χ��%d-%d��,��ǰ��Χ��%d",1,col_n,col);
		AfxMessageBox(str);
		return -996699;
	}
	float res = 0;
	for(int m=0;m<row_m;m++)
	{
		res = res+data[m][col-1];
	}
	return res;
}

//����������ͣ���������������
CMatrixCal CMatrixCal::SumRow_toCol(CMatrixCal M)
{
	CMatrixCal Res(M.row_m,1);
	for(int m=0;m<M.row_m;m++)
	{
		for(int n=0;n<M.col_n;n++)
		{
			Res.data[m][0] = Res.data[m][0]+M.data[m][n];
		}
	}
	return Res;
}

//����������ͣ���������������
void CMatrixCal::SumRow_toCol()
{
	int m_new = row_m;
	int n_new = 1;
	float** temp = init_floatmatrix(m_new,n_new);
	for(int m=0;m<m_new;m++)
	{
		temp[m][0] = 0;
		for(int n=0;n<col_n;n++)
		{
			temp[m][0] = temp[m][0] + data[m][n];
		}
	}
	releasedata(data,row_m);
	data = temp;
	row_m = m_new;
	col_n = n_new;
}

//����������ͣ���������������
CMatrixCal CMatrixCal::SumCol_toRow(CMatrixCal M)
{
	CMatrixCal Res(1,M.col_n);
	for(int m=0;m<M.row_m;m++)
	{
		for(int n=0;n<M.col_n;n++)
		{
			Res.data[0][n] = Res.data[0][n]+M.data[m][n];
		}
	}
	return Res;
}


//����������ͣ���������������
void CMatrixCal::SumCol_toRow()
{
	int m_new = 1;
	int n_new = col_n;
	float** temp = init_floatmatrix(m_new,n_new);
	for(int n=0;n<n_new;n++)
	{
		temp[0][n] = 0;
		for(int m=0;m<row_m;m++)
		{
			temp[0][n] = temp[m][0] + data[m][n];
		}
	}
	releasedata(data,row_m);
	data = temp;
	row_m = m_new;
	col_n = n_new;
}

//ȡM = -Matrix��ȡ�෴����
CMatrixCal CMatrixCal::OppositeMatrix(CMatrixCal Matrix)
{
	CMatrixCal Res(Matrix.row_m,Matrix.col_n);
	for(int m=0;m<Res.row_m;m++)
	{
		for(int n=0;n<Res.col_n;n++)
		{
			Res.data[m][n] = -Matrix.data[m][n];
		}
	}
	return Res;
}

//ȡM = -M��ȡ�෴����
void CMatrixCal::OppositeMatrix()
{
	for(int m=0;m<row_m;m++)
	{
		for(int n=0;n<col_n;n++)
		{
			data[m][n] = -data[m][n];
		}
	}
}

//ȡ������������ֵ
float CMatrixCal::Max_ofAll()
{
	float res = data[0][0];
	for(int m=0;m<row_m;m++)
	{
		for(int n=0;n<col_n;n++)
		{
			if(res < data[m][n])
			{
				res = data[m][n];
			}
		}
	}
	return res;
}

//ȡ�����������Сֵ
float CMatrixCal::Min_ofAll()
{
	float res = data[0][0];
	for(int m=0;m<row_m;m++)
	{
		for(int n=0;n<col_n;n++)
		{
			if(res > data[m][n])
			{
				res = data[m][n];
			}
		}
	}
	return res;
}

//ȡ�����Row�У���1���㣩�����ֵ
float CMatrixCal::Max_ofRow(int Row)
{
	float res = data[0][0];;
	if(Row < 1 || Row > row_m)
	{
		CString str;
		str.Format("���������ֵ��ȡֵ��Χ��%d-%d��,��ǰ��Χ��%d",1,row_m,Row);
		AfxMessageBox(str);
		res = -996699;
	}
	for(int n=0;n<col_n;n++)
	{
		if(res < data[Row-1][n])
		{
			res = data[Row-1][n];
		}
	}
	return res;
}
//ȡ�����Row�У���1���㣩����Сֵ
float CMatrixCal::Min_ofRow(int Row)
{
	float res = data[0][0];;
	if(Row < 1 || Row > row_m)
	{
		CString str;
		str.Format("��������Сֵ��ȡֵ��Χ��%d-%d��,��ǰ��Χ��%d",1,row_m,Row);
		AfxMessageBox(str);
		res = -996699;
	}
	for(int n=0;n<col_n;n++)
	{
		if(res > data[Row-1][n])
		{
			res = data[Row-1][n];
		}
	}
	return res;
}

//ȡ�����Col�У���1���㣩�����ֵ
float CMatrixCal::Max_ofCol(int Col)
{
	float res = data[0][0];;
	if(Col < 1 || Col > col_n)
	{
		CString str;
		str.Format("������ʾ�����ݣ�ȡֵ��Χ��%d-%d��,��ǰ��Χ��%d",1,col_n,Col);
		AfxMessageBox(str);
		res = -996699;
	}
	for(int m=0;m<row_m;m++)
	{
		if(res < data[m][Col-1])
		{
			res = data[m][Col-1];
		}
	}
	return res;
}

//ȡ�����Col�У���1���㣩����Сֵ
float CMatrixCal::Min_ofCol(int Col)
{
	float res = data[0][0];;
	if(Col < 1 || Col > col_n)
	{
		CString str;
		str.Format("������ʾ�����ݣ�ȡֵ��Χ��%d-%d��,��ǰ��Χ��%d",1,col_n,Col);
		AfxMessageBox(str);
		res = -996699;
	}
	for(int m=0;m<row_m;m++)
	{
		if(res > data[m][Col-1])
		{
			res = data[m][Col-1];
		}
	}
	return res;
}
//��������ֵ>tʱ����ֵΪ1������Ϊ0
void CMatrixCal::Segmente_toBinary(float t)
{
	for(int m=0;m<row_m;m++)
	{
		for(int n=0;n<col_n;n++)
		{
			if(data[m][n]>t)
			{
				data[m][n] = 1;
			}
			else
			{
				data[m][n] = 0;
			}
		}
	}
}

//��������ֵ>tʱ����ֵΪ0�����಻��
void CMatrixCal::Check_LargetValue(float t)
{
	for(int m=0;m<row_m;m++)
	{
		for(int n=0;n<col_n;n++)
		{
			if(data[m][n]>t || data[m][n] < -t)
			{
				data[m][n] = gaussrand(0,1)*0.01;
			}
		}
	}
}
//��ͬ��������M2���󣬼ӵ�M1���·�
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

//��ͬ��������M���󣬼ӵ�ԭ������·�
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
double CMatrixCal::gaussrand(double E_std,double sigma_std)
{
	static double V1, V2, S;
    static int phase = 0;
    double X;
     
    if ( phase == 0 ) {
        do {
            double U1 = (double)rand() / RAND_MAX;
            double U2 = (double)rand() / RAND_MAX;
             
            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while(S >= 1 || S == 0);
         
        X = V1 * sqrt(-2 * log(S) / S);
    } else
        X = V2 * sqrt(-2 * log(S) / S);
         
    phase = 1 - phase;
	/*X = X * sigma_std + E_std; */
	X = X * pow(sigma_std,0.5) + E_std; 
    return X;
}
double CMatrixCal::randomUniform(double dMinValue,double dMaxValue)//���ȷֲ�
{
	//srand(time(NULL));
	double pRandomValue = (double)(rand()/(double)RAND_MAX);
    pRandomValue = pRandomValue*(dMaxValue-dMinValue)+dMinValue;
    return pRandomValue;
}