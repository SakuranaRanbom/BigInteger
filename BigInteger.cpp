#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
class BigInteger{
	
	int cut=10000;       //ÿ��λΪһ����λ���� 
	int digit[100]={0};  //�ӵ�λ��ʼ�洢;��1234567890�������е���������Ϊ digit[0]:7890 digit[1]:3456 digit[2]:12 
	int size=0;          //digit����δ���õĵ�һ��Ԫ�ص��±�
	
	public:
	void tran(string s,int jz=10);   //jz�����ַ���ת��Ϊ�߾�������,Ĭ��Ϊʮ���� 
	void output(int jz=10);          //��jz���������Ĭ��Ϊʮ���� 	
	BigInteger operator= (int x);    //��ͨ������ʼת���߾���������ʽ
	BigInteger operator+ (const BigInteger &b);  //�߾��������ӷ�����
	BigInteger operator* (int x);    //С�����˸߾�������
	BigInteger operator/ (int x);    //�߾�����������С����
	int operator% (int x);           //�߾�������ģС����
};

int main()
{	
	//����s��init�������룬��aim������� 
	string s;
	int init,aim;
	BigInteger c;
	while(cin>>init>>aim>>s)
	{
		c.tran(s,init);
		c.output(aim);	
		cout<<endl;	
	}
	
	return 0;
}

//�ຯ��ʵ��
 
BigInteger BigInteger::operator= (int x)
{
	size=0;
	while(x)
	{
		digit[size++]=x%cut;
		x=x/cut;
	} 
	return *this;
} 

BigInteger BigInteger::operator +(const BigInteger &b)
{
	BigInteger res;
	int end=max(size,b.size),tmp,up=0;
	for(int i=0;i<end;i++)	//�ӵ�λ��ʼ�ۼ� 
	{
		tmp=digit[i]+b.digit[i]+up;//��ǰλ���ּ��Ͻ�λ 
		res.digit[i]=tmp%cut; //�洢����Ϊģ�洢��λ����֮���ֵ 
		up=tmp/cut;   //�����λ 
	}
	res.size=end;
	if(up) res.digit[res.size++]=up; //���н�λ,Ӧ����һλ 
	return res; 
}

BigInteger BigInteger::operator* (int x)
{
	BigInteger res;
	int tmp,up=0;
	for(int i=0;i<size;i++)  //�����λ��ʼ���� 
	{
		tmp=digit[i]*x+up;
		res.digit[i]=tmp%cut;
		up=tmp/cut;
	} 
	res.size=size;
	if(up) res.digit[res.size++]=up;
	return res;
} 


BigInteger BigInteger::operator/ (int x)
{
	BigInteger res;
	int tmp,remainder=0;
	for(int i=size-1;i>=0;i--)  //�����λ��ʼ���� 
	{
		tmp=remainder*cut+digit[i]; //��λ���ּ���һλ������remainder 
		res.digit[i]=tmp/x;
		remainder=tmp%x;
	}
	res.size=size;
	while(res.digit[res.size]==0) res.size--; //�����λ��ʼ�ҵ���һ��Ԫ�ز�Ϊ0��λ�� 
	res.size++;
	return res;
}

int BigInteger::operator% (int x)
{
	int tmp,remainder=0;
	for(int i=size-1;i>=0;i--) //ͬ�������ƣ������λ��ʼ���㣬������������ 
	{
		tmp=remainder*cut+digit[i];
		remainder=tmp%x;
	}
	return remainder;
}

void BigInteger::tran(string s,int jz)
{
	if(jz==10)//��Ϊʮ������������ֱ��ÿ��λ��ȡһ�� 
	{
		size=0;
		int pos=s.size();
		while(pos-4>=0)	digit[size++]=atoi(s.substr(pos-4,4).c_str());
		if(pos>0) digit[size++]=atoi(s.substr(0,pos).c_str());
		return;
	}
	
	
	BigInteger mul,tmp;
	mul=1;tmp=0;
	int num;
	for(int i=s.size()-1;i>=0;i--)
	{
		if(s[i]>='0'&&s[i]<='9')
			num=s[i]-'0';
		else 
			num=s[i]-'A'+10;
		tmp=tmp+mul*num;	   //����λ�����뱶�����,�ۼӵ�tmp�� 
		mul=mul*jz;		       //������һ����λ�ı���,��1,jz,jz^2,jz^3�仯 
	}
	*this=tmp;
}

void BigInteger::output(int jz)
{
	if(size==0) printf("0");
	if(jz==10)//ʮ���ƿ�ֱ����� 
	{		
		printf("%d",digit[size-1]);
		for(int i=size-2;i>=0;i--) printf("%04d",digit[i]);
		return; 
	}
	
	string res="";
	BigInteger tmp;
	tmp=*this;
	int num;
	while(tmp.size!=0)//����ת���㷨 
	{
		num=tmp%jz;
		if(num>=10) res+=num-10+'A';
		else res+=num+'0';
		tmp=tmp/jz;
	}
	for(int i=res.size()-1;i>=0;i--)
	{
		printf("%c",res[i]); 
	}
}   
