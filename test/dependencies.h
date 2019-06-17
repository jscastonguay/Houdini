#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H

typedef struct {
    int x;
} Info;

int depRetInt();
int depRetIntPointerParam(Info * info);

void depV0();
int dep0();
void depV1(int);
int dep1(int);
void depV2(int, int);
int dep2(int, int);
void depV3(int, int, int);
int dep3(int, int, int);
void depV4(int, int, int, int);
int dep4(int, int, int, int);
void depV5(int, int, int, int, int);
int dep5(int, int, int, int, int);
void depV6(int, int, int, int, int, int);
int dep6(int, int, int, int, int, int);
void depV7(int, int, int, int, int, int, int);
int dep7(int, int, int, int, int, int, int);
void depV8(int, int, int, int, int, int, int, int);
int dep8(int, int, int, int, int, int, int, int);

#endif