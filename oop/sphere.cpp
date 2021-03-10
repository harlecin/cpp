#include <cassert>
#include <cmath>
#include <stdexcept>
#include <numbers>
#include <cmath>
// TODO: Define class Sphere
class Sphere {
 public:
  // Constructor
    Sphere(double radius) {
        Radius(radius);
    }
  // Accessors
    void Radius(double radius) {this->radius_=radius;}
    double Radius() {this->radius_;}
    double Volume() { this->radius_*this->radius_*std::numbers::pi;}
 private:
  // Private members
  double radius_;
};

// Test
int main(void) {
  Sphere sphere(5);
  assert(sphere.Radius() == 5);
  assert(abs(sphere.Volume() - 523.6) < 1);
}