#ifndef QUEUE_WITH_PRIORITY_HPP
#define QUEUE_WITH_PRIORITY_HPP

#include <list>
#include <array>
#include <stdexcept>
#include <algorithm>

template< class T >
class QueueWithPriority
{
public:
  enum Priority
  {
    LOW,
    NORMAL,
    HIGH
  };
  static const size_t PRIORITY_COUNT = 3;

  void put(const T &element, const Priority priority = Priority::LOW);
  void accelerate();
  bool empty() const;
  void clear();

  T& getTop();
  void pop();

private:
  std::array<std::list<T>, PRIORITY_COUNT> arrayOfElements_;
};


template<class T>
void QueueWithPriority<T>::put(const T &element, const Priority priority)
{
  arrayOfElements_[priority].push_back(element);
}

template<class T>
void QueueWithPriority<T>::accelerate()
{
  arrayOfElements_[Priority::HIGH].splice(arrayOfElements_[Priority::HIGH].end(), arrayOfElements_[Priority::LOW]);
}

template<class T>
bool QueueWithPriority<T>::empty() const
{
  for (std::size_t i = 0; i < arrayOfElements_.size(); ++i) {
    if (!arrayOfElements_[i].empty()) {
      return false;
    }
  }
  return true;
}

template<class T>
T& QueueWithPriority<T>::getTop()
{
  if (empty()) {
    throw std::out_of_range("Trying get element in empty queue");
  }
  Priority priority = Priority::LOW;
  if (!arrayOfElements_[Priority::HIGH].empty()) {
    priority = Priority::HIGH;
  } else if (!arrayOfElements_[Priority::NORMAL].empty()) {
    priority = Priority::NORMAL;
  }
  return arrayOfElements_[priority].front();
}

template<class T>
void QueueWithPriority<T>::clear()
{
  for (unsigned int i = 0; i < arrayOfElements_.size(); i++) {
    arrayOfElements_[i].clear();
  }
}

template<class T>
void QueueWithPriority<T>::pop()
{
  if (empty()) {
    throw std::out_of_range("Trying pop element in empty queue");
  }
  Priority priority = Priority::LOW;
  if (!arrayOfElements_[Priority::HIGH].empty()) {
    priority = Priority::HIGH;
  } else if (!arrayOfElements_[Priority::NORMAL].empty()) {
    priority = Priority::NORMAL;
  }
  arrayOfElements_[priority].pop_front();
}

#endif //QUEUE_WITH_PRIORITY_HPP
