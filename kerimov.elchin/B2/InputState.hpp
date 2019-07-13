#ifndef INPUT_STATE_HPP
#define INPUT_STATE_HPP

class InputState
{
public:
  InputState();

  bool getSpace();
  bool getNewWord();

  void setWord();
  void setSyntax();
  void setComma();
  void setDash();
  void setSpace();

private:
  bool word_;
  bool syntax_;
  bool space_;
  bool comma_;
};

#endif //INPUT_STATE_HPP
