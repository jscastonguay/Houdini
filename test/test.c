#include <stdio.h>
#include <stdlib.h>
#include "mock.h"

#include "cut.c"

/*********************************************************/
TEST(cut1_withoutMock)
    cut1();
    ASSERT(globalVariable == 0);
END_TEST

/*********************************************************/

CREATE_MOCK_0(int, depRetInt)

int mock1() {
    return 10;
}

TEST(cut2_mockReturnIntWithoutParameter)
    SUB(depRetInt, mock1, 1);
    cut2();
    ASSERT(globalVariable == 10);    
END_TEST

/*********************************************************/

CREATE_MOCK_1(int, depRetIntPointerParam, Info *);

int mock2(Info * info) {
    info->x = 100;
    return 0;
}

TEST(cut3_mockReturnSuccessAndXByReference)
    SUB(depRetIntPointerParam, mock2, 1);
    cut3();
    ASSERT(globalVariable == 100);
END_TEST

/*********************************************************/

int mock3() {
    const int retValues[] = {10, 20, 30};
    unsigned int i = CALLING_INDEX(depRetInt);
    return retValues[i];
}

TEST(cut4_multipuleCallsUsingCALLING_INDEX)
    SUB(depRetInt, mock3, 3);
    ASSERT(cut4() == 60);
END_TEST

/*********************************************************/

int var = 0;

void setup() {
    var = 1;
}

void teardown() {
    var = 2;
}

TEST(setupAndTeardown)
    ASSERT(var == 1);
END_TEST

/*********************************************************/

CREATE_MOCK_V0(depV0);
CREATE_MOCK_0(int, dep0);
CREATE_MOCK_V1(depV1, int);
CREATE_MOCK_1(int, dep1, int)
CREATE_MOCK_V2(depV2, int, int);
CREATE_MOCK_2(int, dep2, int, int);
CREATE_MOCK_V3(depV3, int, int, int);
CREATE_MOCK_3(int, dep3, int, int, int);
CREATE_MOCK_V4(depV4, int, int, int, int);
CREATE_MOCK_4(int, dep4, int, int, int, int);
CREATE_MOCK_V5(depV5, int, int, int, int, int);
CREATE_MOCK_5(int, dep5, int, int, int, int, int);
CREATE_MOCK_V6(depV6, int, int, int, int, int, int);
CREATE_MOCK_6(int, dep6, int, int, int, int, int, int);
CREATE_MOCK_V7(depV7, int, int, int, int, int, int, int);
CREATE_MOCK_7(int, dep7, int, int, int, int, int, int, int);
CREATE_MOCK_V8(depV8, int, int, int, int, int, int, int, int);
CREATE_MOCK_8(int, dep8, int, int, int, int, int, int, int, int);

void subV0() {
}

int sub0() {
    return 1;
}

void subV1(int p1) {
    ASSERT(p1 == 1);
}

int sub1(int p1) {
    ASSERT(p1 == 2);
    return 2;
}

void subV2(int p1, int p2) {
    ASSERT(p1 == 3);
    ASSERT(p2 == 4);
}

int sub2(int p1, int p2) {
    ASSERT(p1 == 5);
    ASSERT(p2 == 6);
    return 3;
}

void subV3(int p1, int p2, int p3) {
    ASSERT(p1 == 7);
    ASSERT(p2 == 8);
    ASSERT(p3 == 9);
}

int sub3(int p1, int p2, int p3) {
    ASSERT(p1 == 10);
    ASSERT(p2 == 11);
    ASSERT(p3 == 12);
    return 4;
}

void subV4(int p1, int p2, int p3, int p4) {
    ASSERT(p1 == 13);
    ASSERT(p2 == 14);
    ASSERT(p3 == 15);
    ASSERT(p4 == 16);
}

int sub4(int p1, int p2, int p3, int p4) {
    ASSERT(p1 == 17);
    ASSERT(p2 == 18);
    ASSERT(p3 == 19);
    ASSERT(p4 == 20);
    return 5;
}

