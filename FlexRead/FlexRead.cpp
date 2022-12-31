#include <stdint.h>
#include "Arduino.h"
#include "LiquidCrystal.h"
#include "DFRobotDFPlayerMini.h"
#include "./DFPlayer/DFPlayer.h"
#include "FlexRead.h"

uint16_t analog_data = 0;
uint16_t threshold = 580;

uint32_t previousMillis = 0;
const uint32_t interval = 5000;

void FlexLoop(LiquidCrystal &lcdF, DFRobotDFPlayerMini &myDFPlayerF) {
  analog_data = analogRead(A0);
  //Serial.println(analog_data);
  uint32_t currentMillis = millis();
  if (analog_data > threshold + 50) {
    /* DOWNWARD BEND FUNCTION */
    lcdF.clear();
    lcdF.print("I want water");
    uint32_t currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      myDFPlayerF.play(1);
    }
  } else if (analog_data < threshold - 50) {
    lcdF.clear();
    lcdF.print("I want food");
    uint32_t currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      myDFPlayerF.play(2);
    }
  } else {
    lcdF.clear();
    lcdF.print("NO COMMAND");
  }
}
