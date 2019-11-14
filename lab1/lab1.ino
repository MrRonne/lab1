#include "button.h"

#define PIN_BUTTON 5
Button button(PIN_BUTTON);

int lampsPins[] = {6, 7, 8};
int lampsCount = sizeof(lampsPins)/sizeof(int);
bool allLampsAreOn;
bool allLampsAreOff;

#define totalModes 4;
int currentMode;

unsigned long modeStartTimeMs;
unsigned long delayTimeMs;

void setup() {
  allLampsAreOn = false;
  allLampsAreOff = false;
  currentMode = 0;
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
    if (allLampsAreOn)
      modeTurnedOff();
    else
      modeTurnedOn();
    modeStartTimeMs = millis();
  }
}

int currentLamp = 0;
void modeSnake() {
  if (millis() - modeStartTimeMs >= delayTimeMs)
  {
    modeTurnedOff();
    currentLamp = (currentLamp + 1) % lampsCount;
    setBrightness(lampsPins[currentLamp], 255);
    allLampsAreOn = false;
    allLampsAreOff = false;
    modeStartTimeMs = millis();
  }
}
