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
		if(z>=10)
		{
			a=1;
		}
		else if(z<=-10)
		{
			a=-1;
		}
		else
		{
			a = (pow((float)e_sci,z)-pow((float)e_sci,-z))/(pow((float)e_sci,z)+pow((float)e_sci,-z));
		}
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
				if(Z.data[m][n]>=10)
				{
					A.data[m][n]=1;
				}
				else if(Z.data[m][n]<=-10)
				{
					A.data[m][n]=-1;
				}
				else
				{
					A.data[m][n] = (pow((float)e_sci,Z.data[m][n])-pow((float)e_sci,-Z.data[m][n]))/(pow((float)e_sci,Z.data[m][n])+pow((float)e_sci,-Z.data[m][n]));
				}
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
CMatrixCal CNeuralNetWorks::Derivative_Activation(CMatrixCal G, CString style)
{
	CMatrixCal G_dot(G.row_m,G.col_n);
	if(style == "sigmoid")
	{
		for(int m=0;m<G_dot.row_m;m++)
		{
			for(int n=0;n<G_dot.col_n;n++)
			{
				G_dot.data[m][n] = G.data[m][n] - G.data[m][n]*G.data[m][n];
			}
		}
		
	}
	else if(style == "tanh")
	{
		for(int m=0;m<G_dot.row_m;m++)
		{
			for(int n=0;n<G_dot.col_n;n++)
			{
				G_dot.data[m][n] = 1 - G.data[m][n]*G.data[m][n];
			}
		}
	}
	else if(style == "ReLU")
	{
		for(int m=0;m<G_dot.row_m;m++)
		{
			for(int n=0;n<G_dot.col_n;n++)
			{
				if(G.data[m][n]>0)
				{
					G_dot.data[m][n] = 1;
				}
				else
				{
					G_dot.data[m][n] = 0;
				}
			}
		}
	}
	else if(style == "Leaky ReLU")
	{
		for(int m=0;m<G_dot.row_m;m++)
		{
			for(int n=0;n<G_dot.col_n;n++)
			{
				if(G.data[m][n]>0)
				{
					G_dot.data[m][n] = 1;
				}
				else
				{
					G_dot.data[m][n] = 0.01;
				}
			}
		}
	}
	else
	{
		AfxMessageBox("激活函数格式出错！\n请检查代码重新编译。");
	}
	return G_dot;
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
	CMatrixCal Z = Z.Plus_MatrixByColV(WX,b);
	WX.Release();
	WX.data = NULL;
	return Z;
}
//2级函数，中间调用了HiddenLayerCal；
CMatrixCal CNeuralNetWorks::FowardPro_ToNextLayer(CMatrixCal W, CMatrixCal A_last, CMatrixCal b,CString style)
{
	CMatrixCal Z = HiddenLayerCal(W,A_last,b);
	CMatrixCal A = ActivationFunction(Z,style);
	Z.Release();
	Z.data = NULL;
	return Z;
}

//2级函数，是FowardPro_ToNextLayer的sigmoid激活版，输出为二元结果
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
//dZ = A - Y = Y_hat - Y;针对输出层sigmoid激活方式的dZ值
CMatrixCal CNeuralNetWorks::dZ_of_OutputLayer(CMatrixCal Y_hat, CMatrixCal Y)
{
	//Y_hat = A; dZ = A - Y = Y_hat - Y;
	CMatrixCal dZ = dZ.Sub(Y_hat,Y);
	return dZ;
}

//dW = 1/m * A_last·(dZ_out).T,仅针对sigmoid模式的输出层
CMatrixCal CNeuralNetWorks::dW_of_OutputLayer(CMatrixCal A_previous, CMatrixCal dZ_out)
{
	CMatrixCal AT = A_previous.Transpose(A_previous);
	CMatrixCal dW = dW.Multiply(dZ_out,AT);
	float p = 1.0/dZ_out.col_n;
	dW.MultiBy(p);
	AT.Release();
	AT.data = NULL;
	return dW;
}

