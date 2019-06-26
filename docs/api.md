# Application Programming Interface (API)

## Test Setup

Parler des #include, de main, etc.

A test project is made of test files (standard C source file). Each test file **includes** Houdini framework simply by ``#include "houdini.h"``. Then a test file **includes an application file (the code under test)** by doing ``#include "path/to/cut.c"``. This is a base principle behind Houdini: the test cases are within the same compiler "unit" than the code under test. Also, each test file must include a test runner function that may be a ``main`` function or another function depending on the strategy used for the test project (see TBD). The following source code shows the project setup in *utest.c* for the Houdini example:

``` C
#include "../../src/houdini.h"
#include "../../example/app/application.c"

int main() {
  return 0;
}
```

Aussi parler du projet "makefile" et autres.

## CREATE_MOCK_x(...)

This macro creates the mock mechanism for a given function. **x** and the number of marco's parameters are variable and must be according to the return type and the parameter's definitions of the mock function. Use ``CREATE_MOCK_x`` only once per mock function per test file.

### Example 1

For a function declared as ``void foo(int x, float y);``, mock mechanism creation is as follows:
``` C
CREATE_MOCK_V2(foo, int, float);
```
where
* *V*: returns ``void``
* *2*: has 2 parameters

Then, the macro takes the name of the function and the type of each parameter.  

### Example 2

For a function declared as ``int foo(float x);``, mock mechanism creation is as follows:
``` C
CREATE_MOCK_1(int, foo, float);
```
where
* *1*: returns something and takes one parameter.

Then, the macro takes the return type, the name of the function following by the type of the parameter.

## TEST(testName) ... END_TEST

These macros define a test case where ``testName`` is the name of the test case. Inside the test case, the mock substitution, the execution of the code under test and further validations if any must be done. They are used as follows:

``` C
TEST(foo_thatReturnsOK)
    // Define the test case: substitutions, call of code under test, etc.
END_TEST
```

Note that each test case must be ran by a ``RUN_TEST`` macro with ``testName`` as parameter.

## SUB(funcName, subName, nbOfCalls)

Within a test case, ``SUB`` substitutes a function (``funcName``) that depends the code under test for another one (``subName``) and indicates the number of function calls expected. In the following example, the code under test will calls the function ``foo_test`` 2 times instead of calling ``foo``. The function ``foo_test`` must be defined in test file and allows developers to verify parameters' values as well as defines return value.

``` C
SUB(foo, foo_test, 2);
```

## ASSERT(test)

## RUN_TEST(testName)

## CALLING_INDEX(cutName)

## ATTACHED_SETUP(funcName) and ATTACHED_TEARDOWN(funcName)
