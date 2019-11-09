#include "button.h"

#define R_OUT 6
#define G_OUT 7
#define B_OUT 8

void setup()
{
    Serial.begin(115200);
    pinMode(R_OUT, OUTPUT);
    pinMode(G_OUT, OUTPUT);
    pinMode(B_OUT, OUTPUT);
}

void loop() {
    if (buttonOff.wasPressed())
    {
      //меняем режим
    }
    //проигрываем текущий режим
}

void set_rgb_led(colorData rgb)
{
    analogWrite(R_OUT, 255 - rgb.value[TCS230_RGB_R]);
    analogWrite(G_OUT, 255 - rgb.value[TCS230_RGB_G]);
    analogWrite(B_OUT, 255 - rgb.value[TCS230_RGB_B]);
}
