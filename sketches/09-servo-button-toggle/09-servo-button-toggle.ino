// Experiment 09: Toggle the target on each distinct button press.
// The release-wait loop intentionally blocks other work in this simple example.
#include <Servo.h>

Servo myServo;

const int servoPin = 9;
const int buttonPin = 2;

bool is90 = false;

void setup()
{
    myServo.attach(servoPin);
    pinMode(buttonPin, INPUT_PULLUP);

    myServo.write(30);
}

void loop()
{
    if (digitalRead(buttonPin) == LOW) {
        delay(30);

        if (digitalRead(buttonPin) == LOW) {
            is90 = !is90;

            if (is90) {
                myServo.write(90);
            } else {
                myServo.write(30);
            }

            while (digitalRead(buttonPin) == LOW) {
                delay(1);
            }

            delay(30);
        }
    }
}
