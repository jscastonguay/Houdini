# Getting Started

We will go through a simple example to show Houdini's features and how to use them. First of all, get Houdini from github by cloning the project or by downloading it. Note that this example uses GCC tool chain.

In this document, we will ... TDB

The example shown below is extracted from the test file *utest.c* that tests the code under test *application.c* that depends on *adc.h*.

## Presentation of Houdini directory structure

By cloning or downloading Houdini, you get

```
houdini
|-- doc
|-- example
|-- src
|-- test
```
where
* *docs* is the folder of Houdini documentation
* *example* presents the example used within this getting started
* *src* is the folder of the Houdini source code: *test.h* and *houdini.h*
* *test* is the folder of test cases used to test Houdini

In this getting started, we use the example source code and test project.

```
houdini
|-- example
    |-- app
        |-- adc.h
        |-- application.c
    |-- utest
        |-- Makefile
        |-- utest.c
```
where
* *application.c* is the code under test (CUT)
* *adc.h* is the code that the CUT depends on (i.e. this is the dependency of the CUT)
* *utest.c* is the test code (i.e. test cases and test runner)
* *Makefile* is the test project definition

The test cases defined in *utest.c* test functions defined in *application.c* that depends on *adc.h*. The *makefile* build the test project using GCC tool chain.

## Project setup

### In test file

A test project is made of test files (standard C source file). Each test file **includes** Houdini framework simply by ``#include "houdini.h"``. Then a test file **includes an application file (the code under test)** by doing ``#include "path/to/cut.c"``. This is a base principle behind Houdini: the test cases are within the same compiler "unit" than the code under test. Also, each test file must include a test runner function that may be a ``main`` function or another function depending on the strategy used for the test project (see TBD). The following source code shows the project setup in *utest.c* for the Houdini example:

``` C
#include "../../src/houdini.h"
#include "../../example/app/application.c"

int main() {
  return 0;
}
```

### In project definition

Obviously, the test project must instruct the compiler with the path of the code under test and Houdini source code such way that the references are resolved. The example uses GCC tool chain but can be any type of development environment for any target. Here is the *Makefile* of the test project:

``` bash
all:
	gcc -I"../../src" -I"../../example/app" -Wall -Wextra -g -o utest.exe utest.c
```

