// Experiment 07: Compare DC meter readings for two PWM settings.
// Measure D9 relative to GND with the multimeter in DC voltage mode.
// First upload with pwmValue = 128; change it to 64 and upload again.
const int ledPin = 9;
const int pwmValue = 128;

void setup()
{
    pinMode(ledPin, OUTPUT);
}

void loop()
{
    analogWrite(ledPin, pwmValue);
}
