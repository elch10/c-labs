#include "Tasks.hpp"
#include <iostream>
#include <sstream>
#include "InputHandler.hpp"
#include "BookmarkManager.hpp"

void Task1()
{
  BookmarkManager manager;
  std::string string;
  while (std::getline(std::cin, string))
  {
    try
    {
      std::istringstream input{string};
      std::string command;
      input >> command;
      if (command == "add")
      {
        InputHandler::addEntry(input, manager);
      }
      else if (command == "insert")
      {
        InputHandler::insert(input, manager);
      }
      else if (command == "delete")
      {
        InputHandler::remove(input, manager);
      }
      else if (command == "store")
      {
        InputHandler::store(input, manager);
      }
      else if (command == "move")
      {
       InputHandler::move(input, manager);
      }
      else if (command == "show")
      {
        try
        {
          InputHandler::show(input, manager);
        }
        catch (std::invalid_argument &)
        {
          std::cout << "<INVALID BOOKMARK>" << std::endl;
        }
      }
      else
      {
        throw std::invalid_argument("");
      }
    }
    catch (std::invalid_argument &)
    {
      std::cout << "<INVALID COMMAND>" << std::endl;
    }
  }
}


