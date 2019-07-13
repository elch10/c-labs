#include <iostream>
#include <memory>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace kerimov;
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
    CompositeShape cs;

    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {10.0, 20.0}, 10.0, 2.0 });
    cs.add(rect);

    std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{ 5.0, 6.0 }, 10.0);
    cs.add(circle);

    cout << "\tBefore scaling" << endl;
    printShapeInfo(cs);
    
    cout << "\tAfter scaling" << endl;
    cs.scale(5.0);
    printShapeInfo(cs);

    cout << "\tAfter moving" << endl;
    cs.move(10.0, 20.0);
    printShapeInfo(cs);

  } catch(const std::bad_alloc & ba) {
    cerr << ba.what() << endl;
    return 2;
  } catch(const std::exception & ia) {
    cerr << ia.what() << endl;
    return 1;
  }

  return 0;
}
