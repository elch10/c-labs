#ifndef UTILS_HPP
#define UTILS_HPP

#include <iosfwd>
#include <vector>
#include <fstream>

namespace kerimov
{
  void fillRandom(double * array, int size);

  namespace detail
  {
    template< typename Container, typename Char >
    void printValues(std::basic_ostream<Char> &stream, const Container &arr, 
                     const char* delimiter, bool newline)
    {
      for (typename Container::const_reference value: arr) {
        stream << value << delimiter;
      }
      if (newline) {
        stream << std::endl;
      }
    }

    /*
      readValues reads stream
      if fail occures while reading, then std::istream::failure is thrown
      if stream empty before reading, then empty vector will be returned
    */
    template< typename T, typename Char >
    std::vector<T> readValues(std::basic_istream<Char> &stream)
    {
      std::vector<T> input;
      std::istream::sentry s(stream, true);
      if (!s) {
        throw std::istream::failure("Error while reading: stream is not ready");
      }
      
      T value;
      while (true) {
        stream >> value;
        if (!stream && !stream.eof()) {
          throw std::istream::failure("Error while reading value in stream");
        } else if (stream.eof()) {
          break;
        }
        input.push_back(value);
      }
      return input;
    }
  } //detail
} //kerimov

#endif //UTILS_HPP
