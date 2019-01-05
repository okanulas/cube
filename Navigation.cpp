#include "Navigation.h"

static const uint8_t
SELECT = 0,
PLAY = 1,
WAIT = 2,
N_BUTTONS = 16;

uint8_t _state = SELECT;
uint8_t _activeRotaryButtonState = -1;
int8_t _rotaryVal;

Navigation::Navigation(Adafruit_TrellisSet *trellis, Rotary *rotary) {
  _trellis = trellis;
  _rotary = rotary;
}

uint8_t Navigation::getState() {
  return _state;
}

uint8_t Navigation::getProgramIndex() {
  return _rotaryVal;
}

bool Navigation::updateState(uint8_t rotaryButtonState) {

  if (_state == WAIT) return false;

  if (_activeRotaryButtonState == 1 && rotaryButtonState == 0 ) {
    switchState();
  }

  if (_activeRotaryButtonState != rotaryButtonState) {
    _activeRotaryButtonState = rotaryButtonState;
  }

  if (_state == SELECT) {
    unsigned char result = _rotary->process();
    if (result) {
      _trellis->clrLED(_rotaryVal);
      _rotaryVal += result == DIR_CCW ? 1 : -1;
      if (_rotaryVal < 0) {
        _rotaryVal = 15;
      } else if (_rotaryVal > 15) {
        _rotaryVal = 0;
      }
      _rotaryVal = _rotaryVal % N_BUTTONS;
      _trellis->setLED(_rotaryVal);
      _trellis->writeDisplay();
    }
    return false;
  } else {
    return true;
  }

  return false;
}

void Navigation::switchState() {
  clearTrellis();
  _state = _state == SELECT ? PLAY : SELECT;

  if (_state == SELECT) {
    selectButton(_rotaryVal);
  } else if (_state == PLAY) {
    selectProgram();
  }

  Serial.print(">>>> CURRENT STATE IS ");
  Serial.print(_state);
  Serial.println(" ");
}

void Navigation::selectButton(uint8_t no) {
  uint8_t oldState = _state;
  _state = WAIT;

  uint8_t x = no % 4;
  uint8_t y = (no / 4);

  if ((x < 1 || x > 2) || (y < 1 || y > 2)) {
    lightDiagonal(x, y, 4);
    delay(100);
  }

  lightDiagonal(x, y, 3);
  delay(100);
  lightDiagonal(x, y, 2);
  delay(100);

  clearTrellis();
  _trellis->setLED(no);
  _trellis->writeDisplay();
  delay(100);
  _state = oldState;
}

void Navigation::selectProgram() {
  uint8_t oldState = _state;
  _state = WAIT;

  clearTrellis();
  uint8_t d = 10;
  delay(d);

  for (uint8_t i = 0; i < N_BUTTONS; i++) {
    _trellis->setLED(i);
    _trellis->writeDisplay();
    delay(d);
  }

  for (uint8_t i = 0; i < N_BUTTONS; i++) {
    _trellis->clrLED(i);
    _trellis->writeDisplay();
    delay(d);
  }

  _state = oldState;

  Serial.print("SELECT PROGRAM");
  Serial.print(_state);
}

// TRELLIS EFFECTS

void Navigation::blinkButton(int no) {
  uint8_t oldState = _state;
  _state = WAIT;
  uint8_t blinkCount = 3;
  for (uint8_t i = 0; i < blinkCount; i++) {
    _trellis->clrLED(no);
    _trellis->writeDisplay();
    delay(100);
    _trellis->setLED(no);
    _trellis->writeDisplay();
  }
  _state = oldState;
}

void Navigation::lightDiagonal(uint8_t x, uint8_t y, uint8_t d) {
  for (uint8_t i = 0; i < N_BUTTONS; i++) {
    uint8_t ix = i % 4;
    uint8_t iy = i / 4;
    uint8_t dx = abs(x - ix);
    uint8_t dy = abs(y - iy);

    if (dx >= d || dy >= d) {
      _trellis->clrLED(i);
    } else {
      if (ix == x || iy == y) {
        _trellis->setLED(i);
      } else {
        _trellis->clrLED(i);
      }
    }
  }
  _trellis->writeDisplay();
}

void Navigation::clearTrellis() {
  for (uint8_t i = 0; i < N_BUTTONS; i++) {
    _trellis->clrLED(i);
  }
  _trellis->writeDisplay();
}
