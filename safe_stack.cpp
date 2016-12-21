// safe_stack.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <mutex>
#include <thread>
template<typename T>
class safe_stack {
private: 
	T * ptr;
	size_t size;
	size_t count;
	mutable std::mutex m;
public:
	safe_stack();
	safe_stack(safe_stack const & other);
	~safe_stack();
	auto operator= (safe_stack const & other)->safe_stack&;
	auto push(T const & obj)->void;
	auto pop()->void;
	auto top()->T&;
	auto count_()->size_t;
};

template<typename T>
auto copy(T* ptr, size_t size, size_t count) -> T* {
	T* buff = new T[size];
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
safe_stack<T>::safe_stack():ptr(nullptr), size(0), count(0), m() {}
template<typename T>
safe_stack<T>::safe_stack(safe_stack const & other) : ptr(other.ptr), size(other.size), count(other.count), m() {}
template<typename T>
safe_stack<T>::~safe_stack() {
	delete[] ptr;
}
template<typename T>
auto safe_stack<T>::operator=(safe_stack const & other)->safe_stack& {
	if (this != other) {
		std::lock(m, other.m);
		std::lock_guard<std::mutex> lk1(m, std::adopt_lock);
		std::lock_guard<std::mutex> lk2(other.m, std::adopt_lock);
		T * buff = copy(other.ptr, other.size, other.count);
		delete[] ptr;
		ptr = copy(other.ptr, other.size, other.count);
		size = other.size;
		count = other.count;
	}
	return *this;

}

template<typename T>
auto safe_stack<T>::push(T const & obj) -> void {
	std::lock_guard<std::mutex> lk(m);
	if (size == count) {
		size_t size_ = size * 2 + (count == 0);
		T * buff = copy(ptr, size_, count);
		delete[] ptr;
		ptr = copy(buff, size_, count);
		size = size_;
	}
	ptr[count] = obj;
	++count;
}

template<typename T>
auto safe_stack<T>::pop() -> void {
	std::lock_guard<std::mutex> lk(m);
	if (count == 0) {
		throw std::logic_error("Stack is empty!");
	}
	else {
		count--;
	}
}

template<typename T>
auto safe_stack<T>::top() -> T&{
	std::lock_guard<std::mutex> lk(m);
	if (count == 0) {
		throw ("Stack is empty!");
	}
	return ptr[count - 1];
}

template<typename T>
auto safe_stack<T>::count_() -> size_t {
	std::lock_guard<std::mutex> lk(m);
	return count;
}

void func() {
	safe_stack<int> t;
	t.push(1);
	for (int i = 1; i < 50; i++) {
		t.push(i);
		std::cout << "th1_push" << std::endl << t.top() << std::endl;
		t.pop();
		std::cout << "th1_pop" << std::endl << t.top() << std::endl;
	}
}

int main()
{
	std::thread (func).join();
	//std::thread (func).join();
	getchar();
    return 0;
}

