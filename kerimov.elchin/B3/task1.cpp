#include <istream>
#include <ostream>
#include <functional>
#include <stdexcept>
#include <cstring>
#include "QueueWithPriority.hpp"
#include "CommandParser.hpp"

namespace Tasks
{
  const detail::detail::command<std::string> parsers[3] = {{"add",        &detail::Commands::add},
                                                           {"get",        &detail::Commands::get},
                                                           {"accelerate", &detail::Commands::accelerate}};


  std::istream &operator>>(std::istream &istream, detail::Commands::command<std::string> &function)
  {
    std::string str = {};
    istream >> str;
    if (istream.eof() && str.empty()) {
      function = detail::Commands::command<std::string>([](QueueWithPriority<std::string> &, std::ostream &) {});
      return istream;
    }

    if (!str.empty()) {
      const char *command = str.data();
      for (int i = 0; i < 3; ++i) {
        if (std::strcmp(command, parsers[i].name_) == 0) {
          function = parsers[i].parse_(istream);
          return istream;
        }
      }
    }

    std::getline(istream, str);
    function = detail::detail::invalidCommand;
    return istream;
  }

  void task1(std::istream &istream, std::ostream &ostream)
  {
    QueueWithPriority<std::string> queue = {};
    while (istream && !istream.eof()) {
      detail::Commands::command<std::string> command;
      istream >> command;
      command(queue, ostream);
    }
    if (!istream.eof() && (istream.bad() || istream.fail())) {
      throw std::ios_base::failure("Error while reading");
    }
  }
}
