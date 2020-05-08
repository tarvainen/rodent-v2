#include <Arduino.h>
#include <Stepper.h>
#include <GCode.h>
#include "commands/MoveLinear.h"
#include "commands/StartSpindle.h"
#include "commands/StopSpindle.h"

Stepper stepperY(7, 8, 9, 200, 360);
Stepper stepperX(10, 11, 12, 200, 360);
Stepper stepperZ(4, 5, 6, 200, 360);

void handleCommand(MoveLinear);
void handleCommand(StartSpindle);
void handleCommand(StopSpindle);

void setup() {
  Serial.begin(9600);

  stepperX.disable();
  stepperY.disable();
  stepperZ.disable();
}

void loop() {
  if (Serial.available()) {
    char result[100];

    Serial.readBytesUntil('\n', result, 100);

    GCode code;
    code.parse(result);

    if (code.has('G')) {
      float g = code.get('G');

      if (g == 1) {
        MoveLinear cmd(code.get('X'), code.get('Y'), code.get('Z'));
        handleCommand(cmd);
      }
    }

    if (code.has('M')) {
      float m = code.get('M');

      if (m == 3) {
        StartSpindle cmd;
        handleCommand(cmd);
      }

      if (m == 5) {
        StopSpindle cmd;
        handleCommand(cmd);
      }
    }
  }
}

void handleCommand(MoveLinear cmd) {
  Serial.println("Linear movement");

  float x = cmd.getX();
  float y = cmd.getY();
  float z = cmd.getZ();

  if (x != 0) {
    stepperX.enable();
    stepperX.setDirection(-x / abs(x));

    for (int i = 0; i < 250 * abs(x); i++) {
      stepperX.step();
      delayMicroseconds(800);
    }

    stepperX.disable();
  }

  if (y != 0) {
    stepperY.enable();
    stepperY.setDirection(-y / abs(y));

    for (int i = 0; i < 250 * abs(y); i++) {
      stepperY.step();
      delayMicroseconds(800);
    }

    stepperY.disable();
  }

  if (z != 0) {
    stepperZ.enable();
    stepperZ.setDirection(-z / abs(z));

    for (int i = 0; i < 250 * abs(z); i++) {
      stepperZ.step();
      delayMicroseconds(800);
    }

    stepperZ.disable();
  }
}

void handleCommand(StartSpindle cmd) {
  Serial.println("Start spindle");
}

void handleCommand(StopSpindle cmd) {
  Serial.println("Stop spindle");
}
