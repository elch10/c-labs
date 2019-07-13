#include <iostream>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"

using std::cout;
using std::endl;
using std::cerr;

void printShapeInfo(const Shape & shape)
{
  cout << "Area = " << shape.getArea() << endl;
  rectangle_t rect = shape.getFrameRect();
  cout << "Frame rect: x = " << rect.pos.x << ", y = " << rect.pos.y
      << ", width = " << rect.width << ", height = " << rect.height << endl;
}

int main()
{
  try {
    Circle circle{ {5.0, 5.0}, 10.0 };
    Rectangle rectangle{ {{20.0, 20.0}, 40.0, 20.0} };

    cout << "\t\tCircle" << endl;
    printShapeInfo(circle);
    cout << "\t\tRectangle" << endl;
    printShapeInfo(rectangle);

    circle.move(15.0, 15.0);
    rectangle.move({5.0, 5.0});

    cout << "-----------After Move-----------" << endl;

    cout << "\t\tCircle" << endl;
    printShapeInfo(circle);
    cout << "\t\tRectangle" << endl;
    printShapeInfo(rectangle);
  } catch(std::invalid_argument & ia) {
    cerr << ia.what() << endl;
    return 1;
  }

  return 0;
}
