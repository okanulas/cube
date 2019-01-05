#include "Arduino.h"
#include "Adafruit_Trellis.h"
#include <Rotary.h>

class Navigation{
  public:
    Navigation(Adafruit_TrellisSet *trellis, Rotary *rotary);

    static const uint8_t 
      SELECT = 0, 
      PLAY = 1,
      WAIT = 2;

    uint8_t getState();
    uint8_t getProgramIndex();
    bool updateState(uint8_t rotaryButtonState);
    void switchState();

  private:
    Adafruit_TrellisSet *_trellis;
    Rotary *_rotary;
    uint8_t _state;

    void selectProgram();
    void selectButton(uint8_t no);
    
    void blinkButton(int no);
    void lightDiagonal(uint8_t x, uint8_t y, uint8_t d);
    void clearTrellis();

    uint8_t _activeRotaryButtonState;
    int8_t _rotaryVal;
};
