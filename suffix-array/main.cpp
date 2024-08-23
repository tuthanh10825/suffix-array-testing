#include "Header.h"
#include <iostream>
#include <random>
#include <chrono>
#include <cstdlib>
using namespace std; 

int main()
{
	std::string test; 
	std::random_device rd; 
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> unidist(0,25); 
	int n; std::cin >> n;
	for (int i = 0; i < n; ++i)
		test += (unidist(rng) + 'a'); 
	test.push_back('@'); 
	//std::cout << "string value: " << test << "\n"; 
	
	auto start = std::chrono::high_resolution_clock::now();
	suffix_arr t; t.text = test; 
	t.build();
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "Time used: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
	string prev; 
	string curr; 
	
	for (int i = 0; i < t.text.size(); ++i)
	{
		curr = t.text.substr(t.SA_index[i]); 
		try
		{
			if (prev > curr) throw("Wrong order.");
		}
		catch (const char* error)
		{
			std::cout << error << " "; 
			return -1; 
		}
		prev = curr; 
		//std::cout << t.text.substr(t.SA_index[i]) << " ";
	}
	return 0; 
}