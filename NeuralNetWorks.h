#pragma once
class CNeuralNetWorks
{
public:
	CNeuralNetWorks(void);
	~CNeuralNetWorks(void);

public:
	typedef struct Parameters
	{
		CMatrixCal W;
		float b;
	};

public:
	int m;//��������
	/////////////////////////////////////////////////Activation-��������ϣ������ã�style��1-sigmoid,2-tanh,3-ReLU,4-Leaky ReLU
	float ActivationFunction(float z, CString style);
	CMatrixCal ActivationFunction(CMatrixCal Z, CString style);

	/////////////////////////////////////////////////��������
	float LinearCal(float w, float x, float b);
	CMatrixCal LinearCal(CMatrixCal W, CMatrixCal X, CMatrixCal b);
	CMatrixCal LinearCal_LR(CMatrixCal W, CMatrixCal X, float b);

	/////////////////////////////////////////////////��ʧ����
	float Loss_LR(float y_hat, float y);
	float Cost_LR(int m, CMatrixCal Y_hat, CMatrixCal Y);

	/////////////////////////////////////////////////���򴫲�
	CMatrixCal dJ_dZ_sigmoid(CMatrixCal Y_hat, CMatrixCal Y);
	CMatrixCal dW_LR(int m,CMatrixCal X, CMatrixCal dZ);
	float db_LR(int m ,CMatrixCal dZ);

	/////////////////////////////////////////////////����
	float Update_LR(CMatrixCal W, float b, CMatrixCal dW, float db,float alpha);
	Parameters UpdateWb_LR(CMatrixCal W, float b, CMatrixCal dW, float db,float alpha);
	/////////////////////////////////////////////////���
	CMatrixCal LR_Yhat(CMatrixCal X, CMatrixCal W,float b,CString style);
	//////////////////////////////////////////////////��Ϻ���--�߼��ع�
	void LogisticRegression_ParaTrain(CMatrixCal X, CMatrixCal Y,int n,float alpha);
	void LR_RedBlueTest();
	Parameters LR_Train(CMatrixCal X, CMatrixCal Y,int n,float alpha);
	void LR_RBTestPara(int n ,float alpha);
	//////////////////////////////////////////////////������
	void BackTest();//ͨ��
	void IrTest();//ͨ��


	/////////////////////////////////////////////////////////////////////////////////////////////L+1�������磺����Ϊ0�㣬���ΪL�㣬������1~L-1
	//�����泬�����飺����L����������n��ѧϰ��a��ÿ��ڵ���
	CMatrixCal HiddenLayerCal(CMatrixCal W, CMatrixCal A_last, CMatrixCal b);//�������£�һ�����㵥Ԫ����������Ӱ�챾���W,b��ά�Ȳ�����A_last�����������仯����������ȣ���������ڵ�������������������
	CMatrixCal FowardPro_ToNextLayer(CMatrixCal W, CMatrixCal A_last, CMatrixCal b,CString style);
	CMatrixCal OutLayer_Bin(CMatrixCal W, CMatrixCal A_last, CMatrixCal b);
};

