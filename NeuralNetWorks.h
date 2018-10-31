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
	int m;//样本数量
	/////////////////////////////////////////////////Activation-激活函数集合，可重用，style：1-sigmoid,2-tanh,3-ReLU,4-Leaky ReLU
	float ActivationFunction(float z, CString style);
	CMatrixCal ActivationFunction(CMatrixCal Z, CString style);
	CMatrixCal Derivative_Activation(CMatrixCal G, CString style);

	/////////////////////////////////////////////////线性运算
	float LinearCal(float w, float x, float b);
	CMatrixCal LinearCal(CMatrixCal W, CMatrixCal X, CMatrixCal b);
	CMatrixCal LinearCal_LR(CMatrixCal W, CMatrixCal X, float b);

	/////////////////////////////////////////////////损失函数
	float Loss_LR(float y_hat, float y);//y_hat与y间的log公式差
	float Cost_LR(int m, CMatrixCal Y_hat, CMatrixCal Y);

	/////////////////////////////////////////////////反向传播
	CMatrixCal dJ_dZ_sigmoid(CMatrixCal Y_hat, CMatrixCal Y);
	CMatrixCal dW_LR(int m,CMatrixCal X, CMatrixCal dZ);
	float db_LR(int m ,CMatrixCal dZ);

	/////////////////////////////////////////////////更新
	float Update_LR(CMatrixCal W, float b, CMatrixCal dW, float db,float alpha);
	Parameters UpdateWb_LR(CMatrixCal W, float b, CMatrixCal dW, float db,float alpha);
	/////////////////////////////////////////////////输出
	CMatrixCal LR_Yhat(CMatrixCal X, CMatrixCal W,float b,CString style);
	//////////////////////////////////////////////////组合函数--逻辑回归
	void LogisticRegression_ParaTrain(CMatrixCal X, CMatrixCal Y,int n,float alpha);
	void LR_RedBlueTest();
	Parameters LR_Train(CMatrixCal X, CMatrixCal Y,int n,float alpha);
	void LR_RBTestPara(int n ,float alpha);
	//////////////////////////////////////////////////测试组
	void BackTest();//通过
	void IrTest();//通过


	/////////////////////////////////////////////////////////////////////////////////////////////L+1层神经网络：输入为0层，输出为L层，隐层编号1~L-1
	//基础版超参数组：层数L，迭代次数n，学习率a，每层节点数；
	//第l层的矢量化w的结构为：nx*m,nx是该层节点数，m为输入的个数，第1层的m与输入数据维度相等；输出层w[L]的行数为1
	//正向传播组
	CMatrixCal HiddenLayerCal(CMatrixCal W, CMatrixCal A_last, CMatrixCal b);//1级函数；单样本下，一个计算单元：样本数不影响本层的W,b的维度参数，A_last的列数发生变化，与样本相等，行数代表节点数，列数代表样本数
	CMatrixCal FowardPro_ToNextLayer(CMatrixCal W, CMatrixCal A_last, CMatrixCal b,CString style);//2级函数，中间调用了HiddenLayerCal；
	CMatrixCal OutLayer_Bin(CMatrixCal W, CMatrixCal A_last, CMatrixCal b);//2级函数，是FowardPro_ToNextLayer的sigmoid激活版，输出为二元结果
	//后向传播组
	CMatrixCal dZ_of_OutputLayer(CMatrixCal Y_hat, CMatrixCal Y);//dZ = A - Y = Y_hat - Y;针对输出层sigmoid激活方式的dZ值
	CMatrixCal dW_of_OutputLayer(CMatrixCal A_previous, CMatrixCal dZ_out);//dW = 1/m * A_last·(dZ_out).T,仅针对sigmoid模式的输出层
	CMatrixCal db_of_OutputLayer(CMatrixCal dZ_out);//db = sum(dZ_out)/m;仅针对sigmoid模式的输出层
	CMatrixCal dZ_of_HiddenLayer(CMatrixCal W_later, CMatrixCal dZ_later, CMatrixCal A_current, CString style);//隐层的dZ计算，dZ = W[l+1层].T*dZ[l+1层]·g'(Z[本层])[本层]
	CMatrixCal dW_of_HiddenLayer(CMatrixCal A_previous, CMatrixCal dZ_current);//dW = 1/m * A_last·(dZ_out).T
	CMatrixCal db_of_HiddenLayer(CMatrixCal dZ_current);//db = sum(dZ_out)/m;
	//初始化部分
	//参数及网络配置
	typedef struct NetConfig_NN//网络结构配置说明
	{
		BOOL IS_INIT;//该文件中node_num是否初始化了
		float a;//学习率
		int n;//迭代次数
		int Layer_num;//网络层数，按L层记
		int* node_num;//每层的节点数，使用前需要根据Layer_num初始化，使用后要释放；node_num[0]为第一层，node_num[L-1]为输出层，sigmoid输出时值为1；
		CString* Act_style;//激活方式
		CMatrixCal Loss;
	};
	void ReleaseNetConfig_NN(NetConfig_NN Config);
	typedef struct Parameters_NN
	{
		int m_numofnode;//W的行数，表示当前层的节点数，也是下一层的输入维度
		int n_numofinput;//W的列数，表示上一层的输入维度
		CMatrixCal W;//m*n:节点数*上一层输入维度
		CMatrixCal b;//列向量，行数为m，列数为1
		CMatrixCal A;
		CMatrixCal dZ;
		CMatrixCal dW;
		CMatrixCal db;
		CMatrixCal Z;
	};
	void ReleasePara_NN(Parameters_NN &Para);
	void ReleaseOthers_ResearveWB_Para_NN(Parameters_NN &Para);
	Parameters_NN* InitParameters_NN(NetConfig_NN Config, int input_dimension);//从config来初始化参数,input_dimension是初始的输入维度，与样本X的行数相等
	//启动、组合、应用函数，输入数据：叠加了Y的X
	Parameters_NN* ParaTrain_of_NN(NetConfig_NN Config, CMatrixCal X, CMatrixCal Y);//X:输入数据，维度为input_dimension*m,Y:标准二值数据 Config:配置信息，生成训练好的参数
	//测试组
	void NN_Test();
	void NN_Test2();
	void NN_Test3();
	void NN_Test4();
};