void subV5(int p1, int p2, int p3, int p4, int p5) {
    ASSERT(p1 == 21);
    ASSERT(p2 == 22);
    ASSERT(p3 == 23);
    ASSERT(p4 == 24);
    ASSERT(p5 == 25);
}

int sub5(int p1, int p2, int p3, int p4, int p5) {
    ASSERT(p1 == 26);
    ASSERT(p2 == 27);
    ASSERT(p3 == 28);
    ASSERT(p4 == 29);
    ASSERT(p5 == 30);
    return 6;
}

void subV6(int p1, int p2, int p3, int p4, int p5, int p6) {
    ASSERT(p1 == 31);
    ASSERT(p2 == 32);
    ASSERT(p3 == 33);
    ASSERT(p4 == 34);
    ASSERT(p5 == 35);
    ASSERT(p6 == 36);
}

int sub6(int p1, int p2, int p3, int p4, int p5, int p6) {
    ASSERT(p1 == 37);
    ASSERT(p2 == 38);
    ASSERT(p3 == 39);
    ASSERT(p4 == 40);
    ASSERT(p5 == 41);
    ASSERT(p6 == 42);
    return 7;
}

void subV7(int p1, int p2, int p3, int p4, int p5, int p6, int p7) {
    ASSERT(p1 == 43);
    ASSERT(p2 == 44);
    ASSERT(p3 == 45);
    ASSERT(p4 == 46);
    ASSERT(p5 == 47);
    ASSERT(p6 == 48);
    ASSERT(p7 == 49);
}

int sub7(int p1, int p2, int p3, int p4, int p5, int p6, int p7) {
    ASSERT(p1 == 50);
    ASSERT(p2 == 51);
    ASSERT(p3 == 52);
    ASSERT(p4 == 53);
    ASSERT(p5 == 54);
    ASSERT(p6 == 55);
    ASSERT(p7 == 56);
    return 8;
}

void subV8(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8) {
    ASSERT(p1 == 57);
    ASSERT(p2 == 58);
    ASSERT(p3 == 59);
    ASSERT(p4 == 60);
    ASSERT(p5 == 61);
    ASSERT(p6 == 62);
    ASSERT(p7 == 63);
    ASSERT(p8 == 64);
}

int sub8(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8) {
    ASSERT(p1 == 65);
    ASSERT(p2 == 66);
    ASSERT(p3 == 67);
    ASSERT(p4 == 68);
    ASSERT(p5 == 69);
    ASSERT(p6 == 70);
    ASSERT(p7 == 71);
    ASSERT(p8 == 72);
    return 9;
}


TEST(cut5_allCreateMock)
    SUB(depV0, subV0, 1);
    SUB(dep0, sub0, 1);
    SUB(depV1, subV1, 1);
    SUB(dep1, sub1, 1);
    SUB(depV2, subV2, 1);
    SUB(dep2, sub2, 1);
    SUB(depV3, subV3, 1);
    SUB(dep3, sub3, 1);
    SUB(depV4, subV4, 1);
    SUB(dep4, sub4, 1);
    SUB(depV5, subV5, 1);
    SUB(dep5, sub5, 1);
    SUB(depV6, subV6, 1);
    SUB(dep6, sub6, 1);
    SUB(depV7, subV7, 1);
    SUB(dep7, sub7, 1);
    SUB(depV8, subV8, 1);
    SUB(dep8, sub8, 1);

    int result = cut5();

    ASSERT(result == 45);
END_TEST

/*********************************************************/

int main() {
    
    RUN_TEST(cut1_withoutMock);
    RUN_TEST(cut2_mockReturnIntWithoutParameter);
    RUN_TEST(cut3_mockReturnSuccessAndXByReference);
    RUN_TEST(cut4_multipuleCallsUsingCALLING_INDEX);
    
    // Special test definition to verify setup and teardown functionalities.
    ATTACHED_SETUP(setup);
    ATTACHED_TEARDOWN(teardown);
    RUN_TEST(setupAndTeardown);
    ASSERT(var == 2);
    ATTACHED_SETUP(NULL);
    ATTACHED_TEARDOWN(NULL);

    RUN_TEST(cut5_allCreateMock);
    
    return 0;
}