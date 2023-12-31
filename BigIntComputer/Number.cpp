#include "Number.h"
using namespace std;
class Integer;
class DEcimal;
class Complex;
vector<string> Number::var;
vector<string> Number::varAns;
bool haveBlank = false;
//輸入任意數學式
void Number::setInput(const string& line) /////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!要處理連續負號，需修改這裡的格式!!!!!!!!!!!!!!!!!!!!!!!!!!!!/////
{											//(目前想法為 如果遇到連續正負號 就在負號之間插入')' 這樣才能應對轉換後序式
											//(或是直接將鄭負號判別完縮減成一個運算符號)
	for (int t = 0;t < line.length();t++)
	{
		if (line[t] == ' ')
		{
			haveBlank = true;
			errorTyep = 4;
			break;
		}
	}

	input.clear();
	istringstream ss(line);
	string in, temp;
	//消除空格     //之前輸入空格會有錯 不確定這裡消除的效能如何
	while (ss >> in)
		temp += in;
	//將負號轉成'!'
	for (int i = 0; i < temp.size(); i++) //將字串全掃描過一次
	{
		if (i != temp.size() - 1) //字串結束前
		{
			//連續加減號改成只剩一個
			if (temp[i] == '+' || temp[i] == '-')
			{
				int tempI = i + 1;
				while (temp[tempI] == '+' || temp[tempI] == '-')
				{
					if (temp[tempI] == '+')
					{
						temp.erase(tempI, 1);
					}
					else if (temp[tempI] == '-' && temp[i] == '+')
					{
						temp.erase(tempI, 1);
						temp[i] = '-';
					}
					else if (temp[tempI] == '-' && temp[i] == '-')
					{
						temp.erase(tempI, 1);
						temp[i] = '+';
					}
				}
			}
			//乘除號後面的加減改成一個(改成沒有符號(正)  或   #(負)
			else if (temp[i] == '*' || temp[i] == '/')
			{
				int tempI = i + 1;
				if (temp[tempI] == '+' || temp[tempI] == '-')
				{
					//先改第一個負號(正號直接跳過)
					while (temp[tempI] == '+')
					{
						temp.erase(tempI, 1);
					}
					if (temp[tempI] == '-')
					{
						temp[tempI] = '#';
					}
					//再看後面的
					while (temp[tempI + 1] == '+' || temp[tempI + 1] == '-')
					{
						if (temp[tempI + 1] == '+')
						{
							temp.erase(tempI + 1, 1);
						}
						else if (temp[tempI + 1] == '-' && temp[tempI] == '#')
						{
							temp.erase(tempI + 1, 1);
							temp[tempI] = '+';
						}
						else if (temp[tempI + 1] == '-' && temp[tempI] == '+')
						{
							temp.erase(tempI + 1, 1);
							temp[tempI] = '#';
						}
					}
					if (temp[tempI] == '+')
					{
						temp.erase(tempI, 1);
					}
				}
			}
			//次方後面加減號改成一個
			else if (temp[i] == '^')
			{
				int tempI = i + 1;
				if (temp[tempI] == '+' || temp[tempI] == '-')
				{
					//先改第一個負號(正號直接跳過)
					while (temp[tempI] == '+')
					{
						temp.erase(tempI, 1);
					}
					if (temp[tempI] == '-')
					{
						temp[tempI] = '#';
					}
					//再看後面的
					while (temp[tempI + 1] == '+' || temp[tempI + 1] == '-')
					{
						if (temp[tempI + 1] == '+')
						{
							temp.erase(tempI + 1, 1);
						}
						else if (temp[tempI + 1] == '-' && temp[tempI] == '#')
						{
							temp.erase(tempI + 1, 1);
							temp[tempI] = '+';
						}
						else if (temp[tempI + 1] == '-' && temp[tempI] == '+')
						{
							temp.erase(tempI + 1, 1);
							temp[tempI] = '#';
						}
					}
					if (temp[tempI] == '+')
					{
						temp.erase(tempI, 1);
					}
				}
			}

			//i不等於0且temp[i]等於'-' (遇到非首項的減號)    或     temp[i]='-'且temp[i+1]='-' (遇到連續減號)
			if ((!i && temp[i] == '-') || ((temp[i] < '0' || temp[i] == '^') && temp[i] != ')' && temp[i + 1] == '-'))
			{
				//首項是非負號    或   temp[i]是其他運算符號
				if (i && temp[i] != '-' || ((temp[i] < '0' || temp[i] == '^') && temp[i] != ')' && temp[i + 1] == '-'))
				{
					input += temp[i++];	//input += '-'(減號)
				}

				input += '#';			//input += '#'(負號)
				continue;
			}
		}
		input += temp[i];
	}
}


