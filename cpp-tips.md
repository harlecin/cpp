You can see in the above program that the variable count is declared as static. So, its value is carried through the function calls. The variable count is not getting initialized for every time the function is called.
As a side note, Java doesn’t allow static local variables in functions.
Static variables in a class: As the variables declared as static are initialized only once as they are allocated space in separate static storage so, the static variables in a class are shared by the objects. There can not be multiple copies of same static variables for different objects. Also because of this reason static variables can not be initialized using constructors. 

source:https://www.geeksforgeeks.org/static-keyword-cpp/

Exercise: Static Method

In addition to static member variables, C++ supports static member functions (or "methods"). Just like static member variables, static member functions are instance-independent: they belong to the class, not to any particular instance of the class.

One corollary to this is that we can method invoke a static member function without ever creating an instance of the class.

You will try just that in this exercise.
source: udacity.com


## Debugging with gdb

### finding seg-faults and std::bad_alloc
https://www.tutorialspoint.com/how-to-find-segmentation-error-in-c-and-cplusplus-using-gdb

gdb ./a.out core
catch catch -> catch exception and show catch point
r -> to run 
set break point on specific exception:
b 'std::bad_alloc::bad_alloc()'

use backtrace to see trace

## Const correctness
https://www.cprogramming.com/tutorial/const_correctness.html

## Valgrind on Linux
https://www.cprogramming.com/tutorial/const_correctness.html

## Class members and initialization the right way
https://medium.com/pranayaggarwal25/using-modern-class-members-and-initializations-c11e931c3ba

## Overview ByVal, ByRef, ByPointer
```
#include <stdio.h>
    
void CallByValue(int i)
{
    int j = 1; 
    printf ("call-by-value: %p\n",&j);
}

void CallByPointer(int *i)
{
    int j = 1; 
    printf ("call-by-pointer: %p\n",&j);
}

void CallByReference(int &i)
{
    int j = 1; 
    printf ("call-by-reference: %p\n",&j);
}

void CallByReferenceConst(int const &i) {
    int j = 1;
    printf ("call-by-reference: %p\n",&j);
}

int main()
{
    int i = 0;
    printf ("stack bottom: %p\n",&i);
    
    CallByValue(i);

    CallByPointer(&i);

    CallByReference(i);

    CallByReferenceConst(i);

    return 0;
}
```
vs.
```
#include<iostream>
using namespace std;
class Demo {
   int val;
   public:
   Demo(int x = 0) {
      val = x;
   }
   int getValue() const { //--> this tells the compiler that the function will not modify the class object Demo, but if you pass arguments they can be modified! (void X::access(Y const& y) const;)
      return val;
   }
};
```