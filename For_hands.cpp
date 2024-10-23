#include "For_hands.hpp"
class Object {
public:
    int value;
    explicit Object(int val) : value(val) {}
};

std::map<std::string, SmrtPtr<Object>> pointerMap;
std::map<std::string, SmrtPtr<std::string>> stringPointerMap;

bool isValidPointerName(const std::string& name) {
    if (name.empty()) {
        return false;
    }
    bool hasLetter = false;
    for (char c : name) {
        if (!std::isalnum(c)) {
            return false;
        }
        if (std::isalpha(c)) {
            hasLetter = true;
        }
    }
    return hasLetter;
}

void createPointer() {
    std::string name;
    std::cout << "Введите имя указателя: ";
    std::cin >> name;
    if (pointerMap.find(name) != pointerMap.end() || stringPointerMap.find(name) != stringPointerMap.end()) {
        std::cout << "Указатель с именем " << name << " уже существует." << std::endl;
        return;
    }
    if (!isValidPointerName(name)) {
        std::cout << "Имя указателя должно содержать хотя бы одну латинскую букву и может содержать только латинские буквы и цифры." << std::endl;
        return;
    }

    int choice;
    std::cout << "Введите тип объекта (1 - число, 2 - строка): ";
    std::cin >> choice;

    if (choice == 1) {
        int value;
        std::cout << "Введите значение для объекта: ";
        while (!(std::cin >> value)) {
            std::cin.clear(); // Сбрасываем флаг ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Пропускаем неверный ввод
            std::cout << "Неверное значение. Введите целое число: ";
        }
        pointerMap[name] = SmrtPtr<Object>(new Object(value));
        std::cout << "Указатель " << name << " на число создан." << std::endl;
    }
    else if (choice == 2) {
        std::string value;
        std::cout << "Введите строку: ";
        std::cin.ignore(); // Игнорируем остаток предыдущей строки
        std::getline(std::cin, value);
        stringPointerMap[name] = SmrtPtr<std::string>(new std::string(value));
        std::cout << "Указатель " << name << " на строку создан." << std::endl;
    }
    else {
        std::cout << "Неверный выбор типа." << std::endl;
    }
}

void createAdditionalPointer() {
    std::string name, existingPointerName;
    std::cout << "Введите новое имя указателя: ";
    std::cin >> name;
    if (pointerMap.find(name) != pointerMap.end() || stringPointerMap.find(name) != stringPointerMap.end()) {
        std::cout << "Указатель с именем " << name << " уже существует." << std::endl;
        return;
    }
    if (!isValidPointerName(name)) {
        std::cout << "Имя указателя должно содержать хотя бы одну латинскую букву и может содержать только латинские буквы и цифры." << std::endl;
        return;
    }
    std::cout << "Введите имя существующего указателя: ";
    std::cin >> existingPointerName;
    if (pointerMap.find(existingPointerName) != pointerMap.end()) {
        pointerMap[name] = pointerMap[existingPointerName];
        std::cout << "Указатель " << name << " создан и указывает на тот же объект, что и " << existingPointerName << "." << std::endl;
    }
    else if (stringPointerMap.find(existingPointerName) != stringPointerMap.end()) {
        stringPointerMap[name] = stringPointerMap[existingPointerName];
        std::cout << "Указатель " << name << " создан и указывает на ту же строку, что и " << existingPointerName << "." << std::endl;
    }
    else {
        std::cout << "Указатель " << existingPointerName << " не существует." << std::endl;
    }
}

void deletePointer() {
    std::string name;
    std::cout << "Введите имя указателя для удаления: ";
    std::cin >> name;
    if (pointerMap.erase(name) > 0 || stringPointerMap.erase(name) > 0) {
        std::cout << "Указатель " << name << " удален." << std::endl;
    }
    else {
        std::cout << "Указатель " << name << " не существует." << std::endl;
    }
}

void getPointerValue() {
    std::string name;
    std::cout << "Введите имя указателя для получения значения: ";
    std::cin >> name;
    if (pointerMap.find(name) != pointerMap.end()) {
        std::cout << "Значение: " << pointerMap[name]->value << std::endl;
    }
    else if (stringPointerMap.find(name) != stringPointerMap.end()) {
        std::cout << "Значение: " << *(stringPointerMap[name]) << std::endl;
    }
    else {
        std::cout << "Указатель " << name << " не существует." << std::endl;
    }
}

void getReferenceCount() {
    std::string name;
    std::cout << "Введите имя указателя для получения общего количества указателей на его же объект: ";
    std::cin >> name;
    if (pointerMap.find(name) != pointerMap.end()) {
        std::cout << "Количество указателей: " << pointerMap[name].amount_RefCount() << std::endl;
    }
    else if (stringPointerMap.find(name) != stringPointerMap.end()) {
        std::cout << "Количество указателей: " << stringPointerMap[name].amount_RefCount() << std::endl;
    }
    else {
        std::cout << "Указатель " << name << " не существует." << std::endl;
    }
}

void displayPointers() {
    std::cout << "\nТекущие указатели и их значения:" << std::endl;
    if (pointerMap.empty() && stringPointerMap.empty()) {
        std::cout << "Указатели не созданы." << std::endl;
    }
    else {
        for (const auto& pair : pointerMap) {
            std::cout << "Имя указателя: " << pair.first << ", Значение: " << pair.second->value
                << ", Адрес: " << pair.second.get() << ", Количество указателей: " << pair.second.amount_RefCount() << std::endl;
        }
        for (const auto& pair : stringPointerMap) {
            std::cout << "Имя указателя: " << pair.first << ", Значение: " << *(pair.second)
                << ", Адрес: " << pair.second.get() << ", Количество указателей: " << pair.second.amount_RefCount() << std::endl;
        }
    }
}