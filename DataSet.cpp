#include "stdafx.h"
#include "DataSet.h"


CDataSet::CDataSet(void)
{
	width_image = 0;
	height_image = 0;
	channel_image = 0;
}


CDataSet::~CDataSet(void)
{
}
float** CDataSet::init_floatmatrix(int width,int height)//��ʼ��һ����ά���飬����Ϊ�����߶�
{
	float **data=new float*[height];
	for(int i=0;i<height;i++)
	{
		data[i]=new float[width];
		for(int j = 0;j<width;j++)
		{
			data[i][j] = (float)0;//��ʼ��ָ��
		}
	}
	return data;
}
float*** CDataSet::init_floatmatrix(int width,int height,int channel)//��ʼ��һ����ά���飬����Ϊ�����߶���ͨ����
{
	float ***data=new float**[height];
	{
		for(int i=0;i<height;i++)
		{
			data[i]=new float*[width*channel];
			for(int j = 0;j<width;j++)
			{
				data[i][j] = new float[channel];
				for(int k=0;k<channel;k++)
				{
					data[i][j][k] = (float)0;
				}
			}
		}
	}
	return data;
}
void CDataSet::releasedata(float** data, int height)
{
	if(data == NULL)
	{
		return;
	}
	for (int i = 0; i < height; i++)
	{
		delete []data[i];
		data[i] = NULL;
	}
	delete []data;
	data = NULL;
}
void CDataSet::releasedata(float*** data, int width,int height)
{
	if(data == NULL)
	{
		return;
	}
	for (int i = 0; i < height; i++)
	{
		for(int j=0;j<width;j++)
		{
			delete []data[i][j];
			data[i][j] = NULL;
		}
		delete []data[i];
		data[i] = NULL;
	}
	delete []data;
	data = NULL;
}
BYTE* CDataSet::ReadBmpData(CString path)
{
	
	CFile file;
	CFileException e;
	BYTE *bmp;
	if(file.Open(path, CFile::modeRead,&e))
	{
		BITMAPFILEHEADER bh;
		BITMAPINFOHEADER bInfo;
		file.Read(&bh,sizeof(bh));
		file.Read(&bInfo,sizeof(bInfo));
		int offset = bh.bfOffBits;
		file.Seek(offset,CFile::begin);
		width_image = bInfo.biWidth;
		height_image = bInfo.biHeight;
		if(bInfo.biBitCount == 8)
		{
			int emptynum = bInfo.biWidth%4;
			int space;
			if( emptynum == 0)
			{
				space = 0;
			}
			if( emptynum!= 0)
			{
				space = 4 - emptynum;
			}
			int PosofCol;
			int length;
			length = width_image+space;
			bmp = new BYTE[height_image*length];
			file.Read(bmp,height_image*length);
			IS_COLOR = FALSE;
		}
		else if(bInfo.biBitCount == 24)
		{
			int emptynum = bInfo.biWidth*3%4;
			int space;
			if( emptynum == 0)
			{
				space = 0;
			}
			if( emptynum!= 0)
			{
				space = 4 - emptynum;
			}
			int PosofCol;
			int length;
			length = width_image*3+space;
			bmp = new BYTE[height_image*length];
			file.Read(bmp,height_image*length);
			IS_COLOR = TRUE;
		}
		else 
		{
			bmp = NULL;
		}
		file.Close();

	}
	else
	{
		return NULL;
	}
	return bmp;
}
float** CDataSet::TransToData(BYTE* bmp,int width,int height)
{
	//Clear_raw();
	float **data;

	
	if(IS_COLOR == FALSE)
	{

		int left = width%4;
		int space;
		if(left == 0)
		{
			space = 0;
		}
		if(left!= 0)
		{
			space = 4 - left;
		}
		int PosofCol;
		int length;
		length = width+space;
		data=new float*[height];
		for(int i = 0;i<height;i++)
		{
			PosofCol = height - i - 1;
			data[PosofCol]=new float[width];
			for(int j = 0;j<width;j++)
			{
				data[PosofCol][j] = bmp[i*length+j];
			}
		}
	}
	else if(IS_COLOR == TRUE)
	{
		int left = width*3%4;
		int space;
		if(left == 0)
		{
			space = 0;
		}
		if(left!= 0)
		{
			space = 4 - left;
		}
		int PosofCol;
		int length;
		length = width*3+space;
		data=new float*[height];
		for(int i = 0;i<height;i++)
		{
			PosofCol = height - i - 1;
			data[PosofCol]=new float[width];
			for(int j = 0;j<width;j++)
			{
				data[PosofCol][j] = 0.114*bmp[i*length+3*j]+0.587*bmp[i*length+3*j+1]+0.299*bmp[i*length+3*j+2];
			}
		}
	}
	else
	{
		data = NULL;
	}
	return data;
}
//��ͼ������ת��Ϊ��ά����
float** CDataSet::LoadBmp()
{
	CString path;
	CString title;
	CString Ext;
	char szFilter[]="bmp file (*.bmp)|*.bmp|all file (*.*)|*.*||";//�޶�ֻ�ܴ�BMP��ʽ�ļ�
	CFileDialog fileOpenDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);//���ļ��Ի���
	if (fileOpenDlg.DoModal () == IDOK)  //���ļ��Ի���ѡ��ָ���ļ�
	{
		
		POSITION pos = fileOpenDlg.GetStartPosition();//���ѡ�����ļ�·��
		path = fileOpenDlg.GetNextPathName(pos);//�����ļ�·����Ϊ������ļ���׼��
		title = fileOpenDlg.GetFileTitle();
		Ext = fileOpenDlg.GetFileExt();
		path_current = path;
	}

	BYTE* bmp = ReadBmpData(path);
	int width = width_image;
	int height = height_image;
	float** data = TransToData(bmp,width,height);

	delete []bmp;
	bmp = NULL;
	return data;
}

