# Experiment 15 — ESP32-S3 Wi-Fi and Bluetooth LE

**Date:** 2026-10-19  
**Status:** In progress — Wi-Fi scanning succeeded; association, data exchange and BLE remain unverified

## Objective

Test wireless networking on the XIAO ESP32S3 Sense, first discovering nearby 2.4 GHz Wi-Fi access points, then progressing to network communication and Bluetooth Low Energy.

## Reference / theory

The ESP32-S3 radio supports 2.4 GHz Wi-Fi and Bluetooth Low Energy. A successful Wi-Fi **scan** demonstrates local network discovery, but does not mean the device is connected to an access point, has obtained an IP address, or can exchange application data.

## Equipment

- Seeed Studio XIAO ESP32S3 Sense
- External antenna and u.FL antenna connector
- USB connection to Mac; Arduino IDE and ESP32 Wi-Fi scan program

## Circuit

The XIAO was powered by USB, and the external antenna was connected for the successful scan. No breadboard, IMU, servo, or OLED was necessary in the scanning setup.

## Experimental procedure

1. Power the XIAO ESP32S3 Sense over USB and run a Wi-Fi scanning program.
2. Record the initial scan result before the external antenna is connected.
3. Connect the external antenna carefully to the u.FL connector.
4. Repeat the scan and compare the number of discovered networks.
5. Stop at network discovery; do not report association, IP configuration, application data transfer, or Bluetooth LE as completed.

## Predictions

When properly connected to an antenna and powered, the ESP32-S3 should discover visible nearby 2.4 GHz networks. Network count varies with RF conditions and location.

## Measurements and observations

| Test | Expected | Observation | Qualification |
| --- | --- | --- | --- |
| Initial network scan | Some nearby SSIDs may be found | **Networks found: 0** | External antenna had not been connected |
| Scan after connecting external antenna | Nearby SSIDs detected | **11 SSIDs listed** | Direct Arduino Serial Monitor output |
| Wi-Fi association | Connected and assigned an address | **Not tested or verified** | Work remaining |
| Mac-to-XIAO data transfer | Successful application messages | **Not tested or verified** | Work remaining |
| Bluetooth LE discovery and transfer | Advertise/connect/data | **Not tested or verified** | Work remaining |

The actual neighboring Wi-Fi network names are intentionally omitted from the public log.

## Arduino code

The exact successful Wi-Fi scan source was not saved, so no fabricated 'tested' sketch is added to this repository.

## Photos

No photo of the wireless test setup is included in this update.

## Troubleshooting

The first scan returned **Networks found: 0**. Investigation identified that the external antenna had not been connected. After connecting it and repeating the scan, **11 SSIDs** were listed. This confirms that the antenna connection changed the observed scan outcome, while not constituting a full RF performance test.

## Analysis

The initial zero-network result was followed by successful discovery after the missing external antenna connection was addressed. This supports working basic Wi-Fi network scanning; it does not test reliable data communication or the Bluetooth peripheral.

## Lessons learned

- Handle u.FL antenna connectors carefully and avoid repeated radio testing without a suitable antenna.
- A successful Wi-Fi scan verifies discovery only; it does not verify association, IP networking, or application communication.
- The original tested source should be preserved when it becomes available rather than reconstructed and labeled as historical code.

## Next steps

- Join an authorized Wi-Fi network and retain the connection and IP-address output.
- Exchange a simple HTTP or socket message with the Mac.
- Test Bluetooth Low Energy advertising, discovery, connection, and data transfer independently.
- Keep Experiment 15 **in progress** until those functions are demonstrated.
