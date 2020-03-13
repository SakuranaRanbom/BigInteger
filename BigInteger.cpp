#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
class BigInteger{
	
	int cut=10000;       //每四位为一个单位保存 
	int digit[100]={0};  //从低位开始存储;如1234567890，数组中的内容依次为 digit[0]:7890 digit[1]:3456 digit[2]:12 
	int size=0;          //digit数组未利用的第一个元素的下标
	
	public:
	void tran(string s,int jz=10);   //jz进制字符串转换为高精度整数,默认为十进制 
	void output(int jz=10);          //以jz进制输出，默认为十进制 	
	BigInteger operator= (int x);    //普通整数初始转换高精度整数格式
	BigInteger operator+ (const BigInteger &b);  //高精度整数加法运算
	BigInteger operator* (int x);    //小整数乘高精度整数
	BigInteger operator/ (int x);    //高精度整数整除小整数
	int operator% (int x);           //高精度整数模小整数
};

int main()
{	
	//数字s以init进制输入，以aim进制输出 
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

//类函数实现
 
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
	for(int i=0;i<end;i++)	//从低位开始累加 
	{
		tmp=digit[i]+b.digit[i]+up;//当前位数字加上进位 
		res.digit[i]=tmp%cut; //存储数字为模存储单位长度之后的值 
		up=tmp/cut;   //计算进位 
	}
	res.size=end;
	if(up) res.digit[res.size++]=up; //若有进位,应扩大一位 
	return res; 
}

BigInteger BigInteger::operator* (int x)
{
	BigInteger res;
	int tmp,up=0;
	for(int i=0;i<size;i++)  //从最低位开始计算 
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
	for(int i=size-1;i>=0;i--)  //从最高位开始计算 
	{
		tmp=remainder*cut+digit[i]; //该位数字加上一位的余数remainder 
		res.digit[i]=tmp/x;
		remainder=tmp%x;
	}
	res.size=size;
	while(res.digit[res.size]==0) res.size--; //从最高位开始找到第一个元素不为0的位置 
	res.size++;
	return res;
}

int BigInteger::operator% (int x)
{
	int tmp,remainder=0;
	for(int i=size-1;i>=0;i--) //同整除类似，从最高位开始计算，保留余数即可 
	{
		tmp=remainder*cut+digit[i];
		remainder=tmp%x;
	}
	return remainder;
}

void BigInteger::tran(string s,int jz)
{
	if(jz==10)//若为十进制整数，可直接每四位截取一次 
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
		tmp=tmp+mul*num;	   //将该位数字与倍数相乘,累加到tmp中 
		mul=mul*jz;		       //计算下一数字位的倍数,按1,jz,jz^2,jz^3变化 
	}
	*this=tmp;
}

void BigInteger::output(int jz)
{
	if(size==0) printf("0");
	if(jz==10)//十进制可直接输出 
	{		
		printf("%d",digit[size-1]);
		for(int i=size-2;i>=0;i--) printf("%04d",digit[i]);
		return; 
	}
	
	string res="";
	BigInteger tmp;
	tmp=*this;
	int num;
	while(tmp.size!=0)//进制转换算法 
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
