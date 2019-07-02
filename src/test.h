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

#ifndef TEST_H
#define TEST_H

#include <stdio.h>

//Prefix added to each ERROR or warning messages. Useful to separate test names from
// errors/warnings printed to the console.
#define PREFIX  "   "

// Can be redefined for your system if required. mock.h uses 
//    - PRINT macro but without variable arguments. You can redefine it as
//      simple as a "write string" function.
//    - PRINT_INT to print line numbers.
//    - FLUSH in some circumstances when it is important to make sure that
//      the error message is outputted before the next line of code.
#define PRINT(text) printf(text)
#define PRINT_INT(nb) printf("%d", nb);
#define FLUSH() fflush(NULL);

#define ASSERT(test) if (!(test)) { PRINT(PREFIX "ERROR ("); PRINT(#test); PRINT(") in "); PRINT(__FILE__); PRINT(" at line "); PRINT_INT(__LINE__); PRINT("\n\r"); }
#define ASSERT_EQ(x, y) if ((x) != (y)) { PRINT(PREFIX "ERROR (value is "); PRINT_INT(x); PRINT(", expected equal to "); PRINT_INT(y); PRINT(") in "); PRINT(__FILE__); PRINT(" at line "); PRINT_INT(__LINE__); PRINT("\n\r"); }
#define ASSERT_LE(x, y) if ((x) > (y)) { PRINT(PREFIX "ERROR (value is "); PRINT_INT(x); PRINT(", expected least or equal to "); PRINT_INT(y); PRINT(") in "); PRINT(__FILE__); PRINT(" at line "); PRINT_INT(__LINE__); PRINT("\n\r"); }
#define ASSERT_LT(x, y) if ((x) >= (y)) { PRINT(PREFIX "ERROR (value is "); PRINT_INT(x); PRINT(", expected least then "); PRINT_INT(y); PRINT(") in "); PRINT(__FILE__); PRINT(" at line "); PRINT_INT(__LINE__); PRINT("\n\r"); }
#define ASSERT_GE(x, y) if ((x) < (y)) { PRINT(PREFIX "ERROR (value is "); PRINT_INT(x); PRINT(", expected greater or equal to "); PRINT_INT(y); PRINT(") in "); PRINT(__FILE__); PRINT(" at line "); PRINT_INT(__LINE__); PRINT("\n\r"); }
#define ASSERT_GT(x, y) if ((x) <= (y)) { PRINT(PREFIX "ERROR (value is "); PRINT_INT(x); PRINT(", expected greater then "); PRINT_INT(y); PRINT(") in "); PRINT(__FILE__); PRINT(" at line "); PRINT_INT(__LINE__); PRINT("\n\r"); }

#endif