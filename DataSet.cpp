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
float** CDataSet::init_floatmatrix(int width,int height)//初始化一个二维数组，输入为宽度与高度
{
	float **data=new float*[height];
	for(int i=0;i<height;i++)
	{
		data[i]=new float[width];
		for(int j = 0;j<width;j++)
		{
			data[i][j] = (float)0;//初始化指针
		}
	}
	return data;
}
float*** CDataSet::init_floatmatrix(int width,int height,int channel)//初始化一个三维数组，输入为宽度与高度与通道数
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
//把图像数据转换为二维数组
float** CDataSet::LoadBmp()
{
	CString path;
	CString title;
	CString Ext;
	char szFilter[]="bmp file (*.bmp)|*.bmp|all file (*.*)|*.*||";//限定只能打开BMP格式文件
	CFileDialog fileOpenDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);//打开文件对话框
	if (fileOpenDlg.DoModal () == IDOK)  //打开文件对话框，选定指定文件
	{
		
		POSITION pos = fileOpenDlg.GetStartPosition();//获得选定的文件路径
		path = fileOpenDlg.GetNextPathName(pos);//储存文件路径，为后面打开文件做准备
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

BYTE* CDataSet::TransToBmp(float** data,int width,int height)//将一个二维指针转换为满足BMP格式的指针数据
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
	BITMAPINFOHEADER bInfo;//位图信息头
	bh.bfType=((WORD)('M'<<8)|'B');//"BM"说明文件类型
	bh.bfReserved1=0;//保留
	bh.bfReserved2=0;//保留
	bh.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256 + height*length;//文件大小
	bh.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256;
	//表示从头文件开始到实际图像数据数据之间的字节的偏移量。bfOffBits可以直接定位像素数据

	//BITMAPINFOHEADER bInfo;//位图信息头
	bInfo.biSize=sizeof(BITMAPINFOHEADER);//说明BITMAPINFOHEADER结构所需的字数
	bInfo.biWidth= width;//图像宽度，以像素为单位
	bInfo.biHeight=height;//图像高度，以像素为单位
	bInfo.biPlanes=1;//为目标设备说明位面数，其中总是被设为1
	bInfo.biBitCount=8;//说明比特数/像素的颜色深度，值为0，1，4，8，16，24或32，256灰度级的颜色深度为8，因为2^8=256
	bInfo.biCompression=BI_RGB;//说明图像数据压缩类型
	bInfo.biSizeImage=width*height;//说明图像的大小，一字节为单位，
	bInfo.biXPelsPerMeter=0;//水平分辨率，可以设为0
	bInfo.biYPelsPerMeter=0;//垂直分辨率，可以设为0
	bInfo.biClrUsed=256;//说明位图实际使用的彩色表中颜色索引数
	bInfo.biClrImportant=0;//说明对图像显示有重要影响的颜色索引数目，为0表示都重要。

	
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
//将二维数组写为灰度bmp文件
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
	BITMAPINFOHEADER bInfo;//位图信息头
	bh.bfType=((WORD)('M'<<8)|'B');//"BM"说明文件类型
	bh.bfReserved1=0;//保留
	bh.bfReserved2=0;//保留
	bh.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER) + 3*width*height;//文件大小
	bh.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
	//表示从头文件开始到实际图像数据数据之间的字节的偏移量。bfOffBits可以直接定位像素数据

	//BITMAPINFOHEADER bInfo;//位图信息头
	bInfo.biSize=sizeof(BITMAPINFOHEADER);//说明BITMAPINFOHEADER结构所需的字数
	bInfo.biWidth= width;//图像宽度，以像素为单位
	bInfo.biHeight=height;//图像高度，以像素为单位
	bInfo.biPlanes=1;//为目标设备说明位面数，其中总是被设为1
	bInfo.biBitCount=24;//说明比特数/像素的颜色深度，值为0，1，4，8，16，24或32，256灰度级的颜色深度为8，因为2^8=256
	bInfo.biCompression=BI_RGB;//说明图像数据压缩类型
	bInfo.biSizeImage=width*height;//说明图像的大小，一字节为单位，
	bInfo.biXPelsPerMeter=0;//水平分辨率，可以设为0
	bInfo.biYPelsPerMeter=0;//垂直分辨率，可以设为0
	bInfo.biClrUsed=0;//说明位图实际使用的彩色表中颜色索引数
	bInfo.biClrImportant=0;//说明对图像显示有重要影响的颜色索引数目，为0表示都重要。

	//使每一行为4的倍数
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
	int length = 3*width+space;//包含0值的长度
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
CMatrixCal CDataSet::LoadLRTestData()//载入逻辑回归红蓝点测试图,X+Y
{

	CString path;
	CString title;
	CString Ext;
	char szFilter[]="bmp file (*.bmp)|*.bmp|bin file (*.bin)|*.bin|raw file (*.raw)|*.raw|all file (*.*)|*.*||";//限定只能打开BMP格式文件
	CFileDialog fileOpenDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);//打开文件对话框
	if (fileOpenDlg.DoModal () == IDOK)  //打开文件对话框，选定指定文件
	{
		
		POSITION pos = fileOpenDlg.GetStartPosition();//获得选定的文件路径
		path = fileOpenDlg.GetNextPathName(pos);//储存文件路径，为后面打开文件做准备
		title = fileOpenDlg.GetFileTitle();
		Ext = fileOpenDlg.GetFileExt();
		//检查并创建根目录与对应输出目录
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
//		if(XY.data[XY.row_m-1][m] <= 0.5)//红色
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
//	BYTE* R = TransToBmp(r,width_image,height_image);//将一个二维指针转换为逆序标准bmp指针
//	BYTE* G = TransToBmp(g,width_image,height_image);//将一个二维指针转换为逆序标准bmp指针
//	BYTE* B = TransToBmp(b,width_image,height_image);//将一个二维指针转换为逆序标准bmp指针
//	releasedata(r,height_image);
//	releasedata(g,height_image);
//	releasedata(b,height_image);
//	Bmp24Write(width_image,height_image,R,G,B,"E:\\NN程序测试数据\\1_逻辑回归\\红蓝分类结果.bmp");
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
		if(XY.data[XY.row_m-1][m] <= 0.5)//红色
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
	Bmp24Write(width_image,height_image,R,G,B,"E:\\NN程序测试数据\\1_逻辑回归\\红蓝分类结果.bmp");
	delete []R;
	delete []G;
	delete []B;
}


//方形切片：paht:输入文件路径；width_cut:切片宽度；height_cut：切片高度；stride：切片移动步长；
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