BYTE* CDataSet::TransToBmp(float** data,int width,int height)//��һ����άָ��ת��Ϊ����BMP��ʽ��ָ������
{
	int left = width%4;
	int space;
	if(left == 0)
	{
		space = 0;
	}
	if(left!= 0)
	{
		space = 4 - left;
	}
	int PosofCol;
	int length;
	length = width+space;
	BYTE *bmp = new BYTE[height*length];
	for(int i=0;i<height;i++)
	{
		PosofCol = height- i - 1;
		int pos = PosofCol*length;
		for(int j = 0;j<width;j++)
		{
			bmp[pos + j] = (BYTE)(data[i][j]+0.5);
		}
		for(int j = 0;j<space;j++)
		{
			bmp[pos + width + j] = 0;
		}
	}
	return bmp;
}
void CDataSet::BMPWrite(int width,int height,BYTE* data,CString path)
{
	CFile file;
	CFileException e;

	int emptynum = width%4;
	int space;
	if( emptynum == 0)
	{
		space = 0;
	}
	if( emptynum!= 0)
	{
		space = 4 - emptynum;
	}
	int length;
	length = width+space;

	BITMAPFILEHEADER bh;
	BITMAPINFOHEADER bInfo;//λͼ��Ϣͷ
	bh.bfType=((WORD)('M'<<8)|'B');//"BM"˵���ļ�����
	bh.bfReserved1=0;//����
	bh.bfReserved2=0;//����
	bh.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256 + height*length;//�ļ���С
	bh.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256;
	//��ʾ��ͷ�ļ���ʼ��ʵ��ͼ����������֮����ֽڵ�ƫ������bfOffBits����ֱ�Ӷ�λ��������

	//BITMAPINFOHEADER bInfo;//λͼ��Ϣͷ
	bInfo.biSize=sizeof(BITMAPINFOHEADER);//˵��BITMAPINFOHEADER�ṹ���������
	bInfo.biWidth= width;//ͼ���ȣ�������Ϊ��λ
	bInfo.biHeight=height;//ͼ��߶ȣ�������Ϊ��λ
	bInfo.biPlanes=1;//ΪĿ���豸˵��λ�������������Ǳ���Ϊ1
	bInfo.biBitCount=8;//˵��������/���ص���ɫ��ȣ�ֵΪ0��1��4��8��16��24��32��256�Ҷȼ�����ɫ���Ϊ8����Ϊ2^8=256
	bInfo.biCompression=BI_RGB;//˵��ͼ������ѹ������
	bInfo.biSizeImage=width*height;//˵��ͼ��Ĵ�С��һ�ֽ�Ϊ��λ��
	bInfo.biXPelsPerMeter=0;//ˮƽ�ֱ��ʣ�������Ϊ0
	bInfo.biYPelsPerMeter=0;//��ֱ�ֱ��ʣ�������Ϊ0
	bInfo.biClrUsed=256;//˵��λͼʵ��ʹ�õĲ�ɫ������ɫ������
	bInfo.biClrImportant=0;//˵����ͼ����ʾ����ҪӰ�����ɫ������Ŀ��Ϊ0��ʾ����Ҫ��

	
	if(file.Open(path, CFile::modeCreate|CFile::modeWrite,&e))
	{
		file.Write(&bh,sizeof(BITMAPFILEHEADER));
		file.Write(&bInfo,sizeof(BITMAPINFOHEADER));
		RGBQUAD rgb;
		rgb.rgbReserved=0;
		for(int i=0;i<256;i++)
		{
			rgb.rgbBlue=rgb.rgbRed=rgb.rgbGreen=i;
			file.Write(&rgb,sizeof(RGBQUAD));
		}
		file.Write(data,height*length);
		file.Close();
	}
}
//����ά����дΪ�Ҷ�bmp�ļ�
void CDataSet::WriteBmpFile(int width,int height,float** data, CString path)
{
	BYTE* bmp = TransToBmp(data,width,height);
	BMPWrite(width,height,bmp,path);
	delete []bmp;
	bmp = NULL;
}
void CDataSet::Bmp24Write(int width,int height,BYTE* R,BYTE* G, BYTE* B, CString path)
{
	BITMAPFILEHEADER bh;
	BITMAPINFOHEADER bInfo;//λͼ��Ϣͷ
	bh.bfType=((WORD)('M'<<8)|'B');//"BM"˵���ļ�����
	bh.bfReserved1=0;//����
	bh.bfReserved2=0;//����
	bh.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER) + 3*width*height;//�ļ���С
	bh.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
	//��ʾ��ͷ�ļ���ʼ��ʵ��ͼ����������֮����ֽڵ�ƫ������bfOffBits����ֱ�Ӷ�λ��������

	//BITMAPINFOHEADER bInfo;//λͼ��Ϣͷ
	bInfo.biSize=sizeof(BITMAPINFOHEADER);//˵��BITMAPINFOHEADER�ṹ���������
	bInfo.biWidth= width;//ͼ���ȣ�������Ϊ��λ
	bInfo.biHeight=height;//ͼ��߶ȣ�������Ϊ��λ
	bInfo.biPlanes=1;//ΪĿ���豸˵��λ�������������Ǳ���Ϊ1
	bInfo.biBitCount=24;//˵��������/���ص���ɫ��ȣ�ֵΪ0��1��4��8��16��24��32��256�Ҷȼ�����ɫ���Ϊ8����Ϊ2^8=256
	bInfo.biCompression=BI_RGB;//˵��ͼ������ѹ������
	bInfo.biSizeImage=width*height;//˵��ͼ��Ĵ�С��һ�ֽ�Ϊ��λ��
	bInfo.biXPelsPerMeter=0;//ˮƽ�ֱ��ʣ�������Ϊ0
	bInfo.biYPelsPerMeter=0;//��ֱ�ֱ��ʣ�������Ϊ0
	bInfo.biClrUsed=0;//˵��λͼʵ��ʹ�õĲ�ɫ������ɫ������
	bInfo.biClrImportant=0;//˵����ͼ����ʾ����ҪӰ�����ɫ������Ŀ��Ϊ0��ʾ����Ҫ��

	//ʹÿһ��Ϊ4�ı���
	int left = 3*width%4;
	int space;
	if(left == 0)
	{
		space = 0;
	}
	if(left!= 0)
	{
		space = 4 - left;
	}
	int length = 3*width+space;//����0ֵ�ĳ���
	BYTE *bmp = new BYTE[height*length];
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			bmp[i*length + 3*j] = B[i*width + j];
			bmp[i*length + 3*j + 1] = G[i*width + j];
			bmp[i*length + 3*j + 2] = R[i*width + j];
		}
		/*for(int j=0;j<space;j++)
		{
			bmp[i*length + width + j] = 0;
		}*/
	}


	CFile file;
	CFileException e;
	if(file.Open(path,CFile::modeWrite | CFile::modeCreate,&e))
	{
		file.Write(&bh,sizeof(BITMAPFILEHEADER));
		file.Write(&bInfo,sizeof(BITMAPINFOHEADER));
		file.Write(bmp,sizeof(BYTE)*height*length);
		file.Close();
	}
	delete []bmp;
}
CMatrixCal CDataSet::LoadLRTestData()//�����߼��ع���������ͼ,X+Y
{

	CString path;
	CString title;
	CString Ext;
	char szFilter[]="bmp file (*.bmp)|*.bmp|bin file (*.bin)|*.bin|raw file (*.raw)|*.raw|all file (*.*)|*.*||";//�޶�ֻ�ܴ�BMP��ʽ�ļ�
	CFileDialog fileOpenDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);//���ļ��Ի���
	if (fileOpenDlg.DoModal () == IDOK)  //���ļ��Ի���ѡ��ָ���ļ�
	{
		
		POSITION pos = fileOpenDlg.GetStartPosition();//���ѡ�����ļ�·��
		path = fileOpenDlg.GetNextPathName(pos);//�����ļ�·����Ϊ������ļ���׼��
		title = fileOpenDlg.GetFileTitle();
		Ext = fileOpenDlg.GetFileExt();
		//��鲢������Ŀ¼���Ӧ���Ŀ¼
		/*filefolder_path_output = filefolder_path_root + "\\" + file_name_raw;
		if (!PathFileExists(filefolder_path_root))
		{
			CreateDirectory(filefolder_path_root, NULL); 
		}
		if (!PathFileExists(filefolder_path_output))
		{
			CreateDirectory(filefolder_path_output, NULL); 
		}*/
	}


	BYTE* bmp = ReadBmpData(path);

	int m1,m2,m;
	m1=0;
	m2=0;
	m=0;

	int left = width_image*3%4;
	int space;
	if(left == 0)
	{
		space = 0;
	}
	if(left!= 0)
	{
		space = 4 - left;
	}
	int PosofCol;
	int length;
	length = width_image*3+space;

	for(int i = 0;i<height_image;i++)
	{
		PosofCol = height_image - i - 1;

		for(int j = 0;j<width_image;j++)
		{
			/*data[PosofCol][j] = 0.114*bmp[i*length+3*j]+0.587*bmp[i*length+3*j+1]+0.299*bmp[i*length+3*j+2];*/
			BYTE B = bmp[i*length+3*j];
			BYTE G = bmp[i*length+3*j+1];
			BYTE R = bmp[i*length+3*j+2];
			if(R==125 && G ==0 && B==0)
			{
				m1++;
				m++;
			}
			else if(R==0 && G ==0 && B==125)
			{
				m2++;
				m++;
			}
		}
	}

	CMatrixCal XY(3,m);
	int tag = 0;
	for(int i = 0;i<height_image;i++)
	{
		PosofCol = height_image - i - 1;
		for(int j = 0;j<width_image;j++)
		{
			BYTE B = bmp[i*length+3*j];
			BYTE G = bmp[i*length+3*j+1];
			BYTE R = bmp[i*length+3*j+2];
			
			if(R==125 && G ==0 && B==0)
			{
				XY.data[0][tag]=PosofCol;
				XY.data[1][tag]=j;
				XY.data[2][tag]=0;
				tag++;
			}
			else if(R==0 && G ==0 && B==125)
			{
				XY.data[0][tag]=PosofCol;
				XY.data[1][tag]=j;
				XY.data[2][tag]=1;
				tag++;
			}
		}
	}
	delete []bmp;
	return XY;
}
CMatrixCal CDataSet::ExtractX(CMatrixCal XY)
{
	CMatrixCal X(XY.row_m-1,XY.col_n);
	for(int m=0;m<X.row_m;m++)
	{
		for(int n=0;n<X.col_n;n++)
		{
			X.data[m][n] = XY.data[m][n];
		}
	}
	return X;
}
CMatrixCal CDataSet::ExtractY(CMatrixCal XY)
{
	CMatrixCal Y(1,XY.col_n);
	for(int n=0;n<Y.col_n;n++)
	{
		Y.data[0][n] = XY.data[XY.row_m-1][n];
	}
	return Y;
}
CMatrixCal CDataSet::MergeXY(CMatrixCal X, CMatrixCal Y)
{
	CMatrixCal XY(X.row_m+1,X.col_n);
	for(int m=0;m<XY.row_m-1;m++)
	{
		for(int n=0;n<XY.col_n;n++)
		{
			XY.data[m][n] = X.data[m][n];
		}
	}
	for(int n=0;n<XY.col_n;n++)
	{
		XY.data[XY.row_m-1][n] = Y.data[0][n];
	}
	return XY;
}
//void CDataSet::PostProcess_RB(CMatrixCal XY)
//{
//	XY.ShowData();
//	float** r = init_floatmatrix(width_image,height_image);
//	float** g = init_floatmatrix(width_image,height_image);
//	float** b = init_floatmatrix(width_image,height_image);
//	for(int m=0;m<XY.col_n;m++)
//	{
//		if(XY.data[XY.row_m-1][m] <= 0.5)//��ɫ
//		{
//			if(m==50)
//			{
//				AfxMessageBox("");
//			}
//			int x = (int)(XY.data[0][m]+0.5);
//			int y = (int)(XY.data[1][m]+0.5);
//			if(x==35 && y==4)
//			{
//				AfxMessageBox("");
//			}
//			r[x][y] = 255;
//			g[x][y] = 0;
//			b[x][y] = 0;
//		}
//		else
//		{
//			int x = (int)(XY.data[0][m]+0.5);
//			int y = (int)(XY.data[1][m]+0.5);
//			r[x][y] = 0;
//			g[x][y] = 0;
//			b[x][y] = 255;
//		}
//	}
//
//	BYTE* R = TransToBmp(r,width_image,height_image);//��һ����άָ��ת��Ϊ�����׼bmpָ��
//	BYTE* G = TransToBmp(g,width_image,height_image);//��һ����άָ��ת��Ϊ�����׼bmpָ��
//	BYTE* B = TransToBmp(b,width_image,height_image);//��һ����άָ��ת��Ϊ�����׼bmpָ��
//	releasedata(r,height_image);
//	releasedata(g,height_image);
//	releasedata(b,height_image);
//	Bmp24Write(width_image,height_image,R,G,B,"E:\\NN�����������\\1_�߼��ع�\\����������.bmp");
//	delete []R;
//	delete []G;
//	delete []B;
//}



