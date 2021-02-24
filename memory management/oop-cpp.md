# Classes and OOP

C++ is also commonly called C with classes, but before we dive into classes let's take a look at `structures`:

## Structures
Structs allow you define your own custom types to complement the build-in types (also called 'primitives' or fundamental types) such as `int`, `float`, `string` and so forth. For example we could implement the following type:
```
struct Date {
    // You can provide defaults in {}
    int day{1};
    int month{1};
    int year{1970};
};

Date date;
date.day = 1;
date.month = 1;
date.year = 2020;
```

We can also restrict access and validate inputs like so:
```
struct Date {
    // You can provide defaults in {}
    // You can use private and public to restrict access
    // We used const to protect member data in getters
    public:
        int Day() const { return day; }
        int Month() const { return month; }
        int Year() const { return year; }

        void Day(int d) { 
            if(d > 0 && d <= 31) {day = d;}
        }
    private:
        int day{1};
        int month{1};
        int year{1970};
};

Date date;
date.Day(1);
date.Month(1);
date.Year(2020);
```
Private attributes can only be accessed and changed by methods from within the struct. If we set members as private, we need methods to access and change them, called 'getters' and 'setters'.

As you can see, the code became quite a bit longer and harder to read, so if possible keep attributes public and avoid gettes and setters.

What we did above is we defined 'invariants'. Invariants restrict the range of attributes, so it is basically a rule that defines which values are allowed.

## Classes

You could also implement your custom type as a class. All you have to do is switch the `struct` keyword with the `class` keyword. The key difference is that structs use public access by default and classes private access. You can find a detailed discussion of when to use classes vs. structs in [this stackoverflow post](https://stackoverflow.com/questions/54585/when-should-you-use-a-class-vs-a-struct-in-c#54596)

### Constructors

Constructors initalize objects. All classes come with a default constructor that takes no arguments, but we can also implement our own. 

Including a constructor is easy, just include a method with the same name as the class:
```
class Date {
    public:
        // We used an initalizer list, but be careful this by-passes potential setters!
        Date(int d, int m, int y): year(y) {
            day = d;
            month = m;
        }
    private:
        int day;
        int month;
        int year;
};

```
The benefit of using initalizer lists is that initialization sets the value as soon as the object exits in contrast to assigment which sets the value after the object is created (see [c++ core guidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c49-prefer-initialization-to-assignment-in-constructors)). Member variables can be set to `const` if you use an initializer list!

The syntax for initializer lists is simple: Pass the argument to the constructor to the variable you want to assign to in ():
```
...
    public:
        Constructor(int v): var(v) {}

    private:
        int var;
...
```
Also note that attributes defined as references have to use initialization lists!


In order to keep our class definition lean, we can separate the code for class declaration (header file) and class definition (cpp file):
```
// date.h
class Date {
    public:
        int Day();
        int Month();
        int Year();
    private:
        int day{1};
        int month{1};
        int year{1};
};

// date.cpp
include "date.h"

int Date::Day() { return day; }
int Date::Month() { return month; }
int Date::Year() { return year; }
```
## Composition vs. Inheritance

<TODO: include>

## Virtual functions

We can use virtual functions to create an abstract base class like so:

```
#include <iostream>

class Vehicle {
    virtual void Drive() const = 0;
};

class Car : Vehicle {
    void Drive() {
        std::cout << "brumbrum\n";
    }
};
```
Virtual functions can be used to declare an interface. By having `=0` behind the virtual function, we declare it as a 'pure' virtual function. A pure virtual function is only declared, but not defined. Pure functions make a class abstract, i.e. it cannot be instantiated. You can also omit the `=0` and provide an implementation for the virtual function.

I