//判斷字串、轉換後序式
void Number::computInput()
{
	vector<string> _operator, postfix;//stack堆疊  _operator(堆疊中的運算子)  postfix(後序式)
	vector<int> operatorPriority;//存堆疊中運算子的優先順序
	int nowPriority;//存當前運算子優先順序
	for (int i = 0; i < input.size(); i++)
	{
		//遇變數檢查後輸出至postfix
		if ((input[i] <= 'Z' && input[i] >= 'A') || (input[i] <= 'z' && input[i] >= 'a'))
		{
			//抓出變數部分
			string temp;
			int j = i;
			while (j < input.size() && ((input[j] <= 'Z' && input[j] >= 'A') || (input[j] <= 'z' && input[j] >= 'a') || (input[j] <= '9' && input[j] >= '0')))
			{
				temp += input[j];
				j++;
			}
			//查找變數是否存在
			bool found = false;
			for (int k = 0; k < var.size() && !found; k++)
			{
				if (var[k] == temp)
				{
					postfix.push_back(varAns[k]);
					found = true;
				}
			}
			for (int k = 0; k < var.size() && !found; k++)
			{
				if (var[k] == temp)
				{
					postfix.push_back(varAns[k]);
					found = true;
				}
			}
			/*if (!found)
			{
				cout << "Variable Not found.\n";
			}*/
			i = j - 1;
			continue;
		}
		//遇運算元(<=這裡應改成數字)直接輸出至 postfix(後序式)
		//遇數字直接輸出至postfix
		else if (input[i] <= '9' && input[i] >= '0' || input[i] == '.')
		{
			string temp;
			int j = i;
			while (j < input.size() && (input[j] <= '9' && input[j] >= '0' || input[j] == '.'))
			{
				temp += input[j];//當前運算元
				j++;
			}
			postfix.push_back(temp);
			i = j - 1;
		}
		//遇右括號')'輸出stack中的operator至')'
		else if (input[i] == ')')
		{
			while (!_operator.empty())
			{
				int top = _operator.size() - 1;
				if (_operator[top] == "(") {
					_operator.pop_back();
					operatorPriority.pop_back();
					break;
				}
				postfix.push_back(_operator[top]);
				_operator.pop_back();
				operatorPriority.pop_back();
			}
		}
		//其他狀況：比較運算子優先順序，並判斷要存入運算子堆疊或輸出至後序式
		else {
			switch (input[i])
			{
			case'(':	//左括號優先度：6
				nowPriority = priority[6];
				break;
			case'#':	//負號號優先度：5
				nowPriority = priority[5];
				break;
			case'i':	//虛部優先度：4
				nowPriority = priority[4];
				break;
			case'!':	//階成優先度：3
				nowPriority = priority[3];
				break;
			case'^':	//次方優先度：2
				nowPriority = priority[2];
				break;
			case'*':	//乘號號優先度：1
				nowPriority = priority[1];
				break;
			case'/':	//除號號優先度：1
				nowPriority = priority[1];
				break;
			case'+':	//加號號優先度：0
				nowPriority = priority[0];
				break;
			case'-':	//減號號優先度：0
				nowPriority = priority[0];
				break;
			default:  //讀到錯誤自
				errorTyep = 5;
				break;
			}
			//stack最上方運算子優先度 大於等於 當前運算子優先度 → 輸出至postfix(後序式)
			//若最上方運算子為左括號，則直接堆疊運算子
			if (!operatorPriority.empty())
			{
				while (operatorPriority[operatorPriority.size() - 1] != 6
					&& operatorPriority[operatorPriority.size() - 1] >= nowPriority)
				{
					postfix.push_back(_operator[_operator.size() - 1]);
					_operator.pop_back();
					operatorPriority.pop_back();
					if (operatorPriority.empty())
						break;
				}
			}
			string operat;//堆疊operator
			operat = input[i];//char 轉存 string
			_operator.push_back(operat);//堆疊當前運算子至_operator
			operatorPriority.push_back(nowPriority);//堆疊運算子優先度至operatorPriority
		}
	}
	while (!(_operator.empty()))
	{
		postfix.push_back(_operator[_operator.size() - 1]);
		_operator.pop_back();
		operatorPriority.pop_back();
	}

	//運算後序式
	vector<Fraction> stack;//stack[堆疊中的大數(分數型態)]
	for (int i = 0; i < postfix.size(); i++)
	{
		if ((postfix[i][0] < '0' || postfix[i][0] == '^' || postfix[i][0] == 'i') && !stack.empty()) //遇到符號  //開頭字元 < 0(非數字符號) || 是'^' || 是'i'
		{
			if (postfix[i][0] == '#') //負號
			{
				changeSign(stack[stack.size() - 1]);
			}
			else if (postfix[i][0] == 'i') //虛部
			{
				stack[stack.size() - 1] = toImag(stack[stack.size() - 1]);
			}
			else if (postfix[i][0] == '!') //階乘
			{
				stack[stack.size() - 1] = fracFac(stack[stack.size() - 1]);
			}
			else if (stack.size() >= 2) //前面至少還有兩數字能做運算 開始運算
			{
				switch (postfix[i][0])
				{
				case'+': 
					stack[stack.size() - 2] = fracAdd(stack[stack.size() - 2], stack[stack.size() - 1]);
					stack.pop_back();
					break;
				case'-':
					stack[stack.size() - 2] = fracSub(stack[stack.size() - 2], stack[stack.size() - 1]);
					stack.pop_back();
					break;
				case'*':
					stack[stack.size() - 2] = fracMul(stack[stack.size() - 2], stack[stack.size() - 1]);
					stack.pop_back();
					break;
				case'/':
					stack[stack.size() - 2] = fracDiv(stack[stack.size() - 2], stack[stack.size() - 1]);
					stack.pop_back();
					break;
				case'^':
					stack[stack.size() - 2] = fracPow(stack[stack.size() - 2], stack[stack.size() - 1]);
					stack.pop_back();
					break;
				default:
					break;
				}
			}
		}
		else // 遇到數字    放進stack
		{
			stack.push_back(posToStack(postfix[i]));
		}

		if (i == postfix.size() - 1)
			fracAns = stack[0];

		

	}
}

/*******************************************************************************************************************************************************
***************** ↓ 複數實作 ↓ ******* ↓ 不予理會 ↓ *******************************************************************************************************
********************************************************************************************************************************************************/
//分數轉虛部
Fraction Number::toImag(Fraction f)
{
	if (f.denominator == "0" && f.numerator == "0")
		return f;
	f.comSign = true;

	f.imag.denominator = f.denominator;
	f.imag.numerator = f.numerator;
	f.imag.sign = f.sign;
	f.sign = false;
	f.denominator = f.numerator = "0";
	return f;
}

//虛部轉實部
void Number::imagToReal(Fraction f, Fraction& a)
{
	a.numerator = f.imag.numerator;
	a.denominator = f.imag.denominator;
	a.sign = f.imag.sign;
	return;
}

//實部轉虛部
void Number::realToImag(Fraction& f, Fraction a)
{
	if (a.numerator == "0" && a.denominator == "0")
	{
		f.imag.numerator = "0";
		f.imag.denominator = "0";
		f.comSign = false;
		return;
	}
	f.imag.numerator = a.numerator;
	f.imag.denominator = a.denominator;
	f.imag.sign = a.sign;
	f.comSign = true;
	return;
}

//複數加法
Fraction Number::comAdd(Fraction left, Fraction right)
{
	Fraction ans, a, b;
	left.comSign = right.comSign = false;
	imagToReal(left, a);
	imagToReal(right, b);

	ans = fracAdd(left, right); //實部相加
	a = fracAdd(a, b); //虛部相加

	realToImag(ans, a);
	if (ans.imag.numerator != "0" && ans.imag.denominator != "0")
		ans.comSign = true;
	return ans;
}

//複數減法
Fraction Number::comSub(Fraction left, Fraction right)
{
	Fraction ans, a, b;
	left.comSign = right.comSign = false;
	imagToReal(left, a);
	imagToReal(right, b);

	ans = fracSub(left, right); //實部相減
	a = fracSub(a, b); //虛部相減

	realToImag(ans, a);
	if (ans.imag.numerator != "0" && ans.imag.denominator != "0")
		ans.comSign = true;
	return ans;
}

