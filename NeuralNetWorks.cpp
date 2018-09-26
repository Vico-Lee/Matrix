#include "stdafx.h"
#include "NeuralNetWorks.h"
//#include "MatrixCal.h"
//#include "math.h"

#define e_sci  2.7182818284
CNeuralNetWorks::CNeuralNetWorks(void)
{
}


CNeuralNetWorks::~CNeuralNetWorks(void)
{
}

float CNeuralNetWorks::ActivationFunction(float z, CString style)
{
	float a;
	if(style == "sigmoid")
	{
		a = 1/(1+pow((float)e_sci,-z));
	}
	else if(style == "tanh")
	{
		a = (pow((float)e_sci,z)-pow((float)e_sci,-z))/(pow((float)e_sci,z)+pow((float)e_sci,-z));
	}
	else if(style == "ReLU")
	{
		a = max(0,z);
	}
	else if(style == "Leaky ReLU")
	{
		a = max(0.01*z,z);
	}
	else
	{
		AfxMessageBox("激活函数格式出错！\n请检查代码重新编译。");
		a = -996699;
	}
	return a;
}
CMatrixCal CNeuralNetWorks::ActivationFunction(CMatrixCal Z, CString style)
{
	CMatrixCal A(Z.row_m,Z.col_n);
	if(style == "sigmoid")
	{
		for(int m=0;m<A.row_m;m++)
		{
			for(int n=0;n<A.col_n;n++)
			{
				A.data[m][n] = 1/(1+pow((float)e_sci,-Z.data[m][n]));
			}
		}
		
	}
	else if(style == "tanh")
	{
		for(int m=0;m<A.row_m;m++)
		{
			for(int n=0;n<A.col_n;n++)
			{
				A.data[m][n] = (pow((float)e_sci,Z.data[m][n])-pow((float)e_sci,-Z.data[m][n]))/(pow((float)e_sci,Z.data[m][n])+pow((float)e_sci,-Z.data[m][n]));
			}
		}
	}
	else if(style == "ReLU")
	{
		for(int m=0;m<A.row_m;m++)
		{
			for(int n=0;n<A.col_n;n++)
			{
				A.data[m][n] = max(0,Z.data[m][n]);
			}
		}
	}
	else if(style == "Leaky ReLU")
	{
		for(int m=0;m<A.row_m;m++)
		{
			for(int n=0;n<A.col_n;n++)
			{
				A.data[m][n] = max(0.01*Z.data[m][n],Z.data[m][n]);
			}
		}
	}
	else
	{
		AfxMessageBox("激活函数格式出错！\n请检查代码重新编译。");
	}
	return A;
}

float CNeuralNetWorks::LinearCal(float w, float x, float b)
{
	float z;
	z = w*x+b;
	return z;
}
CMatrixCal CNeuralNetWorks::LinearCal(CMatrixCal W, CMatrixCal X, CMatrixCal b)
{
	CMatrixCal WT = W.Transpose(W);
	CMatrixCal WTxX = WT.Multiply(WT,X); 
	CMatrixCal Z = Z.Plus(WTxX,b);
	WT.Release();
	WTxX.Release();
	return Z;
}
CMatrixCal CNeuralNetWorks::LinearCal_LR(CMatrixCal W, CMatrixCal X, float b)
{
	CMatrixCal WT = W.Transpose(W);
	CMatrixCal WTxX = WT.Multiply(WT,X); 
	CMatrixCal Z = Z.Plus(WTxX,b);
	WT.Release();
	WTxX.Release();

	return Z;
}
float CNeuralNetWorks::Loss_LR(float y_hat, float y)
{
	float L;
	float temp1 = y*log(y_hat+0.0000001);
	float temp2 = (1-y)*log(1-y_hat+0.0000001);
	if(1-y==0)
	{
		temp2=0;
	}
	L = -(temp1 + temp2);
	return L;
}
float CNeuralNetWorks::Cost_LR(int m, CMatrixCal Y_hat, CMatrixCal Y)
{
	float cost = 0;
	if(Y_hat.row_m != 1 || Y.row_m != 1)
	{
		AfxMessageBox("Y矩阵不是一个行向量");
		return cost;
	}
	else if(Y_hat.col_n != m || Y.col_n !=m)
	{
		AfxMessageBox("Y矩阵列数与样本数不等");
		return cost;
	}
	else
	{
		for(int n=0;n<m;n++)
		{
			cost = cost+Loss_LR(Y_hat.data[0][n],Y.data[0][n]);
		}
		cost = cost/m;
		return cost;
	}	
}

