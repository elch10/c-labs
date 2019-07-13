#define BOOST_TEST_MODULE COMPOSITE_SHAPE
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace kerimov;

const double EPSILON = 1e-6;

BOOST_AUTO_TEST_CASE(CopyConstructor)
{
  CompositeShape cs2;

  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {10.0, 20.0}, 10.0, 2.0 });
  cs2.add(rect);

  std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 15.0);
  cs2.add(circle);

  CompositeShape cs1{cs2};

  BOOST_CHECK_EQUAL(cs1.getArea(), cs2.getArea());
  BOOST_CHECK_EQUAL(cs1.getSize(), cs2.getSize());
  rectangle_t rect1 = cs1.getFrameRect();
  rectangle_t rect2 = cs2.getFrameRect();
  BOOST_CHECK_EQUAL(rect1.width, rect2.width);
  BOOST_CHECK_EQUAL(rect1.height, rect2.height);
  BOOST_CHECK_EQUAL(rect1.pos.x, rect2.pos.x);
  BOOST_CHECK_EQUAL(rect1.pos.y, rect2.pos.y);
}

BOOST_AUTO_TEST_CASE(MoveConstructor)
{
  CompositeShape cs2;
  
  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {10.0, 20.0}, 10.0, 2.0 });
  cs2.add(rect);

  std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 15.0);
  cs2.add(circle);

  double beforeMovingArea = cs2.getArea();
  size_t beforeMovingSize = cs2.getSize();
  rectangle_t rect2 = cs2.getFrameRect();

  CompositeShape cs1{ std::move(cs2) };

  BOOST_CHECK_EQUAL(cs1.getArea(), beforeMovingArea);
  BOOST_CHECK_EQUAL(cs1.getSize(), beforeMovingSize);
  rectangle_t rect1 = cs1.getFrameRect();
  BOOST_CHECK_EQUAL(rect1.width, rect2.width);
  BOOST_CHECK_EQUAL(rect1.height, rect2.height);
  BOOST_CHECK_EQUAL(rect1.pos.x, rect2.pos.x);
  BOOST_CHECK_EQUAL(rect1.pos.y, rect2.pos.y);

  BOOST_CHECK_EQUAL(cs2.getArea(), 0.0);
  BOOST_CHECK_EQUAL(cs2.getSize(), 0.0);
  rect2 = cs2.getFrameRect();
  BOOST_CHECK_EQUAL(rect2.width, 0.0);
  BOOST_CHECK_EQUAL(rect2.height, 0.0);
  BOOST_CHECK_EQUAL(rect2.pos.x, 0.0);
  BOOST_CHECK_EQUAL(rect2.pos.y, 0.0);
}

BOOST_AUTO_TEST_CASE(AssignmentCopy)
{
  CompositeShape cs1, cs2;
  
  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {10.0, 20.0}, 10.0, 2.0 });
  cs2.add(rect);

  std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 15.0);
  cs2.add(circle);

  cs1 = cs2;

  BOOST_CHECK_EQUAL(cs1.getArea(), cs2.getArea());
  BOOST_CHECK_EQUAL(cs1.getSize(), cs2.getSize());
  rectangle_t rect1 = cs1.getFrameRect();
  rectangle_t rect2 = cs2.getFrameRect();
  BOOST_CHECK_EQUAL(rect1.width, rect2.width);
  BOOST_CHECK_EQUAL(rect1.height, rect2.height);
  BOOST_CHECK_EQUAL(rect1.pos.x, rect2.pos.x);
  BOOST_CHECK_EQUAL(rect1.pos.y, rect2.pos.y);
}

BOOST_AUTO_TEST_CASE(AssignmentMove)
{
  CompositeShape cs1, cs2;
  
  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {10.0, 20.0}, 10.0, 2.0 });
  cs2.add(rect);

  std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 15.0);
  cs2.add(circle);
  
  double beforeMovingArea = cs2.getArea();
  size_t beforeMovingSize = cs2.getSize();
  rectangle_t rect2 = cs2.getFrameRect();
  
  cs1 = std::move(cs2);

  BOOST_CHECK_EQUAL(cs1.getArea(), beforeMovingArea);
  BOOST_CHECK_EQUAL(cs1.getSize(), beforeMovingSize);
  rectangle_t rect1 = cs1.getFrameRect();
  BOOST_CHECK_EQUAL(rect1.width, rect2.width);
  BOOST_CHECK_EQUAL(rect1.height, rect2.height);
  BOOST_CHECK_EQUAL(rect1.pos.x, rect2.pos.x);
  BOOST_CHECK_EQUAL(rect1.pos.y, rect2.pos.y);

  BOOST_CHECK_EQUAL(cs2.getArea(), 0.0);
  BOOST_CHECK_EQUAL(cs2.getSize(), 0.0);
  rect2 = cs2.getFrameRect();
  BOOST_CHECK_EQUAL(rect2.width, 0.0);
  BOOST_CHECK_EQUAL(rect2.height, 0.0);
  BOOST_CHECK_EQUAL(rect2.pos.x, 0.0);
  BOOST_CHECK_EQUAL(rect2.pos.y, 0.0);
}

