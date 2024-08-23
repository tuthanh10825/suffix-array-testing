#pragma once
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <iostream>
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
		std::sort(SA_index.begin(), SA_index.end(), [this ](int a, int b) { return text[a]  < text[b];  }); 
		
		
		vector<int> primary_key(n); int value = 0; primary_key[SA_index[0]] = 0; 
		vector<bool> mark(n, false); mark[0] = true; 

		for (int i = 1; i < n; ++i)
		{
			if (text[SA_index[i]] != text[SA_index[i - 1]])
			{
				++value;
				mark[i] = true;
			}
			else mark[i] = false; 
			primary_key[SA_index[i]] = value;
		}
		if (value == n - 1) return; 
		vector<int> temp_SA_index;
		int k = 1;
		
		while (k < n)
		{
			temp_SA_index.resize(n);
			for (int i = 0; i < n; ++i)
				temp_SA_index[i] = (SA_index[i] + n - k) % n;
					
			vector <int> cou(10000, 0);
			vector <int> temp_vector(n);
			for (int count = 1; count <= n; count *= 10000)
			{
				temp_vector.resize(n);
				std::fill(cou.begin(), cou.end(), 0);
				for (int i = 0; i < n; ++i)
					++cou[primary_key[temp_SA_index[i]] / count % 10000];

				for (int i = 1; i < 10000; ++i)
					cou[i] += cou[i - 1];

				for (int i = n - 1; i >= 0; --i)
				{
					temp_vector[--cou[(primary_key[temp_SA_index[i]] / count) % 10000]] = temp_SA_index[i];
				}
				temp_SA_index = std::move(temp_vector);
			}

			
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