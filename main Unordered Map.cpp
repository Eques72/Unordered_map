#include <iostream>
#include <string>

#include "Unordered_map.h"

//Examples of usage of the unordered associative container based on hash function
// - adding new key-data element, 
// - search of the element by given key ([] operator), 
// - Iteration through map elements 

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	//////////////////////////////////////////
	// EXAMPLES
	//////////////////////////////////////////

	std::cout << "\n ///////////// Map: INT key and DOUBLE data, collisions and [] access ////////////////\n";
	Unordered_map<int, double> m1(10);
	m1.insert(14, 53.33);
	for (int q{ 0 }; q < 5; q++)
	{
		m1.insert(q, 1 + q * 13);
	}
	for (size_t q{ 0 }; q < 5; q++)
	{
		std::cout << q << " " << m1[q] << std::endl;;
	}
	std::cout << 14 << " " << m1[14] << std::endl;;
	std::cout << "Size, elements, collisions: " << m1.size() << " " << m1.get_number_of_elements() << "  " << m1.get_collisons() << std::endl;
	std::cout << "All elements: \n";
	for (auto w : m1)
	{
		std::cout << w << std::endl;
	}

	std::cout << "\n ////////// Map creation with lambda //////////////\n";
	Unordered_map<int, double> m2(13, [](const size_t i) { return i * 2.55; });
	for (auto w : m2)
	{
		std::cout << w << std::endl;
	}

	std::cout << "\n ////////// Map: key CHAR and STRING data //////////////\n";
	Unordered_map<char, std::string> m3(18);
	for (size_t q{ 0 }; q < 20; q++)
	{
		char a = 'a' + q;
		std::string b = std::to_string('z' - q) + a + std::to_string(q + 'a');
		m3.insert(a, b);
	}
	for (auto w : m3)
	{
		std::cout << w << std::endl;
	}

	std::cout << "\n ////////// Map: key CHAR[] and INT  data //////////////\n";
	Unordered_map<char*, int> mChar;
	for (size_t q{ 0 }; q < 10; q++)
	{
		char t[] = { 'a' + q, q , 'a' + q, 'a' + q * 2 };
		mChar.insert(t, 5);
	}
	for (auto w : mChar)
	{
		std::cout << w << std::endl;
	}

	std::cout << "\n ////////// Map: key STRING and DOUBLE data //////////////\n";
	Unordered_map<std::string, double> mS;
	for (size_t q{ 0 }; q < 43; q++)
	{
		char a = 'a' + q;
		std::string b = std::to_string('z' - q) + a;
		mS.insert(b, q * 3.22 + 4.44);
	}
	for (auto w : mS)
	{
		std::cout << w << std::endl;
	}

	return 0;

}
