//****************finished**********************//
#ifndef BISA_H
#define BISA_H
//大數加、減法實作
#include <iostream>
#include <string>
#include <vector>

struct N
{
	std::string bigNum;
	bool sign;
};

class BigIntAddSub
{
public:
	BigIntAddSub();
	BigIntAddSub(std::string);
	std::string bigIntAdd(N, N);	//相加
	std::string bigIntSub(N, N);	//相減
	N getNumber();	//return num

private:
	N num;
};

#endif // !BISA_H