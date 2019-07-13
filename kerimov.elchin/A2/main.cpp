#include <iostream>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"

using namespace kerimov;
using std::cout;
using std::endl;
using std::cerr;

int main()
{
  try {
    Circle circle{ {5.0, 5.0}, 10.0 };
    Rectangle rectangle{ {{20.0, 20.0}, 40.0, 20.0} };

    cout << "Rectangle area = " << rectangle.getArea() << endl;
    cout << "Circle area = " << circle.getArea() << endl;

    const double ratio = 10.0;
    cout << endl << "After scaling with ratio = " << ratio << endl << endl;

    circle.scale(ratio);
    rectangle.scale(ratio);

    cout << "Rectangle area = " << rectangle.getArea() << endl;
    cout << "Circle area = " << circle.getArea() << endl;
  } catch(std::invalid_argument & ia) {
    cerr << ia.what() << endl;
    return 1;
  }

  return 0;
}
