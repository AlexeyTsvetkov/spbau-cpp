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

template<typename T, typename D>
struct unique_ptr_ref {
    T* pointer_;
    D deleter_;
};

template<typename T, typename D = default_deleter<T> >
class unique_ptr {
public:
  explicit unique_ptr(T* pointer = NULL, D deleter = D()): pointer_(pointer), deleter_(deleter) {}
  ~unique_ptr() { reset(NULL); };

  unique_ptr(unique_ptr& other): pointer_(other.pointer_), deleter_(other.deleter_) {
    other.pointer_ = NULL;
  }

  unique_ptr(unique_ptr_ref<T, D> ref): pointer_(ref.pointer_), deleter_(ref.deleter_) {
    ref.pointer_ = NULL;
  }

  unique_ptr<T, D>& operator=(unique_ptr<T, D>& other) {
    unique_ptr<T, D> temp(other);
    temp.swap(*this);
    return *this;
  }

  void swap(unique_ptr<T, D>& other) {
    std::swap(this->pointer_, other.pointer_);
    this->deleter_ = other.deleter_;
  }

  operator unique_ptr_ref<T, D> () {
    unique_ptr_ref<T, D> ref;
    ref.pointer_ = pointer_;
    ref.deleter_ = deleter_;
    pointer_ = NULL;
    
    return ref;
  }

  void reset(T* pointer) {
    deleter_(pointer_);
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
  D deleter_;
};

#endif