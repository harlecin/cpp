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

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=/home/workspace/valgrind-out.txt /home/workspace/a.out

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

Wieso funktioniert das:
```
int *p = (int*)malloc(1); //malloc(2*sizeof(int))
    p[0] = 1; p[1] = 2;
```
--
From Udacity:
In some cases, it makes sense to separate memory allocation from object construction. Consider a case where we need to reconstruct an object several times. If we were to use the standard new/delete construct, memory would be allocated and freed unnecessarily as only the content of the memory block changes but not its size. By separating allocation from construction, we can get a significant performance increase.

C++ allows us to do this by using a construct called placement new: With placement new, we can pass a preallocated memory and construct an object at that memory location. Consider the following code:

void *memory = malloc(sizeof(MyClass));
MyClass *object = new (memory) MyClass;
There is however, no delete equivalent to placement new, so we have to call the destructor explicitly in this case instead of using delete as we would have done with a regular call to new:

object->~MyClass();
free(memory); 


In addition to the new and delete operators we have seen so far, we can use the following code to create an array of objects:

void* operator new[](size_t size);
void operator delete[](void*);

Let us consider the example on the right, which has been slightly modified to allocate an array of objects instead of a single one.
--


## exclusive copy
```
#include <iostream>

class ExclusiveCopy
{
private:
    int *_myInt;

public:
    ExclusiveCopy()
    {
        _myInt = (int *)malloc(sizeof(int));
        std::cout << "resource allocated" << std::endl;
    }
    ~ExclusiveCopy()
    {
        if (_myInt != nullptr)
        {
            free(_myInt);
            std::cout << "resource freed" << std::endl;
        }
            
    }
    ExclusiveCopy(ExclusiveCopy &source)
    {
        _myInt = source._myInt;
        source._myInt = nullptr;
    }
    ExclusiveCopy &operator=(ExclusiveCopy &source)
    {
        _myInt = source._myInt;
        source._myInt = nullptr;
        return *this;
    }
};

int main()
{
    ExclusiveCopy source;
    ExclusiveCopy destination(source);

    return 0;
}
```

## deep copy
```
#include <iostream>

class DeepCopy
{
private:
    int *_myInt;

public:
    DeepCopy(int val)
    {
        _myInt = (int *)malloc(sizeof(int));
        *_myInt = val;
        std::cout << "resource allocated at address " << _myInt << std::endl;
    }
    ~DeepCopy()
    {
        free(_myInt);
        std::cout << "resource freed at address " << _myInt << std::endl;
    }
    DeepCopy(DeepCopy &source)
    {
        _myInt = (int *)malloc(sizeof(int));
        *_myInt = *source._myInt;
        std::cout << "resource allocated at address " << _myInt << " with _myInt = " << *_myInt << std::endl;
    }
    DeepCopy &operator=(DeepCopy &source)
    {
        _myInt = (int *)malloc(sizeof(int));
        std::cout << "resource allocated at address " << _myInt << " with _myInt=" << *_myInt << std::endl;
        *_myInt = *source._myInt;
        return *this;
    }
};

int main()
{
    DeepCopy source(42);
    DeepCopy dest1(source);
    DeepCopy dest2 = dest1;

    return 0;
}
```


## Shared copy
```
#include <iostream>

class SharedCopy
{
private:
    int *_myInt;
    static int _cnt; //use static to make this variable visible to all instances

public:
    SharedCopy(int val);
    ~SharedCopy();
    SharedCopy(SharedCopy &source);
};

int SharedCopy::_cnt = 0;

SharedCopy::SharedCopy(int val)
{
    _myInt = (int *)malloc(sizeof(int));
    *_myInt = val;
    ++_cnt;
    std::cout << "resource allocated at address " << _myInt << std::endl;
}

SharedCopy::~SharedCopy()
{
    --_cnt;
    if (_cnt == 0)
    {
        free(_myInt);
        std::cout << "resource freed at address " << _myInt << std::endl;
    }
    else
    {
        std::cout << "instance at address " << this << " goes out of scope with _cnt = " << _cnt << std::endl;
    }
}

SharedCopy::SharedCopy(SharedCopy &source)
{
    _myInt = source._myInt;
    ++_cnt;
    std::cout << _cnt << " instances with handles to address " << _myInt << " with _myInt = " << *_myInt << std::endl;
}

int main()
{
    SharedCopy source(42);
    source.
    SharedCopy destination1(source);
    SharedCopy destination2(source);
    SharedCopy destination3(source);

    return 0;
}
```

- Deleting object remains that were moved?

make_unique()
make_shared()