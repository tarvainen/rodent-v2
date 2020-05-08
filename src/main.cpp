#include <Arduino.h>
#include <Stepper.h>

Stepper stepperY(7, 8, 9, 200, 360);
Stepper stepperX(10, 11, 12, 200, 360);
Stepper stepperZ(4, 5, 6, 200, 360);

void setup() {
  
}

void loop() {
  stepperY.enable();
  stepperX.enable();
  stepperZ.enable();

  stepperY.setDirection(1);
  stepperX.setDirection(1);
  stepperZ.setDirection(1);

  int len = 5000;

  for (int i = 0; i < len; i++) {
    stepperY.step();
    stepperX.step();
    stepperZ.step();
    delayMicroseconds(700);
  }

  stepperY.disable();
  stepperX.disable();
  stepperZ.disable();

  delay(2000);

  stepperY.enable();
  stepperX.enable();
  stepperZ.enable();
  
  stepperY.setDirection(-1);
  stepperX.setDirection(-1);
  stepperZ.setDirection(-1);

  for (int i = 0; i < len; i++) {
    stepperY.step();
    stepperX.step();
    stepperZ.step();
    delayMicroseconds(700);
  }
  
  stepperY.disable();
  stepperX.disable();
  stepperZ.disable();

  delay(2000);
}