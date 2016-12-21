// queue.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
template<typename T>
class queue {
private :
	T * ptr;
	size_t first;
	size_t last;
	size_t size;
	size_t count;

public:
	queue();
	queue(queue const & other);
	~queue();
	auto operator =(queue const & other)->queue &;
	auto push(T const & obj) -> void;
	auto pop() -> void;
	auto first_()->T&;
	auto last_()->T&;
};

template<typename T>
auto copy(T* ptr, size_t size, size_t count)->T*{
	T* buff = new T[size];
	std::copy(ptr, ptr + count, buff);
	return buff;
}

template<typename T>
queue<T>::queue() : ptr(nullptr), first(0), size(0), count(0){}

template<typename T>
queue<T>::queue(queue const & other) : ptr(other.ptr), first(other.first), last(other.last), size(other.size), count(other.count) {}

template<typename T>
queue<T>::~queue() {
	delete[] ptr;
}

template<typename T>
auto queue<T>::operator=(queue const & other)->queue& {
	if (this != &other) {
		T * buff = copy(other.ptr, other.size, other.count);
		delete[] ptr;
		ptr = buff;
		first = other.first;
		last = other.last;
		size = other.size;
		count = other.count;
	}
	return *this;
}

template<typename T>
auto queue<T>::push(T const & obj)->void {
	if (count == size) {
		size_t size_ = size * 2 + (size == 0);
		T* buff = copy(ptr, size_, count);
		delete[] ptr;
		ptr = buff;
		size = size_;
	}
	ptr[count] = obj;
	last = count;
	++count;
}

template<typename T>
auto queue<T>::pop()->void {
	if (count == 0)
		throw std::logic_error("count = 0");
	++first;
}
template<typename T>
auto queue<T>::first_()->T&{
	return ptr[first];
}

template<typename T>
auto queue<T>::last_()->T& {
	return ptr[last];
}

int main()
{	
	queue<int> t;
	t.push(1);
	for (int i = 2; i < 50; i++) {
		t.push(i);
		std::cout << "th1_push" << std::endl << t.first_() << std::endl;
		t.pop();
		std::cout << "th1_pop" << std::endl << t.last_() << std::endl;
	}
	getchar();
	return 0;
}