//************finished*************//
#ifndef INTEGER_H
#define INTEGER_H
#include "Number.h"
class DEcimal;
class Complex;
class Integer : public Number 		
{
public:
	Integer();
	Integer(std::string);
	~Integer();

	std::string getAns()const;
	Fraction getFrac()const;
	std::string getInput()const;
	virtual void assign();
	virtual void print(std::ostream&)const;

	Integer& operator=(Integer&);
	Integer& operator=(DEcimal&);
	Integer& operator=(Complex&);	
	Integer& operator=(std::string&);

	friend Integer operator+(Integer&, Integer&);
	friend Integer operator-(Integer&, Integer&);
	friend Integer operator*(Integer&, Integer&);
	friend Integer operator/(Integer&, Integer&);
	//power 都是用複數表示
	friend Complex Power(Integer& left, Integer& right);
	friend Complex Power(Integer& left, DEcimal& right);
	friend Complex Power(Integer& left, Complex& right);
	friend Complex Power(Integer& left, std::string& right);
	friend Integer Factorial(Integer& a);	//階乘
	friend Integer Factorial(std::string& a);	//複數階乘
	
private:
	std::string ans;
};
#endif // !INTEGER_H