#ifndef NUMBER_H
#define NUMBER_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip> 
#include <algorithm>


const int priority[] = { 0,1,2,3,4,5,6 };
//�u������ �A��6(����J�ϬA���~��X) > �t��5 > �곡(i)4 > ����3 > ����2 > ���B��1 > �[�B��0
//�ϥΰj��A���X���Ǧ����r���A�J�B�⤸������X�F���|�B��l�P���A��
//���|���B��l�u�����ǭY�j�󵥩�Ū�J���B��l�u�����Ǫ��ܡA������X���|�����B��l�A�A�NŪ�J���B��l�m�J���|�F
//�J�k�A����X���|�����B��l�ܥ��A���C

struct ImagPart
{
	ImagPart& operator=(const ImagPart&r)	
	{
		this->sign = r.sign;
		this->numerator = r.numerator;
		this->denominator = r.denominator;
		return *this;
	}
	bool sign = false; //�w�]������
	std::string numerator = "0";	//�곡���l
	std::string denominator = "0";	//�곡����
};

struct Fraction
{
	Fraction& operator=(const Fraction& r)	
	{
		this->isInt = r.isInt;
		this->sign = r.sign;
		this->numerator = r.numerator;
		this->denominator = r.denominator;
		this->comSign = r.comSign;
		this->imag = r.imag;
		return *this;
	}
	Fraction() 
	{
		numerator = "0";
		denominator = "0";
	}
	bool sign = false; //�w�]������
	bool isInt = false;
	std::string numerator = "0";	//���l
	std::string denominator = "0"; //����

	bool comSign = false; // �w�]�����O�Ƽ�
	ImagPart imag;//�곡
};

class Number
{
public:
	Number();
	Number(std::string);
	~Number();

	static std::vector<std::string> var;
	static std::vector<std::string> varAns;
	std::string name;//�s�ܼƦW��
	int errorTyep = -1;//���~�s��
	void setInput(const std::string&);//��J�ƾǦ�	
	void computInput();//�B��					
	std::string printAns();//��X����(�t���b)	
	std::string getInt();	
	std::string getDec();	
	std::string getCom();	
	Fraction getFrac();	
	Fraction getReal();	
	bool getComSign();	
	void setFrac(Fraction&);



	virtual void assign();				
	virtual void print(std::ostream&)const;	

	friend std::ostream& operator<<(std::ostream& outputStream, const Number&); //��X	
	friend std::istream& operator>> (std::istream& inputStream, Number&); //��J			


	//�Ƽơ�
	Fraction toImag(Fraction);//������곡				
	void imagToReal(Fraction, Fraction&);//�곡��곡	
	void realToImag(Fraction&, Fraction);//�곡��곡	
	Fraction comAdd(Fraction, Fraction);//�Ƽƥ[�k		
	Fraction comSub(Fraction, Fraction);//�Ƽƴ�k		
	Fraction comMul(Fraction, Fraction);//�Ƽƭ��k		
	Fraction comDiv(Fraction, Fraction);//�Ƽư��k		
	Fraction comPow(Fraction, Fraction);//�ƼƦ���		

	//�ڸ���
	Fraction comRoot(Fraction, bool);//�Ƽƶ}�ڸ�(���y�Ф�k)	
	Fraction fracRoot(Fraction, bool);//���ƶ}�ڸ�				

	//���ơ�
	Fraction posToStack(std::string);//���or�p�������		
	Fraction fracPow(Fraction, Fraction);//���Ʀ���		
	Fraction fracFac(Fraction);//����					
	Fraction fracAdd(Fraction, Fraction);//���ƥ[�k		
	Fraction fracSub(Fraction, Fraction);//���ƴ�k		
	Fraction fracMul(Fraction, Fraction);//���ƭ��k		
	Fraction fracDiv(Fraction, Fraction);//���ư��k		
	std::string gcd(std::string, std::string);//���̤j���]��	
	Fraction about(Fraction);//����						
	void changeSign(Fraction&);							
	bool sign(std::string&);//���t���P�_						

	//��ơ�
	std::string getRoot120(std::string);//���o�@��ƶ}�ڸ��ܤp���I��150��		
	std::string printRoot(std::string);//�}�ڸ���X�p���I��100��				
	std::string mod(std::string, std::string);//�j�ƨ��l��		
	std::string pow(std::string, std::string);//�j�Ʀ���		
	std::string fac(std::string);//�j�ƶ���				
	int multiply(int x, std::vector<int> &ans, int res_size);	
	std::string add(std::string, std::string);//�j�ƥ[�k	
	std::string sub(std::string, std::string);//�j�ƴ�k	
	std::string mul(std::string, std::string);//�j�ƭ��k	
	std::string div(std::string, std::string);//�j�ư��k	
	int cmp(std::string, std::string);//�j�Ƥ��		
	std::string get110Dec(Fraction);				
	std::string get100Dec(Fraction);				
	std::string get10Dec(Fraction);				
protected:
	Fraction fracAns;
	std::string input;
	//�s��J�r��(�L�Ů� '#'�N��t��)
};
#include "BISA.h"
#include "Integer.h"
#include "Decimal.h"
#include "Complex.h"
#endif // !NUMBER_H
