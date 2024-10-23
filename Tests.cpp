#include "Tests.h"

void testCopy() {
    // �������� �����������
    SmrtPtr<int> ptr1(new int(10));
    assert(ptr1.amount_RefCount() == 1); // ������� ������ ������ ���� 1

    SmrtPtr<int> ptr2 = ptr1; // ����������� ptr1 � ptr2
    assert(ptr1.amount_RefCount() == 2); // ������� ������ ������ ���� 2 ����� �����������
    assert(ptr2.amount_RefCount() == 2); // ������� ������ ������ ���� 2 ����� �����������
}

// ������������ �����������
void testMove() {
    // �������� �����������
    SmrtPtr<int> ptr1(new int(10));
    SmrtPtr<int> ptr3 = std::move(ptr1); // ����������� ptr1 � ptr3
    assert(ptr1.get() == nullptr); // ptr1 ������ ����� nullptr ����� �����������
    assert(ptr3.amount_RefCount() == 1); // ������� ������ ������ ���� 1, ��� ��� ptr3 ������ ������������ �������� �������
}

// ������������ ��������� ��������
void TestChangeValue() {
    SmrtPtr<int> ptr1(new int(123));   // ������� ��������� �� �������� 123
    *ptr1 = 321;                       // �������� �������� �� 321
    assert(*ptr1 == 321);              // ���������, ��� �������� ����������
    *ptr1 = 404;                       // ������ �������� �� 404
    assert(*ptr1 == 404);              // ��������� ����� ��������
}

// ���� �� �������� ������ ��������� �� ������
void TestSmrtPtrReference(SmrtPtr<int>& ptr) {
    unsigned initialCount = ptr.amount_RefCount(); // ��������� ������� ���������� ������
    SmrtPtr<int> ptr1 = ptr;                       // �������� ptr
    SmrtPtr<int> ptr2 = ptr;                       // ��� ��� �������� ptr
    assert(ptr.amount_RefCount() == initialCount + 2); // ���������, ��� ������� ���������� �� 2
}

// ������������ �������� ��������� �� ������ � �������� �����������
void testSmartPointerReference() {
    SmrtPtr<int> ptr(new int(10)); // ������� ����� ���������
    assert(ptr.amount_RefCount() == 1); // ���������, ��� ������� ������ ����� 1

    TestSmrtPtrReference(ptr); // �������� ��������� �� ������
    assert(ptr.amount_RefCount() == 1); // ������� ������ �������� 1 ����� �������� �� �������, ��� ��� ����� ������ �� ������� ptr1 � ptr2 ������������ 
}


double loadTest(const int N) {

    std::vector<SmrtPtr<int>> buff(N);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        if (i % 5 == 0) {
            buff[i] = SmrtPtr<int>(new int());  //������� ��������� ���� ���, ������� �������    ������ new
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
    std::vector<std::shared_ptr<int>> buff(N);  // ������ shared_ptr

    auto start = std::chrono::high_resolution_clock::now();  // �������� ������

    for (int i = 0; i < N; ++i) {
        if (i % 5 == 0) {
            buff[i] = std::make_shared<int>();  // ������ ����� ������
        }
        else {
            buff[i] = buff[i - (i%5)];  // �������� ��������� �� ������������ ������
        }
    }

    auto end = std::chrono::high_resolution_clock::now();  // �������� �����

    std::chrono::duration<double> duration = end - start;  // ������������

    return duration.count();  // ���������� ����� ����������
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

