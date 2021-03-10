#include<iostream>
#include<string>

class Animal {
    public:
        std::string color;
        std::string name;
        float age;
};


class Snake : Animal {
    public:
        float length;
        void makeSound(){std::cout << "hiss!\n";}
};

class Cat : Animal {
    public:
        float height;
        void makeSound(){std::cout << "miau!\n";}
};

int main() {

    Snake snake;
    Cat cat;
    snake.makeSound();
    cat.makeSound();

    return 0;
}