# C++ Foundations

When I left my old job at Austrian Post, my colleagues got me an amazing parting-gift: An Amazon Deep Racer :)

While it is quite easy to work with Deep Racer using AWS sagemaker, I wanted to program Deep Racer directly. Deep Racer runs on Ubuntu Linux with the Robot Operating System (ROS).

ROS is primarily programmed in C++ (although there are wrappers for Python and Julia). I took a C/C++ course many years ago at university and so I decided maybe this is the perfect reason to dive into C++ again, so here I am :)

Since my knowledge of C++ is extremely rusty/non-existent anymore, I decided to start from the foundations again.

## Getting started

Maybe it's best to take a quick look at the C++ core guidelines first. You can find them [here](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#mains). The core guidelines outline lot's of different best practices one can follow. 

The most important namespace of cpp is the standard library `std::`. Use `std::vector` to access the `vector` class in the SL and include the necessary head file: `#include <vector>'.

Perhaps the single most frustrating thing about compiled languages is that the need to be compiled (I know, shocking:) and often there is no "official" compiler. The same is true for cpp. There are lots of different compilers to choose (e.g. g++, clang, or the visual studio c++ compiler).

If you are working with VS Code, there is a very nice overview how to setup everything to get started programming in cpp [here](https://code.visualstudio.com/docs/cpp/config-msvc).

To help simplify the build process you can use so called 'build tools' (again shocking, righ?:). Popular ones are `MAKE` and `CMAKE`. Build tools automate compiling lots of different source code files into object files and finally linking them together to create an executable. They are also often smart enough to figure out to rebuild only files that changed and so can speed up the build process quite a bit.

Since I am working on both Windows and Linux systems, I will probably stick to `CMAKE`.

You can also install the `clang-format` VS Code extension to help format your code in a consistent manner.

## Intro to C++ Syntax
Contrary to R or Python, every C++ program contains a `main()` function that is executed automatically when the program starts. This is the entry point to your code:

```
#include <iostream> // preprocessor command: executed before compilation - gets iostream.h

using std::cout;    // this is cpp's version of Python's from foo import bar
int main() {        // main returns int

    // print to standard out
    cout << "Hello World!" << "\n";

    return 0;       // 0 = success
}
```
You also have to end your commands with `;` unfortunately...

A very important container type to store data is the `vector`.

```
#include <iostream>
#include <vector>

using std::vector;
using std::cout;

int main() {
    vector<int> vec_1{0, 1, 2};
    vector<int> vec_2 = {3,4,5};
    vector<int> vec_3;
    vec_3 = {6};

    //nested vector
    vector<vector<int>> vec_nested {{1,2}, {3,4}};

    cout << "Vectors rock XD \n";

    return 0;
}
```
If you don't want to bother specifying the type manually, you can use `auto` to let the compiler figure out the type (but that can lead to problems if you accidentally get ints instead of floats for example):
```
    vector<int> vec_manual = {1,2}
    auto vec_auto = {3,4}
```

You can access vector elements like so (Attention R people - 0 based indexing:):
```
vector<int> vec = {0, 1, 2, 3, 4};
    cout << vec[0];
    cout << vec[1];
    cout << vec[100];   //Undefined behavior!
    cout << vec.size()

    vec.push_back(5)    // Add item to end of vecto
```

Now let's take a look at looping:
```
//index-based loop:
for (int i=0; i < 10; i++) { //start condition; run until; de-/increment by ...
    cout << i << "\n";
}

//range-based loop:
vector<vector<int>> vec = {{1,2,3,4}, {5}};
for (vector<int> i: vec) {
    for(int j: i){
        cout << j << "\n";
    }
}
```

While loops work as follows:
```
int i = 1;
while(i < 11){
    if(i % 2 == 0) {
        cout << i << "\n";
    }
    i++;
}
```

Declaring functions is also straightforward:
```
//use 'void' if your function does not return values
return_type SomeFunctionName(type_param1 param1, type_param2 param2) {
    // stuff
    return something_with_return_type;
}
```
Now let's take a look at `enum`, short for enumerator. You can use `enum` to define custom types in cpp. A color type could look like this:
```
// create the enum class
enum class Color {white, black, blue, red};

// set my_color to blue
Color my_color = Color::blue;
```

You can pass values by reference like so:
```
int AddOne(int &i){
    return i++;
}
```

Use `const` if you want to enforce that a variable is not mutated after it is initalized at runtime. `constexpr` is used to guarantee that a variable can be evaluated at compile time and is not mutated after initialization.

If you want to guard against accidentally changing a variable that is passed by reference, use `const`.

## OPEN

- Core Guidelines checker for VS Code?
- Difference between int vec[2]{0,1} and vector<int> vec{0,1}: array vs. vector
- Are there no named parameters in c++ functions?