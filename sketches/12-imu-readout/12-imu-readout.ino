// Experiment 12: read LSM6DSV16X acceleration and angular rate.
// Code transcribed from the successful 2026-10-19 demonstration.
#include <Wire.h>

const uint8_t IMU = 0x6A;
bool imuReady = false;

bool writeReg(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(IMU);
    Wire.write(reg);
    Wire.write(value);
    return Wire.endTransmission() == 0;
}

bool readRegs(uint8_t reg, uint8_t *data, uint8_t length) {
    Wire.beginTransmission(IMU);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0) return false;
    if (Wire.requestFrom(IMU, length) != length) return false;
    for (int i = 0; i < length; i++) data[i] = Wire.read();
    return true;
}

void setup() {
    Serial.begin(115200);
    delay(2000);
    Wire.begin(5, 6);
    Wire.setClock(100000);
    Wire.setTimeOut(100);
    Serial.println("LSM6DSV16X Starting...");

    uint8_t id;
    if (!readRegs(0x0F, &id, 1)) {
        Serial.println("IMU communication failed");
        return;
    }
    Serial.print("WHO_AM_I: 0x");
    Serial.println(id, HEX);
    if (id != 0x70) {
        Serial.println("Unexpected device ID");
        return;
    }

    imuReady =
        writeReg(0x12, 0x44) &&
        writeReg(0x17, 0x00) &&
        writeReg(0x15, 0x01) &&
        writeReg(0x10, 0x06) &&
        writeReg(0x11, 0x06);
    Serial.println(imuReady ? "IMU initialized!" : "IMU configuration failed");
}

void loop() {
    if (!imuReady) { delay(1000); return; }
    uint8_t data[12];
    if (!readRegs(0x22, data, 12)) {
        Serial.println("Sensor read failed");
        delay(500);
        return;
    }

    int16_t gx = (int16_t)((data[1] << 8) | data[0]);
    int16_t gy = (int16_t)((data[3] << 8) | data[2]);
    int16_t gz = (int16_t)((data[5] << 8) | data[4]);
    int16_t ax = (int16_t)((data[7] << 8) | data[6]);
    int16_t ay = (int16_t)((data[9] << 8) | data[8]);
    int16_t az = (int16_t)((data[11] << 8) | data[10]);

    Serial.print("ACC: ");
    Serial.print(ax * 0.00059820565f);
    Serial.print(", ");
    Serial.print(ay * 0.00059820565f);
    Serial.print(", ");
    Serial.println(az * 0.00059820565f);

    Serial.print("GYRO: ");
    Serial.print(gx * 0.00875f);
    Serial.print(", ");
    Serial.print(gy * 0.00875f);
    Serial.print(", ");
    Serial.println(gz * 0.00875f);
    Serial.println("--------------------");
    delay(500);
}