//複數乘法
Fraction Number::comMul(Fraction left, Fraction right)
{
	Fraction ans, a, b;
	left.comSign = right.comSign = false;
	imagToReal(left, a);
	imagToReal(right, b);
	Fraction t1 = fracMul(left, right), t2 = fracMul(a, b);
	ans = fracSub(fracMul(left, right), fracMul(a, b));	//實部
	a = fracAdd(fracMul(left, b), fracMul(right, a));	//虛部
	if (a.denominator != "0")
		a = about(a);
	if (ans.denominator != "0")
		ans = about(ans);

	realToImag(ans, a);
	if (ans.imag.numerator != "0" && ans.imag.denominator != "0")
		ans.comSign = true;
	return ans;
}

//複數除法
Fraction Number::comDiv(Fraction left, Fraction right)
{
	Fraction ans, temp, a, b, p;
	left.comSign = right.comSign = false;
	imagToReal(left, a);
	imagToReal(right, b);
	// p=2
	p.numerator = "2";
	p.denominator = "1";

	ans = fracAdd(fracMul(left, right), fracMul(a, b));	//實部
	temp = fracSub(fracMul(right, a), fracMul(left, b));//虛部

	Fraction t1 = fracAdd(fracPow(right, p), fracPow(b, p)), t2 = fracPow(right, p), t3 = fracPow(b, p);

	ans = fracDiv(ans, fracAdd(fracPow(right, p), fracPow(b, p))); //實部
	temp = fracDiv(temp, fracAdd(fracPow(right, p), fracPow(b, p))); //虛部

	realToImag(ans, temp);
	if (ans.imag.numerator != "0" && ans.imag.denominator != "0")
		ans.comSign = true;
	return ans;
}

//複數次方
Fraction Number::comPow(Fraction a, Fraction b)
{
	if (b.numerator == "1" && b.denominator == "2")
		return comRoot(a, b.sign);
	else if (b.denominator == "0")
	{
		Fraction f;
		f.numerator = f.denominator = "1";
		return f;
	}
	else if (b.denominator != "1")
		cout << "Illegal Power(a,b)" << endl;

	//if (right == "0.5" || right == "1/2")  return root(left);
	int tempPow = 0, count = 0;

	for (int i = 0; i < b.numerator.size(); i++)   //字串轉整數
	{
		tempPow *= count;
		tempPow += (b.numerator[i] - '0');
		count = 10;
	}

	Fraction ans, t, temp;
	Fraction basisTwo = comMul(a, a);  //二次方
	string ts = "0.";
	ts.insert(ts.end(), 110, '0');
	imagToReal(basisTwo, t);
	if (get110Dec(t) == ts)
		realToImag(basisTwo, temp);
	if (get110Dec(basisTwo) == ts)
	{
		imagToReal(temp, basisTwo);
	}

	int i;
	if (tempPow % 2 == 0)
	{
		ans = basisTwo;
		i = 1;
	}
	else
	{
		ans = a;
		i = 0;
	}
	tempPow /= 2;

	for (i; i < tempPow; i++)
	{
		imagToReal(basisTwo, t);
		if (get110Dec(t) == ts)
			realToImag(basisTwo, temp);
		if (get110Dec(basisTwo) == ts)
		{
			imagToReal(temp, basisTwo);
		}
		ans = comMul(ans, basisTwo);
	}

	if (b.sign)
	{
		Fraction i;
		i.numerator = i.denominator = "1";
		return comDiv(i, ans);
	}

	return ans;
}


/*************************************************************************************************************************************************************
***************** ↑ 複數實作 ↑ ********************* ↑ 不予理會 ↑ ***********************************************************************************************
**************************************************************************************************************************************************************/



/***********************************************
***************** ↓ 根號實作 ↓ ***************
************************************************/

//分數開根號
Fraction Number::fracRoot(Fraction f, bool sign)
{
	if (f.comSign)					//如果為複數，return不理會
		return comRoot(f, sign);
	if (f.sign)		//如果根號內為負數 轉換成虛數 /////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 因為不須實作複數 須改為防呆message !!!!!!!!!!!!
	{
		Fraction t;
		f.sign = false;
		f = fracRoot(f, sign);
		realToImag(t, f);
		return t;
	}
	string t1, t2, s;
	t1 = getRoot120(f.numerator);  //呼叫getRoot120  友怡part
	t2 = getRoot120(f.denominator);   //呼叫getRoot120  友怡part
	s.insert(s.end(), 50, '0');
	size_t f1, f2;
	f1 = t1.find('.');
	f2 = t2.find('.');
	if (t1.substr(f1 + 1, 50) == s && t2.substr(f2 + 1, 50) == s)
	{
		f.numerator.assign(t1.begin(), t1.begin() + f1);
		f.denominator.assign(t2.begin(), t2.begin() + f2);
		if (sign)
		{
			string temp = f.denominator;
			f.denominator = f.numerator;
			f.numerator = temp;
		}
		return f;
	}
	else
	{
		t1.erase(f1, 1);
		t2.erase(f2, 1);
		if (sign)
			f.numerator = t2, f.denominator = t1;
		else
			f.numerator = t1, f.denominator = t2;
	}
	if (f.denominator != "0")     //如果分母不等於零
		f = about(f);		//檢查分數約分
	return f;
}

//複數開根號 (不予理會) XXXXXXXX
Fraction Number::comRoot(Fraction a, bool sign)
{
	//a:實部 b:虛部
	//t1: x^2+y^2 = root(a^2+b^2)
	//t2: 2*x*y = b
	Fraction x, y, b, t1, t, p;
	a.comSign = false;
	imagToReal(a, b);
	p.numerator = "2", p.denominator = "1";
	bool k = false;
	t1 = fracRoot(fracAdd(fracPow(a, p), fracPow(b, p)), k);
	t = fracRoot(fracAdd(t1, b), k);
	b = fracRoot(fracSub(t1, b), k);
	if (a.sign)
	{
		x = fracDiv(fracSub(t, b), p);
		y = fracSub(t, x);
		realToImag(x, y);
	}
	else
	{
		y = fracDiv(fracSub(t, b), p);
		x = fracSub(t, y);
		realToImag(x, y);
	}
	p.numerator = "1";

	if (sign)
		return fracDiv(p, x);
	return x;
}

/***********************************************
***************** ↑ 根號實作 ↑ ***************
************************************************/



