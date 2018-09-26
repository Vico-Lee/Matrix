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

	/////////////////////////////////////////////////线性运算
	float LinearCal(float w, float x, float b);
	CMatrixCal LinearCal(CMatrixCal W, CMatrixCal X, CMatrixCal b);
	CMatrixCal LinearCal_LR(CMatrixCal W, CMatrixCal X, float b);

	/////////////////////////////////////////////////损失函数
	float Loss_LR(float y_hat, float y);
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
	//基础版超参数组：层数L，迭代次数n，学习率a，每层节点数
	CMatrixCal HiddenLayerCal(CMatrixCal W, CMatrixCal A_last, CMatrixCal b);//单样本下，一个计算单元：样本数不影响本层的W,b的维度参数，A_last的列数发生变化，与样本相等，行数代表节点数，列数代表样本数
	CMatrixCal FowardPro_ToNextLayer(CMatrixCal W, CMatrixCal A_last, CMatrixCal b,CString style);
	CMatrixCal OutLayer_Bin(CMatrixCal W, CMatrixCal A_last, CMatrixCal b);
};

