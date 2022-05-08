#ifndef UN_MAP_H
#define UN_MAP_H

#include <memory>
#include <functional>
#include "Hash.h"

template<typename K, typename T>
class Unordered_map
{
private:

	class Pair
	{
		K _key;
		T data;
		bool active = false;
	public:
		std::shared_ptr<Pair> next = nullptr;

		inline Pair() : next(nullptr) { data = T(); _key = K(); }
		inline Pair(K k, T d) : _key(k), data(d), next(nullptr) {}
		inline Pair(K k, T d, bool a) : _key(k), data(d), active(a), next(nullptr) {}
		inline Pair(K k, T d, Pair& p) : _key(k), data(d), next(p) { active = true; }

		inline K first() { return _key; }
		inline T& second() { return data; }
		inline bool isActive() { return active; }

	};

	class const_iterator
	{
		Pair* obj;
		Pair* bucket;
	public:
		const_iterator() = delete;
		inline const_iterator(std::shared_ptr<Pair> p) : obj(p), bucket(p) {}
		const_iterator(Pair* p, const size_t i);
		~const_iterator();

		auto& operator++();
		auto operator++(int);

		inline const T& operator*() const { return obj->second(); }
		inline const T* operator->() const { return *(obj->second()); }

		inline bool operator!=(const const_iterator& c2) const { return obj != c2.obj; }
		inline bool operator==(const const_iterator& c2) const { return obj == c2.obj; }


	};

	class iterator
	{
		Pair* obj;
		Pair* bucket;
	public:
		iterator() = delete;
		inline iterator(Pair* p) : obj(p), bucket(p) {}
		iterator(Pair* p, const size_t i);
		~iterator();

		auto& operator++();

		auto operator++(int);

		inline T& operator*() { return obj->second(); }

		inline T* operator->() { return *(obj->second()); }

		inline bool operator!=(const iterator& c2) const { return obj != c2.obj; }
		inline bool operator==(const iterator& c2) const { return obj == c2.obj; }
	};

	std::shared_ptr<Pair[]> array;
	size_t _size{ 8 };
	size_t _space_taken{ 0 };
	size_t collisions{ 0 };
	static double FILL_LIMIT;

	void resize();

public:
	Unordered_map();
	Unordered_map(size_t s);
	Unordered_map(size_t s, const std::function<T(const size_t i)>& f);
	~Unordered_map() = default;

	void insert(K k, const T& val);

	const_iterator cbegin() const { return const_iterator(array.get()); }
	const_iterator cend() const { return const_iterator(array.get(), _size); }

	iterator begin() { return iterator(array.get()); }
	iterator end() { return iterator(array.get(), _size); }

	inline size_t size() const { return _size; }
	inline size_t get_collisons() const { return collisions; }
	inline size_t get_number_of_elements() const { return _space_taken; }

	T& operator[](K k);

};




#include "Unordered_map.cpp"
#include "Iterator.cpp"
#include "Const_iterator.cpp"

#endif // UN_MAP_H
