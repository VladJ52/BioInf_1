// bioinf_8.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

string reverse(string t)
{
	string res;
	int n = t.length();
	for (int i = n - 1; i >= 0; i--)
		res += t[i];
	return res;
}


string suf(string a, int k)
{
	string res = "";
	for (int i = 1; i < a.length(); i++)
	{
		res += a[i];
	}
	return res;
}

string pref(string a, int k)
{
	string res = "";
	for (int i = 0; i < a.length() - 1; i++)
		res += a[i];
	return res;
}

vector<string> task1(string dna, int k) // строку на все подстроки
{
	vector<string> res;
	string temp = "";
	int j = 0;
	for (int i = 0; i < dna.length() - k +1; i++)
	{
		while (j < k)
		{
			temp += dna[i];
			j++;
			i++;
		}
		res.push_back(temp);
		j = 0;
		i -= k;
		temp = "";
	}
	return res;
}


string task2(vector<string> mas) // восстановить днк по пути
{
	string res = "";
	string temp = "";
	for (int i = 0; i < mas.size(); i++)
	{
		if (i == 0)
			res += mas[i];
		else
		{
			temp = mas[i];
			res += temp[temp.length() - 1];
		}
	}
	return res;
}

vector<string> task3(vector<string> matr)
{
	vector<string> res;
	int temp;
	int k = matr[0].length();
	for (int i = 0; i < matr.size(); i++)
	{
		for (int j = 0; j < matr.size(); j++)
		{
			if (i != j)
			{
				if (suf(matr[i], k) == pref(matr[j], k))
				{
					res.push_back(matr[i]);
					res.push_back(matr[j]);
				}
			}
		}
	}
	return res;	
}

bool findstr(string a, string b)
{
	bool flag = false;
	int temp;
	for (int i = 0; i < a.length() && !flag; i++)
	{
		temp = i;
		for (int j = 0; j < b.length(); j++)
		{
			if (a[i] == b[j])
			{
				i++;
			}
			else
				break;
			if (j == (b.length() - 1))
				flag = true;
		}
		i = temp;
	}
	return flag;
}

int cntindna(string a, string b)
{
	int res = 0;
	int len = b.length();
	string temp = "";
	for (int i = 0; i <= a.length() - len; i++)
	{
		for (int j = i; j < len + i; j++)
			temp += a[j];
		if (temp == b)
			res++;
		temp = "";
	}
	return res;
}

vector<string> task4(int k, string a)
{
	vector<string> res;
	vector<string> tops;
	vector<string> kmers;
	bool flag1 = true, flag2 = true;
	kmers = task1(a, k);
	string temp;
	for (int i = 0; i < kmers.size(); i++) // формирование неповторяющихся вершин
	{
		flag1 = flag2 = true;
		for (int j = 0; j < tops.size(); j++)
		{
			if (tops[j] == (suf(kmers[i], k)))
				flag1 = false;
			if (tops[j] == (pref(kmers[i], k)))
				flag2 = false;
		}
		if ((suf(kmers[i], k)) == (pref(kmers[i], k)))
			flag1 = flag2 = false;
		if (flag1)
			tops.push_back(suf(kmers[i], k));
		if (flag2)
			tops.push_back(pref(kmers[i], k));
	}
	string t,tt = "";
	int num;
	for (int i = 0; i < tops.size(); i++)
	{
		flag1 = false;
		for (int j = 0; j < tops.size(); j++)
		{
			if (i != j)
			{
				if (suf(tops[i], k-1) == pref(tops[j], k-1))
				{
					t = tops[j];
					tt = tops[i] + t[k-2];
					flag2 = findstr(a, tt);
					if (flag2 == true)
					{
						num = cntindna(a, tt);
						for (int k = 0; k < num; k++)
						{
							res.push_back(tops[i]);
							res.push_back(tops[j]);
							res.push_back("&&");
						}
						flag1 = true;
					}
				}
			}
		}
		if (flag1)
			res.pop_back();
	}
	return res;
}

int main()
{
	/*int k;
	string dna;
	vector<string> res;
	cin >> k;
	cin >> dna;
	res = task1(dna, k);
	for (int i = 0; i < res.size(); i++)
	{
		cout << res[i] << endl;
	}
    return 0;*/
	//------------------------------ task2
	//vector<string> matrix;
	//string temp;
	//string res;
	//while (!cin.eof())
	//{
	//	cin >> temp;
	//	matrix.push_back(temp);
	//}
	//matrix.pop_back();
	//res = task2(matrix);
	//cout << res;
	//return 0;
	//----------------------------- task3
	/*vector<string> matrix;
	vector<string> res1;
	string temp;
	while (!cin.eof())
	{
		cin >> temp;
		matrix.push_back(temp);
	}
	matrix.pop_back();
	res1 = task3(matrix);
	for (int i = 0; i < res1.size() - 1; i+=2)
	{
		cout << res1[i] << " -> " << res1[i + 1] << endl;
	}*/
	// --------------------------------- task4
	string a;
	int k;
	cin >> k;
	cin >> a;
	vector<string> res;
	res = task4(k, a);
	for (int i = 0; i < res.size() - 1; i+=2)
	{
		cout << res[i] << " -> " << res[i + 1];
		if (i < res.size() - 4)
		{
			while (res[i + 2] == "&&")
			{
				cout << ',' << res[i + 4];
				i += 3;
			}
		}
		cout << endl;
	}
	return 0;
}

