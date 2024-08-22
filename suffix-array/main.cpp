#include "Header.h"
#include <iostream>
using namespace std; 

int main()
{
	std::string test = "suffixarraytest@";
	suffix_arr t; t.text = test; 
	t.build(); 
	for (int i = 0; i < t.text.size(); ++i)
		std::cout << t.text.substr(t.SA_index[i]) << " ";
}