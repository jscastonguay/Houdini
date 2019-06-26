# Houdini - A Unit Testing and Mocking Framework for C Language

IN DEVELOPMENT !!!

Houdini is a easy unit testing and mocking framework for **C language**, especially for **embedded systems**. It is implemented in only **two C header files** and does not required any complex scripting language or complex environment.

> Everything is in C, no C++, no Python, no Ruby, just good old plain C, even for the mocking framework !!!

Unit testing framework is the easy part: every C programmer can do it minimally with the standard `` assert() `` or the equivalent. The real challenge however is managing the dependencies with a mocking framework and this is our focus. Houdini is not perfect, there are other frameworks that are pretty good at mocking functions that take less testing code. But often they use either C++ features and/or an external tool/language like python or ruby that make the glue between elements. This is where Houdini is special:

* Only two C header files;
* only five marcos for the basic usage;
* helped by three other marcos if needed.

This simplicity allows:

* Easy learning
* Easy integration with build tool
* Easy integration with embedded target (i.e. microcontrollers from small 8 bits to 32 bits MCUs) or microcontroller simulator
* Developers have control over almost everything 
* No weird tool's errors

The only things required by the developers are knowing C language and knowing how to setup a project for their development environment.

> Houdini should be a good compromise between functionalities, test efforts and usability for C language and embedded systems.

Here is a small example of a test case. The code under test, the function `` int application_init() ``, is defined in *application.c*. This function depends on another file as it calls the function `` int ADC_init(int)``.

``` C
#include "../../src/houdini.h"
#include "../../example/app/application.c"

// Done only once per test file
CREATE_MOCK_1(int, ADC_init, int);

// Starting point of the test case
int sub1(int x) { ASSERT(x == 2); return 1023;}

TEST(application_init_EverythingOK)
  SUB(ADC_init, sub1, 1);
  int result = application_init();
  ASSERT(result == 0);
END_TEST
// Ending point of the test case

// "Test runner" for all tests
int main() {
  RUN_TEST(application_init_EverythingOK);
  return 0;
}
```

If ``ADC_init`` is not called once by ``application_init`` or if it does not received the value of 2 in parameter, an error will be produced. If the code under test does not react correctly to the return value of ``ADC_init``, another error will be generated. Finally, if ``application_init`` calls functions from dependencies that are not suppose to, an error will also be produced.

## Getting started and user guide

Houdini is easy to use. You only have to know how code in C and how to create and configure a project for the desire development environment. Here are two documents to read:

* [Getting started guide that shows how Houdini works](getting-started.md)
* [Application Programming Interface (API)](api.md)

## How to install Houdini

### For using Houdini

Clone or download Houdini. The Houdini source code is under *src* folder. The source code consists of two files: *test.h* and *houdini.h*. Develop and build your test project using these two files.

### For testing or execute the example of Houdini

Clone or download Houdini. Make sure that your system support GCC tool chain.
* To test Houdini, go to *test* folder. Do *make*, then *./test*.
* To try Houdini with the example, go to *example/utest* folder. Do *make*, then *./utest*.

## Licence

TBD