#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>

constexpr int KEY_RANGE_BEGIN = -5;
constexpr int KEY_RANGE_END   = 5;
constexpr char DELIMITER      = ',';

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

bool operator<(const DataStruct &lhs, const DataStruct &rhs);
std::istream &operator>>(std::istream &istream, DataStruct &data);
std::ostream &operator<<(std::ostream &ostream, const DataStruct &data);

#endif //DATA_STRUCT_HPP
