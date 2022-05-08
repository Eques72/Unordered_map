#include "Unordered_map.h"

template<typename K, typename T>
Unordered_map<K, T>::const_iterator::const_iterator(Pair* p, const size_t i) : obj(p), bucket(p)
{
	for (size_t q{ 0 }; q < i; q++)
		++obj;
}

template<typename K, typename T>
Unordered_map<K, T>::const_iterator::~const_iterator()
{
	bucket = nullptr; obj = nullptr;
}

template<typename K, typename T>
auto& Unordered_map<K, T>::const_iterator::operator++()
{
	if (obj->next == nullptr)
		if (obj == bucket++)
			++obj;
		else
			obj = ++bucket;
	else
		obj = obj->next.get();

	return *this;
}

template<typename K, typename T>
auto Unordered_map<K, T>::const_iterator::operator++(int)
{
	auto old = this->obj;
	if (obj->next == nullptr)
		if (obj == bucket)
			this.obj++;
		else
			obj = ++bucket;
	else
		obj = obj->next;

	return const_iterator(old);
}


//Unordered_map<K, T>::iterator::
//template<typename K, typename T>