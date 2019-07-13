#ifndef TEXT_HANDLER_HPP
#define TEXT_HANDLER_HPP

#include "InputState.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <locale>

template<typename Iterator>
class TextHandler
{
public:
  TextHandler(size_t lineWidth);
  void handle(Iterator begin, Iterator end);

private:
  InputState state_;
  const size_t lineWidth_;
  std::vector<char> string_;
  std::vector<char> word_;
  Iterator iter_;
  Iterator end_;

  void newWord();
  bool readWord();
  bool readNumber();
  bool readSyntex();
  bool readSpace();
};

template<typename Iterator>
TextHandler<Iterator>::TextHandler(size_t lineWidth) :
  state_(),
  lineWidth_(lineWidth),
  string_(),
  word_(),
  iter_(),
  end_()
{}

template<typename Iterator>
void TextHandler<Iterator>::handle(Iterator begin, Iterator end)
{
  if (begin == end)
  {
    return;
  }
  iter_ = begin;
  end_ = end;
  iter_--;

  while (iter_ != end_)
  {
    iter_++;
    if (!(readWord() || readNumber() || readSpace() || readSyntex()))
    {
      return;
    }
  }

  newWord();
  if (!string_.empty())
  {
    std::copy(string_.begin(), string_.end() - 1, std::ostream_iterator<char>(std::cout));
    std::cout << std::endl;
  }
}

template<typename Iterator>
void TextHandler<Iterator>::newWord()
{
  size_t sizeW = word_.size();
  size_t sizeStr = string_.size();

  if (sizeStr + sizeW < lineWidth_)
  {
    string_.insert(string_.end(), word_.begin(), word_.end());
    if (!string_.empty())
    {
      string_.push_back(' ');
    }
  }
  else if (sizeStr + sizeW == lineWidth_)
  {
    std::copy(string_.begin(), string_.end(), std::ostream_iterator<char>(std::cout));
    std::copy(word_.begin(), word_.end(), std::ostream_iterator<char>(std::cout));
    std::cout << std::endl;
    string_.clear();
  }
  else
  {
    std::copy(string_.begin(), string_.end() - 1, std::ostream_iterator<char>(std::cout));
    std::cout << std::endl;
    string_.clear();
    std::vector<char>::iterator begin = word_.begin();
    string_.insert(string_.end(), begin, word_.end());
    string_.push_back(' ');
  }

  word_.clear();
  state_.setWord();
}

template<typename Iterator>
bool TextHandler<Iterator>::readWord()
{
  std::locale cloc("C");
  if (std::isalpha(*iter_, cloc))
  {
    if (state_.getNewWord())
    {
      newWord();
    }
  }
  else
  {
    return false;
  }

  while (iter_ != end_)
  {
    if (std::isalpha(*iter_, cloc))
    {
      word_.push_back(*iter_);
    }
    else if (*iter_ == '-')
    {
      word_.push_back(*iter_);
      break;
    }
    else
    {
      iter_--;
      break;
    }

    iter_++;
  }

  if (word_.size() > 20)
  {
    throw std::invalid_argument("The word can not be more than 20 characters!");
  }

  return true;
}

template<typename Iterator>
bool TextHandler<Iterator>::readNumber()
{

  std::locale cloc("C");
  if (isdigit(*iter_, cloc) || *iter_ == '+')
  {
    newWord();
  }
  else if (*iter_ == '-' && isdigit(*(iter_+1), cloc))
  {
    ++iter_;
    newWord();
    word_.push_back('-');
  }
  else
  {
    return false;
  }

  char point = std::use_facet< std::numpunct<char> >(std::cin.getloc()).decimal_point();

  while (iter_ != end_)
  {
    if (isdigit(*iter_, cloc) || *iter_ == point || *iter_ == '+')
    {
      word_.push_back(*iter_);
    }
    else
    {
      iter_--;
      break;
    }
    iter_++;
  }

  if (word_.size() > 20)
  {
    throw std::invalid_argument("The number can not be more than 20 characters!");
  }

  return true;
}


template<typename Iterator>
bool TextHandler<Iterator>::readSyntex()
{
  if (*iter_ == '-')
  {
    state_.setDash();

    if (*(++iter_) == '-' && *(++iter_) == '-')
    {
      word_.push_back(' ');
      word_.push_back('-');
      word_.push_back('-');
      word_.push_back('-');
    }
    else
    {
      throw std::invalid_argument("Unknown character");
    }
  }
  else if (ispunct(*iter_))
  {
    if (*iter_ == ',')
    {
      state_.setComma();
    }
    else
    {
      state_.setSyntax();
    }

    word_.push_back(*iter_);
  }
  else
  {
    return false;
  }

  return true;
}

template<typename Iterator>
bool TextHandler<Iterator>::readSpace()
{
  if (isspace(*iter_))
  {
    state_.setSpace();
    while (iter_ != end_)
    {
      if (!isspace(*iter_))
      {
        iter_--;
        break;
      }
      iter_++;
    }
  }
  else
  {
    return false;
  }

  return true;
}

#endif //TEXT_HANDLER_HPP
