
#include "ShortcutKeys.h"
#include "Keyboard.h"


ShortcutKeys::ShortcutKeys(Adafruit_TrellisSet *trellis){
  _trellis = trellis;
}

void ShortcutKeys::loop(){
  if (_trellis->readSwitches()) {
    for (uint8_t i = 0; i < 16; i++) {
      if (_trellis->justPressed(i)) {
        sendToKeyboard(i);  
        _trellis->setLED(i);
      } else if (_trellis->justReleased(i)) {
        _trellis->clrLED(i);
      }
    }
    _trellis->writeDisplay();
  }
  delay(30);
  
}

void ShortcutKeys::sendToKeyboard(uint8_t index){
  if(index == 0){ 
    // LOCK MAC
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(' ');
    Keyboard.releaseAll();
    Keyboard.print("lock");
    Keyboard.write(KEY_RETURN);
  }else if ( index == 1){ 
    // UNLOCK MAC
    Keyboard.print("123qwe");
    Keyboard.write(KEY_RETURN);
  }else if ( index == 2){ 
    // FORCE QUIT 
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_ESC);
    Keyboard.releaseAll();
  }else if ( index == 3){
    // MUTE - UNMUTE
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('m');
    Keyboard.releaseAll();
  }else if ( index == 4){
    // F1
    Keyboard.write(KEY_F1);
  }else if ( index == 5){
    // F2
    Keyboard.write(KEY_F2);
  }else if ( index == 6){
    // UNITY WORK VIEW COMMAND 1
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('1');
    Keyboard.releaseAll();
  }else if ( index == 7){
    // UNITY GAME VIEW COMMAND 2
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('2');
    Keyboard.releaseAll();
  }

  delay(50);
}
