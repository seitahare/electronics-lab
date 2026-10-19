// Experiment 14: accelerometer tilt commands an external-powered SG90.
// Code transcribed from the 2026-10-19 demonstration.
#include <Wire.h>
#include <math.h>

const int SDA_PIN = 5;
const int SCL_PIN = 6;
const int SERVO_PIN = 3;  // XIAO D2
const uint8_t IMU_ADDR = 0x6A;
const int PWM_FREQ = 50;
const int PWM_BITS = 14;
bool imuReady = false;
float filteredTilt = 0.0f;
bool firstReading = true;

bool writeReg(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(IMU_ADDR);
    Wire.write(reg);
    Wire.write(value);
    return Wire.endTransmission() == 0;
}

bool readRegs(uint8_t reg, uint8_t *data, uint8_t len) {
    Wire.beginTransmission(IMU_ADDR);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0) return false;
    if (Wire.requestFrom(IMU_ADDR, len) != len) return false;
    for (int i = 0; i < len; i++) data[i] = Wire.read();
    return true;
}

void setServoAngle(float angle) {
    angle = constrain(angle, 30.0f, 150.0f);
    float pulseUs = 1000.0f + angle * (1000.0f / 180.0f);
    uint32_t duty = (uint32_t)(pulseUs * (1 << PWM_BITS) / 20000.0f);
    ledcWrite(SERVO_PIN, duty);
}

void setup() {
    Serial.begin(115200);
    delay(2000);
    Wire.begin(SDA_PIN, SCL_PIN);
    Wire.setClock(100000);
    Wire.setTimeOut(100);

    uint8_t id;
    if (!readRegs(0x0F, &id, 1) || id != 0x70) {
        Serial.println("IMU not detected");
        return;
    }
    imuReady =
        writeReg(0x12, 0x44) &&
        writeReg(0x17, 0x00) &&
        writeReg(0x15, 0x01) &&
        writeReg(0x10, 0x06) &&
        writeReg(0x11, 0x06);
    if (!imuReady) {
        Serial.println("IMU initialization failed");
        return;
    }
    if (!ledcAttach(SERVO_PIN, PWM_FREQ, PWM_BITS)) {
        Serial.println("PWM initialization failed");
        imuReady = false;
        return;
    }
    setServoAngle(90);
    Serial.println("Experiment 14 Started!");
}

void loop() {
    if (!imuReady) { delay(1000); return; }
    uint8_t data[6];
    if (!readRegs(0x28, data, 6)) {
        Serial.println("IMU read failed");
        delay(100);
        return;
    }

    int16_t axRaw = (int16_t)((data[1] << 8) | data[0]);
    int16_t ayRaw = (int16_t)((data[3] << 8) | data[2]);
    int16_t azRaw = (int16_t)((data[5] << 8) | data[4]);
    float ax = axRaw * 0.00059820565f;
    float ay = ayRaw * 0.00059820565f;
    float az = azRaw * 0.00059820565f;

    float tilt = atan2(ay, az) * 180.0f / PI;
    if (firstReading) {
        filteredTilt = tilt;
        firstReading = false;
    } else {
        filteredTilt = 0.85f * filteredTilt + 0.15f * tilt;
    }
    float servoAngle = 90.0f + filteredTilt * (60.0f / 45.0f);
    servoAngle = constrain(servoAngle, 30.0f, 150.0f);
    setServoAngle(servoAngle);

    Serial.print("Tilt: ");
    Serial.print(filteredTilt, 1);
    Serial.print(" deg | Servo: ");
    Serial.println(servoAngle, 1);
    delay(50);
}
