//******************finished******************//
#include "BISA.h"
using namespace std;
//�w�]��0
BigIntAddSub::BigIntAddSub()
{
	num.bigNum = "0";
	num.sign = false;
}
//�]�w�j��
BigIntAddSub::BigIntAddSub(string a)
{
	if (a[0] == '-')	//�t��
	{
		num.sign = true;//-			sign==true���ɭԬO�t��
		a.erase(a.begin());	//��t���屼
	}
	else
	{
		num.sign = false;//+
	}
	num.bigNum = a;
}
//return �j��
N BigIntAddSub::getNumber()
{
	return num;
}
//�j�ƥ[�k(A+B)
string BigIntAddSub::bigIntAdd(N A, N B)
{
	N ans, temp;
	int size1 = A.bigNum.size(), size2 = B.bigNum.size();
	if (A.sign && !B.sign)	//A�t��   �B   B����
	{
		A.sign = false;//-A��+A
		ans.bigNum = bigIntSub(B, A);	//��⦡�令 B-A
		return ans.bigNum;
	}
	else if (!A.sign && B.sign)	//A����  �B  B�t��
	{
		B.sign = false;//-B��+B
		ans.bigNum = bigIntSub(A, B);	//��⦡�令A-B
		return ans.bigNum;
	}
	else  //��ӳ����� �� ��ӳ��t��
	{
		//��Ƹ��h����ans  ���֪���temp
		if (size1 >= size2)	//A��Ƥ�B�h
		{
			ans = A;
			temp = B;
		}
		else  //B��Ƥ�A�h
		{
			ans = B;
			temp = A;
		}
	}
	//size1�令ans����  size2�令temp����
	size1 = ans.bigNum.size();
	size2 = temp.bigNum.size();
	int i = size1 - 1, j = size2 - 1;	// i j ���O�Oans temp���̫�@��

	for (i; i >= 0; i--, j--)
	{
		if (j >= 0)	//�[���Ƥp������
		{
			ans.bigNum[i] += temp.bigNum[j] - '0';
		}
		//�i��
		if (ans.bigNum[i] > '9')
		{
			ans.bigNum[i] -= 10;
			if (i > 0)
				ans.bigNum[i - 1] += 1;
			else if (i == 0)
				ans.bigNum.insert(ans.bigNum.begin(), '1');
		}
	}
	if (ans.sign)	//�t��
	{
		return "-" + ans.bigNum;
	}
	else  //����
	{
		return ans.bigNum;
	}
		
}

string BigIntAddSub::bigIntSub(N A, N B)
{
	N ans, temp;
	int token = 0;//������ƬۦP�ɱq�Y��_�Ĥ@�Ӥ��P���Ʀr
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
		if (size1 > size2)	//�j��p
		{
			ans = A;
			temp = B;
		}
		else if (size1 < size2)	//�p��j
		{
			ans = B;
			ans.sign = true;
			temp = A;
			size1 = ans.bigNum.size();
			size2 = temp.bigNum.size();
		}
		else if (size1 == size2) //��ƬۦP
		{
			for (int i = 0; i < size1; i++)
			{
				//����Ĥ@�ӼƦr  ����j���Oans  �p���Otemp
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
				else if (i == size1 - 1) //�p�G���᳣̫�ۦP  �hA=B �� A-B=0 
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
		if (j >= 0)	//�q�̫�@��}�l��
		{
			ans.bigNum[i] -= temp.bigNum[j] - '0';
		}
		//�i��
		if (ans.bigNum[i] < '0')
		{
			ans.bigNum[i] += 10;
			if (i > 0)
			{
				ans.bigNum[i - 1] -= 1;
			}
		}
	}
	//��e����0�h��
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
	if (ans.sign)	//�t��
	{
		return "-" + ans.bigNum;
	}
	else  //����
	{
		return ans.bigNum;
	}
}