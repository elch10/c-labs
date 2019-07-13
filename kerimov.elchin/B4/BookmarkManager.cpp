#include "BookmarkManager.hpp"
#include <iostream>
#include <algorithm>

BookmarkManager::BookmarkManager()
{
  bookmarks_["current"] = records_.end();
}

BookmarkManager::BookmarkManager(const BookmarkManager &rhs)
{
  *this = rhs;
}

BookmarkManager &BookmarkManager::operator=(const BookmarkManager &rhs)
{
  if (this != &rhs)
  {
    records_ = rhs.records_;
    bookmarks_.clear();
    for (auto bmark : rhs.bookmarks_)
    {
      std::list<PhoneBookEntry>::const_iterator iter = bmark.second;
      bookmarks_[bmark.first] = std::next(records_.begin(), std::distance(rhs.records_.cbegin(), iter));
    }
  }
  return *this;
}

void BookmarkManager::replaceEntry(const std::string &bookmark, const PhoneBookEntry & entry)
{
  *(getIterator(bookmark)->second) = entry;
}

void BookmarkManager::showCurrent(const std::string &bookmark)
{
  auto iter = getIterator(bookmark);
  if (iter->second == records_.end())
  {
    std::cout << "<EMPTY>" << std::endl;
  }
  else
  {
    std::cout << iter->second->number << " " << iter->second->name << std::endl;
  }
}

void BookmarkManager::addToEnd(const PhoneBookEntry &entry)
{
  if (records_.empty())
  {
    records_.pushBack(entry);
    bookmarks_["current"] = records_.begin();
  }
  else
  {
    records_.pushBack(entry);
  }
}

void BookmarkManager::storeBookmark(const std::string &currentBookmark, const std::string &newBookmark)
{
  auto iter = getIterator(currentBookmark);
  if (!bookmarks_.emplace(newBookmark, iter->second).second)
  {
    throw std::invalid_argument("This bookmark already exists");
  }
}

void BookmarkManager::insertBefore(const std::string &bookmark, const PhoneBookEntry & entry)
{
  insert(bookmark, entry, false);
}

void BookmarkManager::insertAfter(const std::string &bookmark, const PhoneBookEntry & entry)
{
  insert(bookmark, entry, true);
}

void BookmarkManager::insert(const std::string &bookmark, const PhoneBookEntry & entry, const bool after)
{
  if (records_.empty())
  {
    addToEnd(entry);
    return;
  }
  auto iter = getIterator(bookmark);
  if (iter->second != records_.end())
  {
    if (!after)
    {
      records_.insert(iter->second, entry);
    }
    else
    {
      records_.insert(std::next(iter->second), entry);
    }
  }
  else
  {
    records_.pushBack(entry);
  }
}

void BookmarkManager::removeEntry(const std::string &bookmark)
{
  auto iter = getIterator(bookmark);
  if (records_.empty() || iter->second == records_.end())
  {
    throw std::invalid_argument("Removing from empty PhoneBook");
  }
  auto current = iter->second;
  auto next = std::next(current);
  std::for_each(bookmarks_.begin(), bookmarks_.end(), [&](auto &mark)
  {
    if (mark.second == current) {
      mark.second = next;
    }
  });
  records_.erase(current);
  std::for_each(bookmarks_.begin(), bookmarks_.end(), [&](auto &mark)
  {
    if (mark.second == records_.end()) {
      mark.second = --records_.end();
    }
  });
}

void BookmarkManager::moveToPrev(const std::string &bookmark)
{
  moveTab(bookmark, -1);
}

void BookmarkManager::moveToNext(const std::string &bookmark)
{
  moveTab(bookmark, 1);
}

BookmarkManager::bookmark_type::iterator BookmarkManager::getIterator(const std::string &bookmark)
{
  auto iter = bookmarks_.find(bookmark);
  if (iter == bookmarks_.end())
  {
    throw std::invalid_argument("error");
  }
  return iter;
}

void BookmarkManager::moveTab(const std::string &bookmark, const int shift)
{
  auto iter = getIterator(bookmark);
  std::advance(iter->second, shift);
}

void BookmarkManager::moveTab(const std::string &bookmark, const std::string & position)
{
  auto iter = getIterator(bookmark);
  if (position != "first" && position != "last")
  {
    std::cout << "<INVALID STEP>" << std::endl;
    return;
  }
  if (records_.empty())
  {
    iter->second = records_.end();
    return;
  }
  if (position == "first")
  {
    iter->second = records_.begin();
  }
  else
  {
    iter->second = std::prev(records_.end());
  }
}
