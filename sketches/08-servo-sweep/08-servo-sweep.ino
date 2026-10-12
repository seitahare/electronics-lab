// Experiment 08: Command several positions on an SG90 servo.
// Power the servo from the external regulated 5 V source, and share GND.
#include <Servo.h>

Servo myServo;

void setup()
{
    myServo.attach(9);
}

void loop()
{
    myServo.write(30);
    delay(1500);

    myServo.write(90);
    delay(1500);

    myServo.write(150);
    delay(1500);

    myServo.write(90);
    delay(1500);
}
