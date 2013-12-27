#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>

#include <algorithm>

template<typename T>
class Vector {
public:
  Vector(): size_(0), capacity_(kInitialCapacity), data_(alloc(kInitialCapacity)) {}
  
  ~Vector() {
    free();
  }

  T& operator[] (size_t i) {
    return data_[i];
  }

  const T& operator[] (size_t i) const {
    return data_[i];
  }

  void push_back(const T& value) {
    if(size_ == capacity_)
      reserve(capacity_ * kExpansionCoef);

    new (data_+size_) T(value);
    size_++;
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

    T* data = alloc(capacity);
    for(size_t i = 0; i < size_; ++i) 
      new (data+i) T(data_[i]);

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

  T* alloc(size_t size) {
    return (T*)::operator new(sizeof(T) * size);
  }

  void free() {
    for(size_t i = 0; i < size_; ++i) 
      (data_+i)->~T();

    ::operator delete(data_);
    data_ = nullptr;
  }

  size_t size_;
  size_t capacity_;
  T* data_;
};

#endif