/***********************************************
***************** ↓ 分數實作 ↓ ***************
************************************************/
//後序式string 轉成分子、分母部分
Fraction Number::posToStack(string pos)
{
	//判斷是否為小數
	int index = 0; //小數點所在位數

	//if(pos == "")
	for (int i = 0; i < pos.size() - 1; i++)
	{
		if (pos[i] == '.') 
		{
			index = i;
			break;
		}
	}
	Fraction temp; 
	//
	bool isZero = true;
	string Zero = "0.";
	
	if (index == 1 && pos[0] == '0') {
		for (int k = index + 1; k < pos.size(); k++) {
			if (pos[k] != '0') {
				isZero = false;
				break;
			}
		}
	}
	else {
		isZero = false;
	}
	if (isZero) {
		pos = "0";
	}
	if (index == 0 || pos == "0") 
	{
		temp.isInt = true; //標記成整數

		if (pos != "0")
		{
			temp.numerator.assign(pos);
			temp.denominator = "1";  //  pos/1
		}
		else
			temp.denominator = "0"; //  0/0
	}
	else //小數 轉 分數型態
	{
		temp.isInt = false;  //標記成小數

		string a = "1";
		pos.erase(pos.begin() + index);
		for (int i = pos.size() - index; i > 0; i--)
			a.push_back('0');
		temp.denominator.assign(a);
		while (pos.size())
		{
			if (pos[0] == '0')
				pos.erase(pos.begin());
			else if (pos[0] != '0')
				break;
		}
		temp.numerator.assign(pos);
	}
	if (temp.denominator != "0")
		temp = about(temp);//約分
	return temp;
}

//負號
void Number::changeSign(Fraction& f) //變號運算
{
	if (f.numerator != "0" && f.denominator != "0") //分子分母皆不為零 分數才有正負號能討論
		f.sign = !f.sign;
	if (f.comSign)  //為複數 (不予理會)
		if (f.imag.numerator != "0" && f.imag.denominator != "0")
			f.imag.sign = !f.imag.sign;
}

//分數約分
Fraction Number::about(Fraction f)
{
	if (f.numerator.size() > 150 && f.denominator.size() > 150)  /////如果分子分母超過150位以上 用long long處理
	{
		long long s1 = f.numerator.size(), s2 = f.denominator.size();
		s1 -= s2;
		f.numerator.erase(f.numerator.begin() + 150 + s1, f.numerator.end());
		f.denominator.erase(f.denominator.begin() + 150, f.denominator.end());
	}
	string g = gcd(f.numerator, f.denominator); //算出分子分母最大公因數 g 後
	int c1 = cmp(g, f.numerator), c2 = cmp(g, f.denominator);   ///////////////////////////////////////////////////////////////////////////意義不明
	f.numerator = div(f.numerator, g);			//呼叫大數除法
	f.denominator = div(f.denominator, g);		//呼叫大數除法

	return f;
}

//最大公因數GCD
string Number::gcd(string a, string b)
{
	if (b == "0")
		return a;
	else
		return gcd(b, mod(a, b));
}

//取餘數 left%right
string Number::mod(string left, string right)
{
	string a = left;
	a += 'r';//加一個判斷字元
	return div(a, right); //呼叫大數除法
}

//正負號判斷
bool Number::sign(string& str)
{
	bool s = false; 
	if (str[0] == '-')
	{
		s = true;
		str.erase(str.begin());
	}
	return s;
}

//分數次方
Fraction Number::fracPow(Fraction a, Fraction b)
{


	if ((b.denominator != "1" && b.denominator != "0") && !(b.numerator == "1" && b.denominator == "2") || //如果次方不為整數 或是不為1/2 無法計算次方
		(b.comSign && b.imag.denominator != "0"))
	{
		if (errorTyep == -1)
			errorTyep = 2;
		return a;
	}
	if (a.comSign)		//複數次方 (不予理會)
		return comPow(a, b);
	if (b.numerator == "1" && b.denominator == "2")		//如果次方為1/2
		return fracRoot(a, b.sign);		//開根號
	else if (b.denominator == "0")		//次方分母 == 0 --> 開0次方 結果 == 1  ?????????????????????????????????????????????????????????????????
	{
		a.numerator = a.denominator = "1";		//將欲算次方目標改為 +1 return
		a.sign = false;
		return a;
	}
	if (mod(b.numerator, "2") == "0")		//偶數次方 負負得正
		a.sign = false;

	a.numerator = pow(a.numerator, b.numerator); //分子乘次方
	a.denominator = pow(a.denominator, b.numerator);	//分母乘次方

	if (a.denominator != "0")	//如果分母不為零 檢查約分
		a = about(a);//約分

	if (b.sign) //乘負數次方 將a倒數再return
	{
		string temp;
		temp = a.denominator;
		a.denominator = a.numerator;
		a.numerator = temp;
	}
	return a;
}

//階乘
Fraction Number::fracFac(Fraction f)
{
	bool tmpSign = f.sign;
	bool tmpInt = f.isInt;
	string s = get100Dec(f);  //呼叫get100Dec 友怡part

	f = posToStack(s);
	f.sign = tmpSign;
	f.isInt = tmpInt;
	if (f.numerator == "0") //f.denominator == "0" && 
	{
		Fraction ret;
		ret.numerator = "1";
		ret.denominator = "1";
		ret.isInt = true;
		return ret;
	}

	if (f.denominator != "1" || f.comSign == true || f.sign) //非整數 複數 非正數 不能階乘
	{
		if (errorTyep == -1)
			errorTyep = 1;
	}
	else
	{
		f.numerator = fac(f.numerator);
		f.isInt = true;
	}
		 	
	return f;
}

//分數加法
Fraction Number::fracAdd(Fraction left, Fraction right)
{
	if (left.comSign || right.comSign) //如果左右任一數為複數，return不理會
		return comAdd(left, right);

	Fraction f; //暫存結果

	if (left.isInt && right.isInt)  //如果左右皆為整數 標記整數
	{
		f.isInt = true;
	}

	//還原負號
	if (left.sign)			//如果左分數為複號 補上負號回去 
		left.numerator.insert(0, "-");
	if (right.sign)			//如果右分數為複號 補上負號回去 
		right.numerator.insert(0, "-");

	int c = cmp(left.denominator, right.denominator); //cmp 0: 左右分母相等 1:左分母 < 右分母 -1: 左分母 > 右分母
	if (c == 0)//若分母相同，分子直接相加
	{
		f.numerator = add(left.numerator, right.numerator);
		f.denominator = left.denominator;
	}
	else if (left.numerator == "0" && left.denominator == "0")
	{
		right.sign = sign(right.numerator);
		return right;
	}
	else if (right.numerator == "0" && right.denominator == "0")
	{
		left.sign = sign(left.numerator);
		return left;
	}
	else//若分母不相同，通分後相加
	{
		f.denominator = mul(left.denominator, right.denominator);
		left.numerator = mul(left.numerator, right.denominator);
		right.numerator = mul(right.numerator, left.denominator);
		f.numerator = add(left.numerator, right.numerator);
	}
	f.sign = sign(f.numerator);
	if (f.numerator == "0")
		f.denominator = "0";
	if (f.denominator != "0")
		f = about(f);//約分

	if (f.isInt) //如果f為整數 砍掉小數點後面部分
	{
		f.numerator = get100Dec(f);
		//分子 = 分子 / 分母  

		int index = 0; //小數點所在位數
		for (int i = 0; i < f.numerator.size() - 1; i++)
		{
			if (f.numerator[i] == '.')
			{
				index = i;
				break;
			}
		}

		//刪除小數點後小數
		f.numerator.erase(index);
		//分母 = 1 ;
		if (f.numerator == "0")
		{
			f.denominator = "0";
		}
		else
		{
			f.denominator = "1";
		}
	}

	return f;
}

