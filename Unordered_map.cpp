#include "Unordered_map.h"

///////////					////////////
template<typename K, typename T>
double Unordered_map<K, T>::FILL_LIMIT = 0.75;
//////////						////////////


template<typename K, typename T>
Unordered_map<K, T>::Unordered_map() : _size(8)
{
	array = std::shared_ptr<Pair[]>(new Pair[_size]);
}

template<typename K, typename T>
Unordered_map<K, T>::Unordered_map(size_t s) :_size(s)
{
	array = std::shared_ptr<Pair[]>(new Pair[_size]);
}

template<typename K, typename T>
Unordered_map<K, T>::Unordered_map(size_t s, const std::function<T(const size_t i)>& f) : _size((size_t)(2 * s / FILL_LIMIT))
{
	array = std::unique_ptr<Pair[]>(new Pair[_size]);
	for (size_t i{ 0 }; i < s; i++)
		insert(i, f(i));
}


template<typename K, typename T>
void Unordered_map<K, T>::resize()
{
	if (_size == INT_MAX)
		return;

	collisions = 0;
	std::shared_ptr<Pair[]> old = array;
	size_t old_size = _size;

	_size = _size * 2;
	if (_size < 0)
		_size = INT_MAX;
	std::shared_ptr<Pair[]> tmp(new Pair[_size]);
	array = tmp;

	_space_taken = 0;
	for (size_t b{ 0 }; b < old_size; b++)
		if (old[b].isActive())
		{
			std::shared_ptr<Pair> ptr = std::make_shared<Pair>(old[b]);
			do
			{
				insert(ptr->first(), ptr->second());
				ptr = ptr->next;
			} while (ptr != nullptr);
		}
}


template<typename K, typename T>
T& Unordered_map<K, T>::operator[](K k)
{
	Hash H;
	int index = H.hash(k, _size);

	if (array[index].first() == k && array[index].isActive())
		return array[index].second();
	else if (array[index].isActive())
	{
		std::shared_ptr<Pair> ptr = std::make_shared<Pair>(array[index]);
		while (ptr->first() != k && ptr->next != nullptr)
			ptr = ptr->next;
		return ptr->second();
	}
	else
		return array[index].second();
}


template<typename K, typename T>
void Unordered_map<K, T>::insert(K k, const T& val)
{
	if ((double)(_space_taken + 1) >= FILL_LIMIT * _size)
		resize();

	Hash H;
	int index = H.hash(k, _size);

	if (!array[index].isActive())
		array[index] = Pair(k, val, true);
	else if (array[index].first() == k)
	{
		array[index] = Pair(k, val);
		--_space_taken;
	}
	else
	{
		std::shared_ptr<Pair> ptr = std::make_shared<Pair>(array[index]);
		array[index] = Pair(k, val, true);
		array[index].next = ptr;

		collisions++;
	}
	_space_taken++;
}

//Unordered_map<K, T>::
//template<typename K, typename T>