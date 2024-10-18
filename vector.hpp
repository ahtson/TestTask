#include <algorithm>
#include <cstddef>
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

  vector() { vector(1); }

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
    T return_value = data_[size_ - 1];
    data_[size_ - 1] = 0;
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
    } catch (...) {
      throw VectorException("Failed to resize");
    }
  }

  T front() const {
    try {
      return data_[0];
    } catch (...) {
      throw VectorException("Something wrong...");
    }
  }

  T back() const {
    try {
      return data_[size_ - 1];
    } catch (...) {
      throw VectorException("Something wrong...");
    }
  }

  void operator=(const vector &other) {
    capacity_ = other.capacity();
    size_ = other.size();
    std::copy(other.begin(), other.end(), data_);
  }

  T operator[](size_t index) const {
    try {
      return data_[index];
    } catch (...) {
      throw VectorException("Tried to access element out of vector's bounds");
    }
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
  Iterator end() { return Iterator(&data_[size_ - 1]); }

  vector(const vector &other)
      : size_(other.size()), capacity_(other.capacity()) {
    data_ = new T[capacity_];
    std::copy(other.begin(), other.end(), data_);
  }

  void operator=(std::initializer_list<T> init_list) {
    delete[] data_;
    capacity_ = init_list.size();
    size_ = init_list.size();
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
    } catch (...) {
      throw VectorException("Failed to allocate more memory for a vector");
    }
  }

  void shrink_array() {
    capacity_ = size_;
    T *buffer = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
      buffer[i] = data_[i];
    }
    delete data_;
    data_ = buffer;
  }
};
