#pragma once

#include <cassert>
#include <cstdlib>
#include <algorithm>

template <typename Type>
class ArrayPtr {
public:
    
    ArrayPtr() = default;

    explicit ArrayPtr(size_t size) {
        if (size == 0) raw_ptr_ = nullptr;
        else raw_ptr_ = new Type[size];
    }

    explicit ArrayPtr(Type* raw_ptr) noexcept
        : raw_ptr_(raw_ptr)
    {
    }

    ArrayPtr(ArrayPtr&& other) noexcept {
        raw_ptr_ = other.raw_ptr_;
        other.raw_ptr_ = nullptr;
    }

    ArrayPtr& operator=(ArrayPtr&& other) noexcept {
        if (this != &other) {
            std::swap(raw_ptr_, other.raw_ptr_);
        }
        return *this;
    }

    Type& operator[](size_t index) noexcept {
        return raw_ptr_[index];
    }

    const Type& operator[](size_t index) const noexcept {
        return raw_ptr_[index];
    }

    explicit operator bool() const {
        if (raw_ptr_) return true;
        return false;
    }

    Type* Get() const noexcept {
        return &raw_ptr_[0];
    }

    void swap(ArrayPtr& other) noexcept {
        std::swap(other.raw_ptr_, raw_ptr_);
    }

private:
   Type* raw_ptr_ = nullptr;
};
