#include "ContainerOfFactorials.hpp"

constexpr size_t FACTORIAL_INDEX_BEGIN = 1;
constexpr size_t FACTORIAL_INDEX_END = 11;
constexpr size_t FACTORIAL_OF_1 = 1;
constexpr size_t FACTORIAL_OF_11 = 39916800;

ContainerOfFactorials::Iterator::Iterator(size_t index, size_t value):
  index_(index),
  value_(value)
{}

const size_t *ContainerOfFactorials::Iterator::operator->() const
{
  return &value_;
}

const size_t &ContainerOfFactorials::Iterator::operator*() const
{
  return value_;
}

ContainerOfFactorials::Iterator ContainerOfFactorials::begin() const
{
  return ContainerOfFactorials::Iterator(FACTORIAL_INDEX_BEGIN, FACTORIAL_OF_1);
}

ContainerOfFactorials::Iterator ContainerOfFactorials::end() const
{
  return ContainerOfFactorials::Iterator(FACTORIAL_INDEX_END, FACTORIAL_OF_11);
}

ContainerOfFactorials::Iterator & ContainerOfFactorials::Iterator::operator++()
{
  value_ *= ++index_;
  return *this;
}

ContainerOfFactorials::Iterator ContainerOfFactorials::Iterator::operator++(int)
{
  Iterator prev = *this;
  ++(*this);
  return prev;
}

ContainerOfFactorials::Iterator & ContainerOfFactorials::Iterator::operator--()
{
  value_ /= index_--;
  return *this;
}

bool ContainerOfFactorials::Iterator::operator==(const Iterator &other) const
{
  return (index_ == other.index_);
}

bool ContainerOfFactorials::Iterator::operator!=(const Iterator &other) const
{
  return (!(other == *this));
}

ContainerOfFactorials::Iterator ContainerOfFactorials::Iterator::operator--(int)
{
  Iterator prev = *this;
  --(*this);
  return prev;
}
