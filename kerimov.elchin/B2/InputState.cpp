#include "InputState.hpp"
#include <stdexcept>

InputState::InputState() :
  word_(false),
  syntax_(false),
  space_(true),
  comma_(false)
{}

void InputState::setWord()
{
  word_ = true;
  space_ = false;
  syntax_ = false;
  comma_ = false;
}

void InputState::setSyntax()
{
  if (syntax_)
  {
    throw std::invalid_argument("Syntax befor syntax");
  }

  if (!word_)
  {
    throw std::invalid_argument("Unexpected syntax");
  }

  syntax_ = true;
  word_ = false;
  space_ = true;
}

void InputState::setComma()
{
  setSyntax();
  comma_ = true;
}

void InputState::setDash()
{
  if (!(comma_ || word_))
  {
    throw std::invalid_argument("Unexpected syntax");
  }

  syntax_ = true;
  word_ = false;
  comma_ = false;
  space_ = true;
}

void InputState::setSpace()
{
  space_ = true;
}

bool InputState::getSpace()
{
  return space_;
}

bool InputState::getNewWord()
{
  return syntax_ || space_ || !word_;
}
