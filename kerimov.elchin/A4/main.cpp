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
    
    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {1.0, 1.0}, 20.0, 15.0 });
    cs.add(rect);
  
    std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{2.0, 2.0}, 10.0);
    cs.add(circle);

    cout << "\tBefore rotating" << endl;
    printShapeInfo(cs);
    
    cout << "\tAfter rotating" << endl;
    cs.rotate(60.0);
    printShapeInfo(cs);

    Matrix matrix = cs.split();

    for (size_t i = 0; i < matrix.getLayers(); ++i) {
      Matrix::layer_type layer = matrix[i];
      cout << "\t\tLayer " << i << ":" << endl;
      for (size_t j = 0; j < matrix.getLayerSize(); ++j) {
        if (!layer[j]) {
          break;
        }
        cout << "\tElement " << j << ":" << endl;
        printShapeInfo(*layer[j]);
      }
    }

  } catch(const std::bad_alloc & ba) {
    cerr << ba.what() << endl;
    return 2;
  } catch(const std::exception & ia) {
    cerr << ia.what() << endl;
    return 1;
  }

  return 0;
}