//分數減法
Fraction Number::fracSub(Fraction left, Fraction right)
{
	if (left.comSign || right.comSign)	//如果左右任一數為複數，return不理會
		return comSub(left, right);
	Fraction f;
	//還原負號

	if (left.isInt && right.isInt)  //如果左右皆為整數 標記整數
	{
		f.isInt = true;
	}

	if (left.sign)
		left.numerator.insert(0, "-");
	if (right.sign)
		right.numerator.insert(0, "-");

	int c = cmp(left.denominator, right.denominator);
	if (c == 0)//若分母相同，分子直接相加
	{
		f.numerator = sub(left.numerator, right.numerator);
		f.denominator = left.denominator;
	}
	else if (left.numerator == "0" && left.denominator == "0")
	{
		right.sign = !sign(right.numerator);
		return right;
	}
	else if (right.numerator == "0" && right.denominator == "0")
	{
		left.sign = sign(left.numerator);
		return left;
	}
	else//若分母不相同，通分後相減
	{
		f.denominator = mul(left.denominator, right.denominator);
		left.numerator = mul(left.numerator, right.denominator);
		right.numerator = mul(right.numerator, left.denominator);
		f.numerator = sub(left.numerator, right.numerator);
	}
	f.sign = sign(f.numerator);
	if (f.numerator == "0")
		f.denominator = "0";
	if (f.denominator != "0")
		f = about(f);//約分

	if (f.isInt) //如果f為整數 砍掉小數點後面部分
	{
		f.numerator = get100Dec(f);
		//分子 = 分子 / 分母  

		int index = 0; //小數點所在位數
		for (int i = 0; i < f.numerator.size() - 1; i++)
		{
			if (f.numerator[i] == '.')
			{
				index = i;
				break;
			}
		}

		//刪除小數點後小數
		f.numerator.erase(index);
		//分母 = 1 ;
		if (f.numerator == "0")
		{
			f.denominator = "0";
		}
		else
		{
			f.denominator = "1";
		}
	}

	return f;
}

//分數乘法
Fraction Number::fracMul(Fraction left, Fraction right)
{
	if (left.comSign || right.comSign)	//如果左右任一數為複數，return不理會
		return comMul(left, right);

	Fraction f;

	/// -2 = -2 / -1
	/// 1   / 7.0  * 3 = 0
	/// 
	/// 1.0 / 7    * 3
	/// 
	/// 1   / 7

	if (left.isInt && right.isInt)  //如果左右皆為整數 標記整數
	{
		f.isInt = true;
	}

	if (left.sign && right.sign)	//flase為正數，同號相乘為正
		f.sign = false;
	else if (left.sign || right.sign) //異號相乘為負
		f.sign = true;
	else f.sign = false; //正



	f.numerator = mul(left.numerator, right.numerator); //分子乘分子
	f.denominator = mul(left.denominator, right.denominator); //分母乘分母

	if (f.numerator == "0" && f.denominator == "0") //分子分母皆為零	///////////////////////////////////////////////////////
		f.sign = false;	//正數

	if (f.denominator != "0") //分母不為零  要約分
		f = about(f);//約分

	if (f.isInt) //如果f為整數 砍掉小數點後面部分
	{
		f.numerator = get100Dec(f);
		//分子 = 分子 / 分母  

		int index = 0; //小數點所在位數
		for (int i = 0; i < f.numerator.size() - 1; i++)
		{
			if (f.numerator[i] == '.')
			{
				index = i;
				break;
			}
		}

		//刪除小數點後小數
		f.numerator.erase(index);
		//分母 = 1 ;
		if (f.numerator == "0")
		{
			f.denominator = "0";
		}
		else
		{
			f.denominator = "1";
		}
	}

	return f;
}

//分數除法
Fraction Number::fracDiv(Fraction left, Fraction right)
{
	if (right.denominator == "0" && right.imag.denominator == "0")
	{
		if (errorTyep == -1)
			errorTyep = 3;		//////////////////////////////////////////////////////查詢error type
		return left;
	}

	if (left.comSign || right.comSign) //如果左右任一數為複數，return不理會
		return comDiv(left, right);

	Fraction f;

	if (left.isInt && right.isInt)  //如果左右皆為整數 標記整數
	{
		f.isInt = true;
	}

	if (left.sign && right.sign)		//flase為正數，同號相乘為正
		f.sign = false;
	else if (left.sign || right.sign)		//異號相乘為負
		f.sign = true;
	else f.sign = false;		//為正

	//內相乘為分母 外相乘為分子

	f.numerator = mul(left.numerator, right.denominator);
	f.denominator = mul(left.denominator, right.numerator);

	if (f.denominator != "0")
		f = about(f);//約分

	if (f.isInt) //如果f為整數 砍掉小數點後面部分
	{
		f.numerator = get100Dec(f);
		//分子 = 分子 / 分母  

		int index = 0; //小數點所在位數
		for (int i = 0; i < f.numerator.size() - 1; i++)
		{
			if (f.numerator[i] == '.')
			{
				index = i;
				break;
			}
		}

		//刪除小數點後小數
		f.numerator.erase(index);
		//分母 = 1 ;

		if (f.numerator == "0")
		{
			f.denominator = "0";
		}
		else
		{
			f.denominator = "1";
		}
		
	}

	return f;
}
/***********************************************
***************** ↑ 分數實作 ↑ ***************
************************************************/

//Yui

