#include <future>
#include <thread>
#include <queue>
#include <functional>
#include <atomic>
#include <queue>
#include <vector>
#include <iostream>

class thread_pool
{
private:
	std::atomic_bool done = false;
	std::vector<std::thread> threads;
	std::queue<std::function<void()>> worker_queue;

	void worker_thread() {
		while (!done.load()) {
			std::function<void()> task;
			if (!worker_queue.empty()) {
				worker_queue.pop();
				task();
			} else
				std::this_thread::yield();
		}
	}

public:
	~thread_pool() {
		done.store(true);
	}

	thread_pool() {
		int const count = std::thread::hardware_concurrency();
		try {
			for (auto i = 0; i < count; ++i) {
				threads.push_back(std::thread(&thread_pool::worker_thread, this));
			}
		}
		catch (...) {
			done.store(true);
		}
	}

	template<typename func>
	void submit(func f) {
		worker_queue.push(std::function<void()> (f));
	}

};

void task() {
	std::cout << "task is done" << std::endl;
}

int main() {
	thread_pool a;
	std::cout << "test";
	//a.submit(task);
	getchar();
	return 0;
}