#pragma once

#include <memory>
#include <mutex>

template <typename T, typename Mutex> class UniqueMutexPtr
{
  public:
    explicit UniqueMutexPtr(std::unique_ptr<T> ptr) : _ptr(std::move(ptr))
    {
    }

    T *ptr()
    {
        return _ptr.get();
    };

    Mutex &mutex()
    {
        return _mutex;
    };

  private:
    std::unique_ptr<T> _ptr;
    mutable Mutex _mutex;
};