/***********************************************
***************** ↓ 整數實作 ↓ ***************
************************************************/
//大數次方
string Number::pow(string left, string right)
{
	//遞迴運算次方 到1次或2次回傳
	if (right == "1")
		return left;
	if (right == "2")
		return mul(left, left);

	int tempPow = 0, count = 10;

	for (int i = 0; i < right.size(); i++)   //字串轉整數
	{
		tempPow *= count;
		tempPow += (right[i] - '0');
	}
	//ret = power / 2 回傳left^ret * left^ret
	int ret = tempPow / 2;
	return mul(pow(left, to_string(ret)), pow(left, to_string(tempPow - ret)));
	//}
	////if (right == "0.5" || right == "1/2")  return root(left);
	//if (right == "0") return "1";

	//int tempPow = 0, count = 10;

	//for (int i = 0; i < right.size(); i++)   //字串轉整數
	//{
	// tempPow *= count;
	// tempPow += (right[i] - '0');
	//}

	//string ans;
	//int i;
	//if (tempPow % 2 == 0)
	//{
	// ans = mul(left, left);
	// i = 1;
	//}
	//else
	//{
	// ans = left;
	// i = 0;
	//}
	//tempPow /= 2;

	//string basisTwo = mul(left, left);  //二次方

	//for (i; i < tempPow; i++)
	// ans = mul(ans, basisTwo);

	//return ans;
}

//大數階乘
string Number::fac(string str)
{
	int n = 0, count = 0;
	//str to int
	for (int i = 0; i < str.size(); i++)
	{
		n *= count;
		n += (str[i] - '0');
		count = 10;
	}
	vector<int> ans;
	ans.push_back(1);
	int res_size = 1;
	//從1開始做階乘 結果依位數小到大儲存在vector<int> ans
	//ex: 4321 -> 1 2 3 4
	//res_size = ans位數
	for (int x = 2; x <= n; x++)
		res_size = multiply(x, ans, res_size);

	//ans to str
	str.clear();
	for (int i = res_size - 1; i >= 0; i--)
		str += ans[i] + '0';
	return str;
}

//階乘function (for each factor)
int Number::multiply(int x, vector<int>& ans, int res_size)
{
	int carry = 0;
	for (int i = 0; i < res_size; i++)
	{
		int prod = ans[i] * x + carry;
		ans[i] = prod % 10;
		carry = prod / 10;
	}
	while (carry)
	{
		ans.push_back(carry % 10);
		carry = carry / 10;
		res_size++;
	}
	return res_size;
}

//大數加法 left+fight
string Number::add(string left, string right)
{
	BigIntAddSub A(left), B(right);
	return A.bigIntAdd(A.getNumber(), B.getNumber());
}

//大數減法 left-right
string Number::sub(string left, string right)
{
	BigIntAddSub A(left), B(right);
	return A.bigIntSub(A.getNumber(), B.getNumber());
}

//大數乘法 left*right
string Number::mul(string left, string right)
{
	//判斷正負號
	bool mulSign = false;//存正負號，default為正號(false)
	if (left[0] == '-' && right[0] == '-')
	{
		left.erase(left.begin());
		right.erase(right.begin());
	}
	else if (left[0] == '-')
	{
		left.erase(left.begin());
		mulSign = true;
	}
	else if (right[0] == '-')
	{
		right.erase(right.begin());
		mulSign = true;
	}

	//大數乘法實作
	int integer[10] = { 0,1,2,3,4,5,6,7,8,9 };
	vector<int> num;
	int now = 0, next, index;
	for (int j = right.size() - 1; j >= 0; j--)
	{
		index = right.size() - j - 1;
		//index為現在做的乘法所在位數
		for (int i = left.size() - 1; i >= 0; i--, index++)
		{
			next = 0;
			if (integer[left[i] - '0'] != 0 && integer[right[j] - '0'] != 0) //遇零進位//皆不是零才進這個if
			{
				now += integer[left[i] - '0'] * integer[right[j] - '0'];
			}
			if (now >= 10)//超過10就進位到next
			{
				next += now / 10;
				now %= 10;
			}
			if (num.size() <= index)//
				num.push_back(now);
			else
			{
				num[index] += now;
				if (num[index] >= 10)//超過10就進位到next
				{
					next += num[index] / 10;
					num[index] %= 10;
				}
			}
			now = next;
		}
		while (now > 0)
		{
			num.push_back(now % 10);
			now /= 10;
		}
	}
	while (now > 0)
	{
		num.push_back(now % 10);
		now /= 10;
	}


	//反轉vector<int>並轉成string
	string strNum;
	bool zero = true;
	for (int i = num.size() - 1; i >= 0; i--)
	{
		//直到找到非0位
		if (num[i] != 0)
			zero = false;
		//找到非零 開始轉str
		if (!zero)
			strNum += num[i] + '0';
		else if (i == 0)//全部為0
			strNum = "0";
	}
	if (mulSign && strNum != "0")
		return "-" + strNum; //相乘結果為負數
	return strNum; //相乘結果為正數
}

//大數除法 left/right 附取餘數功能
string Number::div(string left, string right)
{
	bool r = false;//判斷是否要取餘數//要的話left尾端會是r
	if (left[left.size() - 1] == 'r')
	{
		r = true;
		left.pop_back();
	}

	if (right == "0")
	{
		cout << "Illegal input!" << endl;
		return "0";
	}
	//判斷正負號
	bool divSign = false;//存正負號，default為正號(false)
	if (left[0] == '-' && right[0] == '-')
	{
		left.erase(left.begin());
		right.erase(right.begin());
	}
	else if (left[0] == '-')
	{
		left.erase(left.begin());
		divSign = true;
	}
	else if (right[0] == '-')
	{
		right.erase(right.begin());
		divSign = true;
	}

	string rem; //餘數
	   //判斷大小
	int c = cmp(left, right);
	if (c == 0)//兩數相等
	{
		rem = "0";
		if (r)
			return rem;
		if (divSign)
			return "-1";
		return "1";
	}
	else if (c == 1)//除數>被除數
	{
		rem = left;
		if (r)
			return rem;
		return "0";
	}
	else
	{
		string rem = left, R = right;
		string quotient;
		int s = left.size() - right.size() + 1;
		for (int i = 0; i < s - 1; i++) //若長度不一樣，將right補零至與left一樣長
			R.push_back('0');
		while (s--)//差s位 做s+1次
		{
			string a, m;
			for (int i = 9; i >= 0; i--)
			{
				a = '0' + i;
				m = mul(R, a);
				c = cmp(m, rem);
				if (c >= 0)
				{
					quotient += a;//商+a
					rem = sub(rem, m);//被除數-m
					break;
				}
			}
			R.pop_back();
		}
		if (r)
			return rem;

		if (quotient[0] == '0')
			quotient.erase(quotient.begin());

		if (divSign)
			return "-" + quotient;
		return quotient;
	}
}

