#include <string>
#include <cstring>
#include <iostream>

class Car {
    // TODO: Declare private attributes
    private:
        int horsepower;
        double weigth;
        std::string brand;
    // TODO: Declare getter and setter for brand
    public:
        Car(int hp, double w, char* brand) {
            setHorsePower(hp);
            setWeight(w);
            setBrand(brand);
        }

        void setHorsePower(int hp);
        void setWeight(double w);
        void setBrand(char* brand);

        int getHorsePower() const;
        double getWeight() const;
        std::string getBrand() const;

};

// Define setters
void Car::setHorsePower(int hp) { this->horsepower = hp;}
void Car::setWeight(double weight) { this->weigth = weight;}
void Car::setBrand(char* brand) { this->brand = brand;}

int Car::getHorsePower() const {return this->horsepower;}
double Car::getWeight()  const {return this->weigth;}
std::string Car::getBrand() const {
    return this->brand;
}

// Define getters

// Test in main()
int main() 
{
    char brand[] = {"Peugeot"};
    Car car = Car(10, 2500.1, brand);
    std::cout << car.getBrand() << "\n";   
}

// Array to pointer decay: https://stackoverflow.com/questions/1461432/what-is-array-to-pointer-decay#1461449