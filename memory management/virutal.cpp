#include <assert.h>
#include <string>
#include <iostream>

class Animal {
public:
  virtual std::string Talk() const = 0;
  virtual void Walk() {std::cout << "Walk\n";};
};

// TODO: Declare a class Dog that inherits from Animal
class Dog : public Animal {
    public:
        std::string Talk() const override { return std::string("Woof");})
        
};

int main() {
  Dog dog;
  assert(dog.Talk() == "Woof");
  dog.Walk();
}