CMatrixCal CNeuralNetWorks::dJ_dZ_sigmoid(CMatrixCal A, CMatrixCal Y)
{
	CMatrixCal dZ = dZ.Sub(A,Y);
	return dZ;
}
CMatrixCal CNeuralNetWorks::dW_LR(int m,CMatrixCal X, CMatrixCal dZ)
{
	CMatrixCal dZT = dZ.Transpose(dZ);
	CMatrixCal dW = dW.Multiply(X,dZT);
	float p = 1.0/m;
	dW.MultiBy(p);
	dZT.Release();
	return dW;
}
float CNeuralNetWorks::db_LR(int m ,CMatrixCal dZ)
{
	float db;
	db = dZ.SumAll()/m;
	return db;
}
float CNeuralNetWorks::Update_LR(CMatrixCal W, float b, CMatrixCal dW, float db,float alpha)
{
	dW.MultiBy(alpha);
	W.SubBy(dW);
	float res = b-alpha*db;
	return res;
}
CNeuralNetWorks::Parameters CNeuralNetWorks::UpdateWb_LR(CMatrixCal W, float b, CMatrixCal dW, float db,float alpha)
{
	Parameters para;
	para.W.InitMatrix(W.row_m,W.col_n);
	para.W.CopyMatrixData(W);
	dW.MultiBy(alpha);
	para.W.SubBy(dW);
	para.b = b-alpha*db;
	return para;
}
CMatrixCal CNeuralNetWorks::LR_Yhat(CMatrixCal X, CMatrixCal W,float b,CString style)
{
	CMatrixCal A_hat = LinearCal_LR(W, X, b);
	CMatrixCal Y_hat = ActivationFunction(A_hat, "sigmoid");
	A_hat.Release();
	return Y_hat;
}
void CNeuralNetWorks::LogisticRegression_ParaTrain(CMatrixCal X, CMatrixCal Y, int n,float alpha)
{
	////可删除起始
	X.ChangeName("样本矩阵X");
	//X.ShowStruct();
	////可删除结束


	m = X.col_n;
	CMatrixCal W(X.row_m,1);
	for(int i=0;i<W.row_m;i++)
	{
		for(int j=0;j<W.col_n;j++)
		{
			W.data[i][j] = 4;
		}
	}
	float b=0;
	
	////可删除起始
	W.ChangeName("初始化参数矩阵W");
	//W.ShowStruct();
	////可删除结束

	for(int i=0;i<n;i++)
	{	
		CString str;

		CMatrixCal Y_hat = LR_Yhat(X,W,b,"sigmoid");
		
		CMatrixCal dZ = dJ_dZ_sigmoid(Y_hat, Y);
		CMatrixCal dW = dW_LR(m,X,dZ);
		float db = db_LR(m,dZ);
		b = Update_LR(W,b,dW,db,alpha);
		str.Format("b：%f",b);
		/*AfxMessageBox(str);*/
		float Loss = Cost_LR(m,Y_hat,Y);
		//可删除起始
		W.ChangeName("训练中W");
		//W.ShowData();
		//可删除结束
		
		str.Format("损失：%f",Loss);
		//AfxMessageBox(str);

		Y_hat.Release();
		dZ.Release();
		dW.Release();
	}


	//可删除起始
	W.ChangeName("训练结束后W");
	//W.ShowStruct();
	//W.ShowData();
	//可删除结束
	CMatrixCal Y_hat = LR_Yhat(X,W,b,"sigmoid");
	float Loss = Cost_LR(m,Y_hat,Y);
	CString str;
	str.Format("损失：%f",Loss);
	//AfxMessageBox(str);
	Y_hat.Release();
}
CNeuralNetWorks::Parameters CNeuralNetWorks::LR_Train(CMatrixCal X, CMatrixCal Y,int n,float alpha)
{
	//提取样本信息
	X.ChangeName("样本矩阵X");
	m = X.col_n;
	//初始化参数
	Parameters para;
	para.W.InitMatrix(X.row_m,1);
	for(int i=0;i<para.W.row_m;i++)
	{
		for(int j=0;j<para.W.col_n;j++)
		{
			para.W.data[i][j] = 0;
		}
	}
	para.b=0;
	para.W.ChangeName("初始化参数矩阵W");
	

	//开始迭代
	for(int i=0;i<n;i++)
	{	
		CMatrixCal Y_hat = LR_Yhat(X,para.W,para.b,"sigmoid");
		CMatrixCal dZ = dJ_dZ_sigmoid(Y_hat, Y);
		CMatrixCal dW = dW_LR(m,X,dZ);
		float db = db_LR(m,dZ);
		Parameters para_temp = UpdateWb_LR(para.W,para.b,dW,db,alpha);
		para.W.CopyMatrixData(para_temp.W);
		para.b = para_temp.b;
		para_temp.W.Release();
		Y_hat.Release();
		dZ.Release();
		dW.Release();
	}
	return para;
}
void CNeuralNetWorks::BackTest()
{
	CMatrixCal X(2,3);
	X.ChangeName("X");
	X.data[0][0] = 1;
	X.data[0][1] = 2;
	X.data[0][2] = -1;

	X.data[1][0] = 3;
	X.data[1][1] = 4;
	X.data[1][2] = -3.2;


	float b = 2;

	CMatrixCal Y(1,3);
	Y.ChangeName("Y");
	Y.data[0][0] = 1;
	Y.data[0][1] = 0;
	Y.data[0][2] = 1;


	CMatrixCal W(2,1);
	W.ChangeName("W");
	W.data[0][0] = 1;
	W.data[1][0] = 2;

	m = 3;
	CMatrixCal A_hat = LinearCal_LR(W, X, b);
	A_hat.ChangeName("A_hat");
	A_hat.ShowData();
	CMatrixCal Y_hat = LR_Yhat(X,W,b,"sigmoid");
	CMatrixCal dZ = dJ_dZ_sigmoid(Y_hat,Y);
	CMatrixCal dW = dW_LR(3,X,dZ);
	float db = db_LR(3,dZ);
	Y_hat.ChangeName("Y_hat");
	Y_hat.ShowData();
	dW.ChangeName("dW");
	dW.ShowData();
	CString str;
	str.Format("db：%f",db);
	AfxMessageBox(str);

	float Loss = Cost_LR(m,Y_hat,Y);

	str.Format("损失：%f",Loss);
	AfxMessageBox(str);
}
void CNeuralNetWorks::IrTest()
{
	CMatrixCal X(2,3);
	X.ChangeName("X");
	X.data[0][0] = 1;
	X.data[0][1] = 2;
	X.data[0][2] = -1;

	X.data[1][0] = 3;
	X.data[1][1] = 4;
	X.data[1][2] = -3.2;


	float b = 2;

	CMatrixCal Y(1,3);
	Y.ChangeName("Y");
	Y.data[0][0] = 1;
	Y.data[0][1] = 0;
	Y.data[0][2] = 1;


	CMatrixCal W(2,1);
	W.ChangeName("W");
	W.data[0][0] = 1;
	W.data[1][0] = 2;
	m = 3;
	CMatrixCal dW(2,1);
	float db;
	int n = 100;
	float alpha = 0.009;

	for(int i=0;i<n;i++)
	{	
		CString str;

		CMatrixCal Y_hat = LR_Yhat(X,W,b,"sigmoid");
		CMatrixCal dZ = dJ_dZ_sigmoid(Y_hat, Y);
		dW = dW_LR(m,X,dZ);
		db = db_LR(m,dZ);
		b = Update_LR(W,b,dW,db,alpha);
		str.Format("b：%f",b);
		/*AfxMessageBox(str);*/
		float Loss = Cost_LR(m,Y_hat,Y);
		//可删除起始
		/*W.ChangeName("训练中W");
		W.ShowData();*/
		//可删除结束
		
		str.Format("损失：%f",Loss);
		//AfxMessageBox(str);

		/*Y_hat.Release();
		dZ.Release();
		dW.Release();*/
	}















	CMatrixCal Y_hat = LR_Yhat(X,W,b,"sigmoid");



	//Y_hat.ChangeName("Y_hat");
	//Y_hat.ShowData();

	W.ShowData();
	CString str;
	str.Format("b：%f",b);
	AfxMessageBox(str);
	str.Format("db：%f",db);
	AfxMessageBox(str);

	float Loss = Cost_LR(m,Y_hat,Y);

	str.Format("损失：%f",Loss);
	AfxMessageBox(str);
}
void CNeuralNetWorks::LR_RedBlueTest()
{
	CDataSet m_data;
	CMatrixCal XY = m_data.LoadLRTestData();
	CMatrixCal X = m_data.ExtractX(XY);
	CMatrixCal Y = m_data.ExtractY(XY);
	X.ChangeName("X");
	Y.ChangeName("Y");
	XY.ChangeName("XY");
	//XY.ShowData();


	m = X.col_n;
	int n = 10000;
	float alpha = 0.09;
	CMatrixCal W(X.row_m,1);
	for(int i=0;i<W.row_m;i++)
	{
		for(int j=0;j<W.col_n;j++)
		{
			W.data[i][j] = 0;
		}
	}
	float b=0;

	
	for(int i=0;i<n;i++)
	{	
		
		CMatrixCal Y_hat = LR_Yhat(X,W,b,"sigmoid");
		CMatrixCal dZ = dJ_dZ_sigmoid(Y_hat, Y);
		CMatrixCal dW = dW_LR(m,X,dZ);
		float db = db_LR(m,dZ);
		b = Update_LR(W,b,dW,db,alpha);
		W.ChangeName("训练中W");
		if(i%1000 == 0)
		{
			float Loss = Cost_LR(m,Y_hat,Y);
			CString str;
			str.Format("损失：%f",Loss);
			//AfxMessageBox(str);
			//W.ShowData();
		}

		Y_hat.Release();
		dZ.Release();
		dW.Release();
	}
	W.ChangeName("训练结束后W");
	//W.ShowData();
	CString str;
	str.Format("b：%f",b);
	//AfxMessageBox(str);
	CMatrixCal X_test(2,m_data.height_image*m_data.width_image);
	
	for(int m=0;m<m_data.height_image;m++)
	{
		for(int n=0;n<m_data.width_image;n++)
		{
			X_test.data[0][m*m_data.width_image+n] = m;
			X_test.data[1][m*m_data.width_image+n] = n;
		}
	}
	CMatrixCal Y_test = LR_Yhat(X_test,W,b,"sigmoid");
	CMatrixCal XY_test = m_data.MergeXY(X_test,Y_test);
	m_data.PostProcess_RB(XY_test);


	XY.Release();
	X.Release();
	Y.Release();
	XY_test.Release();
	Y_test.Release();
	X_test.Release();
	W.Release();
}
void CNeuralNetWorks::LR_RBTestPara(int n ,float alpha)
{
	int time_begin = clock();

	CDataSet m_data;
	CMatrixCal XY = m_data.LoadLRTestData();
	CMatrixCal X = m_data.ExtractX(XY);
	CMatrixCal Y = m_data.ExtractY(XY);
	X.ChangeName("X");
	Y.ChangeName("Y");
	XY.ChangeName("XY");
	//XY.ShowData();


	m = X.col_n;
	Parameters para = LR_Train(X, Y, n,alpha);

	CMatrixCal X_test(2,m_data.height_image*m_data.width_image);
	
	for(int m=0;m<m_data.height_image;m++)
	{
		for(int n=0;n<m_data.width_image;n++)
		{
			X_test.data[0][m*m_data.width_image+n] = m;
			X_test.data[1][m*m_data.width_image+n] = n;
		}
	}
	CMatrixCal Y_test = LR_Yhat(X_test,para.W,para.b,"sigmoid");
	CMatrixCal XY_test = m_data.MergeXY(X_test,Y_test);
	m_data.PostProcess_RB(XY_test);


	XY.Release();
	X.Release();
	Y.Release();
	XY_test.Release();
	Y_test.Release();
	X_test.Release();
	para.W.Release();

	int time_end = clock();
	int time_consume = time_end - time_begin;
	float time_s = (float)time_consume/1000;
	CString time_message;
	time_message.Format("运行完毕！\n参数组：循环次数n=%d,学习率alpha=%f\n耗时为%d毫秒，%.3f秒",n,alpha,time_consume,time_s);
	AfxMessageBox(time_message);
}
//一个计算单元,输入上一层的输出，与大的组合W相乘，与b相加
CMatrixCal CNeuralNetWorks::HiddenLayerCal(CMatrixCal W, CMatrixCal A_last, CMatrixCal b)
{
	CMatrixCal WX = WX.Multiply(W,A_last); 
	CMatrixCal Z = Z.Plus(WX,b);
	WX.Release();
	return Z;
}
CMatrixCal CNeuralNetWorks::FowardPro_ToNextLayer(CMatrixCal W, CMatrixCal A_last, CMatrixCal b,CString style)
{
	CMatrixCal Z = HiddenLayerCal(W,A_last,b);
	CMatrixCal A = ActivationFunction(Z,style);
	Z.Release();
	return Z;
}
CMatrixCal CNeuralNetWorks::OutLayer_Bin(CMatrixCal W, CMatrixCal A_last, CMatrixCal b)
{
	if(W.row_m != 1)
	{
		CMatrixCal temp;
		AfxMessageBox("输出层W的维度不为1");
		return temp;
	}
	else
	{
		CMatrixCal Y_hat = FowardPro_ToNextLayer(W, A_last, b,"sigmoid");
		return Y_hat;
	}
}