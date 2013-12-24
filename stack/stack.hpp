#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>

#include <array>

template<typename T, size_t MaxSize = 100, template<typename, size_t> class Container = std::array>
class Stack {
public:
	Stack(): container_(), index_(-1) {}
	~Stack() {}

	void push(const T& value) {
		container_[++index_] = value;
	}

	void pop() {
		if(index_ >= 0)
			index_--;
	}

	T& top() {
		return container_[index_];
	}

	bool empty() {
		return index_ < 0;
	}
	
	size_t size() {
		if(index_ < 0)
			return 0;

		return (size_t)index_+1;
	}

private:
	static const size_t kMaxSize = MaxSize;
	Container<T, kMaxSize> container_;
	int index_;

	Stack(const Stack& other);
	Stack& operator=(const Stack& other);
};

#endif