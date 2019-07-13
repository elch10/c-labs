#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <memory>
#include "shape.hpp"

namespace kerimov
{
  class Matrix
  {
  public:
    using element_type = std::shared_ptr< Shape >;
    using layer_type = std::unique_ptr< element_type[] >;

    Matrix() noexcept;
    Matrix(Matrix & rhs);
    Matrix(Matrix && rhs) noexcept;

    Matrix & operator= (const Matrix & rhs);
    Matrix & operator= (Matrix && rhs) noexcept;
    layer_type operator[] (size_t index) const;

    void add(const element_type & shape);
    void clear() noexcept;
    size_t getLayers() const noexcept;
    size_t getLayerSize() const noexcept;
  private:
    layer_type shapes_;
    size_t layers_;
    size_t layerSize_;
    static bool intersect(const element_type & lhs, const element_type & rhs) noexcept;
  }; //Matrix
} // kerimov


#endif // MATRIX_HPP
