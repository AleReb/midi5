// Inclusión de la biblioteca MIDIUSB para la comunicación MIDI
#include "MIDIUSB.h"

// Definición de pines para los botones que enviarán las notas MIDI
const int buttonPins[] = {4, 5, 6, 7, 8, 9, 10, 11};
const int numButtons = sizeof(buttonPins) / sizeof(int);

// Notas base en formato MIDI: C4 (DO), D4 (RE), E4 (MI), F4 (FA), G4 (SOL), A4 (LA), B4 (SI) y C5 (DO)
const int baseMidiNotes[] = {60, 62, 64, 65, 67, 69, 71, 72};

// Array para almacenar el estado anterior de los botones
bool lastButtonState[numButtons] = {0};

// Definición de pines para los potenciómetros
const int volumePot = A0;
const int scalePot = A1;
const int modulationPot = A2;

int currentScale = 0;
int lastModulationValue = -1; 
int lastVolumeValue = -1;

void setup() {
  // Configuración de los pines de botones como entrada con resistencia pull-up interna
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  // Lectura del potenciómetro de volumen y ajuste al rango MIDI (0-127)
  int volume = analogRead(volumePot) / 8;

  // Determinación de la escala actual basada en la lectura del potenciómetro de escala
  int newScale;
  int scaleRead = analogRead(scalePot);
  if (scaleRead < 205) newScale = -2;
  else if (scaleRead < 410) newScale = -1;
  else if (scaleRead < 615) newScale = 0;
  else if (scaleRead < 820) newScale = 1;
  else newScale = 2;

  // Si hay un cambio en la escala, ajustar las notas de acuerdo a la nueva escala
  if (newScale != currentScale) {
    for (int i = 0; i < numButtons; i++) {
      if (digitalRead(buttonPins[i]) == LOW) {
        noteOff(0x0, baseMidiNotes[i] + (currentScale * 12), volume); 
        noteOn(0x0, baseMidiNotes[i] + (newScale * 12), volume);
      }
    }
    currentScale = newScale;
  }

  // Lectura del potenciómetro de modulación y ajuste al rango MIDI (0-127)
  int modulationValue = analogRead(modulationPot) / 8;

  // Si hay un cambio en la modulación, enviar el nuevo valor
  if (abs(modulationValue - lastModulationValue) > 1) {
    sendModulation(modulationValue, 0x0);
    lastModulationValue = modulationValue;
  }

  // Si hay un cambio en el volumen, enviar el nuevo valor
  if (abs(volume - lastVolumeValue) > 1) {
    sendVolumeChange(volume, 0x0);
    lastVolumeValue = volume;
  }

  // Verificar el estado de cada botón y enviar la nota correspondiente si se presiona o se suelta
  for (int i = 0; i < numButtons; i++) {
    bool buttonState = digitalRead(buttonPins[i]) == LOW;

    if (buttonState != lastButtonState[i]) {
      if (buttonState) {
        noteOn(0x0, baseMidiNotes[i] + (currentScale * 12), volume); 
      } else {
        noteOff(0x0, baseMidiNotes[i] + (currentScale * 12), volume);
      }

      lastButtonState[i] = buttonState;
    }
  }

  // Enviar todos los mensajes MIDI acumulados
  MidiUSB.flush();
}

// Funciones auxiliares para enviar mensajes MIDI
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void sendModulation(int modulationValue, byte channel) {
  midiEventPacket_t modulation = {0x0B, 0xB0 | channel, 1, modulationValue};
  MidiUSB.sendMIDI(modulation);
}

void sendVolumeChange(int volumeValue, byte channel) {
  midiEventPacket_t volumeChange = {0x0B, 0xB0 | channel, 7, volumeValue};
  MidiUSB.sendMIDI(volumeChange);
}
