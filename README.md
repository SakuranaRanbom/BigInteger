# C++中实现BigInteger
实现了高精度整数的加法，与普通整数的乘法、整除、模运算等。也包含了高精度整数的进制转换功能。
BigInteger类的定义与函数声明
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
