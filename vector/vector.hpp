#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>

template<typename T>
class Vector {
public:
  Vector(): size_(0), capacity_(kInitialCapacity), data_(new T[kInitialCapacity]) {}
  
  ~Vector() {
    free();
  }

  T& operator[] (size_t i) {
    return data_[i];
  }

  const T& operator[] (size_t i) const {
    return data_[i];
  }

  void push_back(T value) {
    if(size_ == capacity_)
      reserve(capacity_ * kExpansionCoef);

    data_[size_++] = value;
  }

  void resize(size_t size) {
    if(size == size_)
      return;

    if(size < size_) {
      size_ = size;
      return;
    }

    reserve(size);
    size_ = size;
  }

  void reserve(size_t capacity) {
    if(capacity <= capacity_)
      return;

    T* data = new T[capacity];
    for(size_t i = 0; i < size_; ++i) 
      data[i] = data_[i];

    free();
    capacity_ = capacity;
    data_ = data;
  }

  size_t size() { return size_; }

private:
  static const size_t kExpansionCoef = 2;
  static const size_t kInitialCapacity = 8;
  
  Vector(const Vector& other);
  Vector& operator=(const Vector& other);

  void free() {
    delete [] data_;
    data_ = nullptr;
  }

  size_t size_;
  size_t capacity_;
  T* data_;
};

#endif