//db = sum(dZ_out)/m;仅针对sigmoid模式的输出层
CMatrixCal CNeuralNetWorks::db_of_OutputLayer(CMatrixCal dZ_out)
{
	CMatrixCal db = dZ_out.SumRow_toCol(dZ_out);
	float p = 1.0/dZ_out.col_n;
	db.MultiBy(p);
	return db;
}

//隐层的dZ计算，dZ = W[l+1层].T*dZ[l+1层]·g'(Z[本层])[本层]
CMatrixCal CNeuralNetWorks::dZ_of_HiddenLayer(CMatrixCal W_later, CMatrixCal dZ_later, CMatrixCal A_current, CString style)
{
	CMatrixCal WT = W_later.Transpose(W_later);
	CMatrixCal dZ = dZ.Multiply(WT,dZ_later);
	CMatrixCal G_dot = Derivative_Activation(A_current, style);
	dZ.DotBy(G_dot);
	WT.Release();
	WT.data = NULL;
	G_dot.Release();
	G_dot.data = NULL;

	return dZ;
}

//dW = 1/m * A_last·(dZ_current).T,
CMatrixCal CNeuralNetWorks::dW_of_HiddenLayer(CMatrixCal A_previous, CMatrixCal dZ_current)
{
	CMatrixCal AT = A_previous.Transpose(A_previous);
	CMatrixCal dW = dW.Multiply(dZ_current,AT);
	float p = 1.0/dZ_current.col_n;
	dW.MultiBy(p);
	AT.Release();
	AT.data = NULL;
	return dW;
}

//db = sum(dZ_current)/m;
CMatrixCal CNeuralNetWorks::db_of_HiddenLayer(CMatrixCal dZ_current)
{
	CMatrixCal db = dZ_current.SumRow_toCol(dZ_current);
	float p = 1.0/dZ_current.col_n;
	db.MultiBy(p);
	return db;
}

void CNeuralNetWorks::ReleaseNetConfig_NN(NetConfig_NN Config)
{
	Config.IS_INIT = FALSE;
	delete []Config.node_num;
	Config.node_num = NULL;
	delete []Config.Act_style;
	Config.Act_style = NULL;
	Config.Loss.Release();
}
void CNeuralNetWorks::ReleasePara_NN(Parameters_NN &Para)
{
	Para.W.Release();
	Para.W.data = NULL;
	Para.b.Release();
	Para.b.data = NULL;
	Para.m_numofnode = 0;
	Para.n_numofinput = 0;
}
void CNeuralNetWorks::ReleaseOthers_ResearveWB_Para_NN(Parameters_NN &Para)
{
	Para.Z.Release();
	Para.Z.data = NULL;
	Para.A.Release();
	Para.A.data = NULL;
	Para.dZ.Release();
	Para.dZ.data = NULL;
	Para.dW.Release();
	Para.dW.data = NULL;
	Para.db.Release();
	Para.db.data = NULL;
}
CNeuralNetWorks::Parameters_NN* CNeuralNetWorks::InitParameters_NN(NetConfig_NN Config, int input_dimension)
{
	if(!Config.IS_INIT)
	{
		AfxMessageBox("网络配置未初始化，检查代码或操作");
		return NULL;
	}
	else
	{
		Parameters_NN* Para = new Parameters_NN[Config.Layer_num];
		Para[0].m_numofnode = Config.node_num[0];
		Para[0].n_numofinput = input_dimension;
		Para[0].W.InitMatrix(Para[0].m_numofnode,Para[0].n_numofinput,"gauss");
		Para[0].W.ChangeName("第1层W矩阵");
		Para[0].b.InitMatrix(Para[0].m_numofnode,1);
		Para[0].b.ChangeName("第1层b矩阵");
		for(int l=1;l<Config.Layer_num;l++)
		{
			Para[l].m_numofnode = Config.node_num[l];
			Para[l].n_numofinput = Config.node_num[l-1];
			Para[l].W.InitMatrix(Para[l].m_numofnode,Para[l].n_numofinput,"gauss");
			Para[l].b.InitMatrix(Para[l].m_numofnode,1);

			CString strW,strb;
			strW.Format("第%d层W矩阵",l+1);
			strb.Format("第%d层b矩阵",l+1);
			Para[l].W.ChangeName(strW);
			Para[l].b.ChangeName(strb);
		}
		return Para;
	}
}

