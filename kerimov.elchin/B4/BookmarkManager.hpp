#ifndef BOOKMARK_MANAGER_HPP
#define BOOKMARK_MANAGER_HPP

#include <string>
#include <map>
#include "PhoneBook.hpp"

class BookmarkManager
{
public:
  BookmarkManager();
  BookmarkManager(const BookmarkManager &rhs);
  BookmarkManager(BookmarkManager && rhs) = default;

  BookmarkManager &operator=(const BookmarkManager &rhs);
  BookmarkManager &operator=(BookmarkManager &&rhs) = default;

  void addToEnd(const PhoneBookEntry &entry);
  void storeBookmark(const std::string &currentBookmark, const std::string &newBookmark);
  void showCurrent(const std::string &bookmark);
  void moveToNext(const std::string &bookmark);
  void moveToPrev(const std::string &bookmark);
  void insertBefore(const std::string & bookmark, const PhoneBookEntry &entry);
  void insertAfter(const std::string & bookmark, const PhoneBookEntry &entry);
  void moveTab(const std::string &bookmark, const int shift);
  void moveTab(const std::string &bookmark, const std::string &position);
  void removeEntry(const std::string &bookmark);
  void replaceEntry(const std::string &bookmark, const PhoneBookEntry &entry);

private:
  typedef std::map<std::string, PhoneBook::iterator> bookmark_type;

  PhoneBook records_;
  bookmark_type bookmarks_;

  bookmark_type::iterator getIterator(const std::string &bookmark);
  void insert(const std::string &bookmark, const PhoneBookEntry &entry, const bool after);
};

#endif // BOOKMARK_MANAGER_HPP

