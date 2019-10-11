#include "button.h"

#define PIN_BUTTON 5
Button button(PIN_BUTTON);

//#define PIN_RED 6
//#define PIN_GREEN 7
//#define PIN_BLUE 8
int lampsPins[] = {6, 7, 8};

#define totalModes 4;
int currentMode;

int delayTime;

void setup() {
  // put your setup code here, to run once:
  currentMode = 0;
  delayTime = 500;//ms
}

void loop() {
  // put your main code here, to run repeatedly:
  if (button.wasPressed())
  {
    //TODO: меняем режим
    currentMode = (currentMode + 1) % totalModes;
  }
  //TODO: проигрываем текущий режим
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
  for (int i = 0; i < sizeof(lampsPins)/sizeof(int); i++)
  {
    set_brightness(i, 0);
  }
}
//Постоянно горит
void mode_one() {
  for (int i = 0; i < sizeof(lampsPins)/sizeof(int); i++)
  {
    set_brightness(i, 255);
  }
}
//Мигает всеми сразу
void mode_two() {
  mode_one();
  delay(delayTime);
  mode_zero();
  delay(delayTime);
}
//Горящий смещается (змейка)
void mode_three() {
  mode_zero();
  for (int i = 0; i < sizeof(lampsPins)/sizeof(int); i++)
  {
    set_brightness(i, 255);
    delay(delayTime);
    set_brightness(i, 0);
  }
}
