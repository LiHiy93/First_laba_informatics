#pragma once

#include "SmrtPtr.hpp" 
#include "Tests.h"

#include <iostream>
#include <thread>
#include <iomanip>
#include <vector>
#include <cassert>

//void testCopyAndMove();
void testCopy();
void testMove();
void TestChangeValue();
void TestSmrtPtrReference(SmrtPtr<int>& ptr);
void testSmartPointerReference();
double loadTest(const int N);
double loadTest_shared(const int N);
void  time_test();