void CDataSet::PostProcess_RB(CMatrixCal XY)
{
	BYTE* R = new BYTE[height_image*width_image];
	BYTE* G = new BYTE[height_image*width_image];
	BYTE* B = new BYTE[height_image*width_image];
	for(int m=0;m<XY.col_n;m++)
	{
		if(XY.data[XY.row_m-1][m] <= 0.5)//��ɫ
		{
			int x = (int)(XY.data[0][m]+0.5);
			int y = (int)(XY.data[1][m]+0.5);
			int tag = (height_image-x-1)*width_image + y;
			R[tag] = 255;
			G[tag] = 0;
			B[tag] = 0;
		}
		else
		{
			int x = (int)(XY.data[0][m]+0.5);
			int y = (int)(XY.data[1][m]+0.5);
			int tag = (height_image-x-1)*width_image + y;
			R[tag] = 0;
			G[tag] = 0;
			B[tag] = 255;
		}
	}
	Bmp24Write(width_image,height_image,R,G,B,"E:\\NN�����������\\1_�߼��ع�\\����������.bmp");
	delete []R;
	delete []G;
	delete []B;
}


//������Ƭ��paht:�����ļ�·����width_cut:��Ƭ��ȣ�height_cut����Ƭ�߶ȣ�stride����Ƭ�ƶ�������
void CDataSet::GetPatchFromBMP(int width_cut, int height_cut, int stride_row,int stride_col,CString style)
{
	float** raw = LoadBmp();
	CMatrixCal BMP(raw,height_image,width_image);
	int m_count = 0;
	int n_count = 0;


	CMatrixCal C(height_cut,width_cut,style);
	for(int m=1;m<=height_image-height_cut+1;m+=stride_row)
	{
		m_count++;
		n_count = 0;
		for(int n=1;n<=width_image-width_cut+1;n+=stride_col)
		{
			n_count++;
			CMatrixCal bmp = BMP.SeletctPartMatrixByRowCol(BMP,m,m+height_cut-1,n,n+width_cut-1);
			if(style == "circle" && height_cut == width_cut)
			{
				bmp.DotBy(C);
			}
			CString path_patch = path_current;
			CString str;
			str.Format("_patch_%d_%d.bmp",m_count,n_count);
			path_patch.Replace(".bmp",str);
			WriteBmpFile(width_cut,height_cut,bmp.data,path_patch);
			bmp.Release();
			bmp.data = NULL;
		}
	}
	releasedata(raw,height_image);
	raw = NULL;
	BMP.Release();
	C.Release();
}