#ifndef __SHARED_PTR_HPP
#define __SHARED_PTR_HPP

#include <mutex>

template <typename T>
class SharedPtr {
public:
    SharedPtr() noexcept : _ptr(nullptr), _refCount(nullptr), _mutex(nullptr) {}

    explicit SharedPtr(T* ptr) noexcept : _ptr(ptr), _refCount(ptr? new unsigned int(1) : nullptr), _mutex(ptr? new std::mutex() : nullptr) {}

    SharedPtr(const SharedPtr<T>& other) noexcept {
        lock();
        _ptr = other._ptr;
        _refCount = other._refCount;
        _mutex = other._mutex;
        incrementeRefCount();
        unlock();
    }

    SharedPtr(SharedPtr<T>&& other) noexcept : _ptr(other._ptr), _refCount(other._refCount), _mutex(other._mutex) {
        lock();
        other._ptr = nullptr;
        other._refCount = nullptr;
        other._mutex = nullptr;
        unlock();
    }

    ~SharedPtr() {
        release();
    }

    SharedPtr<T>& operator=(const SharedPtr<T>& other) {
        if (this != &other) {
            release();
            if (other._ptr) {
                lock();

                _ptr = other._ptr;
                _refCount = other._refCount;
                _mutex = other._mutex;
                incrementeRefCount();

                unlock();
            } else {
                _ptr = nullptr;
                _refCount = nullptr;
                _mutex = nullptr;
            }
        }
        return *this;
    }

    SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept {
        if (this != &other) {
            release();
            lock();

            _ptr = other._ptr;
            _refCount = other._refCount;
            _mutex = other._mutex;

            other._ptr = nullptr;
            other._refCount = nullptr;
            other._mutex = nullptr;

            unlock();
        }
        return *this;
    }

    SharedPtr<T>& operator=(T* ptr) noexcept {
        if (this != ptr) {
            release();
            if (ptr) {
                _ptr = ptr;
                _refCount = new unsigned int(1);
                _mutex = new std::mutex();
            } else {
                _ptr = nullptr;
                _refCount = nullptr;
                _mutex = nullptr;
            }
        }
        return *this;
    }

    T& operator*() {
        return *_ptr;
    }

    T* operator->() {
        return _ptr;
    }

    T* get() const {
        return _ptr;
    }

    bool ok() const {
        return _ptr != nullptr;
    }

    bool operator!() const {
        return _ptr == nullptr;
    }

    bool operator == (const SharedPtr<T>& other) const {
        return _ptr == other._ptr;
    }

    bool operator != (const SharedPtr<T>& other) const {
        return _ptr != other._ptr;
    }

    SharedPtr<T> clone() const {
        return SharedPtr<T>(_ptr);
    }

    void remove() {
        release();
    }

    template<typename U>
    SharedPtr<U> cast(const SharedPtr<T>& other) {
        SharedPtr<U> result;
        result._ptr = dynamic_cast<U*>(other._ptr);
        if (result._ptr) {
            result._refCount = other._refCount;
            result._mutex = other._mutex;
            if (result._refCount) {
                ++(*result._refCount);
            }
        }
        return result;
    }

private:
    void incrementeRefCount() {
        if (_refCount) {
            ++(*_refCount);
        }
    }

    void decrementRefCount() {
        if (_refCount) {
            if (*_refCount > 0) {
                --(*_refCount);
            }
        }
    }

    void release() {
        if (_refCount && _mutex) {
            decrementRefCount();
            if (*_refCount == 0) {
                delete _ptr;
                delete _refCount;
                delete _mutex;
            }
            _ptr = nullptr;
            _refCount = nullptr;
            _mutex = nullptr;
        }
    }

    void lock() {
        if (_mutex) {
            _mutex->lock();
        }
    }

    void unlock() {
        if (_mutex) {
            _mutex->unlock();
        }
    }

    T* _ptr;
    unsigned int* _refCount;
    std::mutex* _mutex;

    template<typename U> friend class SharedPtr;
};

template<typename T, typename U>
SharedPtr<T> dynamic_pointer_cast(const SharedPtr<U>& other) {
    SharedPtr<T> result;
    result._ptr = dynamic_cast<T*>(other._ptr);
    if (result._ptr) {
        result._refCount = other._refCount;
        result._mutex = other._mutex;
        if (result._refCount) {
            ++(*result._refCount);
        }
    }
    return result;
}

#endif // __SHARED_PTR_HPP