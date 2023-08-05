#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>
#include <vector>
#include "Sorting.h"
#include "Stack.h"

using namespace std;

string removeDuplicates(string S)
{
	Stack<char> rm;
	for (int i = S.length() - 1; i >= 0; i--)
	{
		if (rm.size() == 0)
		{
			rm.push(S[i]);
		}
		else
		{
			if (rm.top() == S[i])
			{
				rm.pop();
			}
			else
			{
				rm.push(S[i]);
			}
		}
	}
	stringstream rm_str;
	int rm_sz = rm.size();
	if (rm_sz == 0) return ("Empty String");
	for (int i = 0; i < rm_sz; i++)
	{
		rm_str << rm.pop();
	}
	return rm_str.str();
}
bool isValidParentheses(string s) {
	Stack<char> brackets;
	for (int i = 0; i < s.length(); i++)
	{
		if (brackets.empty())
		{
			brackets.push(s[i]);
		}
		else
		{
			if ((brackets.top() == '(' && s[i] == ')') || (brackets.top() == '[' && s[i] == ']') || (brackets.top() == '{' && s[i] == '}'))
			{
				brackets.pop();
			}
			else
			{
				brackets.push(s[i]);
			}
		}
	}
	if (brackets.empty()) return true;
	else return false;
}
vector<int> nextGreater(vector<int>& arr)
{
	Stack<int> stk;
	vector<int> result(arr.size());
	for (int i = arr.size() - 1; i >= 0; i--)
	{
		if (stk.empty() || stk.top() <= arr[i])
		{
			result[i] = -1;
		}
		else
		{
			result[i] = stk.top();
		}	
		stk.push(arr[i]);
	}
	return result;
}


int main()
{
	int arr[] = { 10, 9, 8 , 7 , 6, 5, 4, 3, 2, 1 };
	Sorting<int>::selectionSort(&arr[0], &arr[10]);
	return 0;
}