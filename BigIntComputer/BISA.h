//****************finished**********************//
#ifndef BISA_H
#define BISA_H
//�j�ƥ[�B��k��@
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
	std::string bigIntAdd(N, N);	//�ۥ[
	std::string bigIntSub(N, N);	//�۴�
	N getNumber();	//return num

private:
	N num;
};

#endif // !BISA_H