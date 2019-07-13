#include "PhoneBook.hpp"

PhoneBook::iterator PhoneBook::begin()
{
  return list_.begin();
}

PhoneBook::iterator PhoneBook::end()
{
  return list_.end();
}

PhoneBook::const_iterator PhoneBook::cbegin() const
{
  return list_.cbegin();
}

PhoneBook::const_iterator PhoneBook::cend() const
{
  return list_.cend();
}

bool PhoneBook::empty() const
{
  return list_.empty();
}

void PhoneBook::pushBack(const PhoneBookEntry &element)
{
  list_.push_back(element);
}

void PhoneBook::insert(const typename ElementsContainer::iterator &pos, const PhoneBookEntry &element)
{
  list_.insert(pos, element);
}

std::size_t PhoneBook::size() const
{
  return list_.size();
}

void PhoneBook::erase(const typename ElementsContainer::iterator &pos)
{
  list_.erase(pos);
}
