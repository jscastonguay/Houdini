/*
MIT License

Copyright (c) 2019 Jean-Sébastien Castonguay

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef MOCK_H
#define MOCK_H

#include "test.h"

#define CREATE_TEST \
  typedef struct MockInfo { \
    int nbCalls; \
    int nbCallsTarget; \
    char * funcName; \
    MockInfo * next; \
  } MockInfo; \
  MockInfo * mockInfoHead = NULL

  
static void MockInfo_addToList(MockInfo * toAdd) {
	int stop = 0;
	MockInfo * mi = mockInfoHead;
	if (mi == NULL) {
		// List empty, add MockInfo to it.
		mockInfoHead = toAdd;
	}
	while (mi && !stop) {
		if (mi == toAdd) {
			// MockInfo already in list, stop searching.
			stop = 1;
			
		// Last item of the list, so MockInfo not in list, then add it.
		} else if (mi->next == NULL) {
			mi->next = toAdd;
			stop = 1;
		}
		mi = mi->next;
	}
}


static void MockInfo_initList() {
	MockInfo * mi = mockInfoHead;
	while (mi) {
		mi.nbCalls = 0;
		mi.nbCallsTarget = 0;
		mi = mi->next;
	}
}


static void MockInfo_testList( unsigned int lineNb) {
	MockInfo * mi = mockInfoHead;
	while (mi) {
		if(mi->nbCalls != mi->nbCallsTarget) {
			PRINT("ERROR at ");
			PRINT(lineNb);
			PRINT(" in substitution function ");
			PRINT(mi->funcName);
			PRINT(": nb calls = ");
			PRINT(mi->nbCalls);
			PRINT(", target = ");
			PRINT(mi->nbCallsTarget);
			PRINT("\n\r");
		}
		mi = mi->next;
	}
}


#define CREATE_MOCK_1(retType, funcName, p1Type) \
typedef struct { \
	MockInfo parent; \
	retType (*cb)(p1Type); \
} MockInfo_##funcName; \
MockInfo_##funcName funcName##_mi = {.parent.next = NULL, .parent.nbCallsTarget = 0, .parent.nbCalls = 0, .parent.funcName = "", .cb = NULL}; \
retType funcName(p1Type p1) { \
	funcName##_mi.parent.nbCalls++; \
	if (funcName##_mi.cb) { \
		return funcName##_mi.cb(p1); \
	} \
}


#define CALLING_INDEX(funNameUnderTest)  (funNameUnderTest##_mi.parent.nbCalls - 1)


#define SUB(funNameUnderTest, funNameSubstitue, _nbCalls) \
	MockInfo_addToList((MockInfo *)funNameUnderTest##_mi); \
	funNameUnderTest##_mi.cd = funNameSubstitue; \
	funNameUnderTest##_mi.parent.nbCallsTarget = _nbCalls; \
	funNameUnderTest##_mi.parent.funcName = #funNameSubstitue;


#define TEST(testName) \
void test_##testName() { \
	MockInfo_initList();
  
  
#define END_TEST MockInfo_testList(__LINE__); }


#define RUN_TEST(testName) test_##testName()

#endif
