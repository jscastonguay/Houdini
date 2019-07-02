# Application Programming Interface (API)

## Synthesis

Here is the of Houdini usage:

1. Create a new project. Make sure that the code under test and Houdini paths are added in the project *include* paths. Also make sure that the ``-Wall`` is added.
2. Create a new test file that is a normal C source file. Most of the time there is a test file for any source file to test.
3. In the test file, include *houdini.h* and the source file of the code under test (the .c file).
4. Depending on the test strategy (see [Project strategies section](getting-started.md#-project-strategies)), create a ``main`` function or a test runner function.
5. For each function to mock, call ``CREATE_MOCK_x`` where ``x`` is variable and depends on the return type and the parameter list types.
6. Then, create test cases and create substitution functions if any.
7. Don't forget to execute each test case with ``RUN_TEST`` in ``main`` or in test runner function.

Here is an example:

``` C
// This is a test file.

#include "houdini.h"           // Framework installation... Nothing more to do!
#include "path/to/cut.c"       // IMPORTANT: the code under test.

CREATE_MOCK_1(int, depFunc, float);  // Creates the mock mechanism for the function "depFunc".
                                     // Done only once per function to mock and per test file.

int depFunc_sub(float x) { ASSERT(x < 100.0); return 1; }  // Substitution function that will be 
                                                           // called by the code under test instead.

TEST(testName)                      // Starting point of the test case plus test case's name definition.

    SUB(depFunc, depFunc_sub, 2);   // Substitution of "depFunc" by "depFunc_sub" and indication
                                    // that the function will be called 2 times.

    int result = cutFunc();         // Execution of the code under test
    ASSERT(result == 0);            // and test of the results if required.
END_TEST

int main() {
    RUN_TEST(testName);             // Run the given test case.
    return 0;
}
```

## Marcos

Houdini is used through only 8 marcos:

* CREATE_MOCK_x(...)
* TEST(testName) ... END_TEST
* SUB(funcName, subName, nbOfCalls)
* ASSERT(test)
* RUN_TEST(testName)
* CALLING_INDEX(cutName)
* ATTACHED_SETUP(funcName)
* ATTACHED_TEARDOWN(funcName)

The following sections present each of them.

### CREATE_MOCK_x(...)

This macro creates the mock mechanism for a given function. **x** and the number of marco's parameters are variable and must be according to the return type and the parameter's definitions of the mock function. Use ``CREATE_MOCK_x`` only once per mock function per test file. Use the name of the marco as follows:

| Marcos         | For a function that ...                   |
| -------------- | ----------------------------------------- |
| CREATE_MOCK_V0 | returns ``void`` and takes no parameter   |
| CREATE_MOCK_0  | returns some thing and takes no parameter |
| CREATE_MOCK_V1 | returns ``void`` and takes 1 parameter    |
| CREATE_MOCK_1  | returns some thing and takes 1 parameter  |
| ...            | ...                                       |

Then, the macro's parameters correspond exactly to the function prototype, each element separated by a comma except for a function that returns ``void`` which is omitted.

#### Example 1

For a function declared as ``void foo(int x, float y);``, mock mechanism creation is as follows:
``` C
CREATE_MOCK_V2(foo, int, float);
```
where
* *V*: means return ``void``
* *2*: means 2 parameters

#### Example 2

For a function declared as ``int foo(float x);``, mock mechanism creation is as follows:
``` C
CREATE_MOCK_1(int, foo, float);
```
where
* *1*: returns something and takes one parameter.

### TEST(testName) ... END_TEST

These macros define a test case where ``testName`` is the name of the test case. Inside the test case, mock substitutions, the execution of the code under test and further validations if any must be done. They are used as follows:

``` C
TEST(foo_thatReturnsOK)
    // Define the test case: substitutions, call of code under test, etc.
END_TEST
```

Note that each test case must be run by a ``RUN_TEST`` macro with ``testName`` as parameter.

### SUB(funcName, subName, nbOfCalls)

Within a test case, ``SUB`` substitutes a function (``funcName``) that depends the code under test by another one (``subName``) and indicates the number of function calls expected. In the following example, the code under test will call the function ``foo_test`` 2 times instead of calling ``foo``. The function ``foo_test`` must be defined in test file and allows developers to verify parameters' values as well as defines return value.

``` C
SUB(foo, foo_test, 2);
```

### ASSERT(test)

This marco evaluates the parameter ``test``. If true, nothing append. If false, an error is generated with the file name and the line number. ``ASSERT`` can be use in test cases and in substitute functions.

``` C
ASSERT(x == 3);
```

### RUN_TEST(testName)

Each test case must be run using ``RUN_TEST`` macro. ``testName`` corresponds to the test name defined in ``TEST(testName) ... END_TEST`` macro. If the compiler option ``-Wall`` is used, a compiler warning will be generated if a test case is not run by a corresponding ``RUN_TEST``.

``` C
TEST(testTheFunctionFoo)
    ...
END_TEST

int main() {
    RUN_TEST(testTheFunctionFoo);
}
```

### CALLING_INDEX(subFuncName)

This marco returns the calling index (the number of calls - 1) of a given substitute function given by ``subFuncName``. ``CALLING_INDEX`` can be used within a substitute function and used to index a table.

``` C
void subFunc(int x) {
    int x_test[] = {10, 20, 30};
    unsigned int i = CALLING_INDEX(subFunc);
    ASSERT(x == x_test[i]);
}
```

### ATTACHED_SETUP(funcName) and ATTACHED_TEARDOWN(funcName)

Use ``ATTACHED_SETUP(funcName``) and ``ATTACHED_TEARDOWN(funcName)`` to install setup and/or teardown functions (``funcName``) that are called before and after every test case respectively. These marcos must be used in the ``main`` function or in the test running function within a given test file. ``funcName`` must be a name of a function that returns ``void`` and takes no parameter.

``` C
void theSetup() { cut_init(); }
void theTeardown() { cur_deinit(); }
int main() {
    ATTACHED_SETUP(theSetup);
    ATTACHED_TEARDOWN(theTeardown);
    RUN_TEST(testCase1);
}
```
