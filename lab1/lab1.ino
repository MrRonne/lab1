#include "button.h"

const int totalModes = 4;
const int lampsPins[] = {6, 7, 8};
const int lampsCount = sizeof(lampsPins)/sizeof(int);
const int buttonPin = 5;
const Button button(buttonPin);

int currentMode;
int currentBlinkingLamp;
bool allLampsAreOn;
bool allLampsAreOff;
unsigned long modeStartTimeMs;
unsigned long delayTimeMs;

void setup() {
  currentMode = 0;
  allLampsAreOn = false;
  allLampsAreOff = false;
  modeStartTimeMs = millis();
  delayTimeMs = 500;
  Serial.begin(115200);
}

void loop() {
  if (button.wasPressed())
    setNextMode();
  playCurrentMode();
}

void setNextMode()
{
    currentMode = (currentMode + 1) % totalModes;
    modeStartTimeMs = millis();
    Serial.println(currentMode);
}

void playCurrentMode()
{
  switch (currentMode)
  {
    case 1:
      modeTurnedOn();
    break;
    case 2:
      modeBlink();
    break;
    case 3:
      modeSnake();
    break;
    default:
      modeTurnedOff();
    break;
  }
}

void setBrightness(int pin, int brightness) {
  analogWrite(pin, 255-brightness);
}

void modeTurnedOff() {
  if (!allLampsAreOff)
  {
    for (int i = 0; i < lampsCount; i++)
      setBrightness(lampsPins[i], 0);
    allLampsAreOn = false;
    allLampsAreOff = true;
  }
}

void modeTurnedOn() {
  if (!allLampsAreOn)
  {
    for (int i = 0; i < lampsCount; i++)
      setBrightness(lampsPins[i], 255);
    allLampsAreOn = true;
    allLampsAreOff = false;
  }
}

void modeBlink() {
  if (millis() - modeStartTimeMs >= delayTimeMs)
  {
    if (allLampsAreOn || !allLampsAreOff)
      modeTurnedOff();
    else
      modeTurnedOn();
    modeStartTimeMs = millis();
  }
}

void modeSnake() {
  if (millis() - modeStartTimeMs >= delayTimeMs)
  {
    modeTurnedOff();
    currentBlinkingLamp = (currentBlinkingLamp + 1) % lampsCount;
    setBrightness(lampsPins[currentBlinkingLamp], 255);
    allLampsAreOn = false;
    allLampsAreOff = false;
    modeStartTimeMs = millis();
  }
}
