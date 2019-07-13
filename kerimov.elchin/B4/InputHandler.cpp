#include "InputHandler.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>

std::string InputHandler::readName(std::istream &input)
{
  input.ignore();
  std::string name;
  std::getline(input, name);
  if (name.empty())
  {
    return name;
  }

  if ((name.front() != '\"') || (name.back() != '\"'))
  {
    throw std::invalid_argument("incorrect name");
  }
  name.erase(std::remove(name.begin(), name.end(), '\\'), name.end());
  name.erase(0,1);
  name.pop_back();
  return name;
}

std::string InputHandler::readNumber(std::istream & input)
{
  std::string number;
  input >> number;
  for (auto i : number)
  {
    if (!isdigit(i))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  return number;
}

void InputHandler::show(std::istream& input, BookmarkManager &manager)
{
  std::string markname = readMarkName(input);
  manager.showCurrent(markname);
}

void InputHandler::insert(std::istream& input, BookmarkManager &manager)
{
  std::string position;
  input >> position;

  if ((position != "before") && (position != "after"))
  {
    throw std::invalid_argument("incorrect parameter");  
  }
  else
  {
    std::string markname = readMarkName(input);
    std::string number = readNumber(input);
    std::string name = readName(input);
    if (position == "after")
    {
      manager.insertAfter(markname, PhoneBookEntry{ number,name });
    }
    else
    {
      manager.insertBefore(markname, PhoneBookEntry{ number,name });
    }
  }
}

void InputHandler::addEntry(std::istream& input, BookmarkManager &manager)
{
  std::string number = readNumber(input);
  std::string name = readName(input);
  manager.addToEnd(PhoneBookEntry{ number,name });
}

void InputHandler::move(std::istream& input, BookmarkManager &manager)
{
  std::string markname = readMarkName(input);
  std::string position;
  input >> position;
  if (position != "first" && position != "last")
  {
    try
    {
      manager.moveTab(markname, std::stoi(position));
    }
    catch (std::invalid_argument &)
    {
      std::cout << "<INVALID STEP>" << std::endl;
    }
  }
  else
  {
    manager.moveTab(markname, position);
  }
}

void InputHandler::remove(std::istream& input, BookmarkManager &manager)
{
  std::string markname = readMarkName(input);
  manager.removeEntry(markname);
}

std::string InputHandler::readMarkName(std::istream &input)
{
  std::string markname;
  input >> markname;
  for (auto i : markname)
  {
    if ((!isalnum(i)) && (i != '-'))
    {
      throw std::invalid_argument("<INVALID BOOKMARK>");
    }
  }
  return markname;
}

void InputHandler::store(std::istream& input, BookmarkManager & manager)
{
  std::string old_mark = readMarkName(input);
  std::string new_mark = readMarkName(input);
  manager.storeBookmark(old_mark, new_mark);
}
