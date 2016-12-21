// stack.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class stack {
private:
	T * ptr;
	size_t size;
	size_t count;
public:
	stack();
	stack(stack const & other);
	~stack();
	auto operator = (stack const & other) -> stack&;
	auto push(T const & obj) -> void;
	auto pop()->T;
	auto count_()->size_t;
};

template<typename T>
auto copy(const T * ptr, size_t size, size_t count) -> T* {
	T * buff = new T[size];
	try {
		std::copy(ptr, ptr + count, buff);
	}
	catch (...) {
		delete[] buff;
		throw;
	}
	return buff;
}


template<typename T>
stack<T>::stack() : ptr(nullptr), size(0), count(0) {}

template<typename T>
stack<T>::stack(stack const & other) : size(other.size), count(other.count), ptr(copy(other.ptr, other.size, other.count)) {}

template<typename T>
stack<T>::~stack() {
	delete[] ptr;
}

template<typename T>
auto stack<T>::operator=(stack const & other)->stack& {
	if (this != other) {
		T * buff = copy(other.ptr, other.size, other.count);
		delete[] ptr;
		ptr = buff;
		size = other.size;
		count = other.count;
	}
	return *this;
}

template<typename T>
auto stack<T>::pop()->T {
	if (count == 0)
		throw;
	return ptr[--count];
}

template<typename T>
auto stack<T>::push(T const & obj) -> void {
	if (size == count) {
		size = size * 2 + (size == 0);
		T * buff = copy(ptr, size, count);
		delete[] ptr;
		ptr = copy(buff, size, count);
	}
	ptr[count] = obj;
	++count;
}
template<typename T>
auto stack<T>::count_()->size_t {
	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	stack<int> t;
	t.push(5);
	t.push(5);
	t.pop();
	std::cout << t.count_();
	getchar();
    return 0;
}