#include "button.h"

#define PIN_BUTTON 5
Button button(PIN_BUTTON);

//#define PIN_RED 6
//#define PIN_GREEN 7
//#define PIN_BLUE 8
int lampsPins[] = {6, 7, 8};
int lampsCount = sizeof(lampsPins)/sizeof(int);
bool allLampsAreOn;
bool allLampsAreOff;

#define totalModes 4;
int currentMode;

unsigned long modeStartTime;//ms
unsigned long delayTime;

void setup() {
  allLampsAreOn = false;
  allLampsAreOff = false;
  currentMode = 0;
  modeStartTime = millis();
  delayTime = 500;//ms
  Serial.begin(115200);
}

void loop() {
  if (button.wasPressed())
  {
    //меняем режим
    currentMode = (currentMode + 1) % totalModes;
    modeStartTime = millis();
    Serial.println(currentMode);
  }
  //проигрываем текущий режим
  switch (currentMode)
  {
    case 1:
      mode_one();
    break;
    case 2:
      mode_two();
    break;
    case 3:
      mode_three();
    default:
      mode_zero();
    break;
  }
}

void set_brightness(int pin, int brightness) {
  analogWrite(pin, 255-brightness);
}

//Выключен
void mode_zero() {
  if (!allLampsAreOff)
  {
    for (int i = 0; i < lampsCount; i++)
      set_brightness(lampsPins[i], 0);
    allLampsAreOn = false;
    allLampsAreOff = true;
  }
}
//Постоянно горит
void mode_one() {
  if (!allLampsAreOn)
  {
    for (int i = 0; i < lampsCount; i++)
      set_brightness(lampsPins[i], 255);
    allLampsAreOn = true;
    allLampsAreOff = false;
  }
}
//Мигает всеми сразу
void mode_two() {
  if (millis() - modeStartTime >= delayTime)
  {
    if (allLampsAreOn)
      mode_zero();
    else
      mode_one();
    modeStartTime = millis();
  }
}
//Горящий смещается (змейка)
int currentLamp = 0;
void mode_three() {
  if (millis() - modeStartTime >= delayTime)
  {
    mode_zero();
    currentLamp = (currentLamp + 1) % lampsCount;
    set_brightness(lampsPins[currentLamp], 255);
    allLampsAreOn = false;
    allLampsAreOff = false;
    modeStartTime = millis();
  }
}
