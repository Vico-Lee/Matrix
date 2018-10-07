#pragma once
class CDataSet
{
public:
	CDataSet(void);
	~CDataSet(void);

public:
	int width_image;
	int height_image;
	int channel_image;
	CString path_current;//当前文件
	BOOL IS_COLOR;
public:
	//综合模块
	float **init_floatmatrix(int width,int height);//初始化一个二维数组，一般在生成中间变量时使用，原始数据在读取过程中初始化
	float ***init_floatmatrix(int widht,int height,int channel);
	void releasedata(float**, int height);
	void releasedata(float***, int width,int height);

	//BMP类数据读取与写入操作

	//8位深度操作,读取时如果为彩图，则转换为8为深度图
	//独立功能
	BYTE *ReadBmpData(CString path);//读取BMP数据，赋值一个逆序标准bmp数据指针中
	float **TransToData(BYTE* bmp,int width,int height);//将逆序标准bmp格式转换为正序二维数组
	BYTE *TransToBmp(float** data,int width,int height);//将一个二维指针转换为逆序标准bmp指针
	void BMPWrite(int width,int height,BYTE* data,CString path);//将一个长宽已知的逆序标准bmp指针数据写入path文件中
	//综合功能
	float** LoadBmp();//把图像数据转换为二维数组
	void WriteBmpFile(int width,int height,float** data, CString path);


	//24位深度操作
	void Bmp24Write(int width,int height,BYTE* R,BYTE* G, BYTE* B, CString path);//逆序指针直接写



	//独立模块
	//逻辑回归二元分类测试数据组，红色蓝色分类
	CMatrixCal LoadLRTestData();//载入逻辑回归红蓝点测试图
	CMatrixCal ExtractX(CMatrixCal XY);
	CMatrixCal ExtractY(CMatrixCal XY);
	CMatrixCal MergeXY(CMatrixCal X, CMatrixCal Y);
	//void PostProcess_RB(CMatrixCal XY);
	/*整合功能*/ void PostProcess_RB(CMatrixCal XY);

	//20180927--用于将输入的MiniSAR图像切成小块，生成图像patch：输入：文件路径；输出：多个图像块；文件系统：在原输入文件夹下，按照行列序号生成结果文件
	void GetPatchFromBMP(int width_cut, int height_cut, int stride_row,int stride_col,CString style);//paht:输入文件路径；width_cut:切片宽度；height_cut：切片高度；stride：切片移动步长；
};