//Intent: 大數比較
//Per: 輸入兩個非負整數
//Post: 0:相等 1:left<right -1:left>right
int Number::cmp(string left, string right)
{
	int size1 = left.size();
	int size2 = right.size();

	if (size1 > size2)
		return -1;
	else if (size1 < size2)
		return 1;
	else if (size1 == size2)
	{
		for (int i = 0; i < size1; i++)
		{
			if (left[i] > right[i])
				return -1;
			else if (left[i] < right[i])
				return 1;
			else if (i == size1 - 1)
				return 0;
		}
	}
}
/***********************************************
***************** ↑ 整數實作 ↑ ***************
************************************************/
//給分數f 回傳結果str到小數點後110位
string Number::get110Dec(Fraction f)
{ //輸出110位0.00
	if (f.numerator == "0" && f.denominator == "0")
	{
		string s;
		s.assign(110, '0');
		return "0." + s;
	}
	string temp;
	string quotient = div(f.numerator, f.denominator);
	//len= 整數部分長度
	int len = quotient.length();
	if (cmp(f.numerator, f.denominator) == 1 && f.numerator != "0")//小於1
	{
		temp = "0.";
		while (cmp(f.numerator, f.denominator) == 1)//分子小於分母 補零
		{
			temp += '0';
			f.numerator += '0';
		}
		if (temp[temp.size() - 1] == '0')
			temp.pop_back();
		f.numerator.insert(f.numerator.end(), 110, '0');
		quotient = div(f.numerator, f.denominator);
		temp += quotient;
		return temp.assign(temp, 0, len + 111);
	}
	else
	{
		f.numerator.insert(f.numerator.end(), 110, '0');
		quotient = div(f.numerator, f.denominator);
		quotient.insert(len, ".");
		return quotient.assign(quotient, 0, len + 111);
	}

}
//回傳f to str到小數點後100位
string Number::get100Dec(Fraction f)
{
	string get110 = get110Dec(f);
	string s;
	size_t index;
	index = get110.find('.');
	s.assign(105, '9');
	if (s == get110.substr(index + 1, 105))
	{
		get110.assign(get110.begin(), get110.begin() + index);
		get110 = add(get110, "1");
		get110 += '.';
		get110.insert(get110.end(), 110, '0');
	}
	s.assign(10, '9');
	if (s == get110.substr(index + 100, 10))
	{
		string temp;
		temp.assign(get110.begin(), get110.begin() + index); //小數點前
		get110 = get110.substr(index + 1, 110);
		while (get110[0] == '0')
		{
			get110.erase(get110.begin());
		}
		get110 = add(get110, "1");
		if (get110.size() > 110)
		{
			string a;
			a = get110[0];
			get110.erase(get110.begin());
			temp = add(temp, a);
		}

		temp += '.';
		temp += get110;
		get110 = temp;
	}
	return get110.assign(get110, 0, get110.size() - 10);
}
//f to str到小數點後10位
string Number::get10Dec(Fraction f)
{
	string get100 = get100Dec(f);
	return get100.assign(get100, 0, get100.size() - 90);
}
//求平方根
string Number::getRoot120(string s)
{
	string ans;
	int len1;
	s.length() % 2 == 0 ? len1 = s.length() / 2 : len1 = s.length() / 2 + 1;
	s.insert(s.end(), 300, '0');
	int len = s.length();
	int i, j;
	int x[300] = {}, y[600] = {};
	for (i = 0, j = len - 1; j >= 0; i++)
	{
		x[i] = s[j] - '0';
		if (j - 1 >= 0)    x[i] = x[i] + (s[j - 1] - '0') * 10;
		if (j - 2 >= 0)    x[i] = x[i] + (s[j - 2] - '0') * 100;
		if (j - 3 >= 0)    x[i] = x[i] + (s[j - 3] - '0') * 1000;
		j -= 4;
	}
	int xlen = len, ylen = 0, head = 0;
	while (xlen >= 0 && x[xlen] == 0) xlen--;
	for (j = (len - 1) / 8, i = j * 2; j >= 0; j--, i -= 2)
	{
		ylen++;
		for (int p = ylen; p >= 1; p--)
			y[p] = y[p - 1];
		y[0] = 0;
		if (xlen < j)
		{
			if (!head)
				ans.push_back('0'), head = 1;
			else
				ans = ans + "0000";
			continue;
		}
		int l = 0, r = 9999, p;
		int z[300]; // z = (y*10 + p)*p;
		while (l <= r)
		{
			p = (l + r) / 2;
			y[0] += p;
			z[0] = 0;
			for (int q = 0; q <= ylen + 5; q++)
			{
				z[q] += p * y[q];
				z[q + 1] = z[q] / 10000;
				z[q] %= 10000;
			}
			int chflag = 0;
			for (int q = ylen + 5; q >= 0; q--)
			{
				if (z[q] > x[i + q])
				{
					chflag = 1;
					break;
				}
				else if (z[q] < x[i + q])
				{
					chflag = 0;
					break;
				}
			}
			y[0] -= p;
			if (chflag)
				r = p - 1;
			else
				l = p + 1;
		}
		p = l - 1;
		y[0] = p;
		z[0] = 0;
		for (int q = 0; q <= ylen + 5; q++)
		{
			z[q] += p * y[q];
			z[q + 1] = z[q] / 10000;
			z[q] %= 10000;
		}
		for (int q = ylen + 5; q >= 0; q--)
			x[i + q] -= z[q];
		for (int q = 0; q <= ylen + 5; q++)
		{
			while (x[i + q] < 0)
				x[i + q] += 10000, x[i + q + 1]--;
		}
		y[0] += p;
		for (int q = 0; q <= ylen + 5; q++)
		{
			if (y[q] >= 10000)
			{
				y[q + 1] += y[q] / 10000;
				y[q] %= 10000;
			}
		}
		ylen += 5;
		while (ylen >= 0 && y[ylen] == 0)    ylen--;
		while (xlen >= 0 && x[xlen] == 0)    xlen--;
		if (!head)
		{
			ans = ans + to_string(p);
			head = 1;
		}
		else
		{
			string str = to_string(p);
			for (int w = 0; w < 4 - str.length(); w++)
				ans.push_back('0');
			ans = ans + str;
		}
	}
	ans.insert(len1, ".");
	return ans;
}

