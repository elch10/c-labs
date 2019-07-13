#define BOOST_TEST_MODULE Main
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"

using namespace kerimov;

const double EPSILON = 1e-6;

BOOST_AUTO_TEST_SUITE(RectangleSuite)

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    Rectangle rect{ {{2.0, 4.0}, 5.0, 6.0} };
    rectangle_t rectBeforeMoving = rect.getFrameRect();
    double areaBeforeMoving = rect.getArea();

    rect.move({15.0, 20.0});
    BOOST_CHECK_EQUAL(areaBeforeMoving, rect.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, rect.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(RelativeMoving)
  {
    Rectangle rect{ {{2.0, 4.0}, 5.0, 6.0} };
    rectangle_t rectBeforeMoving = rect.getFrameRect();
    double areaBeforeMoving = rect.getArea();

    rect.move(-10.0, 50.0);
    BOOST_CHECK_EQUAL(areaBeforeMoving, rect.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, rect.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    Rectangle rect{ {{2.0, 4.0}, 5.0, 6.0} };
    double areaBeforeScaling = rect.getArea();
    const double ratio = 3.3;

    rect.scale(ratio);
    BOOST_CHECK_CLOSE(ratio * ratio * areaBeforeScaling, rect.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW( Rectangle({{10.0, 20.0}, 10.0, -15.0}), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    Rectangle rect{ {{2.0, 4.0}, 5.0, 6.0} };
    BOOST_CHECK_THROW( rect.scale(-1.0), std::invalid_argument );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleSuite)

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    Circle circle{ {5.0, 3.0}, 22.0 };
    rectangle_t rectBeforeMoving = circle.getFrameRect();
    double areaBeforeMoving = circle.getArea();

    circle.move({15.0, 20.0});
    BOOST_CHECK_EQUAL(areaBeforeMoving, circle.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, circle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(RelativeMoving)
  {
    Circle circle{ {5.0, 3.0}, 22.0 };
    rectangle_t rectBeforeMoving = circle.getFrameRect();
    double areaBeforeMoving = circle.getArea();

    circle.move(-10.0, 50.0);
    BOOST_CHECK_EQUAL(areaBeforeMoving, circle.getArea());
    BOOST_CHECK_EQUAL(rectBeforeMoving.width, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectBeforeMoving.height, circle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    Circle circle{ {5.0, 3.0}, 22.0 };
    double areaBeforeScaling = circle.getArea();
    const double ratio = 3.3;

    circle.scale(ratio);
    BOOST_CHECK_CLOSE(ratio * ratio * areaBeforeScaling, circle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW( Circle({10.0, 20.0}, -15.0), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    Circle circle{ {5.0, 3.0}, 22.0 };
    BOOST_CHECK_THROW( circle.scale(-1.0), std::invalid_argument );
  }

BOOST_AUTO_TEST_SUITE_END()
