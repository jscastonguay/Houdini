#include "dependencies.h"

int globalVariable = -1;

void cut1() {
    globalVariable = 0;
}

void cut2() {
    globalVariable = depRetInt();
}

void cut3() {
    Info info;
    if (depRetIntPointerParam(&info) == 0) {
        globalVariable = info.x;
    } else {
        globalVariable = -1;
    }
}

int cut4() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += depRetInt();
    }

    return sum;
}

int cut5() {
    
    int x = 0;

    depV0();
    x += dep0();
    depV1(1);
    x += dep1(2);
    depV2(3, 4);
    x += dep2(5, 6);
    depV3(7, 8, 9);
    x += dep3(10, 11, 12);
    depV4(13, 14, 15, 16);
    x += dep4(17, 18, 19, 20);
    depV5(21, 22, 23, 24, 25);
    x += dep5(26, 27, 28, 29, 30);
    depV6(31, 32, 33, 34, 35, 36);
    x += dep6(37, 38, 39, 40, 41, 42);
    depV7(43, 44, 45, 46, 47, 48, 49);
    x += dep7(50, 51, 52, 53, 54, 55, 56);
    depV8(57, 58, 59, 60, 61, 62, 63, 64);
    x += dep8(65, 66, 67, 68, 69, 70, 71, 72);

    return x;
}