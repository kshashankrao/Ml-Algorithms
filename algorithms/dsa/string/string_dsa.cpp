#include "string_dsa.h"

std::string string_dsa::reverse_string(std::string str)
{
	std::cout << "Original string: " << str << std::endl;
	std::string out;
	std::stack<char> stk;
	for (int i = 0; i < str.length(); i++)
	{
		stk.push(str[i]);
	}

	int N = stk.size();
	for (int i = 0; i < N; i++)
	{
		out += stk.top();
		stk.pop();
	}

	std::cout << "Reverse string: " << out << std::endl;
	return out;
}
