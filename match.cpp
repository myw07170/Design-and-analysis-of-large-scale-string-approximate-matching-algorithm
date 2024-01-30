#include <iostream>
#include <fstream>
#include<string>
using namespace std;

ifstream myFileP ("test_cin_P.txt");
ifstream myFileT ("test_cin_T.txt");
ofstream outFile ("test_cout.txt");

//��3�����е����ֵ 
int min(int a,int b,int c)
{
	if(a<=b&&a<=c) return a;
	if(b<=c) return b;
	return c;
}

//�ö�̬�滮�������ַ���T�������ַ���P�ľ�ȷ�༭���� 
int edit_distance(string T,string P)
{
	//������ά��dp[i][j]����¼�����ַ���P�ʹ��⴮T�ı༭���� 
	int i,j,dp[99][99];
	int tl=T.size(),pl=P.size();
	
	//��ʼ�����߽�dp[i][0]=i��dp[0][j]=j 
	for(i=1;i<=tl;i++) 
		dp[i][0]=i;
	for(j=1;j<=pl;j++) 
		dp[0][j]=j;
	dp[0][0]=0;
	
	//��� 
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

//�ظ���̬�滮���̣���ԭ��������⴮T�༭��������P�Ĳ������� 
void get_op(string T,string P)
{
	//������ά��dp[i][j]����¼�����ַ���P�ʹ��⴮T�ı༭���� 
	int i,j,dp[99][99];
	int tl=T.size(),pl=P.size();
	//��ʼ�����߽�dp[i][0]=i��dp[0][j]=j 
	for(i=1;i<=tl;i++) 
		dp[i][0]=i;
	for(j=1;j<=pl;j++) 
		dp[0][j]=j;
	dp[0][0]=0;
	
	//��� 
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
//����Ϊ�ظ���̬�滮�����ݣ�����Ϊ������ά��dp��ԭ�༭�������� 
	i=tl;j=pl;
	while(dp[i][j]>0)
	{
		//��λƥ�䣬T[i-1]���ý��б༭����
		if(T[i-1]==P[j-1]) {i--;j--;}
		
		//��λ��ƥ�䣬T[i-1]��Ҫ���б༭����
		else
		{
			if(dp[i][j]-1==dp[i-1][j-1])
			{
				outFile<<"�޸Ĳ�������ԭ��T�ĵ�"<<i<<"λ"
				<<T[i-1]<<"�޸�Ϊ"<<P[j-1]<<endl;
				i--;j--;
			}
			else if(dp[i][j]-1==dp[i-1][j])
			{
				outFile<<"ɾ��������ɾ��ԭ��T�ĵ�"<<i<<"λ"
	   			<<T[i-1]<<endl;
	   			i--;
			}
			else
			{
				outFile<<"�����������ԭ��T�ĵ�"<<i<<"λ"
				<<T[i-1]<<"ǰ����һλ"<<P[j-1]<<endl;
				j--;
			}
		}
	}
	return ;
}

//�ý����㷨�������ַ���T�������ַ���P�Ľ��Ʊ༭����
int sim_edit_distance(string T,string P)
{
	int tl=T.size(),pl=P.size();
	int i=0,j=0,k=0;
	//i��¼T�±꣬j��¼P�±ꣻk��¼�༭������ 
	while(i<tl&&j<pl)
	{
		//��Ӧλ��ͬ��������б༭���� 
		if(T[i]==P[j]) {i++;j++;}
		//��Ӧλ��ͬ����Ҫ���б༭����
		else
		{
			k++;  //�༭����������k��1 
			//������� 
			if(j+1<pl&&T[i]==P[j+1]) {i++;j+=2;}
			//ɾ������ 
			else if(i+1<tl&&T[i+1]==P[j]) {i+=2;j++;}
			//�޸Ĳ��� 
			else {i++;j++;}
		}
	}
	if(i==tl&&j<pl)      k+=pl-j;  //����ʣ������ȱ�ٵ� 
	else if(i<tl&&j==pl) k+=tl-i;  //ɾ��ʣ�����ж���� 
	return k;
}

//�ظ������㷨���̣�����Ҫ�༭������ÿһ��������Ӧ��� 
void sim_get_op(string T,string P)
{
	int tl=T.size(),pl=P.size();
	int i=0,j=0;  //i��¼T���±꣬j��¼P���±�
	while(i<tl&&j<pl)
	{
		//��Ӧλ��ͬ��������б༭����
		if(T[i]==P[j]) {i++;j++;}
		//��Ӧλ��ͬ����Ҫ���б༭����
		else
		{
			if(j+1<pl&&T[i]==P[j+1]) 
			{
				outFile<<"�����������ԭ��T�ĵ�"<<i+1<<"λ"
				<<T[i]<<"ǰ����һλ"<<P[j++]<<endl;
			}
			else if(i+1<tl&&T[i+1]==P[j]) 
			{
				outFile<<"ɾ��������ɾ��ԭ��T�ĵ�"<<i+1<<"λ"
				<<T[i++]<<endl;
			}
			else 
			{
				outFile<<"�޸Ĳ�������ԭ��T�ĵ�"<<i+1<<"λ"
				<<T[i]<<"�޸�Ϊ"<<P[j]<<endl; 
			}
			i++;j++;
		}
	}
	if(i==tl&&j<pl)      //����ʣ������ȱ�ٵ�
	{
		outFile<<"������������ַ���Tĩβ�����ַ�";
		while(j<pl) outFile<<P[j];
	}
	else if(i<tl&&j==pl) //ɾ��ʣ�����ж���� 
	{
		outFile<<"ɾ��������ɾ���ַ���Tĩβ���ַ�";
		while(i<tl) outFile<<T[i];
	} 
	return ;
}


int main() 
{
	string p,t,r;
	//p,t�ֱ���ÿ��������ı�(������&���⴮)
	//r��ŵ�ǰ������ı༭������С���ı��� 
	int temp,k=9999999;  
	//temp���ÿ��������ı���Ӧ�ı༭����
	//k��ŵ�ǰ���������С�༭���룬��ʼ��Ϊ9999999
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
					temp=edit_distance(t,p);  //�������༭����ĺ��� 
					if(temp<k) {k=temp;r=t;}
				}
				outFile<<"������P��"<<p<<"��"<<"������ı�T����ѽ���ƥ��Ϊ��"
				<<r<<endl<<"��༭����KΪ��"<<k<<endl;
				if(k!=0)
				{
					outFile<<"����༭����Ϊ��"<<endl;
					get_op(r,p); //��������༭�������̵ĺ��� 
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
