
#include <Wire.h>
#include "Adafruit_Trellis.h"
#include <Rotary.h>
#include "MIDIUSB.h"
#include "Navigation.h"
#include "MIdiPlayer.h"
#include "ShortcutKeys.h"
#include "Keyboard.h"
#include "Sequencer.h"

#define MIDI_PROG 0
#define SHORTCUT_KEYS 1
#define SEQUENCER 2

#ifdef ARDUINO_ARCH_SAMD
  Wire.setClock(400000L);
#endif


// SIMON SAYS
// SEQUENCER
// SERIAL DATA TRANSFER
// GIF MAKER
// DEMO MODE

// TRELLIS
// SDA -> PIN 2 YELLOW
// SCL -> PIN 3 GREEN
Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);

// ROTARY CONTROLLER
int pinA = 8;  // Connected to CLK on KY-040 YELLOWc
int pinB = 7;  // Connected to DT on KY-040
int pinP = 6;   // Connected to SW on KY-40
Rotary rotary = Rotary(pinA, pinB);

// NAVIGATION
Navigation navigation = Navigation(&trellis, &rotary);

// MIDI
MidiPlayer midiPlayer = MidiPlayer(&trellis);

// SHORTCUT KEYS
ShortcutKeys shortcutKeys = ShortcutKeys(&trellis);

// SEQUENCER
Sequencer sequencer = Sequencer(&trellis);

void setup() {
  Serial.begin(115200);
  Serial.println("CUBE Demo");

  trellis.begin(0x70);
  pinMode (pinP, INPUT_PULLUP);
  
  trellis.setLED(navigation.getProgramIndex());
  trellis.writeDisplay();

  Keyboard.begin();
}

void loop() {

  if (navigation.updateState(digitalRead(pinP))) {
    uint8_t programIndex = navigation.getProgramIndex();
    switch(programIndex){
      case MIDI_PROG:
        midiPlayer.loop();
        break;
      case SHORTCUT_KEYS:
        shortcutKeys.loop();
        break;
      case SEQUENCER:
        sequencer.loop();
        break;
    }
  }
}