string Number::printRoot(string s)
{
	string ans;
	int len1;
	s.length() % 2 == 0 ? len1 = s.length() / 2 : len1 = s.length() / 2 + 1;
	s.insert(s.end(), 200, '0');
	int len = s.length();
	int i, j;
	int x[300] = {}, y[300] = {};
	for (i = 0, j = len - 1; j >= 0; i++)
	{
		x[i] = s[j] - '0';
		if (j - 1 >= 0)    x[i] = x[i] + (s[j - 1] - '0') * 10;
		if (j - 2 >= 0)    x[i] = x[i] + (s[j - 2] - '0') * 100;
		if (j - 3 >= 0)    x[i] = x[i] + (s[j - 3] - '0') * 1000;
		j -= 4;
	}
	int xlen = len, ylen = 0, head = 0;
	while (xlen >= 0 && x[xlen] == 0) xlen--;
	for (j = (len - 1) / 8, i = j * 2; j >= 0; j--, i -= 2)
	{
		ylen++;
		for (int p = ylen; p >= 1; p--)
			y[p] = y[p - 1];
		y[0] = 0;
		if (xlen < j)
		{
			if (!head)
				ans.push_back('0'), head = 1;
			else
				ans = ans + "0000";
			continue;
		}
		int l = 0, r = 9999, p;
		int z[300]; // z = (y*10 + p)*p;
		while (l <= r)
		{
			p = (l + r) / 2;
			y[0] += p;
			z[0] = 0;
			for (int q = 0; q <= ylen + 5; q++)
			{
				z[q] += p * y[q];
				z[q + 1] = z[q] / 10000;
				z[q] %= 10000;
			}
			int chflag = 0;
			for (int q = ylen + 5; q >= 0; q--)
			{
				if (z[q] > x[i + q])
				{
					chflag = 1;
					break;
				}
				else if (z[q] < x[i + q])
				{
					chflag = 0;
					break;
				}
			}
			y[0] -= p;
			if (chflag)
				r = p - 1;
			else
				l = p + 1;
		}
		p = l - 1;
		y[0] = p;
		z[0] = 0;
		for (int q = 0; q <= ylen + 5; q++)
		{
			z[q] += p * y[q];
			z[q + 1] = z[q] / 10000;
			z[q] %= 10000;
		}
		for (int q = ylen + 5; q >= 0; q--)
			x[i + q] -= z[q];
		for (int q = 0; q <= ylen + 5; q++)
		{
			while (x[i + q] < 0)
				x[i + q] += 10000, x[i + q + 1]--;
		}
		y[0] += p;
		for (int q = 0; q <= ylen + 5; q++)
		{
			if (y[q] >= 10000)
			{
				y[q + 1] += y[q] / 10000;
				y[q] %= 10000;
			}
		}
		ylen += 5;
		while (ylen >= 0 && y[ylen] == 0)    ylen--;
		while (xlen >= 0 && x[xlen] == 0)    xlen--;
		if (!head)
		{
			ans = ans + to_string(p);
			head = 1;
		}
		else
		{
			string str = to_string(p);
			for (int w = 0; w < 4 - str.length(); w++)
				ans.push_back('0');
			ans = ans + str;
		}
	}
	ans.insert(len1, ".");
	return ans;
}

//Number輸出答案
string Number::printAns()
{
	if (haveBlank)
	{
		errorTyep = 4;
	}

	if (errorTyep > 0)
	{
		switch (errorTyep)
		{
		case 1:
			return "Error (1) : 非正整數階乘";
			break;
		case 2:
			return "Error (2) : 非整數或0.5次方";
			break;
		case 3:
			return "Error (3) : 除數不可為0";
			break;
		case 4:
			return "Error (4) : 算式不可有空格";
			break;
		case 5:
			return "Error (5) : 算式中包含未知運算元或其他符號";
			break;
		default:
			break;
		}
	}
	string s = "0.0000000000";
	Fraction temp;
	imagToReal(fracAns, temp);

	if (fracAns.comSign && get10Dec(temp) != s)
		return getCom();
	else if (fracAns.denominator != "1" && fracAns.denominator != "0") //分數
	{
		string test = getDec();
		s.assign(100, '0');
		size_t index = test.find('.');
		//if (test.substr(index + 1) == s)//小數點後皆為零 
		//{
		//	return getInt();
		//}
		return test;
	}

	else //整數
		if (fracAns.isInt)
		{
			return getInt();
		}
		else
		{
			return getDec();
		}
		

}
//default constructor
Number::Number() :Number("0") {}
Number::Number(string input)
{
	setInput(input);
	computInput();
}
Number::~Number() {}

//取整
string Number::getInt()
{
	if (errorTyep > 0)
		return printAns();
	string ret;
	ret = get100Dec(fracAns);
	if (fracAns.sign)
		ret.insert(ret.begin(), '-');
	ret.assign(ret, 0, ret.size() - 101);//去掉小數點
	if (ret == "-0")
		return "0";
	return ret;
}
//取到小數後百位
string Number::getDec()
{
	if (errorTyep > 0)
		return printAns();
	string ret;
	ret = get100Dec(fracAns);
	if (fracAns.sign)
		ret.insert(ret.begin(), '-');
	string s = "-0.";
	s.insert(s.begin(), 100, '0');
	if (ret == s)
		ret.erase(ret.begin());
	return ret;
}
//虛數 不用
string Number::getCom()
{
	if (errorTyep > 0)
		return printAns();
	string s = "-0.0000000000";
	string ret1, ret2;
	if (fracAns.sign)
		ret1 += '-';
	else
		ret1 += ' ';
	ret1 += get10Dec(fracAns);
	Fraction temp;
	imagToReal(fracAns, temp);
	if (temp.sign)
		ret2 += '-';
	else
		ret2 += '+';
	ret2 += get10Dec(temp);
	if (ret1 == s)
		ret1.erase(ret1.begin());
	if (ret2 == s)
		ret2[0] = '+';
	return ret1 + " " + ret2 + "i";
}

void Number::assign() {}

void Number::print(ostream&)const {}


ostream& operator<<(ostream& outputStream, const Number& a)
{
	a.print(outputStream);
	return outputStream;
}

istream& operator>> (istream& inputStream, Number& a)
{
	string in;
	inputStream >> in;
	a.setInput(in);
	a.computInput();
	a.assign();
	return inputStream;
}


Fraction Number::getFrac()
{
	return fracAns;
}

Fraction Number::getReal()
{
	Fraction ret;
	ret.sign = fracAns.sign;
	ret.denominator = fracAns.denominator;
	ret.numerator = fracAns.numerator;
	return ret;
}


bool Number::getComSign()
{
	return fracAns.comSign;
}

void Number::setFrac(Fraction& f)
{
	fracAns = f;
}