Note that it is important to add ``-Wall`` compiler option. Explanation later (TODO: dire que c'est si un test est défini TEST..ENDTEST mais pas ajouté au test runner).

### In Houdini framework

Houdini framework is made of two files: *Houdini.h* that is the implementation of the mock mechanism and *test.h* that defines the way used by Houdini to output the test results. *Houdini.h* is portable and should not be modified. *test.h* can be modified by the developers for their given development environments.  

*test.h* makes 4 definitions:
* ``PRINT(text)`` that prints the given *text*
* ``PRINT_INT(nb)`` that prints the given number *nb* in integer format
* ``FLUSH()`` that blocks until all data has been outputted correctly
* ``ASSERT(test)`` that outputs an error if the given *test* is false

The release version of Houdini uses ``printf`` and ``fflush`` in *test.h*. If your development environment supports them, you can let *test.h* unchanged. However, modifying the definitions for a microcontroller (or another kind of output) should not be a challenge.

## First test case without mock functions

Here is a first test case that don't need any mock function: it tests the function ``application_reset`` that resets the global variable ``temperature`` to -1.

``` C
TEST(application_reset)
	temperature = 100;
	application_reset();
	ASSERT(temperature == -1);
END_TEST

int main() {
  // RUN_TEST of other test cases omitted in this documentation
  RUN_TEST(application_reset);
  return 0;
}
```

This is a lot of code only to make this small test. However, the structure there is required when some functions are mock. Use the structure even if it is not the case. A test case is defined between by two macros ``TEST(testName)`` and ``END_TEST``. The ``testName`` can be any name but must be unique among all test names. ``ASSERT`` marco outputs an error message in consol when it falls.  

Finally, the marco ``RUN_TEST`` is called with the name of the given test case to run. This can be done in the ``main`` function or in another function depending on the strategy used for the test project (see TBD).

## First test case with mocks functions

Lets see the first test case with mocks functions.

``` C
CREATE_MOCK_V0(ADC_init);
CREATE_MOCK_0(ADC_Status, ADC_getStatus);

void ADC_init_1() {}
ADC_Status ADC_getStatus_OK() { return ADC_OK; }

TEST(application_init_ADCStatusOK)

	SUB(ADC_init, ADC_init_1, 1);
	SUB(ADC_getStatus, ADC_getStatus_OK, 1);

	int result = application_init();

	ASSERT(result == 0);

END_TEST

int main() {
  // RUN_TEST of other test cases omitted in this documentation
  RUN_TEST(application_init_ADCStatusOK);
  return 0;
}
```

A marco must be called for every function mock that creates the mocking mechanism. To do so, use the macro ``CREATE_MOCK_x`` where ``x`` vary according to the return type and the number of function's parameters of the function to mock. **This is done only once per function to mock per test file.** Depending on whether the development is done in Test Driven Development (TTD) mode or if the writing of the test cases are done after writing all code, the location of the creation of mock mechanism in the test file may differ. The following shows the mocking mechanism creation of the example above:

``` C
CREATE_MOCK_V0(ADC_init);
CREATE_MOCK_0(ADC_Status, ADC_getStatus);
```

Here, 2 mock mechanisms are created for 2 functions: ``void ADC_init(void)`` and ``ADC_Status ADC_getStatus()``. *V0* indicates that the function to mock returns ``void`` and has no parameter. Then, the marco take only the name of the function to mock. *0* indicates that the function to mock returns something but takes no parameter. Then, the macro takes the return type following by the name of the function to mock.  

Later, the 2 mock functions will be **substitute** by test functions in test case definition that have the same *signature* than the function to mock (same return type and same parameters). Before that, these test functions must be created. Here are these two test functions of the above example:

``` C
void ADC_init_1() {}
ADC_Status ADC_getStatus_OK() { return ADC_OK; }
```

As we will see later, we can do everything in there test functions: using ``ASSERT`` to test parameters' value, return any value by ``return`` keyword or by reference, all of this depending of the function definition. The only restriction is that their name must be unique in the test file.  

Then, the macros ``TEST() ... END_TEST`` encapsule the test case's definition and define the test's name. In this definition, the marco ``SUB`` substitutes functions to mock by test functions and indicates how many times the functions should be called by the code under test. Here is the ``SUB`` usage from the example:

``` C
	SUB(ADC_init, ADC_init_1, 1);
	SUB(ADC_getStatus, ADC_getStatus_OK, 1);
```

The first substitution indicates that ``ADC_init_1`` is called instead of the real dependency function ``ADC_init`` and that the code under test will call it only once. Finally, the code under test is called and a verification is done if required. Then new test cases can be defined in the same test file.  

**That's it for Houdini basis !** The following shows you other important details.

## Substitute functions

The substitute functions can have any name. The only restriction is that they must have the same *signature* of the function they mock. A substitute function can be specific to one test case or generic and reused between several test cases. From the example above, consider the following test case:

``` C
ADC_Status ADC_getStatus_ERROR() { return ADC_ERROR; }

TEST(application_init_ADCStatusERROR)

	SUB(ADC_init, ADC_init_1, 1);
	SUB(ADC_getStatus, ADC_getStatus_ERROR, 1);

	int result = application_init();

	ASSERT(result == 1);

END_TEST
```

``ADC_getStatus`` is substitute by the new substitution function ``ADC_getStatus_ERROR`` while ``ADC_init_1`` is reused. Note that ``CREATE_MOCK_x`` doesn't need to be called again for ``ADC_getStatus`` and ``ADC_init`` since the operation has already be done before.

## Several function's calls and ``CALLING_INDEX`` macro

A mock function can be called more then once. The ``CALLING_INDEX`` helps to know, within a substitute function, how many time the function has been called. Note that the macro returns an *index*, not the number of calls, meaning that the value starts to 0, not to one. So the return value of ``CALLING_INDEX`` can be used directly to index a table as the following example:

``` C
CREATE_MOCK_1(int, ADC_getRawValue, int);

int ADC_getRawValue_1(int ch) {
  int retValues[] = {100, 200, 300, 400, 500};
  ASSERT(ch == 2);
  unsigned int i = CALLING_INDEX(ADC_getRawValue);
  return retValues[i];
}

TEST(application_computeTemperature)
	SUB(ADC_getRawValue, ADC_getRawValue_1, 5);
	application_computeTemperature();
	ASSERT(temperature == 30);
END_TEST

int main() {
  // RUN_TEST of other test cases omitted in this documentation
  RUN_TEST(application_computeTemperature);
  return 0;
}
```

In this case, ``ADC_getRawValue`` is called 5 times. Each time the parameter value must be 2. However, the function returns a different value at each call, from 100 to 500.

## Complex data types, values returned by reference and static declaration

One of the strengths of Houdini is its capacity to manage complex data type, pointers and so one. It is also easy to return value by reference. Here is another example:

``` C
CREATE_MOCK_V1(ADC_getConfig, ADC_Config *);

void ADC_getConfig_givenValues(ADC_Config *config) {
  config->nbChannels = 4;
  config->nbBits = 10;
}

TEST(verifyConfig_returnTrue)
  SUB(ADC_getConfig, ADC_getConfig_givenValues, 1);
  ASSERT(verifyConfig() == true);
END_TEST

int main() {
  // RUN_TEST of other test cases omitted in this documentation
  RUN_TEST(verifyConfig_returnTrue);
  return 0;
}
```

Developers have all the latitude to manipulate complex data types and pointers easily. Note that since the code under test is *included* with the test code, static definitions like the function ``verifyConfig`` and the global variable ``temperature`` can be used and tested.

## General setup and teardown

It can be convenient to use general setup and teardown that are executed for each test cases. It is easily done, see the following example (note that this one is not part of the Houdini *exemple* folder and files):

``` C
Sensor * sensor = NULL;

void setup_1() {
  sensor = malloc(sizeof(Sensor));
  sensor->init = false;
}

void setup_2() {
  sensor = malloc(sizeof(Sensor));
  sensor->init = true;
}

void teardown() {
  free(sensor);
}

int main() {
  
  RUN_TEST(testCase1);

  ATTACHED_SETUP(setup_1);
  ATTACHED_TEARDOWN(teardown);
  RUN_TEST(testCase2);
  RUN_TEST(testCase3);

  ATTACHED_SETUP(setup_2);
  RUN_TEST(testCase4);

  ATTACHED_SETUP(NULL);
  ATTACHED_TEARDOWN(NULL);
  RUN_TEST(testCase5);

  return 0;
}
```

## Project strategies

Test strategy: un main par fichier, plusieurs fichiers pour un seul main...

## Last details

* 
* Pourquoi -Wall
* Les outputs...
* #define HOUDINI dans houdini.h, ça peut servir entre autre pour tester main

## Synthesis (on va en faire un vrai getting started)

``` C
// This is a test file.

#include "path/to/houdini.h"   // Framework installation... Nothing more to do!
#include "path/to/cut.c"       // IMPORTANT: the code under test.

CREATE_MOCK_1(int, depFunc, float);  // Creates the mock mechanism for the function "depFunc".
                                     // Done only once per function to mock and per test file.

int depFunc_sub(float x) { ASSERT(x < 100.0); return 1; }  // Substitution function that will be 
                                                           // called by the code under test instead.

TEST(testName)                    // Starting point of the test case plus test case's name definition.

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

## Test

![alt text]()./UML.png)