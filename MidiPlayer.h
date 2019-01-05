#include "Arduino.h"
#include "MIDIUSB.h"
#include "Adafruit_Trellis.h"

class MidiPlayer{
  public:
    MidiPlayer(Adafruit_TrellisSet *trellis);
    static const uint8_t 
      CHANNEL = 1, 
      LOWNOTE = ((128 - 16) / 2);
      
    void loop();
    void noteOn(byte channel, byte pitch, byte velocity);
    void noteOff(byte channel, byte pitch, byte velocity);
  private:
    Adafruit_TrellisSet *_trellis;
};
