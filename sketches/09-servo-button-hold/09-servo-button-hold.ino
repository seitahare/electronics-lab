// Experiment 09: Hold the button for the 90-degree target.
// D2 connects to GND when pressed; internal pull-up is enabled.
#include <Servo.h>

Servo myServo;

const int servoPin = 9;
const int buttonPin = 2;

void setup()
{
    myServo.attach(servoPin);
    pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
    int buttonState = digitalRead(buttonPin);

    if (buttonState == LOW) {
        myServo.write(90);
    } else {
        myServo.write(30);
    }
}
