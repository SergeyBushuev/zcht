// safe_queue.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <mutex>
#include <thread>

template<typename T>
class safe_queue {
private:
	T * ptr;
	size_t size;
	size_t count;
	size_t first;
	size_t last;
	std::mutex m;
public:
	safe_queue();
	safe_queue(safe_queue const & other);
	~safe_queue();
	auto operator=(safe_queue const & other) -> safe_queue&;
	auto push(T const & obj) -> void;
	auto pop() -> void;
	auto first_()->T&;
	auto last_()->T&;
};

template<typename T>
auto copy(T* ptr, size_t size, size_t count) -> T* {
	T* buff = new T[size];
	std::copy(ptr, ptr + count, buff);
	return buff;
}

template<typename T>
safe_queue<T>::safe_queue() : ptr(nullptr), size(0), count(0), first(0), m() {};

template<typename T>
safe_queue<T>::safe_queue(safe_queue const & other) : ptr(other.ptr), size(other.size), count(other.count), first(other.first), last(other.last), m(other.m) {};

template<typename T>
safe_queue<T>::~safe_queue() {
	std::lock_guard<std::mutex> lk(m);
	delete[] ptr;
}

template<typename T>
auto safe_queue<T>::operator=(safe_queue const & other) -> safe_queue& {
	std::lock(m, other.m);
	std::lock_guard<std::mutex> lk1(m, std::adopt_lock);
	std::lock_guard<std::mutex> lk2(m, std::adopt_lock);
	if (this != &other) {
		T* buff = copy(other.ptr, other.size, other.count);
		delete[] ptr;
		ptr = buff;
		size = other.size;
		count = other.count;
		first = other.first;
		last = other.last;
		m = other.m;
	}
	return *this;
}

template<typename T>
auto safe_queue<T>::push(T const & obj) -> void {
	std::lock_guard<std::mutex> lk(m);
	if (size == count) {
		size_t size_ = size * 2 + (size == 0);
		T * buff = copy(ptr, size_, count);
		delete[] ptr;
		ptr = buff;
		size = size_;
	}
	ptr[count] = obj;
	last = count;
	if (count == 0)
		first = 0;
	++count;
}

template<typename T>
auto safe_queue<T>::pop() -> void {
	std::lock_guard<std::mutex> lk(m);
	if(count == 0)
		throw std::logic_error("count= 0");
	++first;
}

template<typename T>
auto safe_queue<T>::first_() -> T& {
	std::lock_guard<std::mutex> lk(m);
	return ptr[first];
}

template<typename T>
auto safe_queue<T>::last_()->T&{
	std::lock_guard<std::mutex> lk(m);
	return ptr[last];
}

void func() {
	safe_queue<int> t;
	t.push(1);
	for (int i = 1; i < 50; i++) {
		t.push(i);
		std::cout << "th1_push" << std::endl << t.first_() << std::endl;
		t.pop();
		std::cout << "th1_pop" << std::endl << t.last_() << std::endl;
	}
}

int main()
{
	std::thread(func).detach();
	std::thread(func).detach();
	getchar();
	return 0;
}

