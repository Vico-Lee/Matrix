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
	CMatrixCal Derivative_Activation(CMatrixCal G, CString style);

	/////////////////////////////////////////////////��������
	float LinearCal(float w, float x, float b);
	CMatrixCal LinearCal(CMatrixCal W, CMatrixCal X, CMatrixCal b);
	CMatrixCal LinearCal_LR(CMatrixCal W, CMatrixCal X, float b);

	/////////////////////////////////////////////////��ʧ����
	float Loss_LR(float y_hat, float y);//y_hat��y���log��ʽ��
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
	//�����泬�����飺����L����������n��ѧϰ��a��ÿ��ڵ�����
	//��l���ʸ����w�ĽṹΪ��nx*m,nx�Ǹò�ڵ�����mΪ����ĸ�������1���m����������ά����ȣ������w[L]������Ϊ1
	//���򴫲���
	CMatrixCal HiddenLayerCal(CMatrixCal W, CMatrixCal A_last, CMatrixCal b);//1���������������£�һ�����㵥Ԫ����������Ӱ�챾���W,b��ά�Ȳ�����A_last�����������仯����������ȣ���������ڵ�������������������
	CMatrixCal FowardPro_ToNextLayer(CMatrixCal W, CMatrixCal A_last, CMatrixCal b,CString style);//2���������м������HiddenLayerCal��
	CMatrixCal OutLayer_Bin(CMatrixCal W, CMatrixCal A_last, CMatrixCal b);//2����������FowardPro_ToNextLayer��sigmoid����棬���Ϊ��Ԫ���
	//���򴫲���
	CMatrixCal dZ_of_OutputLayer(CMatrixCal Y_hat, CMatrixCal Y);//dZ = A - Y = Y_hat - Y;��������sigmoid���ʽ��dZֵ
	CMatrixCal dW_of_OutputLayer(CMatrixCal A_previous, CMatrixCal dZ_out);//dW = 1/m * A_last��(dZ_out).T,�����sigmoidģʽ�������
	CMatrixCal db_of_OutputLayer(CMatrixCal dZ_out);//db = sum(dZ_out)/m;�����sigmoidģʽ�������
	CMatrixCal dZ_of_HiddenLayer(CMatrixCal W_later, CMatrixCal dZ_later, CMatrixCal A_current, CString style);//�����dZ���㣬dZ = W[l+1��].T*dZ[l+1��]��g'(Z[����])[����]
	CMatrixCal dW_of_HiddenLayer(CMatrixCal A_previous, CMatrixCal dZ_current);//dW = 1/m * A_last��(dZ_out).T
	CMatrixCal db_of_HiddenLayer(CMatrixCal dZ_current);//db = sum(dZ_out)/m;
	//��ʼ������
	//��������������
	typedef struct NetConfig_NN//����ṹ����˵��
	{
		BOOL IS_INIT;//���ļ���node_num�Ƿ��ʼ����
		float a;//ѧϰ��
		int n;//��������
		int Layer_num;//�����������L���
		int* node_num;//ÿ��Ľڵ�����ʹ��ǰ��Ҫ����Layer_num��ʼ����ʹ�ú�Ҫ�ͷţ�node_num[0]Ϊ��һ�㣬node_num[L-1]Ϊ����㣬sigmoid���ʱֵΪ1��
		CString* Act_style;//���ʽ
		CMatrixCal Loss;
	};
	void ReleaseNetConfig_NN(NetConfig_NN Config);
	typedef struct Parameters_NN
	{
		int m_numofnode;//W����������ʾ��ǰ��Ľڵ�����Ҳ����һ�������ά��
		int n_numofinput;//W����������ʾ��һ�������ά��
		CMatrixCal W;//m*n:�ڵ���*��һ������ά��
		CMatrixCal b;//������������Ϊm������Ϊ1
		CMatrixCal A;
		CMatrixCal dZ;
		CMatrixCal dW;
		CMatrixCal db;
		CMatrixCal Z;
	};
	void ReleasePara_NN(Parameters_NN &Para);
	void ReleaseOthers_ResearveWB_Para_NN(Parameters_NN &Para);
	Parameters_NN* InitParameters_NN(NetConfig_NN Config, int input_dimension);//��config����ʼ������,input_dimension�ǳ�ʼ������ά�ȣ�������X���������
	//��������ϡ�Ӧ�ú������������ݣ�������Y��X
	Parameters_NN* ParaTrain_of_NN(NetConfig_NN Config, CMatrixCal X, CMatrixCal Y);//X:�������ݣ�ά��Ϊinput_dimension*m,Y:��׼��ֵ���� Config:������Ϣ������ѵ���õĲ���
	//������
	void NN_Test();
	void NN_Test2();
	void NN_Test3();
	void NN_Test4();
};

