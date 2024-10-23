#include "Interface.hpp"

int Menu() {
    std::setlocale(LC_ALL, "Russian");
    int choice;
    do {
        std::cout << "\nМеню:" << std::endl;
        std::cout << "1. Создать указатель" << std::endl;
        std::cout << "2. Создать дополнительный указатель на существующий объект" << std::endl;
        std::cout << "3. Удалить указатель" << std::endl;
        std::cout << "4. Получить значение указателя" << std::endl;
        std::cout << "5. Получить количество указателей на объект" << std::endl;
        std::cout << "6. Показать всё (указатели, значения, адреса, количество)\n" << std::endl;
        std::cout << "7. Выполнить проверочные тесты\n";
        std::cout << "8. Сравнить время выполнения\n";
        std::cout << "9. Выход" << std::endl;
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            createPointer();
            break;
        case 2:
            createAdditionalPointer();
            break;
        case 3:
            deletePointer();
            break;
        case 4:
            getPointerValue();
            break;
        case 5:
            getReferenceCount();
            break;
        case 6:
            displayPointers();
            break;
        case 7:
            std::cout << "\nВыполнение тестов...\n";
            //testCopyAndMove();
            testCopy();
            testMove();
            TestChangeValue();
            testSmartPointerReference();
            std::cout << "Все тесты успешно пройдены!\n";
            break;
        case 8:
            time_test();  
            break;
        case 9:
            std::cout << "Выход..." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова." << std::endl;
        }
    } while (choice != 9);

    return 0;
}