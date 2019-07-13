#include <map>
#include <iostream>
#include "CommandParser.hpp"

detail::Commands::command<std::string> detail::Commands::add(std::istream &istream)
{
  std::string priorityStr = {};
  istream >> priorityStr;
  if (priorityStr.empty()) {
    std::getline(istream, priorityStr);
    return detail::invalidCommand;
  }

  const std::map<std::string, QueueWithPriority<std::string>::Priority> priorites =
    {{"low",    QueueWithPriority<std::string>::LOW},
     {"normal", QueueWithPriority<std::string>::NORMAL},
     {"high",   QueueWithPriority<std::string>::HIGH}};

  auto priority = priorites.find(priorityStr);
  if (priority == priorites.end()) {
    std::getline(istream, priorityStr);
    return detail::invalidCommand;
  }

  std::string dataStr = {};
  std::getline(istream >> std::ws, dataStr);
  if (dataStr.empty()) {
    std::getline(istream, priorityStr);
    return detail::invalidCommand;
  }

  QueueWithPriority<std::string>::Priority priority1 = priority->second;
  return command<std::string>([priority1, dataStr](QueueWithPriority<std::string> &queue, std::ostream &)
    {
      queue.put(dataStr, priority1);
    });

}

detail::Commands::command<std::string> detail::Commands::get(std::istream &istream)
{
  std::string allCommand;
  std::getline(istream, allCommand);
  if (!allCommand.empty()) {
    return &detail::invalidCommand;
  }

  return command<std::string>([](QueueWithPriority<std::string> &queue, std::ostream &ostream)
    {
      if (queue.empty()) {
        ostream << "<EMPTY>\n";
      } else {
        ostream << queue.getTop() << '\n';
        queue.pop();
      }
    });
}

detail::Commands::command<std::string> detail::Commands::accelerate(std::istream &istream)
{
  std::string allCommand;
  std::getline(istream, allCommand);
  if (!allCommand.empty()) {
    return &detail::invalidCommand;
  }
  return command<std::string>([](QueueWithPriority<std::string> &queue, std::ostream &) { queue.accelerate(); });
}

void detail::detail::invalidCommand(QueueWithPriority<std::string> &, std::ostream &ostream)
{
  ostream << "<INVALID COMMAND>\n";
}
