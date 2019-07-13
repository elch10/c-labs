#ifndef PARSER_HPP
#define PARSER_HPP

#include <functional>
#include <istream>
#include <ostream>
#include "QueueWithPriority.hpp"

namespace detail
{
  namespace Commands
  {
    template< typename T >
    using command = std::function<void(QueueWithPriority<T> &, std::ostream &)>;

    command<std::string> add(std::istream &);
    command<std::string> get(std::istream &);
    command<std::string> accelerate(std::istream &);
  }

  namespace detail
  {
    template< typename T >
    struct command
    {
      const char *name_;
      const std::function<Commands::command<T>(std::istream &)> parse_;
    };
    void invalidCommand(QueueWithPriority<std::string> &, std::ostream &);
  }
}

#endif //PARSER_HPP
