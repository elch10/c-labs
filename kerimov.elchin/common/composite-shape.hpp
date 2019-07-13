#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP
#include <memory>
#include "shape.hpp"
#include "matrix.hpp"

namespace kerimov
{
  class CompositeShape: public Shape
  {
  public:
    using element_type = std::shared_ptr< Shape >;

    CompositeShape() noexcept;
    CompositeShape(const CompositeShape & rhs);
    CompositeShape(CompositeShape && rhs) noexcept;
    
    CompositeShape & operator= (const CompositeShape & rhs);
    CompositeShape & operator= (CompositeShape && rhs) noexcept;
    element_type & operator[] (size_t index) const;

    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t & to) noexcept override;
    void move(double dx, double dy) noexcept override;
    void scale(double ratio) override;
    void rotate(double angle) noexcept override;
    Matrix split() const;

    void add(const element_type & shape);
    void remove(size_t index);
    size_t getSize() const noexcept;
    void clear() noexcept;
  private:
    std::unique_ptr< element_type[] > shapes_;
    size_t size_;
    void validateIndex(size_t index) const;
  };
} //kerimov

#endif //COMPOSITE_SHAPE_HPP
