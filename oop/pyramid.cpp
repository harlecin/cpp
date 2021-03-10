#include <cassert>
#include <stdexcept>

class Pyramid {
    public:
        Pyramid(double l, double w, double h) {
            SetLength(l);
            SetWidth(w);
            SetHeight(h);
        }

        void SetLength(double l) {
            if(l >= 0) {
                this->length_ = l;
                } else {
                    throw std::invalid_argument("negative dimension");
                } 
            }
        void SetWidth(double w) {
            if(w >= 0) {
                this->width_ = w;
               }
            }
        void SetHeight(double h) {
            if(h >= 0){
                this->height_ = h;
                }
            }

        double GetLength() {return this->length_;}
        double GetWidth() {return this->width_;}
        double GetHeight() {return this->height_;}
        double Volume() {
            return this->length_*this->width_*this->height_*1/3;
        }

    private:
       double length_;
       double width_;
       double height_;
};

// Test
int main() {
  Pyramid pyramid(4, 5, 6);
  assert(pyramid.GetLength() == 4);
  assert(pyramid.GetWidth() == 5);
  assert(pyramid.GetHeight() == 6);
  assert(pyramid.Volume() == 40);

  bool caught{false};
  try {
    Pyramid invalid(-1, 2, 3);
  } catch (...) {
    caught = true;
  }
  assert(caught);
}