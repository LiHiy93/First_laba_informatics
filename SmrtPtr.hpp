#pragma once

template <typename T>
class SmrtPtr {
private:
    T* ptr;                    // ��������� �� ����������� ������
    unsigned* refCount;        // ��������� �� ������� ������

    void release() {
        if (refCount) {
            --(*refCount); // ���������� �������� ������
            if (*refCount == 0) { // ���� ��� �������� ������, ����������� ������
                delete ptr;
                delete refCount;
            }
        }
    }

public:

    // ����������� � ����������
    explicit SmrtPtr(T* p = nullptr)
      : ptr(p), refCount(new unsigned(1)) {} // ������������� ��������� � �������� ������

    // ����������� �����������
    SmrtPtr(const SmrtPtr<T>& other)
         : ptr(other.ptr)
         , refCount(other.refCount) 
    {
        ++(*refCount); // ���������� �������� ������
    }

    // �������� ������������
    SmrtPtr<T>& operator=(const SmrtPtr<T>& other) {
        if (this != &other) {
            release(); // ������������ ������� ��������
            ptr = other.ptr;
            refCount = other.refCount;
            ++(*refCount); // ���������� �������� ������
        }
        return *this;
    }


    // ����������� �����������
    SmrtPtr(SmrtPtr<T>&& other) noexcept
      : ptr(other.ptr), refCount(other.refCount) {
        other.ptr = nullptr; // ��������� ��������� � ������������� �������
        other.refCount = new unsigned(1);
    }
 
    // �������� ����������� 
    SmrtPtr<T>& operator=(SmrtPtr<T>&& other) noexcept {
        if (this != &other) {
            release(); // ������������ ������� ��������
            ptr = other.ptr;
            refCount = other.refCount;
            other.ptr = nullptr; // ��������� ��������� � ������������� �������
            other.refCount = new unsigned(1); 
        }
        return *this;
    }

    // ����������
    ~SmrtPtr() {
        release();
    }

    // ������������� ���������
    const T& operator*() const {
        return *ptr; // ������ � ��������, �� ������� ��������� ptr
    }

    // ������ � ������ ������� ����� ���������
    const T* operator->() const {
        return ptr; // ������ � ������ �������, �� ������� ��������� ptr
    }

    // ��������� �������� �������� �������� ������
    unsigned amount_RefCount() const {
        return (refCount) ? *refCount : 0; // ������� �������� �������� ������
    }

    operator bool() const {
        return ptr != nullptr;
    }

    bool operator==(const SmrtPtr& other) const {
        return ptr == other.ptr;
    }

    bool operator!=(const SmrtPtr& other) const {
        return ptr != other.ptr;
    }

    T& operator*()  {
        return *ptr; 
    }

    T* operator->()  {
        return ptr;
    }

    const T* get() const {
      return ptr; 
    }

    T* get() {
        return ptr;
    }
};