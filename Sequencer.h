#include "Arduino.h"
#include "Adafruit_Trellis.h"
#include "MIDIUSB.h"

class Sequencer{
  public:
    static const uint8_t 
      COLUMNS = 4, 
      STEP_DURATION = 1000;

    Sequencer(Adafruit_TrellisSet *trellis);
    void loop();
  private:
    Adafruit_TrellisSet *_trellis;
    uint8_t _index;
    unsigned long _nowMilis = 0;
    int _selectedIds[16];
    int _activeMidiNotes[4];
    void playMidiNotes(uint8_t index);
    void lightColumn(uint8_t column);
    void lightSelectedIds();
    void clearAll();
};
