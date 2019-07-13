#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP

#include <string>
#include <list>

struct PhoneBookEntry
{
  std::string number, name;
};

class PhoneBook
{
public:
  using ElementsContainer = std::list<PhoneBookEntry>;

  using iterator = typename ElementsContainer::iterator;
  using const_iterator = ElementsContainer::const_iterator;
  using value_type = ElementsContainer::value_type;
  using reference = ElementsContainer::reference;
  using const_reference = ElementsContainer::const_reference;
  using size_type = std::size_t;
  using pointer = ElementsContainer::pointer;
  using const_pointer = ElementsContainer::const_pointer;
  using reverse_iterator = ElementsContainer::reverse_iterator;
  using const_reverse_iterator = ElementsContainer::const_reverse_iterator;
  using difference_type = ElementsContainer::difference_type;

  iterator begin();
  iterator end();

  const_iterator cbegin() const;
  const_iterator cend() const;

  void pushBack(const PhoneBookEntry &element);
  void insert(const typename ElementsContainer::iterator &pos, const PhoneBookEntry &element);

  bool empty() const;
  std::size_t size() const;

  void erase(const typename ElementsContainer::iterator &pos);
private:
  ElementsContainer list_;
};

#endif //PHONE_BOOK_HPP
