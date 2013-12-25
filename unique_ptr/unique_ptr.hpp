#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP 

#include <cstdio>

#include <utility>

template<typename T>
struct default_deleter {
  void operator() (T* pointer) {
    if(pointer == NULL)
      return;

    delete pointer;
    pointer = NULL;
  }
};

template<typename T>
struct array_deleter {
  void operator() (T* pointer) {
    if(pointer == NULL) 
      return;

    delete [] pointer;
    pointer = NULL;
  }
};

template<typename T>
struct unique_ptr_ref {
    T* pointer_;
    unique_ptr_ref (T* pointer = NULL) : pointer_(pointer) {}
};

template<typename T, typename Deleter = default_deleter<T> >
class unique_ptr {
public:
  explicit unique_ptr(T* pointer = NULL): pointer_(pointer) {}
  ~unique_ptr() { reset(NULL); };

  unique_ptr(unique_ptr& other): pointer_(other.pointer_) {
    other.pointer_ = NULL;
  }

  unique_ptr(unique_ptr_ref<T> ref): pointer_(ref.pointer_) {
    ref.pointer_ = NULL;
  }

  unique_ptr<T>& operator=(unique_ptr<T>& other) {
    unique_ptr<T> temp(other);
    temp.swap(*this);
    return *this;
  }

  void swap(unique_ptr<T>& other) {
    std::swap(this->pointer_, other.pointer_);
  }

  operator unique_ptr_ref<T> () {
    unique_ptr_ref<T> ref;

    ref.pointer_ = pointer_;
    pointer_ = NULL;
    
    return ref;
  }

  void reset(T* pointer) {
    delete_(pointer_);
    pointer_ = pointer;
  }

  T& operator*() const {
    return *pointer_;
  }

  T* operator->() const {
    return pointer_;
  }
private:
  T* pointer_;
  Deleter delete_;
};

#endif