#include <algorithm>
#include <cstddef>
#include <new>
#include <string>

class VectorException {
public:
  VectorException(const char *msg) : msg_(msg) {}
  const char *what() const throw() { return msg_.c_str(); }

private:
  std::string msg_;
};

template <typename T> class vector {
public:
  vector(size_t capacity) : capacity_(capacity), size_(0), data_(nullptr) {
    try {
      data_ = new T[capacity_];
    } catch (...) {
      throw VectorException("Failed to initialize new vector");
    }
  }

  vector() : vector(1) {}

  vector(const vector &other)
      : size_(other.size()), capacity_(other.capacity()) {
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
  }

  vector(std::initializer_list<T> init_list)
      : capacity_(init_list.size()), size_(init_list.size()),
        data_(new T[capacity_]) {
    std::copy(init_list.begin(), init_list.end(), data_);
  }

  ~vector() { delete[] data_; }

  size_t size() const { return size_; }
  size_t capacity() const { return capacity_; }

  void push_back(const T &value) {
    if (size_ >= capacity_) {
      grow_array();
    }
    data_[size_] = value;
    ++size_;
  }

  T pop_back() {
    if (size_ < 1) {
      delete[] data_;
      throw VectorException("Failed to pop empyt vector");
    }
    T return_value = data_[size_ - 1];
    data_[size_ - 1].~T();
    --size_;
    if ((size_ << 1) <= capacity_) {
      shrink_array();
    }
    return return_value;
  }

  void resize(size_t size) {
    try {
      capacity_ = size << 1;
      T *buffer = new T[capacity_];
      for (size_t i = 0; i < size_; ++i) {
        buffer[i] = data_[i];
      }
      delete[] data_;
      data_ = buffer;
      size_ = size;
    } catch (std::bad_alloc) {
      delete[] data_;
      throw VectorException("Failed to resize");
    }
  }

  T front() const {
    if (size_ < 1) {
      delete[] data_;
      throw VectorException("Something wrong...");
    }
    return data_[0];
  }

  T back() const {
    if (size_ < 1) {
      delete[] data_;
      throw VectorException("Something wrong...");
    }
    return data_[size_ - 1];
  }

  void operator=(const vector &other) {
    if (this == &other) {
      return;
    }
    delete[] data_;
    capacity_ = other.capacity();
    size_ = other.size();
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
  }

  T &operator[](size_t index) {
    if (size_ < 1) {
      delete[] data_;
      if (index >= size_ || index < 0) {
        throw VectorException("Out of bounds");
      }
      throw VectorException("Something wrong...");
    }
    return data_[index];
  }

  T &operator[](size_t index) const {
    if (size_ < 1) {
      delete[] data_;
      if (index >= size_ || index < 0) {
        throw VectorException("Out of bounds");
      }
      throw VectorException("Something wrong...");
    }
    return data_[index];
  }

  class Iterator {
  public:
    Iterator(T *ptr) : ptr_(ptr) {}
    Iterator() { Iterator(nullptr); }

    T &operator*() const { return *ptr_; }
    T *operator->() const { return ptr_; }

    Iterator &operator++() {
      ptr_++;
      return *this;
    }

    Iterator &operator++(int) {
      Iterator temp = *this;
      ++(*this);
      return temp;
    }

    friend bool operator==(const Iterator &lhs, const Iterator &rhs) {
      return lhs.ptr_ == rhs.ptr_;
    }

    friend bool operator!=(const Iterator &lhs, const Iterator &rhs) {
      return lhs.ptr_ != rhs.ptr_;
    }

  private:
    T *ptr_;
  };

  Iterator begin() { return Iterator(&data_[0]); }
  Iterator end() { return Iterator(&data_[size_]); }

  void operator=(std::initializer_list<T> init_list) {
    delete[] data_;
    capacity_ = init_list.size();
    size_ = init_list.size();
    data_ = new T[capacity_];
    std::copy(init_list.begin(), init_list.end(), data_);
  }

private:
  size_t capacity_;
  size_t size_;
  T *data_;

  void grow_array() {
    try {
      capacity_ = capacity_ << 1;
      T *buffer = new T[capacity_];
      for (size_t i = 0; i < size_; ++i) {
        buffer[i] = data_[i];
      }
      delete[] data_;
      data_ = buffer;
    } catch (std::bad_alloc) {
      delete[] data_;
      throw VectorException("Failed to allocate more memory for a vector");
    }
  }

  void shrink_array() {
    capacity_ = size_;
    T *buffer = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
      buffer[i] = data_[i];
    }
    delete[] data_;
    data_ = buffer;
  }
};
