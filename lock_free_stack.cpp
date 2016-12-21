// lock_free_stack.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <atomic>
#include <thread>
template<typename T>
class lock_free_stack {
private:
	struct Node {
		T data;
		Node* prev = nullptr;
		Node(const T& obj) : data(obj), prev(nullptr) {}
		Node(const T& obj, Node * ptr) : data(obj), prev(ptr) {}
	};

	void free_list(Node * node) {
		while (node)
		{
			auto buff = node->prev;
			delete node;
			node = buff;
		}
	}

	std::atomic<Node *> head = nullptr;
	std::atomic<Node *> to_delete = nullptr;
public:
	lock_free_stack() {}
	~lock_free_stack() {
		free_list(to_delete.load());
		free_list(head.load());
	}

	void push(const T & data) {
		Node * new_head = new Node(data, head.load());
		while (!head.compare_exchange_strong(new_head -> prev, new_head)) {}
	}

	 bool try_pop(T & data) {
		Node * old_head = head.load();
		if (old_head == nullptr) {
			return false;
		}
		while (old_head && !head.compare_exchange_strong(old_head, old_head->prev)) {}
		if (old_head == nullptr) {
			return false;
		}

		data = old_head->data;
		old_head->prev = to_delete.load();

		while (!to_delete.compare_exchange_strong(old_head->prev, old_head)) {}
		return true;
	}
};

void task() {
	int a;
	lock_free_stack<int> stack;
	for (int i = 0; i <= 10; i++) {
		stack.push(i);
		stack.try_pop(a);
		std::cout << a << std::endl;
	}
}

int main() {
	std::thread (task).join();
	std::thread (task).join();
	
	getchar();
}