// Experiment 13: I2C OLED greeting and software counter.
// Requires Adafruit SSD1306 and Adafruit GFX libraries.
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
uint8_t oledAddress = 0;
unsigned long counter = 0;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Wire.begin(5, 6);
    Wire.setClock(100000);
    Serial.println("OLED Test Starting...");

    const uint8_t addresses[] = {0x3C, 0x3D};
    for (uint8_t addr : addresses) {
        Wire.beginTransmission(addr);
        if (Wire.endTransmission() == 0) {
            oledAddress = addr;
            break;
        }
    }
    if (oledAddress == 0) {
        Serial.println("OLED not detected");
        return;
    }
    Serial.print("OLED detected: 0x");
    Serial.println(oledAddress, HEX);

    if (!display.begin(SSD1306_SWITCHCAPVCC, oledAddress, true, false)) {
        Serial.println("OLED initialization failed");
        oledAddress = 0;
        return;
    }
    Serial.println("OLED initialized!");
}

void loop() {
    if (oledAddress == 0) { delay(1000); return; }
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("HELLO!");
    display.setTextSize(1);
    display.setCursor(0, 30);
    display.println("electronics-lab");
    display.setCursor(0, 45);
    display.print("Count: ");
    display.println(counter++);
    display.display();
    delay(1000);
}
