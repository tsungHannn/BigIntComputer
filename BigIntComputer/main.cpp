#include "Number.h"
using namespace std;
int main()
{
	vector<Integer> ints;
	vector<DEcimal> decs;
	vector<Complex> coms;

	cout << endl << "  大數計算機指令說明 : 可輸入任意不含空格之算式 ( '^'為次方運算、 '!'為階乘運算)" << endl << endl;;
	cout << "  變數宣告：   set(int / dec) 變數名稱   or   Set(int / dec) 變數名稱 = 運算式" << endl << endl;
	cout << "  其他指令：   print 變數   or   變數       顯示變數當前的值，如未指派則defalut值為0" << endl << endl;
	cout << "               assign 變數1 << 變數2   or   assign 變數 << 任意運算式" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	while (1)
	{
		string in, order;
		getline(cin, in);  /// i am a boy  cin >> 1 2 3 4   in = "i am a boy" ss >> 1 2 3 4 
		istringstream ss(in);	//一種型態  可用在string轉int 或int轉string
		
		while (ss >> order)	//輸入命令 ------------ex:  set int A = 5
		{
			if (order == "Set"||order=="set")
			{
				string type, name, temp;
				int t = 0;
				bool exist = false;
				ss >> type;
				if (type == "Int" || type == "int")
				{
					t = 1;
				}	
				else if (type == "Dec" || type == "dec")
				{
					t = 2;
				}
				else if (type == "Com" || type == "com")
				{
					t = 3;
				}
				//-----------order: set    t: 1
				ss >> name;	//名稱------------A
				if (ss >> temp)	//如果有再輸入東西 ------------temp: =
				{
					Integer i;
					DEcimal d;
					Complex c;
					ss >> temp;	//-----temp: 5
					switch (t)	//依照型態進行設定
					{
					case 1:
						i.name = name;
						i.setInput(temp);
						i.computInput();
						i.assign();
						ints.push_back(i);
						exist = false;
						for (int k = 0; k < Number::var.size(); k++)
						{
							if (i.name == Number::var[k])
							{
								Number::varAns[k] = i.getAns();
								exist = true;
								break;
							}
						}
						if (!exist)
						{
							Number::var.push_back(i.name);
							Number::varAns.push_back(i.getAns());
						}
						break;
					case 2:
						d.name = name;
						d.setInput(temp);
						d.computInput();
						d.assign();
						decs.push_back(d);
						exist = false;
						for (int k = 0; k < Number::var.size(); k++)
						{
							if (d.name == Number::var[k])
							{
								Number::varAns[k] = d.getAns();
								exist = true;
								break;
							}
						}
						if (!exist)
						{
							Number::var.push_back(d.name);
							Number::varAns.push_back(d.getAns());
						}
						break;
					case 3:
						c.name = name;
						c.setInput(temp);
						c.computInput();
						c.assign();
						coms.push_back(c);
						break;
					default:
						break;
					}
				}
				else  //沒有輸入東西(只有宣告一個東西)--------ex: set int A
				{
					if (t == 1)	//依照型態進行設定
					{
						Integer newI;
						newI.name = name;
						ints.push_back(newI);
						exist = false;
						for (int k = 0; k < Number::var.size(); k++)
						{
							if (newI.name == Number::var[k])
							{
								Number::varAns[k] = newI.getAns();
								exist = true;
								break;
							}
						}
						if (!exist)
						{
							Number::var.push_back(newI.name);
							Number::varAns.push_back(newI.getAns());
						}
					}
					else if (t == 2)
					{
						DEcimal newD;
						newD.name = name;
						decs.push_back(newD);
						exist = false;
						for (int k = 0; k < Number::var.size(); k++)
						{
							if (newD.name == Number::var[k])
							{
								Number::varAns[k] = newD.getAns();
								exist = true;
								break;
							}
						}
						if (!exist)
						{
							Number::var.push_back(newD.name);
							Number::varAns.push_back(newD.getAns());
						}
					}
					else if (t == 3)
					{
						Complex newC;
						newC.name = name;
						coms.push_back(newC);
					}
				}
			}
			else if (order == "Print" || order == "print")
			{
				string name;
				ss >> name;	//輸入要print的名稱
				bool found = false;
				//依照名稱來輸出
				for (int i = 0; i < ints.size() && !found; i++)
				{
					if (ints[i].name == name)
					{
						cout << endl << ints[i] << endl;
						cout << "=============================================================================" << endl;
						found = true;
					}
				}
				for (int i = 0; i < decs.size() && !found; i++)
				{
					if (decs[i].name == name)
					{
						cout << endl << decs[i] << endl;
						cout << "=============================================================================" << endl;
						found = true;
					}
				}
				for (int i = 0; i < coms.size() && !found; i++)
				{
					if (coms[i].name == name)
					{
						cout << endl << coms[i] << endl;
						cout << "=============================================================================" << endl;
						found = true;
					}
				}
				if (!found)
				{
					cout << "Not found." << endl;
				}
				
			}
			else if (order == "Assign" || order == "assign")
			{
				//name1 = name2  or  name1 << expression
				string name1, name2, temp;
				ss >> name1 >> temp >> name2;
				if (temp == "=")	//name1 = name2
				{
					bool found1, found2;
					int index1, index2, type1, type2;
					found1 = found2 = false;
					for (int i = 0; i < ints.size() && (!found1||!found2); i++)
					{
						if (ints[i].name == name1 && !found1)
						{
							index1 = i;
							type1 = 1;
							found1 = true;
						}
						if (ints[i].name == name2 && !found2)
						{
							index2 = i;
							type2 = 1;
							found2 = true;
						}
					}
					for (int i = 0; i < decs.size() && (!found1 || !found2); i++)
					{
						if (decs[i].name == name1 && !found1)
						{
							index1 = i;
							type1 = 2;
							found1 = true;
						}
						if (decs[i].name == name2 && !found2)
						{
							index2 = i;
							type2 = 2;
							found2 = true;
						}
					}
					for (int i = 0; i < coms.size() && (!found1 || !found2); i++)
					{
						if (coms[i].name == name1 && !found1)
						{
							index1 = i;
							type1 = 3;
							found1 = true;
						}
						if (coms[i].name == name2 && !found2)
						{
							index2 = i;
							type2 = 3;
							found2 = true;
						}
					}
					if (!found1 || !found2)
						cout << "Not found." << endl;
					else
					{
						if (type1 == 1)
						{
							if (type2 == 1)
							{
								ints[index1] = ints[index2];
								for (int k = 0; k < Number::var.size(); k++)
								{
									if (ints[index1].name == Number::var[k])
									{
										Number::varAns[k] = ints[index1].getAns();
										break;
									}
								}
							}
							else if (type2 == 2)
							{
								ints[index1] = decs[index2];
								for (int k = 0; k < Number::var.size(); k++)
								{
									if (ints[index1].name == Number::var[k])
									{
										Number::varAns[k] = ints[index1].getAns();
										break;
									}
								}
							}
								
							else if (type2 == 3)
								ints[index1] = coms[index2];
						}
						else if (type1 == 2)
						{
							if (type2 == 1)
							{
								decs[index1] = ints[index2];
								for (int k = 0; k < Number::var.size(); k++)
								{
									if (decs[index1].name == Number::var[k])
									{
										Number::varAns[k] = decs[index1].getAns();
										break;
									}
								}
							}
							else if (type2 == 2)
							{
								decs[index1] = decs[index2];
								for (int k = 0; k < Number::var.size(); k++)
								{
									if (decs[index1].name == Number::var[k])
									{
										Number::varAns[k] = decs[index1].getAns();
										break;
									}
								}
							}
							else if (type2 == 3)
								decs[index1] = coms[index2];
						}
						else if (type1 == 3)
						{
							if (type2 == 1)
								coms[index1] = ints[index2];
							else if (type2 == 2)
								coms[index1] = decs[index2];
							else if (type2 == 3)
								coms[index1] = coms[index2];
						}
					}
				}
				//name1 << name2  (name << expression)	
				else if (temp == "<<")
				{
					bool found = false;
					for (int i = 0; i < ints.size() && !found; i++)
					{
						if (ints[i].name == name1)
						{
							ints[i].setInput(name2);
							ints[i].computInput();
							ints[i].assign();
							found = true;
							for (int k = 0; k < Number::var.size(); k++)
							{
								if (ints[i].name == Number::var[k])
								{
									Number::varAns[k] = ints[i].getAns();
									break;
								}
							}
						}
					}
					for (int i = 0; i < decs.size() && !found; i++)
					{
						if (decs[i].name == name1)
						{
							decs[i].setInput(name2);
							decs[i].computInput();
							decs[i].assign();
							found = true;
							for (int k = 0; k < Number::var.size(); k++)
							{
								if (decs[i].name == Number::var[k])
								{
									Number::varAns[k] = decs[i].getAns();
									break;
								}
							}
						}
					}
					for (int i = 0; i < coms.size() && !found; i++)
					{
						if (coms[i].name == name1)
						{
							coms[i].setInput(name2);
							coms[i].computInput();
							coms[i].assign();
							found = true;
						}
					}
					if (!found)
						cout << "Not found." << endl;
				}
			}
			//pow 名稱 , 名稱       pow 名稱 ^ 運算式
			else if (order == "Pow" || order == "pow") //Pow a , b  or Pow a ^ b
			{
				Complex out;
				string name1, name2, temp;
				ss >> name1 >> temp >> name2;
				if (temp == ",")
				{
					bool found1, found2;
					int index1, index2, type1, type2;
					found1 = found2 = false;
					for (int i = 0; i < ints.size() && (!found1 || !found2); i++)
					{
						if (ints[i].name == name1 && !found1)
						{
							index1 = i;
							type1 = 1;
							found1 = true;
						}
						if (ints[i].name == name2 && !found2)
						{
							index2 = i;
							type2 = 1;
							found2 = true;
						}
					}
					for (int i = 0; i < decs.size() && (!found1 || !found2); i++)
					{
						if (decs[i].name == name1 && !found1)
						{
							index1 = i;
							type1 = 2;
							found1 = true;
						}
						if (decs[i].name == name2 && !found2)
						{
							index2 = i;
							type2 = 2;
							found2 = true;
						}
					}
					for (int i = 0; i < coms.size() && (!found1 || !found2); i++)
					{
						if (coms[i].name == name1 && !found1)
						{
							index1 = i;
							type1 = 3;
							found1 = true;
						}
						if (coms[i].name == name2 && !found2)
						{
							index2 = i;
							type2 = 3;
							found2 = true;
						}
					}
					if (!found1 || !found2)
						cout << "Not found." << endl;
					else
					{
						if (type1 == 1)
						{
							if (type2 == 1)
								out = Power(ints[index1], ints[index2]);
							else if (type2 == 2)
								out = Power(ints[index1] , decs[index2]);
							else if (type2 == 3)
								out = Power(ints[index1] , coms[index2]);
						}
						else if (type1 == 2)
						{
							if (type2 == 1)
								out = Power(decs[index1], ints[index2]);
							else if (type2 == 2)
								out = Power(decs[index1], decs[index2]);
							else if (type2 == 3)
								out = Power(decs[index1], coms[index2]);
						}
						else if (type1 == 3)
						{
							if (type2 == 1)
								out = Power(coms[index1], ints[index2]);
							else if (type2 == 2)
								out = Power(coms[index1], decs[index2]);
							else if (type2 == 3)
								out = Power(coms[index1], coms[index2]);
						}
						cout << endl << out << endl;
						cout << "=============================================================================" << endl;
					}
				}
				// pow 名稱 , 運算式
				else if (temp == "^")
				{
					bool found = false;
					for (int i = 0; i < ints.size() && !found; i++)
					{
						if (ints[i].name == name1)
						{
							out = Power(ints[i], name2);
							found = true;
						}
					}
					for (int i = 0; i < decs.size() && !found; i++)
					{
						if (decs[i].name == name1)
						{
							out = Power(decs[i], name2);
							found = true;
						}
					}
					for (int i = 0; i < coms.size() && !found; i++)
					{
						if (coms[i].name == name1)
						{
							out = Power(coms[i], name2);
							found = true;
						}
					}
					if (!found)
						cout << "Not found." << endl;
					else
					{
						cout << endl << out << endl;
						cout << "=============================================================================" << endl;
					}
				}
			}
			//階乘
			else if (order == "Fac" || order == "fac")// Fac a  or  Fac << number
			{
				string name, temp;
				ss >> name;
				Integer integer;
				if (ss >> temp)	//Fac << 運算式
				{
					integer = Factorial(temp);
					cout << endl << integer << endl;
					cout << "=============================================================================" << endl;
				}
				else
				{
					bool found = false;
					for (int i = 0; i < ints.size() && !found; i++)
					{
						if (ints[i].name == name)
						{
							integer = Factorial(ints[i]);
							found = true;
						}
					}
					for (int i = 0; i < decs.size() && !found; i++)
					{
						if (decs[i].name == name)
						{
							integer = Factorial(decs[i]);
							found = true;
						}
					}
					for (int i = 0; i < coms.size() && !found; i++)
					{
						if (coms[i].name == name)
						{
							integer = Factorial(coms[i]);
							found = true;
						}
					}
					if (!found)
						cout << "Not found." << endl;
					else
					{
						cout << endl << integer << endl;
						cout << "=============================================================================" << endl;
					}
				}
			}
			else //不含空格的任意運算式(直接輸出結果或錯誤訊息)
			{
				Number k(order);
				cout << endl << k.printAns() << endl;
				cout << "=============================================================================" << endl;
			}
		}
		

		

		/*
		vector<Number*> nums;
		Complex c,c1;// ("3+2i");
		DEcimal b,b1;// ("5.5+0.4");
		Integer a,a1;// ("2*3");
		Number* ra = &a;
		Number *rb = &b;
		Number* rc = &c;
		cin >> a >> b >> c;
		a = b + c + a;
		cout << a << endl;
		cout << "===================\n";
		b = Power(a, b) + c;
		cout << *rb << endl;
		cout << "===================\n";
		c = Factorial(b);
		cout << *rc << endl;
		cout << "===================\n";
		a = Power(a, c);
		cout << *ra << endl;
		cout << "===================\n";
		a = Factorial(a);
		cout << *ra << endl;
		cout << "===================\n";
		c = Power(b, c);
		cout << *rc << endl;
		cout << "===================\n";
		c = Factorial(b);
		cout << *rc << endl;
		cout << "===================\n";*/

	}
	return 0;
}