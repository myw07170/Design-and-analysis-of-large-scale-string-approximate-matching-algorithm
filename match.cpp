#include <iostream>
#include <fstream>
#include<string>
using namespace std;

ifstream myFileP ("test_cin_P.txt");
ifstream myFileT ("test_cin_T.txt");
ofstream outFile ("test_cout.txt");

//求3个数中的最大值 
int min(int a,int b,int c)
{
	if(a<=b&&a<=c) return a;
	if(b<=c) return b;
	return c;
}

//用动态规划求解待测字符串T与样本字符串P的精确编辑距离 
int edit_distance(string T,string P)
{
	//创建二维表dp[i][j]，记录样本字符串P和待测串T的编辑距离 
	int i,j,dp[99][99];
	int tl=T.size(),pl=P.size();
	
	//初始化：边界dp[i][0]=i，dp[0][j]=j 
	for(i=1;i<=tl;i++) 
		dp[i][0]=i;
	for(j=1;j<=pl;j++) 
		dp[0][j]=j;
	dp[0][0]=0;
	
	//填表 
	for(i=1;i<=tl;i++)
	{
		for(j=1;j<=pl;j++)
		{
			if(T[i-1]==P[j-1]) 
				dp[i][j]=dp[i-1][j-1];
			else 
				dp[i][j]=1+min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1]);
		}
	}
	return dp[tl][pl];
}

//重复动态规划过程，还原并输出待测串T编辑成样本串P的操作过程 
void get_op(string T,string P)
{
	//创建二维表dp[i][j]，记录样本字符串P和待测串T的编辑距离 
	int i,j,dp[99][99];
	int tl=T.size(),pl=P.size();
	//初始化：边界dp[i][0]=i，dp[0][j]=j 
	for(i=1;i<=tl;i++) 
		dp[i][0]=i;
	for(j=1;j<=pl;j++) 
		dp[0][j]=j;
	dp[0][0]=0;
	
	//填表 
	for(i=1;i<=tl;i++)
	{
		for(j=1;j<=pl;j++)
		{
			if(T[i-1]==P[j-1]) 
				dp[i][j]=dp[i-1][j-1];
			else 
				dp[i][j]=1+min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1]);
		}
	}
//以上为重复动态规划的内容，以下为借助二维表dp还原编辑操作过程 
	i=tl;j=pl;
	while(dp[i][j]>0)
	{
		//该位匹配，T[i-1]不用进行编辑操作
		if(T[i-1]==P[j-1]) {i--;j--;}
		
		//该位不匹配，T[i-1]需要进行编辑操作
		else
		{
			if(dp[i][j]-1==dp[i-1][j-1])
			{
				outFile<<"修改操作：将原串T的第"<<i<<"位"
				<<T[i-1]<<"修改为"<<P[j-1]<<endl;
				i--;j--;
			}
			else if(dp[i][j]-1==dp[i-1][j])
			{
				outFile<<"删除操作：删除原串T的第"<<i<<"位"
	   			<<T[i-1]<<endl;
	   			i--;
			}
			else
			{
				outFile<<"插入操作：在原串T的第"<<i<<"位"
				<<T[i-1]<<"前新增一位"<<P[j-1]<<endl;
				j--;
			}
		}
	}
	return ;
}

//用近似算法求解待测字符串T与样本字符串P的近似编辑距离
int sim_edit_distance(string T,string P)
{
	int tl=T.size(),pl=P.size();
	int i=0,j=0,k=0;
	//i记录T下标，j记录P下标；k记录编辑操作数 
	while(i<tl&&j<pl)
	{
		//对应位相同，无需进行编辑操作 
		if(T[i]==P[j]) {i++;j++;}
		//对应位不同，需要进行编辑操作
		else
		{
			k++;  //编辑操作计数君k加1 
			//插入操作 
			if(j+1<pl&&T[i]==P[j+1]) {i++;j+=2;}
			//删除操作 
			else if(i+1<tl&&T[i+1]==P[j]) {i+=2;j++;}
			//修改操作 
			else {i++;j++;}
		}
	}
	if(i==tl&&j<pl)      k+=pl-j;  //插入剩下所有缺少的 
	else if(i<tl&&j==pl) k+=tl-i;  //删除剩下所有多余的 
	return k;
}

//重复近似算法过程，在需要编辑操作的每一步进行相应输出 
void sim_get_op(string T,string P)
{
	int tl=T.size(),pl=P.size();
	int i=0,j=0;  //i记录T中下标，j记录P中下标
	while(i<tl&&j<pl)
	{
		//对应位相同，无需进行编辑操作
		if(T[i]==P[j]) {i++;j++;}
		//对应位不同，需要进行编辑操作
		else
		{
			if(j+1<pl&&T[i]==P[j+1]) 
			{
				outFile<<"插入操作：在原串T的第"<<i+1<<"位"
				<<T[i]<<"前新增一位"<<P[j++]<<endl;
			}
			else if(i+1<tl&&T[i+1]==P[j]) 
			{
				outFile<<"删除操作：删除原串T的第"<<i+1<<"位"
				<<T[i++]<<endl;
			}
			else 
			{
				outFile<<"修改操作：将原串T的第"<<i+1<<"位"
				<<T[i]<<"修改为"<<P[j]<<endl; 
			}
			i++;j++;
		}
	}
	if(i==tl&&j<pl)      //插入剩下所有缺少的
	{
		outFile<<"插入操作：在字符串T末尾新增字符";
		while(j<pl) outFile<<P[j];
	}
	else if(i<tl&&j==pl) //删除剩下所有多余的 
	{
		outFile<<"删除操作：删除字符串T末尾的字符";
		while(i<tl) outFile<<T[i];
	} 
	return ;
}


int main() 
{
	string p,t,r;
	//p,t分别存放每次输入的文本(样本串&待测串)
	//r存放当前已输入的编辑距离最小的文本串 
	int temp,k=9999999;  
	//temp存放每次输入的文本对应的编辑距离
	//k存放当前已输入的最小编辑距离，初始化为9999999
	if(myFileP.is_open()) 
	{
		while(myFileP>>p)
		{
			k=9999999;
			ifstream myFileT ("test_cin_T.txt");
			if(myFileT.is_open())
			{
				while(myFileT>>t)
				{
					temp=edit_distance(t,p);  //调用求解编辑距离的函数 
					if(temp<k) {k=temp;r=t;}
				}
				outFile<<"样本串P（"<<p<<"）"<<"与待测文本T的最佳近似匹配为："
				<<r<<endl<<"其编辑距离K为："<<k<<endl;
				if(k!=0)
				{
					outFile<<"具体编辑操作为："<<endl;
					get_op(r,p); //调用输出编辑操作过程的函数 
				}
			}
			outFile<<endl;
			myFileT.close();
		}
	}
	myFileP.close();
	myFileT.close();
	outFile.close();
	return 0;
}
