#include "Tests.h"

void testCopy() {
    // Проверка копирования
    SmrtPtr<int> ptr1(new int(10));
    assert(ptr1.amount_RefCount() == 1); // Счётчик ссылок должен быть 1

    SmrtPtr<int> ptr2 = ptr1; // Копирование ptr1 в ptr2
    assert(ptr1.amount_RefCount() == 2); // Счётчик ссылок должен быть 2 после копирования
    assert(ptr2.amount_RefCount() == 2); // Счётчик ссылок должен быть 2 после копирования
}

// Тестирование перемещения
void testMove() {
    // Проверка перемещения
    SmrtPtr<int> ptr1(new int(10));
    SmrtPtr<int> ptr3 = std::move(ptr1); // Перемещение ptr1 в ptr3
    assert(ptr1.get() == nullptr); // ptr1 должен стать nullptr после перемещения
    assert(ptr3.amount_RefCount() == 1); // Счётчик ссылок должен быть 1, так как ptr3 теперь единственный владелец объекта
}

// тестирование изменения значения
void TestChangeValue() {
    SmrtPtr<int> ptr1(new int(123));   // Создаем указатель на значение 123
    *ptr1 = 321;                       // Изменяем значение на 321
    assert(*ptr1 == 321);              // Проверяем, что значение изменилось
    *ptr1 = 404;                       // Меняем значение на 404
    assert(*ptr1 == 404);              // Проверяем новое значение
}

// тест на передачу умного указателя по ссылке
void TestSmrtPtrReference(SmrtPtr<int>& ptr) {
    unsigned initialCount = ptr.amount_RefCount(); // Сохраняем текущее количество ссылок
    SmrtPtr<int> ptr1 = ptr;                       // Копируем ptr
    SmrtPtr<int> ptr2 = ptr;                       // Еще раз копируем ptr
    assert(ptr.amount_RefCount() == initialCount + 2); // Проверяем, что счётчик увеличился на 2
}

// тестирование передачи указателя по ссылке и проверка копирования
void testSmartPointerReference() {
    SmrtPtr<int> ptr(new int(10)); // Создаем умный указатель
    assert(ptr.amount_RefCount() == 1); // Проверяем, что счётчик ссылок равен 1

    TestSmrtPtrReference(ptr); // Передаем указатель по ссылке
    assert(ptr.amount_RefCount() == 1); // Счётчик должен остаться 1 после передачи по ссылкею, так как после выхода из функции ptr1 и ptr2 уничтожаются 
}


double loadTest(const int N) {

    std::vector<SmrtPtr<int>> buff(N);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        if (i % 5 == 0) {
            buff[i] = SmrtPtr<int>(new int());  //сделать отдельный масс инт, который заранее    убрать new
        }
        else {
            buff[i] = buff[i - (i%5)];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    return duration.count();
}


double loadTest_shared(const int N) {
    std::vector<std::shared_ptr<int>> buff(N);  // Вектор shared_ptr

    auto start = std::chrono::high_resolution_clock::now();  // Засекаем начало

    for (int i = 0; i < N; ++i) {
        if (i % 5 == 0) {
            buff[i] = std::make_shared<int>();  // Создаём новый объект
        }
        else {
            buff[i] = buff[i - (i%5)];  // Копируем указатель на существующий объект
        }
    }

    auto end = std::chrono::high_resolution_clock::now();  // Засекаем конец

    std::chrono::duration<double> duration = end - start;  // длительность

    return duration.count();  // Возвращаем время выполнения
}

void  time_test() {

    std::cout << std::setw(20) << " SmrtPtr "
        << std::setw(25) << " stdSmrtPtr " << std::endl;

    std::cout << std::setw(10) << loadTest(1000) << " seconds "
        << std::setw(25) << loadTest_shared(1000) << " seconds " << std::endl;

    std::cout << std::setw(10) << loadTest(2500000) << " seconds "
        << std::setw(25) << loadTest_shared(2500000) << " seconds " << std::endl;

    std::cout << std::setw(10) << loadTest(5000000) << " seconds "
        << std::setw(25) << loadTest_shared(5000000) << " seconds " << std::endl;

    std::cout << std::setw(10) << loadTest(7500000) << " seconds "
        << std::setw(25) << loadTest_shared(7500000) << " seconds " << std::endl;

    std::cout << std::setw(10) << loadTest(10000000) << " seconds "
        << std::setw(25) << loadTest_shared(10000000) << " seconds " << std::endl;

}

