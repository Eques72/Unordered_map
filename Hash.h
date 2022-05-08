#ifndef HASH_H
#define HASH_H

#include <string>

class Hash
{
public:
	template<typename K>
	size_t hash(K& k, size_t s)
	{
		return k % s;
	}

	size_t hash(std::string& k, size_t s) // DJB Hash Function
	{
		size_t x = 5381;

		for (auto q : k)
			x = ((x << 5) + x) + (q);

		return x % s;
	}

	size_t hash(char* k, size_t s)
	{
		char x = *k;
		return x % s;
	}
};

#endif // HASH_H