BOOST_AUTO_TEST_CASE(IndexingOperator)
{
  CompositeShape cs;
  
  const double width = 10.0, height = 2.0;
  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {10.0, 20.0}, width, height });
  cs.add(rect);

  const double radius = 15.0;
  std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, radius);
  cs.add(circle);
  
  BOOST_CHECK_CLOSE(cs[0]->getArea(), width * height, EPSILON);
  BOOST_CHECK_CLOSE(cs[1]->getArea(), M_PI * radius * radius, EPSILON);
}

BOOST_AUTO_TEST_CASE(InvalidIndexindOperator)
{
  CompositeShape cs;
  BOOST_CHECK_THROW(cs[0], std::out_of_range);

  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {10.0, 20.0}, 10.0, 2.0 });
  cs.add(rect);

  BOOST_CHECK_THROW(cs[1], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(GetArea)
{
  CompositeShape cs;
  
  const double width = 10.0, height = 2.0;
  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {10.0, 20.0}, width, height });
  cs.add(rect);

  const double radius = 15.0;
  std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, radius);
  cs.add(circle);

  BOOST_CHECK_CLOSE(cs.getArea(), width * height + M_PI * radius * radius, EPSILON);
}

BOOST_AUTO_TEST_CASE(GetFrameRect)
{
  CompositeShape cs;
  
  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {10.0, 20.0}, 10.0, 12.0 });
  cs.add(rect);

  std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{20.0, 40.0}, 5.0);
  cs.add(circle);

  rectangle_t frameRect = cs.getFrameRect();

  BOOST_CHECK_CLOSE(frameRect.pos.x, 15.0, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.pos.y, 29.5, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.width, 20.0, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.height, 31.0, EPSILON);
}

BOOST_AUTO_TEST_CASE(RelativeMove)
{
  CompositeShape cs;
  
  const rectangle_t rectanCenter = { {10.0, 20.0}, 10.0, 12.0 };
  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectanCenter);
  cs.add(rect);

  const point_t circleCenter = {10.0, 20.0};
  const double radius = 5.0;
  std::shared_ptr< Circle > circle = std::make_shared< Circle >(circleCenter, radius);
  cs.add(circle);

  const rectangle_t compositeRect = cs.getFrameRect();

  const double dx = 15.0, dy = 25.0;
  cs.move(dx, dy);

  rectangle_t afterMove = cs.getFrameRect();
  BOOST_CHECK_CLOSE(afterMove.pos.x, compositeRect.pos.x + dx, EPSILON);
  BOOST_CHECK_CLOSE(afterMove.pos.x, compositeRect.pos.x + dx, EPSILON);

  afterMove = cs[0]->getFrameRect(); // Rectangle
  BOOST_CHECK_CLOSE(afterMove.pos.x, rectanCenter.pos.x + dx, EPSILON);
  BOOST_CHECK_CLOSE(afterMove.pos.y, rectanCenter.pos.y + dy, EPSILON);
  BOOST_CHECK_CLOSE(cs[0]->getArea(), rectanCenter.width * rectanCenter.height, EPSILON);

  afterMove = cs[1]->getFrameRect(); // Circle
  BOOST_CHECK_CLOSE(afterMove.pos.x, circleCenter.x + dx, EPSILON);
  BOOST_CHECK_CLOSE(afterMove.pos.y, circleCenter.y + dy, EPSILON);
  BOOST_CHECK_CLOSE(cs[1]->getArea(), M_PI * radius * radius, EPSILON);
}

