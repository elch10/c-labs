#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include "BookmarkManager.hpp"

namespace InputHandler
{
  std::string readName(std::istream &input);
  std::string readNumber(std::istream &input);
  std::string readMarkName(std::istream &input);

  void addEntry(std::istream& input, BookmarkManager &manager);
  void remove(std::istream& input, BookmarkManager &manager);
  void show(std::istream& input, BookmarkManager &manager);
  void insert(std::istream& input, BookmarkManager &manager);
  void store(std::istream& input, BookmarkManager &manager);
  void move(std::istream& input, BookmarkManager &manager);
};

#endif // INPUT_HANDLER_HPP
