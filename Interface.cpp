#include "Interface.hpp"

int Menu() {
    std::setlocale(LC_ALL, "Russian");
    int choice;
    do {
        std::cout << "\n����:" << std::endl;
        std::cout << "1. ������� ���������" << std::endl;
        std::cout << "2. ������� �������������� ��������� �� ������������ ������" << std::endl;
        std::cout << "3. ������� ���������" << std::endl;
        std::cout << "4. �������� �������� ���������" << std::endl;
        std::cout << "5. �������� ���������� ���������� �� ������" << std::endl;
        std::cout << "6. �������� �� (���������, ��������, ������, ����������)\n" << std::endl;
        std::cout << "7. ��������� ����������� �����\n";
        std::cout << "8. �������� ����� ����������\n";
        std::cout << "9. �����" << std::endl;
        std::cout << "������� ��� �����: ";
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
            std::cout << "\n���������� ������...\n";
            //testCopyAndMove();
            testCopy();
            testMove();
            TestChangeValue();
            testSmartPointerReference();
            std::cout << "��� ����� ������� ��������!\n";
            break;
        case 8:
            time_test();  
            break;
        case 9:
            std::cout << "�����..." << std::endl;
            break;
        default:
            std::cout << "�������� �����. ����������, ���������� �����." << std::endl;
        }
    } while (choice != 9);

    return 0;
}