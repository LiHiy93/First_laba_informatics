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
    std::cout << "������� ��� ���������: ";
    std::cin >> name;
    if (pointerMap.find(name) != pointerMap.end() || stringPointerMap.find(name) != stringPointerMap.end()) {
        std::cout << "��������� � ������ " << name << " ��� ����������." << std::endl;
        return;
    }
    if (!isValidPointerName(name)) {
        std::cout << "��� ��������� ������ ��������� ���� �� ���� ��������� ����� � ����� ��������� ������ ��������� ����� � �����." << std::endl;
        return;
    }

    int choice;
    std::cout << "������� ��� ������� (1 - �����, 2 - ������): ";
    std::cin >> choice;

    if (choice == 1) {
        int value;
        std::cout << "������� �������� ��� �������: ";
        while (!(std::cin >> value)) {
            std::cin.clear(); // ���������� ���� ������
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���������� �������� ����
            std::cout << "�������� ��������. ������� ����� �����: ";
        }
        pointerMap[name] = SmrtPtr<Object>(new Object(value));
        std::cout << "��������� " << name << " �� ����� ������." << std::endl;
    }
    else if (choice == 2) {
        std::string value;
        std::cout << "������� ������: ";
        std::cin.ignore(); // ���������� ������� ���������� ������
        std::getline(std::cin, value);
        stringPointerMap[name] = SmrtPtr<std::string>(new std::string(value));
        std::cout << "��������� " << name << " �� ������ ������." << std::endl;
    }
    else {
        std::cout << "�������� ����� ����." << std::endl;
    }
}

void createAdditionalPointer() {
    std::string name, existingPointerName;
    std::cout << "������� ����� ��� ���������: ";
    std::cin >> name;
    if (pointerMap.find(name) != pointerMap.end() || stringPointerMap.find(name) != stringPointerMap.end()) {
        std::cout << "��������� � ������ " << name << " ��� ����������." << std::endl;
        return;
    }
    if (!isValidPointerName(name)) {
        std::cout << "��� ��������� ������ ��������� ���� �� ���� ��������� ����� � ����� ��������� ������ ��������� ����� � �����." << std::endl;
        return;
    }
    std::cout << "������� ��� ������������� ���������: ";
    std::cin >> existingPointerName;
    if (pointerMap.find(existingPointerName) != pointerMap.end()) {
        pointerMap[name] = pointerMap[existingPointerName];
        std::cout << "��������� " << name << " ������ � ��������� �� ��� �� ������, ��� � " << existingPointerName << "." << std::endl;
    }
    else if (stringPointerMap.find(existingPointerName) != stringPointerMap.end()) {
        stringPointerMap[name] = stringPointerMap[existingPointerName];
        std::cout << "��������� " << name << " ������ � ��������� �� �� �� ������, ��� � " << existingPointerName << "." << std::endl;
    }
    else {
        std::cout << "��������� " << existingPointerName << " �� ����������." << std::endl;
    }
}

void deletePointer() {
    std::string name;
    std::cout << "������� ��� ��������� ��� ��������: ";
    std::cin >> name;
    if (pointerMap.erase(name) > 0 || stringPointerMap.erase(name) > 0) {
        std::cout << "��������� " << name << " ������." << std::endl;
    }
    else {
        std::cout << "��������� " << name << " �� ����������." << std::endl;
    }
}

void getPointerValue() {
    std::string name;
    std::cout << "������� ��� ��������� ��� ��������� ��������: ";
    std::cin >> name;
    if (pointerMap.find(name) != pointerMap.end()) {
        std::cout << "��������: " << pointerMap[name]->value << std::endl;
    }
    else if (stringPointerMap.find(name) != stringPointerMap.end()) {
        std::cout << "��������: " << *(stringPointerMap[name]) << std::endl;
    }
    else {
        std::cout << "��������� " << name << " �� ����������." << std::endl;
    }
}

void getReferenceCount() {
    std::string name;
    std::cout << "������� ��� ��������� ��� ��������� ������ ���������� ���������� �� ��� �� ������: ";
    std::cin >> name;
    if (pointerMap.find(name) != pointerMap.end()) {
        std::cout << "���������� ����������: " << pointerMap[name].amount_RefCount() << std::endl;
    }
    else if (stringPointerMap.find(name) != stringPointerMap.end()) {
        std::cout << "���������� ����������: " << stringPointerMap[name].amount_RefCount() << std::endl;
    }
    else {
        std::cout << "��������� " << name << " �� ����������." << std::endl;
    }
}

void displayPointers() {
    std::cout << "\n������� ��������� � �� ��������:" << std::endl;
    if (pointerMap.empty() && stringPointerMap.empty()) {
        std::cout << "��������� �� �������." << std::endl;
    }
    else {
        for (const auto& pair : pointerMap) {
            std::cout << "��� ���������: " << pair.first << ", ��������: " << pair.second->value
                << ", �����: " << pair.second.get() << ", ���������� ����������: " << pair.second.amount_RefCount() << std::endl;
        }
        for (const auto& pair : stringPointerMap) {
            std::cout << "��� ���������: " << pair.first << ", ��������: " << *(pair.second)
                << ", �����: " << pair.second.get() << ", ���������� ����������: " << pair.second.amount_RefCount() << std::endl;
        }
    }
}