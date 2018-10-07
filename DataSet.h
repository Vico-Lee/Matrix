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
	CString path_current;//��ǰ�ļ�
	BOOL IS_COLOR;
public:
	//�ۺ�ģ��
	float **init_floatmatrix(int width,int height);//��ʼ��һ����ά���飬һ���������м����ʱʹ�ã�ԭʼ�����ڶ�ȡ�����г�ʼ��
	float ***init_floatmatrix(int widht,int height,int channel);
	void releasedata(float**, int height);
	void releasedata(float***, int width,int height);

	//BMP�����ݶ�ȡ��д�����

	//8λ��Ȳ���,��ȡʱ���Ϊ��ͼ����ת��Ϊ8Ϊ���ͼ
	//��������
	BYTE *ReadBmpData(CString path);//��ȡBMP���ݣ���ֵһ�������׼bmp����ָ����
	float **TransToData(BYTE* bmp,int width,int height);//�������׼bmp��ʽת��Ϊ�����ά����
	BYTE *TransToBmp(float** data,int width,int height);//��һ����άָ��ת��Ϊ�����׼bmpָ��
	void BMPWrite(int width,int height,BYTE* data,CString path);//��һ��������֪�������׼bmpָ������д��path�ļ���
	//�ۺϹ���
	float** LoadBmp();//��ͼ������ת��Ϊ��ά����
	void WriteBmpFile(int width,int height,float** data, CString path);


	//24λ��Ȳ���
	void Bmp24Write(int width,int height,BYTE* R,BYTE* G, BYTE* B, CString path);//����ָ��ֱ��д



	//����ģ��
	//�߼��ع��Ԫ������������飬��ɫ��ɫ����
	CMatrixCal LoadLRTestData();//�����߼��ع���������ͼ
	CMatrixCal ExtractX(CMatrixCal XY);
	CMatrixCal ExtractY(CMatrixCal XY);
	CMatrixCal MergeXY(CMatrixCal X, CMatrixCal Y);
	//void PostProcess_RB(CMatrixCal XY);
	/*���Ϲ���*/ void PostProcess_RB(CMatrixCal XY);

	//20180927--���ڽ������MiniSARͼ���г�С�飬����ͼ��patch�����룺�ļ�·������������ͼ��飻�ļ�ϵͳ����ԭ�����ļ����£���������������ɽ���ļ�
	void GetPatchFromBMP(int width_cut, int height_cut, int stride_row,int stride_col,CString style);//paht:�����ļ�·����width_cut:��Ƭ��ȣ�height_cut����Ƭ�߶ȣ�stride����Ƭ�ƶ�������
};

