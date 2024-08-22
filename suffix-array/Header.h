#pragma once
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
using std::vector; 
class suffix_arr
{
public: 
	std::string text; 
	vector<int> SA_index; 
	void build()
	{
		int n = text.size(); 
		SA_index.resize(n); 
		std::iota(SA_index.begin(), SA_index.end(), 0); 
		std::sort(SA_index.begin(), SA_index.end(), [this](int a, int b) { return text[a] < text[b];  }); 
		vector<int> primary_key(n); int value = 1; primary_key[SA_index[0]] = 1; 
		vector<bool> mark(n, 0); mark[0] = true; 

		for (int i = 1; i < n; ++i)
		{
			if (text[SA_index[i]] > text[SA_index[i - 1]])
			{
				++value;
				mark[i] = false;
			}
			else mark[i] = true; 
			primary_key[SA_index[i]] = value;
		}
		vector<int> temp_SA_index;
		int k = 1;
		
		while (k < n)
		{
			temp_SA_index.resize(n);
			for (int i = 0; i < n; ++i)
				temp_SA_index[i] = (SA_index[i] + n - k) % n;
					

			std::stable_sort(temp_SA_index.begin(), temp_SA_index.end(), [primary_key](int a, int b) {return primary_key[a] < primary_key[b]; }); 
			SA_index = std::move(temp_SA_index); 
			for (int i = 1; i < n; ++i)
			{
				if (primary_key[(SA_index[i - 1] + k) % n] != primary_key[(SA_index[i] + k) % n])
					mark[i] = true; 
			}
			int nkey = 0; 
			for (int i = 0; i < n; ++i)
			{
				nkey += mark[i]; 
				primary_key[SA_index[i]] = nkey - 1;
			}
			if (nkey == n) break; 
			k *= 2; 
		}
		
	}
}; 