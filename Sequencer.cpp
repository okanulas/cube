
#include "Sequencer.h"

static const uint8_t MIDI_NOTES[4]= { 48, 49, 50, 51};
      
Sequencer::Sequencer(Adafruit_TrellisSet *trellis){
  _trellis = trellis;
}

void Sequencer::loop(){

  if (_trellis->readSwitches()) {
    for (uint8_t i = 0; i < 16; i++) {
      if (_trellis->justPressed(i)) {
        _selectedIds[i] = _selectedIds[i] == 0 ? 1 : 0; 
        lightSelectedIds();
        _trellis->writeDisplay();
        Serial.print("PRESSED:");
        Serial.print(i);
        Serial.print(" State:");
        Serial.print(_selectedIds[i]);
        Serial.println();
      }
    }
  }
  if(millis() > _nowMilis + STEP_DURATION){
      _nowMilis = millis(); 
      _index++;
      if(_index>3) _index = 0;
      clearAll();
      lightColumn(_index);
      lightSelectedIds();
      _trellis->writeDisplay();
      playMidiNotes(_index);
    }
    delay(30);
}

void Sequencer::playMidiNotes(uint8_t index){
  for (uint8_t i = 0; i < 4; i++) {
    if(_activeMidiNotes[i]!= 0){
      midiEventPacket_t noteOff = {0x08, 0x80 | 1, _activeMidiNotes[i], 0};
      MidiUSB.sendMIDI(noteOff); 
    }   
  }

  for (uint8_t j = 0; j < 4; j++) {
    if(_selectedIds[index+j*4] == 1){
      _activeMidiNotes[j] = MIDI_NOTES[j];
      midiEventPacket_t noteOn = {0x09, 0x90 | 1, _activeMidiNotes[j], 127};
      MidiUSB.sendMIDI(noteOn);  
    }else{
      _activeMidiNotes[j] = 0;   
    }
  }
  MidiUSB.flush();
}

void Sequencer::lightColumn(uint8_t column){
  _trellis->setLED(column);
  _trellis->setLED(column+4);
  _trellis->setLED(column+8);
  _trellis->setLED(column+12);
  _trellis->writeDisplay();
}

void Sequencer::lightSelectedIds(){
  for (uint8_t i = 0; i < 16; i++) {
    if(_selectedIds[i] == 1){
      _trellis->setLED(i);
    }
  }
}

void Sequencer::clearAll(){
  for (uint8_t i = 0; i < 16; i++) {
    _trellis->clrLED(i);
  }
}
