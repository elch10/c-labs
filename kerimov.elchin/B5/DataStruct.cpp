#include "DataStruct.hpp"
#include <sstream>
#include <istream>

bool operator<(const DataStruct &lhs, const DataStruct &rhs)
{
  if (lhs.key1 != rhs.key1) {
    return lhs.key1 < rhs.key1;
  }
  if (lhs.key2 != rhs.key2) {
    return lhs.key2 < rhs.key2;
  }
  return lhs.str.size() < rhs.str.size();
}

void readDelimiter(std::istream &istream, char c)
{
  char temp;
  if (!(istream >> temp).good() || temp != c) {
    istream.setstate(std::ios_base::failbit);
  }
}

std::istream &operator>>(std::istream &istream, DataStruct &data)
{
  std::string line;
  std::getline(istream, line);
  if (!istream.good()) {
    return istream;
  }

  std::istringstream input{line};
  input >> data.key1;
  readDelimiter(input, DELIMITER);
  input >> data.key2;
  readDelimiter(input, DELIMITER);
  std::getline(input, data.str);
  
  if (input.fail() || data.str.empty()
      || data.key1 < KEY_RANGE_BEGIN || data.key1 > KEY_RANGE_END
      || data.key2 < KEY_RANGE_BEGIN || data.key2 > KEY_RANGE_END) {
    throw std::istream::failure("Command doesn't satisfy conditions of task");
  }
  return istream;
}

std::ostream &operator<<(std::ostream &ostream, const DataStruct &data)
{
  return ostream << data.key1 << DELIMITER << data.key2 << DELIMITER << data.str << std::endl;
}
