
#include "MidiPlayer.h"

MidiPlayer::MidiPlayer(Adafruit_TrellisSet *trellis) {
  _trellis = trellis;
}

void MidiPlayer::loop() {
  if (_trellis->readSwitches()) {
    for (uint8_t i = 0; i < 16; i++) {
      uint8_t note = LOWNOTE + i;
      if (_trellis->justPressed(i)) {
        Serial.print("v");
        Serial.println(i);
        Serial.println(note);
        noteOn(CHANNEL, note, 127);
        _trellis->setLED(i);
      } else if (_trellis->justReleased(i)) {
        noteOff(CHANNEL, note, 0);
        _trellis->clrLED(i);
      }
    }
    _trellis->writeDisplay();
  }
  delay(30);
}

void MidiPlayer::noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();
}

void MidiPlayer::noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush();
}