BOOST_AUTO_TEST_CASE(MovingToPoint)
{
  CompositeShape cs;
  
  const rectangle_t rectanCenter = { {10.0, 20.0}, 10.0, 12.0 };
  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectanCenter);
  cs.add(rect);

  const point_t circleCenter = {10.0, 20.0};
  const double radius = 5.0;
  std::shared_ptr< Circle > circle = std::make_shared< Circle >(circleCenter, radius);
  cs.add(circle);

  point_t initial = cs.getFrameRect().pos;
  const point_t desination = {100.0, 300.0};
  cs.move(desination);

  rectangle_t afterMove = cs.getFrameRect();
  BOOST_CHECK_CLOSE(afterMove.pos.x, desination.x, EPSILON);
  BOOST_CHECK_CLOSE(afterMove.pos.y, desination.y, EPSILON);

  afterMove = cs[0]->getFrameRect(); // Rectangle
  BOOST_CHECK_CLOSE(afterMove.pos.x - rectanCenter.pos.x, desination.x - initial.x, EPSILON);
  BOOST_CHECK_CLOSE(afterMove.pos.y - rectanCenter.pos.y, desination.y - initial.y, EPSILON);
  BOOST_CHECK_CLOSE(cs[0]->getArea(), rectanCenter.width * rectanCenter.height, EPSILON);

  afterMove = cs[1]->getFrameRect(); // Circle
  BOOST_CHECK_CLOSE(afterMove.pos.x - rectanCenter.pos.x, desination.x - initial.x, EPSILON);
  BOOST_CHECK_CLOSE(afterMove.pos.y - rectanCenter.pos.y, desination.y - initial.y, EPSILON);
  BOOST_CHECK_CLOSE(cs[1]->getArea(), M_PI * radius * radius, EPSILON);
}

BOOST_AUTO_TEST_CASE(Scaling)
{
  CompositeShape cs;
  
  const rectangle_t rectan = { {10.0, 20.0}, 10.0, 12.0 };
  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectan);
  cs.add(rect);

  const point_t circleCenter = {-15.0, 30.0};
  const double radius = 5.0;
  std::shared_ptr< Circle > circle = std::make_shared< Circle >(circleCenter, radius);
  cs.add(circle);

  point_t compositeCenter = cs.getFrameRect().pos;

  const double ratio = 12.0;
  cs.scale(ratio);

  rectangle_t afterScale = cs.getFrameRect();
  BOOST_CHECK_CLOSE(compositeCenter.x, afterScale.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(compositeCenter.y, afterScale.pos.y, EPSILON);

  afterScale = cs[0]->getFrameRect(); // Rectangle
  BOOST_CHECK_CLOSE(afterScale.pos.x, rectan.pos.x + (rectan.pos.x - compositeCenter.x) * (ratio - 1), EPSILON);
  BOOST_CHECK_CLOSE(afterScale.pos.y, rectan.pos.y + (rectan.pos.y - compositeCenter.y) * (ratio - 1), EPSILON);
  BOOST_CHECK_CLOSE(cs[0]->getArea(), rectan.width * rectan.height * ratio * ratio, EPSILON);

  afterScale = cs[1]->getFrameRect(); // Circle
  BOOST_CHECK_CLOSE(afterScale.pos.x, circleCenter.x + (circleCenter.x - compositeCenter.x) * (ratio - 1), EPSILON);
  BOOST_CHECK_CLOSE(afterScale.pos.y, circleCenter.y + (circleCenter.y - compositeCenter.y) * (ratio - 1), EPSILON);
  BOOST_CHECK_CLOSE(cs[1]->getArea(), M_PI * radius * radius * ratio * ratio, EPSILON);
}

BOOST_AUTO_TEST_CASE(InvalidScale)
{
  CompositeShape cs;

  BOOST_CHECK_THROW(cs.scale(-0.5), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(Size)
{
  CompositeShape cs;
  BOOST_CHECK_EQUAL(cs.getSize(), 0);
  
  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {10.0, 20.0}, 10.0, 12.0 });
  cs.add(rect);
  BOOST_CHECK_EQUAL(cs.getSize(), 1);

  std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 5.0);
  cs.add(circle);
  BOOST_CHECK_EQUAL(cs.getSize(), 2);
}

BOOST_AUTO_TEST_CASE(Clear)
{
  CompositeShape cs;
  
  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {10.0, 20.0}, 10.0, 12.0 });
  cs.add(rect);

  std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 5.0);
  cs.add(circle);

  cs.clear();
  BOOST_CHECK_EQUAL(cs.getSize(), 0);
  BOOST_CHECK_THROW(cs[0], std::out_of_range);
}
