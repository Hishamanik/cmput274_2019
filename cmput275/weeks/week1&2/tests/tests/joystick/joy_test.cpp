#include <Arduino.h>

#define JOY_VERT  A9 // should connect A9 to pin VRx
#define JOY_HORIZ A8 // should connect A8 to pin VRy
#define JOY_SEL   51

#define JOY_CENTRE   512
#define JOY_DEADZONE  64

void setup() {
  init();

  pinMode(JOY_SEL, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void joystickReadings() {
  int xVal = analogRead(JOY_HORIZ);
  int yVal = analogRead(JOY_VERT);
  int buttonVal = digitalRead(JOY_SEL);

  // x value increases as we push left, decreases as we push right
  Serial.print("xVal: ");
  Serial.println(xVal);

  // y value increases as we push down, decreases as we push up
  Serial.print("yVal: ");
  Serial.println(yVal);

  Serial.print("buttonVal: ");
  Serial.println(buttonVal);

  Serial.println("-------------");
}

void printDirection() {
  int xVal = analogRead(JOY_HORIZ);
  int yVal = analogRead(JOY_VERT);
  int buttonVal = digitalRead(JOY_SEL);
  bool stickPushed = false;

  if (xVal > JOY_CENTRE + JOY_DEADZONE) {
    Serial.print("left ");
    stickPushed = true;
  }
  else if (xVal < JOY_CENTRE - JOY_DEADZONE) {
    Serial.print("right ");
    stickPushed = true;
  }

  if (yVal < JOY_CENTRE - JOY_DEADZONE) {
    Serial.print("up ");
    stickPushed = true;
  }
  else if (yVal > JOY_CENTRE + JOY_DEADZONE) {
    Serial.print("down ");
    stickPushed = true;
  }

  /**  if (abs(xVal - JOY_CENTRE) <= JOY_DEADZONE &&
      abs(yVal - JOY_CENTRE) <= JOY_DEADZONE) {
    Serial.print("centre ");
    }*/
  if (!stickPushed) {
    Serial.print("centre ");
  }

  if (buttonVal == LOW) {
    Serial.print("pushed ");
  }

  Serial.println();
}

int main() {
  setup();

  while (true) {
    printDirection();
   joystickReadings();
    delay(1000);
  }
  
  Serial.end();
  
  return 0;
}
