//******************finished******************//
#include "BISA.h"
using namespace std;
//箇砞0
BigIntAddSub::BigIntAddSub()
{
	num.bigNum = "0";
	num.sign = false;
}
//砞﹚计
BigIntAddSub::BigIntAddSub(string a)
{
	if (a[0] == '-')	//璽计
	{
		num.sign = true;//-			sign==true琌璽计
		a.erase(a.begin());	//р璽腹奔
	}
	else
	{
		num.sign = false;//+
	}
	num.bigNum = a;
}
//return 计
N BigIntAddSub::getNumber()
{
	return num;
}
//计猭(A+B)
string BigIntAddSub::bigIntAdd(N A, N B)
{
	N ans, temp;
	int size1 = A.bigNum.size(), size2 = B.bigNum.size();
	if (A.sign && !B.sign)	//A璽      Bタ
	{
		A.sign = false;//-A△+A
		ans.bigNum = bigIntSub(B, A);	//р衡ΑэΘ B-A
		return ans.bigNum;
	}
	else if (!A.sign && B.sign)	//Aタ    B璽
	{
		B.sign = false;//-B△+B
		ans.bigNum = bigIntSub(A, B);	//р衡ΑэΘA-B
		return ans.bigNum;
	}
	else  //ㄢ常タ ┪ ㄢ常璽
	{
		//计耕ans  耕ぶtemp
		if (size1 >= size2)	//A计ゑB
		{
			ans = A;
			temp = B;
		}
		else  //B计ゑA
		{
			ans = B;
			temp = A;
		}
	}
	//size1эΘans  size2эΘtemp
	size1 = ans.bigNum.size();
	size2 = temp.bigNum.size();
	int i = size1 - 1, j = size2 - 1;	// i j だ琌ans temp程

	for (i; i >= 0; i--, j--)
	{
		if (j >= 0)	//计挡
		{
			ans.bigNum[i] += temp.bigNum[j] - '0';
		}
		//秈
		if (ans.bigNum[i] > '9')
		{
			ans.bigNum[i] -= 10;
			if (i > 0)
				ans.bigNum[i - 1] += 1;
			else if (i == 0)
				ans.bigNum.insert(ans.bigNum.begin(), '1');
		}
	}
	if (ans.sign)	//璽
	{
		return "-" + ans.bigNum;
	}
	else  //タ
	{
		return ans.bigNum;
	}
		
}

string BigIntAddSub::bigIntSub(N A, N B)
{
	N ans, temp;
	int token = 0;//魁计眖繷衡癬材ぃ计
	int size1 = A.bigNum.size(), size2 = B.bigNum.size();
	if (A.sign && !B.sign)//-A - B = -A + -B
	{
		B.sign = true;
		ans.bigNum = bigIntAdd(A, B);
		return ans.bigNum;
	}
	else if (!A.sign&&B.sign)//A - -B = A + B
	{
		B.sign = false;
		ans.bigNum = bigIntAdd(A, B);
		return ans.bigNum;
	}
	else if (A.sign&&B.sign)//-A - -B= -A + B = B-A
	{
		A.sign = B.sign = false;
		ans.bigNum = bigIntSub(B, A);
		return ans.bigNum;
	}
	else if (!A.sign && !B.sign)//A - B
	{
		if (size1 > size2)	//搭
		{
			ans = A;
			temp = B;
		}
		else if (size1 < size2)	//搭
		{
			ans = B;
			ans.sign = true;
			temp = A;
			size1 = ans.bigNum.size();
			size2 = temp.bigNum.size();
		}
		else if (size1 == size2) //计
		{
			for (int i = 0; i < size1; i++)
			{
				//ゑ耕材计  ゑ耕琌ans  琌temp
				if (A.bigNum[i] > B.bigNum[i])
				{
					ans = A;
					temp = B;
					break;
				}
				else if (A.bigNum[i] < B.bigNum[i])
				{
					ans = B;
					temp = A;
					size1 = ans.bigNum.size();
					size2 = temp.bigNum.size();
					ans.sign = true;
					break;
				}
				else if (i == size1 - 1) //狦ゑ程常  玥A=B △ A-B=0 
				{
					return "0";
				}
					
				token = i;
			}
		}
	}
	int i = size1 - 1, j = size2 - 1;
	for (i; i >= 0; i--, j--)
	{
		if (j >= 0)	//眖程秨﹍搭
		{
			ans.bigNum[i] -= temp.bigNum[j] - '0';
		}
		//秈
		if (ans.bigNum[i] < '0')
		{
			ans.bigNum[i] += 10;
			if (i > 0)
			{
				ans.bigNum[i - 1] -= 1;
			}
		}
	}
	//р玡0奔
	for (; ans.bigNum.size() > 1;)
	{
		if (ans.bigNum[0] == '0')
		{
			ans.bigNum.erase(ans.bigNum.begin());
		}
		else
		{
			break;
		}
	}
	if (ans.sign)	//璽
	{
		return "-" + ans.bigNum;
	}
	else  //タ
	{
		return ans.bigNum;
	}
}