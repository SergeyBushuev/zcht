// optional.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

template<typename T>
class optional {
private:
	T* ptr;
public:
	optional() : ptr(nullptr) {}
	optional(T* obj) : ptr(obj) {}
	optional(optional const & other) : ptr(other.ptr) {}
	optional(optional && other) : ptr(other.ptr) {
		other.ptr = nullptr;
	}
	~optional() {
		delete ptr;
	}
	auto operator=(optional const & other) -> optional& {
		if (this != other) {
			ptr = other.ptr;
		}
		return *this;
	}
	auto operator=(optional && other)->optional&{
		if (this != other) {
			delete ptr;
			ptr = other.ptr;
			other.ptr = nullptr;
		}
		return *this;
	}
	auto value()->T& {
		return *ptr;
	}
	auto reset()->void {
		ptr = nullptr;
	}
	auto swap(optional const & other)->void {
		std::swap(ptr, other.ptr);
	}
};

int main()
{
	optional<int> a(new int(1));

    return 0;
}

