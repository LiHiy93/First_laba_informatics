#pragma once

template <typename T>
class SmrtPtr {
private:
    T* ptr;                    // Указатель на управляемый объект
    unsigned* refCount;        // Указатель на счётчик ссылок

    void release() {
        if (refCount) {
            --(*refCount); // Уменьшение счётчика ссылок
            if (*refCount == 0) { // Если нет активных ссылок, освобождаем память
                delete ptr;
                delete refCount;
            }
        }
    }

public:

    // Конструктор с параметром
    explicit SmrtPtr(T* p = nullptr)
      : ptr(p), refCount(new unsigned(1)) {} // Инициализация указателя и счётчика ссылок

    // Конструктор копирования
    SmrtPtr(const SmrtPtr<T>& other)
         : ptr(other.ptr)
         , refCount(other.refCount) 
    {
        ++(*refCount); // Увеличение счётчика ссылок
    }

    // Оператор присваивания
    SmrtPtr<T>& operator=(const SmrtPtr<T>& other) {
        if (this != &other) {
            release(); // Освобождение текущих ресурсов
            ptr = other.ptr;
            refCount = other.refCount;
            ++(*refCount); // Увеличение счётчика ссылок
        }
        return *this;
    }


    // Конструктор перемещения
    SmrtPtr(SmrtPtr<T>&& other) noexcept
      : ptr(other.ptr), refCount(other.refCount) {
        other.ptr = nullptr; // Обнуление указателя у перемещаемого объекта
        other.refCount = new unsigned(1);
    }
 
    // Оператор перемещения 
    SmrtPtr<T>& operator=(SmrtPtr<T>&& other) noexcept {
        if (this != &other) {
            release(); // Освобождение текущих ресурсов
            ptr = other.ptr;
            refCount = other.refCount;
            other.ptr = nullptr; // Обнуление указателя у перемещаемого объекта
            other.refCount = new unsigned(1); 
        }
        return *this;
    }

    // Деструктор
    ~SmrtPtr() {
        release();
    }

    // Разыменование указателя
    const T& operator*() const {
        return *ptr; // Доступ к значению, на которое указывает ptr
    }

    // Доступ к членам объекта через указатель
    const T* operator->() const {
        return ptr; // Доступ к членам объекта, на который указывает ptr
    }

    // Получение текущего значения счётчика ссылок
    unsigned amount_RefCount() const {
        return (refCount) ? *refCount : 0; // Возврат значения счётчика ссылок
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