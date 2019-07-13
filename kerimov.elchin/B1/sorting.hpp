#ifndef SORTING_HPP
#define SORTING_HPP

#include <utility>
#include <functional>

namespace kerimov
{
  namespace detail
  {
    template< typename Container >
    struct BracketAccess
    {
      typedef typename Container::reference ref;

      static size_t getBegin(const Container&)
      {
        return 0;
      }

      static size_t getEnd(const Container& container)
      {
        return container.size();
      }

      static ref getElement(Container& container, size_t i)
      {
        return container[i];
      }
    };

    template< typename Container >
    struct AtAccess
    {
      typedef typename Container::reference ref;

      static size_t getBegin(const Container&)
      {
        return 0;
      }

      static size_t getEnd(const Container& container)
      {
        return container.size();
      }

      static ref getElement(Container& container, size_t i)
      {
        return container.at(i);
      }
    };

    template <typename Container>
    struct IteratorAccess
    {
      typedef typename Container::reference ref;
      typedef typename Container::iterator iterator;

      static iterator getBegin(Container& container)
      {
        return container.begin();
      }

      static iterator getEnd(Container& container)
      {
        return container.end();
      }

      static ref getElement(const Container&, iterator &it)
      {
        return *it;
      }
    };


    template< template< typename Container > class AccessType,
        typename Container, 
        typename Comparator >
    void sortImplementation(Container &arr, const Comparator &comp)
    {
      typedef AccessType<Container> access;
      for (auto it = access::getBegin(arr); it != access::getEnd(arr); ++it) {
        for (auto it2 = it; it2 != access::getEnd(arr); ++it2) {
          if (comp(access::getElement(arr, it2), access::getElement(arr, it))) {
            std::swap(access::getElement(arr, it2), access::getElement(arr, it));
          }
        }
      }
    }

    template< template< typename > class AccessType,
        typename Container >
    void sort(Container &arr, bool ascending)
    {
      if (ascending) {
        sortImplementation<AccessType>(arr, std::less<typename Container::value_type>());
      } else {
        sortImplementation<AccessType>(arr, std::greater<typename Container::value_type>());
      }
    }
  } //detail
} //kerimov

#endif //SORTING_HPP
