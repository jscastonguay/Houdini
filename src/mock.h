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

struct _MockInfo {
  int nbCalls;
  int nbCallsTarget;
  char * funcName;
  struct _MockInfo * next;
};
typedef struct _MockInfo MockInfo;
static MockInfo * mockInfoHead = NULL;


static void MockInfo_initList() {
  MockInfo * mi = mockInfoHead;
	while (mi) {
		mi->nbCalls = 0;
		mi->nbCallsTarget = 0;    
    mi = mi->next;
	}
}


static void MockInfo_addToList(MockInfo * toAdd) {
	int stop = 0;
  
  toAdd->nbCalls = 0;
  toAdd->nbCallsTarget = 0;
  
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


static void MockInfo_testList( unsigned int lineNb) {
	MockInfo * mi = mockInfoHead;
	while (mi) {
		if(mi->nbCalls != mi->nbCallsTarget) {
			PRINT(PREFIX "ERROR at ");
			PRINT_INT(lineNb);
			PRINT(" in substitution function ");
			PRINT(mi->funcName);
			PRINT(": nb calls = ");
			PRINT_INT(mi->nbCalls);
			PRINT(", target = ");
			PRINT_INT(mi->nbCallsTarget);
			PRINT(".\n\r");
		}
		mi = mi->next;
	}
}


#define CALLING_INDEX(funNameUnderTest)  (funNameUnderTest##_mi.parent.nbCalls - 1)


#define SUB(funNameUnderTest, funNameSubstitue, _nbCalls) \
	MockInfo_addToList((MockInfo *)&funNameUnderTest##_mi); \
	funNameUnderTest##_mi.cb = funNameSubstitue; \
	funNameUnderTest##_mi.parent.nbCallsTarget = _nbCalls; \
	funNameUnderTest##_mi.parent.funcName = #funNameSubstitue;


#define TEST(testName) \
static void test_##testName() { \
	MockInfo_initList(); \
  PRINT(#testName); \
  PRINT("\n\r");
  
  
#define END_TEST MockInfo_testList(__LINE__); }


#define RUN_TEST(testName) test_##testName()


#define CREATE_MOCK_0(retType, name) \
typedef struct { \
	MockInfo parent; \
	retType (*cb)(); \
} MockInfo_##name; \
retType name##_notUsed; \
MockInfo_##name name##_mi = {.parent.next = NULL, .parent.nbCallsTarget = 0, .parent.nbCalls = 0, .parent.funcName = "", .cb = NULL}; \
retType name() { \
	name##_mi.parent.nbCalls++; \
	if (name##_mi.cb != NULL) { \
		return name##_mi.cb(); \
	}else { \
    PRINT(PREFIX "ERROR: A mock function has been called without a corresponding substitute function.\n\r"); \
    FLUSH(); \
    return name##_notUsed; \
  } \
}

#define CREATE_MOCK_1(retType, name, p1Type) \
typedef struct { \
	MockInfo parent; \
	retType (*cb)(); \
} MockInfo_##name; \
retType name##_notUsed; \
MockInfo_##name name##_mi = {.parent.next = NULL, .parent.nbCallsTarget = 0, .parent.nbCalls = 0, .parent.funcName = "", .cb = NULL}; \
retType name(p1Type p1) { \
	name##_mi.parent.nbCalls++; \
	if (name##_mi.cb != NULL) { \
		return name##_mi.cb(p1); \
	} else { \
    PRINT(PREFIX "ERROR: A mock function has been called without a corresponding substitute function.\n\r"); \
    FLUSH(); \
    return name##_notUsed; \
  } \
}

#endif