//X:输入数据，维度为input_dimension*m,Y:标准二值数据 Config:配置信息，生成训练好的参数
CNeuralNetWorks::Parameters_NN* CNeuralNetWorks::ParaTrain_of_NN(NetConfig_NN Config, CMatrixCal X, CMatrixCal Y)
{
	int m = X.col_n;
	int input_dimension = X.row_m;
	Parameters_NN* Para = InitParameters_NN(Config,input_dimension);//初始化所有Wb和
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Parameters_NN* Para = new Parameters_NN[2];
	//Para[0].W.InitMatrix(4,2);
	//Para[0].b.InitMatrix(4,1);
	//Para[1].W.InitMatrix(1,4);
	//Para[1].b.InitMatrix(1,1);

	//Para[0].W.data[0][0] = -0.00416758;
	//Para[0].W.data[0][1] = -0.00056267;

	//Para[0].W.data[1][0] = -0.02163196;
	//Para[0].W.data[1][1] = 0.01640271;

	//Para[0].W.data[2][0] = -0.01793436;
	//Para[0].W.data[2][1] = -0.00841747;

	//Para[0].W.data[3][0] = 0.00502881;
	//Para[0].W.data[3][1] = -0.01245288;


	//Para[1].W.data[0][0] = -0.01057952;
	//Para[1].W.data[0][1] = -0.00909008;
	//Para[1].W.data[0][2] = 0.00551454;
	//Para[1].W.data[0][3] = 0.02292208;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(int i=0;i<Config.n;i++)//迭代次数循环
	{
		//////////////////////一次正反向传播，生成所有的梯度；
		//第一层
		Para[0].Z = HiddenLayerCal(Para[0].W, X, Para[0].b);
		Para[0].A = ActivationFunction(Para[0].Z,Config.Act_style[0]);
		/*if(i>=5)
		{
			CString str;
			str.Format("第%d次迭代，第%d层Z矩阵",i,Config.Layer_num-2);
			Para[Config.Layer_num-2].Z.ChangeName(str);
			Para[Config.Layer_num-2].Z.ShowDataShort();
			Para[0].Z.ShowData(3,5);

			str.Format("第%d次迭代，第%d层A矩阵",i,Config.Layer_num-2);
			Para[Config.Layer_num-2].A.ChangeName(str);
			Para[Config.Layer_num-2].A.ShowDataShort();
			Para[0].A.ShowData(3,5);
		}*/
		//层循环
		//正向传播
		for(int l=1;l<Config.Layer_num-1;l++)
		{
			Para[l].Z = HiddenLayerCal(Para[l].W, Para[l-1].A, Para[l].b);
			Para[l].A = ActivationFunction(Para[l].Z,Config.Act_style[l]);
		}
		Para[Config.Layer_num-1].Z = HiddenLayerCal(Para[Config.Layer_num-1].W, Para[Config.Layer_num-2].A, Para[Config.Layer_num-1].b);
		Para[Config.Layer_num-1].A =  ActivationFunction(Para[Config.Layer_num-1].Z,"sigmoid");		
		float Cost =  Cost_LR(m, Para[Config.Layer_num-1].A, Y);
		if(i%100 == 0)
		{
			int check = (i-i%100)/100;
			Config.Loss.data[0][check] = Cost;
		}
		
		//反向传播
		//输出层
		
		Para[Config.Layer_num-1].dZ = dZ_of_OutputLayer(Para[Config.Layer_num-1].A,Y);
		Para[Config.Layer_num-1].dW = dW_of_OutputLayer(Para[Config.Layer_num-2].A,Para[Config.Layer_num-1].dZ);
		Para[Config.Layer_num-1].db = db_of_OutputLayer(Para[Config.Layer_num-1].dZ);
		//层循环
		for(int l=Config.Layer_num-2;l>0;l--)
		{
			Para[l].dZ = dZ_of_HiddenLayer(Para[l+1].W, Para[l+1].dZ,Para[l].A,Config.Act_style[l]);
			Para[l].dW = dW_of_HiddenLayer(Para[l-1].A, Para[l].dZ);
			Para[l].db = db_of_HiddenLayer(Para[l].dZ);
		}
		//第一层
		Para[0].dZ = dZ_of_HiddenLayer(Para[1].W, Para[1].dZ,Para[0].A,Config.Act_style[0]);
		Para[0].dW = dW_of_HiddenLayer(X, Para[0].dZ);
		Para[0].db = db_of_HiddenLayer(Para[0].dZ);

		
		//if(i>=1346)
		//{
		//	Config.Loss.ShowData(1,i+1);
		//	for(int l=0;l<Config.Layer_num;l++)
		//	{
		//		CString str;

		//		str.Format("第%d次迭代，W%d矩阵",i+1,l+1);
		//		Para[l].W.ChangeName(str);
		//		Para[l].W.ShowData();
		//		
		//		
		//		str.Format("第%d次迭代，b%d矩阵",i+1,l+1);
		//		Para[l].b.ChangeName(str);
		//		Para[l].b.ShowData();
		//		
		//		str.Format("第%d次迭代，Z%d矩阵",i+1,l+1);
		//		Para[l].Z.ChangeName(str);
		//		Para[l].Z.ShowData();

		//		str.Format("第%d次迭代，A%d矩阵",i+1,l+1);
		//		Para[l].A.ChangeName(str);
		//		Para[l].A.ShowData();

		//		//str.Format("第%d次迭代，第%d层dZ矩阵",i,l);
		//		//Para[l].dZ.ChangeName(str);
		//		//Para[l].dZ.ShowDataShort();

		//		str.Format("第%d次迭代，dW%d矩阵",i+1,l+1);
		//		Para[l].dW.ChangeName(str);
		//		Para[l].dW.ShowData();

		//		str.Format("第%d次迭代，db%d矩阵",i+1,l+1);
		//		Para[l].db.ChangeName(str);
		//		Para[l].db.ShowData();

		//
		//	}
		//}
		////////////////////////根据梯度更新；
		for(int l=0;l<Config.Layer_num;l++)
		{
			Para[l].dW.MultiBy(Config.a);
			Para[l].db.MultiBy(Config.a);
			Para[l].W.SubBy(Para[l].dW);
			Para[l].b.SubBy(Para[l].db);
			//////////////////////////////////////////////////极值去除测试
			//Para[l].W.Check_LargetValue(10);
			//Para[l].b.Check_LargetValue(10);
			ReleaseOthers_ResearveWB_Para_NN(Para[l]);			
		}
		/////////////////////////////////////////
		
	}
	return Para;
}
void CNeuralNetWorks::NN_Test3()
{
	CDataSet m_data;
	CMatrixCal XY = m_data.LoadLRTestData();
	CMatrixCal X = m_data.ExtractX(XY);
	CMatrixCal Y = m_data.ExtractY(XY);
	X.ChangeName("X");
	Y.ChangeName("Y");
	XY.ChangeName("XY");
	//XY.ShowData();
	X.MultiBy(1.0/500);
	X.PlusBy(-2.5);

	



	NetConfig_NN Config;
	Config.IS_INIT = TRUE;
	Config.Layer_num = 2;
	Config.a = 0.1;
	Config.n = 1;
	Config.Act_style = new CString[Config.Layer_num];
	for(int i=0;i<Config.Layer_num;i++)
	{
		Config.Act_style[i] = "tanh";
	}
	Config.Loss.InitMatrix(1,Config.n);
	Config.Loss.ChangeName("损失矩阵");
	Config.node_num = new int[Config.Layer_num];
	Config.node_num[0] = 4;
	Config.node_num[1] = 1;
	//Config.node_num[2] = 1;
	//Config.node_num[3] = 1;
	//Config.node_num[4] = 1;
	//Config.node_num[5] = 1;

	Parameters_NN* Para = ParaTrain_of_NN(Config,X,Y);
	/*Config.Loss.ShowDataShort();*/

	CMatrixCal X_test(2,m_data.height_image*m_data.width_image);
	Para[0].W.ShowDataShort();
	Para[0].W.data[0][0] = -0.65848169;
	Para[0].W.data[1][0] = -0.76204273;
	Para[0].W.data[2][0] = 0.5792005;
	Para[0].W.data[3][0] = 0.76773391;

	Para[0].W.data[0][1] = 1.21866811;
	Para[0].W.data[1][1] = 1.39377573;
	Para[0].W.data[2][1] = -1.10397703;
	Para[0].W.data[3][1] = -1.41477129;

	Para[0].b.data[0][0] =  0.287592;
	Para[0].b.data[1][0] =  0.3511264;
	Para[0].b.data[2][0] = -0.2431246;
	Para[0].b.data[3][0] = -0.35772805;

	Para[1].W.data[0][0] = -2.45566237;
	Para[1].W.data[0][1] = -3.27042274;
	Para[1].W.data[0][2] = 2.00784958;
	Para[1].W.data[0][3] = 3.36773273;

	Para[1].b.data[0][0] = 0.20459656;
	
	
	for(int m=0;m<m_data.height_image;m++)
	{
		for(int n=0;n<m_data.width_image;n++)
		{
			X_test.data[0][m*m_data.width_image+n] = m;
			X_test.data[1][m*m_data.width_image+n] = n;
		}
	}

	X_test.MultiBy(1.0/500);
	X_test.PlusBy(-2.5);
	Para[0].Z = HiddenLayerCal(Para[0].W, X_test, Para[0].b);
	Para[0].A = ActivationFunction(Para[0].Z,Config.Act_style[0]);
	//层循环
	//正向传播
	for(int l=1;l<Config.Layer_num-1;l++)
	{
		Para[l].Z = HiddenLayerCal(Para[l].W, Para[l-1].A, Para[l].b);
		Para[l].A = ActivationFunction(Para[l].Z,Config.Act_style[l]);
	}
	Para[Config.Layer_num-1].Z = HiddenLayerCal(Para[Config.Layer_num-1].W, Para[Config.Layer_num-2].A, Para[Config.Layer_num-1].b);
	CMatrixCal Y_test =  ActivationFunction(Para[Config.Layer_num-1].Z,"sigmoid");
	








	X_test.PlusBy(2.5);
	X_test.MultiBy(500);
	CMatrixCal XY_test = m_data.MergeXY(X_test,Y_test);
	m_data.PostProcess_RB(XY_test);


	XY.Release();
	X.Release();
	Y.Release();
	XY_test.Release();
	Y_test.Release();
	X_test.Release();
	for(int i=0;i>Config.Layer_num;i++)
	{
		ReleasePara_NN(Para[i]);
	}
	ReleaseNetConfig_NN(Config);
}
void CNeuralNetWorks::NN_Test2()
{
	NetConfig_NN Config;
	Config.IS_INIT = TRUE;
	Config.Layer_num = 2;
	Config.a = 1.2;
	Config.n = 10;
	Config.Act_style = new CString[Config.Layer_num];
	for(int i=0;i<Config.Layer_num;i++)
	{
		Config.Act_style[i] = "tanh";
	}
	Config.Loss.InitMatrix(1,Config.n);
	Config.node_num = new int[Config.Layer_num];
	Config.node_num[0] = 4;
	Config.node_num[1] = 1;

	CMatrixCal X(2,2);
	X.data[0][0] = -0.41675785;
	X.data[1][0] =-2.1361961;
	X.data[0][1] = -0.05626683;
	X.data[1][1] =1.64027081;
	CMatrixCal Y(1,2);
	Y.data[0][0] = 0;
	Y.data[0][1] = 1;

	X.MultiBy(1);

	Parameters_NN* Para = ParaTrain_of_NN(Config,X,Y);
	Config.Loss.ShowData();
	Para[0].W.ShowData();
	Para[0].b.ShowData();
	Para[1].W.ShowData();
	Para[1].b.ShowData();

}
void CNeuralNetWorks::NN_Test4()
{
	Parameters_NN* Para = new Parameters_NN[2];
	Para[0].W.InitMatrix(4,2);
	Para[0].b.InitMatrix(4,1);
	Para[1].W.InitMatrix(1,4);
	Para[1].b.InitMatrix(1,1);

	Para[0].W.data[0][0] = -0.00416758;
	Para[0].W.data[0][1] = -0.00056267;

	Para[0].W.data[1][0] = -0.02163196;
	Para[0].W.data[1][1] = 0.01640271;

	Para[0].W.data[2][0] = -0.01793436;
	Para[0].W.data[2][1] = -0.00841747;

	Para[0].W.data[3][0] = 0.00502881;
	Para[0].W.data[3][1] = -0.01245288;


	Para[1].W.data[0][0] = -0.01057952;
	Para[1].W.data[0][1] = -0.00909008;
	Para[1].W.data[0][2] = 0.00551454;
	Para[1].W.data[0][3] = 0.02292208;

	CMatrixCal X(2,12);
	CMatrixCal Y(1,12);
	X.data[0][0] = 73;
	X.data[0][1] = 68;
	X.data[0][2] = 67;
	X.data[0][3] = 64;
	X.data[0][4] = 62;
	X.data[0][5] = 60;
	
	X.data[0][6] = 56;
	X.data[0][7] = 55;
	X.data[0][8] = 47;
	X.data[0][9] = 46;
	X.data[0][10] = 36;
	X.data[0][11] = 32;
	
	X.data[1][0] = 26;
	X.data[1][1] = 38;
	X.data[1][2] = 19;
	X.data[1][3] = 26;
	X.data[1][4] = 48;
	X.data[1][5] = 38;
	
	X.data[1][6] = 56;
	X.data[1][7] = 47;
	X.data[1][8] = 57;
	X.data[1][9] = 47;
	X.data[1][10] =47;
	X.data[1][11] = 57;
	
	Y.data[0][0] = 1;
	Y.data[0][1] = 1;
	Y.data[0][2] = 0;
	Y.data[0][3] = 0;
	Y.data[0][4] = 1;
	Y.data[0][5] = 0;
	Y.data[0][6] = 1;
	Y.data[0][7] = 0;
	Y.data[0][8] = 1;
	Y.data[0][9] = 0;
	Y.data[0][10] = 0;
	Y.data[0][11] = 1;

	CMatrixCal Z1 = HiddenLayerCal(Para[0].W,X,Para[0].b);
	Z1.ChangeName("Z1");
	Z1.ShowData();
	CMatrixCal A1 = ActivationFunction(Z1,"tanh");
	A1.ChangeName("A1");
	A1.ShowData();
	CMatrixCal Z2 = HiddenLayerCal(Para[1].W,A1,Para[1].b);
	Z2.ChangeName("Z2");
	Z2.ShowData();
	CMatrixCal A2 = ActivationFunction(Z2,"sigmoid");
	A2.ChangeName("A2");
	A2.ShowData();
	CMatrixCal dZ2 = dZ_of_OutputLayer(A2,Y);
	dZ2.ChangeName("dZ2");
	dZ2.ShowData();
	CMatrixCal dW2 = dW_of_OutputLayer(A1,dZ2);
	dW2.ChangeName("dW2");
	dW2.ShowData();
	CMatrixCal db2 = db_of_OutputLayer(dZ2);
	db2.ChangeName("db2");
	db2.ShowData();
	CMatrixCal dZ1 = dZ_of_HiddenLayer(Para[1].W,dZ2,A1,"tanh");
	dZ1.ChangeName("dZ1");
	dZ1.ShowData();
	CMatrixCal dW1 = dW_of_HiddenLayer(X,dZ1);
	dW1.ChangeName("dW1");
	dW1.ShowData();
	CMatrixCal db1 = db_of_OutputLayer(dZ1);
	db1.ChangeName("db1");
	db1.ShowData();
	
	
}
void CNeuralNetWorks::NN_Test()
{
	CDataSet m_data;
	CMatrixCal XY = m_data.LoadLRTestData();
	CMatrixCal X = m_data.ExtractX(XY);
	CMatrixCal Y = m_data.ExtractY(XY);
	X.ChangeName("X");
	Y.ChangeName("Y");
	XY.ChangeName("XY");
	//XY.ShowData();
	

	X.MultiBy(1.0/100);
	X.PlusBy(-0.5);
	
	//X.ShowRowData(1);
	//X.ShowRowData(2);
	//Y.ShowData();



	NetConfig_NN Config;
	Config.IS_INIT = TRUE;
	Config.Layer_num = 2;
	Config.a = 1.2;
	Config.n = 5000;
	int loss_num = (Config.n - (Config.n%100))/100;
	Config.Act_style = new CString[Config.Layer_num];
	for(int i=0;i<Config.Layer_num;i++)
	{
		Config.Act_style[i] = "ReLU";
	}
	Config.Loss.InitMatrix(1,loss_num);
	Config.Loss.ChangeName("损失矩阵");
	Config.node_num = new int[Config.Layer_num];
	Config.node_num[0] = 16;
	Config.node_num[1] = 1;
	//Config.node_num[2] = 1;
	//Config.node_num[3] = 1;
	//Config.node_num[4] = 1;
	//Config.node_num[5] = 1;

	Parameters_NN* Para = ParaTrain_of_NN(Config,X,Y);
	Config.Loss.ShowData();

	CMatrixCal X_test(2,m_data.height_image*m_data.width_image);
	
	
	for(int m=0;m<m_data.height_image;m++)
	{
		for(int n=0;n<m_data.width_image;n++)
		{
			X_test.data[0][m*m_data.width_image+n] = m;
			X_test.data[1][m*m_data.width_image+n] = n;
		}
	}

	X_test.MultiBy(1.0/100);
	X_test.PlusBy(-0.5);
	Para[0].Z = HiddenLayerCal(Para[0].W, X_test, Para[0].b);
	Para[0].A = ActivationFunction(Para[0].Z,Config.Act_style[0]);
	//层循环
	//正向传播
	for(int l=1;l<Config.Layer_num-1;l++)
	{
		Para[l].Z = HiddenLayerCal(Para[l].W, Para[l-1].A, Para[l].b);
		Para[l].A = ActivationFunction(Para[l].Z,Config.Act_style[l]);
	}
	Para[Config.Layer_num-1].Z = HiddenLayerCal(Para[Config.Layer_num-1].W, Para[Config.Layer_num-2].A, Para[Config.Layer_num-1].b);
	CMatrixCal Y_test =  ActivationFunction(Para[Config.Layer_num-1].Z,"sigmoid");









	X_test.PlusBy(0.5);
	X_test.MultiBy(100);
	CMatrixCal XY_test = m_data.MergeXY(X_test,Y_test);
	m_data.PostProcess_RB(XY_test);


	XY.Release();
	X.Release();
	Y.Release();
	XY_test.Release();
	Y_test.Release();
	X_test.Release();
	for(int i=0;i>Config.Layer_num;i++)
	{
		ReleasePara_NN(Para[i]);
	}
	ReleaseNetConfig_NN(Config);
}