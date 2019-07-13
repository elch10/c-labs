#define BOOST_TEST_MAIN
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace kerimov;

const double EPSILON = 1e-6;

BOOST_AUTO_TEST_SUITE(RectangleSuite)

  BOOST_AUTO_TEST_CASE(DefaultConstructor)
  {
    const rectangle_t rect = { {2.0, 5.0}, 7.0, 8.0 };
    Rectangle rectan{ rect };

    rectangle_t afterConstruct = rectan.getFrameRect();
    BOOST_CHECK_CLOSE(rect.pos.x, afterConstruct.pos.x, EPSILON);
    BOOST_CHECK_CLOSE(rect.pos.y, afterConstruct.pos.y, EPSILON);
    BOOST_CHECK_CLOSE(rect.width, afterConstruct.width, EPSILON);
    BOOST_CHECK_CLOSE(rect.height, afterConstruct.height, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Rotate)
  {
    const rectangle_t rect = { {2.0, 5.0}, 7.0, 8.0 };
    const double angle = 135.0;
    Rectangle rectan{ rect };

    rectan.rotate(angle);

    rectangle_t afterRotate = rectan.getFrameRect();
    BOOST_CHECK_EQUAL(rect.pos.x, afterRotate.pos.x);
    BOOST_CHECK_EQUAL(rect.pos.y, afterRotate.pos.y);

    point_t rightUp = {rect.width / 2, rect.height / 2};
    point_t leftDown = {-rect.width / 2, -rect.height / 2};

    rightUp.rotate(angle);
    leftDown.rotate(angle);

    BOOST_CHECK_CLOSE(leftDown.x - rightUp.x, afterRotate.width, EPSILON);
    
    point_t leftUp = {-rect.width / 2, rect.height / 2};
    point_t rightDown = {rect.width / 2, -rect.height / 2};

    leftUp.rotate(angle);
    rightDown.rotate(angle);

    BOOST_CHECK_CLOSE(rightDown.y - leftUp.y, afterRotate.height, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleSuite)

  BOOST_AUTO_TEST_CASE(Rotate)
  {
    Circle circle{ {2.0, 3.0}, 5.0};

    circle.rotate(55.0);

    rectangle_t frame = circle.getFrameRect();

    BOOST_CHECK_EQUAL(frame.pos.x, 2.0);
    BOOST_CHECK_EQUAL(frame.pos.y, 3.0);
    BOOST_CHECK_CLOSE(frame.width, 10.0, EPSILON);
    BOOST_CHECK_CLOSE(frame.height, 10.0, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompostieShapeSuite)

  BOOST_AUTO_TEST_CASE(Rotate)
  {
    CompositeShape cs;
    
    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {1.0, 2.0}, 5.0, 6.0 });
    cs.add(rect);
  
    std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 6.0);
    cs.add(circle);

    rectangle_t beforeRotate = cs.getFrameRect();

    cs.rotate(90.0);

    rectangle_t afterRotate = cs.getFrameRect();

    BOOST_CHECK_CLOSE(beforeRotate.pos.x, afterRotate.pos.x, EPSILON);
    BOOST_CHECK_CLOSE(beforeRotate.pos.y, afterRotate.pos.y, EPSILON);
    BOOST_CHECK_CLOSE(beforeRotate.height, afterRotate.width, EPSILON);
    BOOST_CHECK_CLOSE(beforeRotate.width, afterRotate.height, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Split)
  {
    CompositeShape cs;
    
    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {3.0, 2.0}, 5.0, 6.0 });
    cs.add(rect);

    std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 2.0);
    cs.add(circle);
  
    std::shared_ptr< Circle > circle1 = std::make_shared< Circle >(point_t{1.0, 2.0}, 6.0);
    cs.add(circle1);

    std::shared_ptr< Rectangle > rect1 = std::make_shared< Rectangle >(rectangle_t{ {4.0, 3.0}, 7.0, 8.0 });
    cs.add(rect1);

    Matrix matrix = cs.split();
    
    BOOST_CHECK_EQUAL(matrix.getLayers(), 3);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(), 2);

    BOOST_CHECK_EQUAL(matrix[0][0], rect);
    BOOST_CHECK_EQUAL(matrix[0][1], circle);
    BOOST_CHECK_EQUAL(matrix[1][0], circle1);
    BOOST_CHECK_EQUAL(matrix[2][0], rect1);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixSuite)

  BOOST_AUTO_TEST_CASE(CopyConstructor)
  {
    Matrix matrix2;

    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {12.0, 15.0}, 10.0, 2.0 });
    matrix2.add(rect);

    std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 9.0);
    matrix2.add(circle);

    Matrix matrix1{matrix2};

    BOOST_CHECK_EQUAL(matrix1.getLayers(), matrix2.getLayers());
    BOOST_CHECK_EQUAL(matrix1.getLayerSize(), matrix2.getLayerSize());
    BOOST_CHECK_EQUAL(matrix1[0][0], matrix2[0][0]);
    BOOST_CHECK_EQUAL(matrix1[1][0], matrix2[1][0]);
  }

  BOOST_AUTO_TEST_CASE(MoveConstrucotr)
  {
    Matrix matrix2;

    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {12.0, 15.0}, 10.0, 2.0 });
    matrix2.add(rect);

    std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 9.0);
    matrix2.add(circle);

    Matrix matrix1{std::move(matrix2)};

    BOOST_CHECK_EQUAL(matrix1.getLayers(), 2);
    BOOST_CHECK_EQUAL(matrix1.getLayerSize(), 1);
    BOOST_CHECK_EQUAL(matrix2.getLayers(), 0);
    BOOST_CHECK_EQUAL(matrix2.getLayerSize(), 0);

    BOOST_CHECK_EQUAL(matrix1[0][0], rect);
    BOOST_CHECK_EQUAL(matrix1[1][0], circle);

    BOOST_CHECK_THROW(matrix2[0], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(AssignmentCopy)
  {
    Matrix matrix2, matrix1;

    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {12.0, 15.0}, 10.0, 2.0 });
    matrix2.add(rect);

    std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 9.0);
    matrix2.add(circle);

    matrix1 = matrix2;

    BOOST_CHECK_EQUAL(matrix1.getLayers(), matrix2.getLayers());
    BOOST_CHECK_EQUAL(matrix1.getLayerSize(), matrix2.getLayerSize());
    BOOST_CHECK_EQUAL(matrix1[0][0], matrix2[0][0]);
    BOOST_CHECK_EQUAL(matrix1[1][0], matrix2[1][0]);
  }

  BOOST_AUTO_TEST_CASE(AssignmentMove)
  {
    Matrix matrix2, matrix1;

    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {12.0, 15.0}, 10.0, 2.0 });
    matrix2.add(rect);

    std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{10.0, 20.0}, 9.0);
    matrix2.add(circle);

    matrix1 = std::move(matrix2);

    BOOST_CHECK_EQUAL(matrix1.getLayers(), 2);
    BOOST_CHECK_EQUAL(matrix1.getLayerSize(), 1);
    BOOST_CHECK_EQUAL(matrix2.getLayers(), 0);
    BOOST_CHECK_EQUAL(matrix2.getLayerSize(), 0);

    BOOST_CHECK_EQUAL(matrix1[0][0], rect);
    BOOST_CHECK_EQUAL(matrix1[1][0], circle);

    BOOST_CHECK_THROW(matrix2[0], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(InvalidIndexindOperator)
  {
    Matrix matrix;
    BOOST_CHECK_THROW(matrix[0], std::out_of_range);

    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {10.0, 20.0}, 10.0, 2.0 });
    matrix.add(rect);

    BOOST_CHECK_THROW(matrix[1], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(Clear)
  {
    Matrix matrix;
    
    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {10.0, 20.0}, 10.0, 12.0 });
    matrix.add(rect);

    matrix.clear();
    BOOST_CHECK_EQUAL(matrix.getLayers(), 0);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(), 0);
    BOOST_CHECK_THROW(matrix[0], std::out_of_range);
  }

BOOST_AUTO_TEST_SUITE_END()
