# Unordered_map
Implementation of associative container template based on hash function. 
Creating this project help me to better understand how smart pointers and dynamic memory management should work.

### Efficiency
Less efficient than template from standard library. 

## Examples
~~~C++ 
Unordered_map<int, double> m1(10);
	m1.insert(14, 53.33);
~~~
~~~C++ 
Unordered_map<int, double> m2(13, [](const size_t i) { return i * 2.55; });

	for (auto w : m2)
		std::cout << w << std::endl;
~~~
#### Project created for learning purposes
