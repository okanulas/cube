
#include "Arduino.h"
#include "Adafruit_Trellis.h"

class ShortcutKeys{
  public:
    ShortcutKeys(Adafruit_TrellisSet *trellis);
    void loop();

  private:
    Adafruit_TrellisSet *_trellis;
    void sendToKeyboard(uint8_t index);
};
