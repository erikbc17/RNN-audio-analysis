// DATA COLLECTION CODE 
// Erik Barraza Cordova

#include <Arduino_BuiltIn.h>

#include <ArduinoBLE.h>
#include <ArduinoSound.h>

const int numWords = 5;
const int ledRed = LEDR;    // Red LED pin
const int ledGreen = LEDG;  // Green LED pin
const int ledBlue = LEDB;   // Blue LED pin

// Absolute language keywords
const char* words[numWords] = {
  "never",
  "none",
  "all",
  "must",
  "only"
};

void setup() {
  Serial.begin(9600); // Serial Monitor Setup for indicators & LED pin
  while (!Serial);

  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
}
// recording the words in a loop so as to collect audio files that will enable us to understand the full 
void loop() {
  for (int i = 0; i < numWords; ++i) {
    recordWord(words[i]);
    delay(2000);
  }
}

void recordWord(const char* word) {
  Serial.print("Recording word: ");
  Serial.println(word);

  setLEDColor(word);

  Serial.println("Recording...");
  delay(500);
  int recordingTime = 3000;
  Sound.startRecording(word, recordingTime);
  delay(recordingTime);
  Sound.stopRecording();

  resetLEDColor();
}

void setLEDColor(const char* word) {
  if (strcmp(word, "never") == 0) {
    analogWrite(ledRed, 255);   // Red for "never"
  } else if (strcmp(word, "none") == 0) {
    analogWrite(ledGreen, 255); // Green for "none"
  } else if (strcmp(word, "all") == 0) {
    analogWrite(ledBlue, 255);  // Blue for "all"
  } else if (strcmp(word, "must") == 0) {
    analogWrite(ledRed, 255);   // Red for "must"
    analogWrite(ledGreen, 255); // Green for "must"
  } else if (strcmp(word, "only") == 0) {
    analogWrite(ledRed, 255);   // Red for "only"
    analogWrite(ledBlue, 255);  // Blue for "only"
  }
}

void resetLEDColor() {
  analogWrite(ledRed, 0);
  analogWrite(ledGreen, 0);
  analogWrite(ledBlue, 0);
}
