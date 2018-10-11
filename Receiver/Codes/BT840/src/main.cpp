#include <Arduino.h>
#include <Wire.h>
#include <BLEPeripheral.h>

// Max Characters = 16  (for now)
BLEPeripheral peripheral = BLEPeripheral();
BLEService service = BLEService("19b11234e8f2537e4f6cd104768a1214");

char var[] = "BLE Character";
BLECharacteristic characteristic = BLECharacteristic("19b10000e8f2537e4f6cd104768a1214", BLERead | BLEWrite, 16);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(38400);
  peripheral.setAdvertisedServiceUuid(service.uuid());
  peripheral.addAttribute(service);

  peripheral.addAttribute(characteristic);

  Serial.println("Start!");

  characteristic.setValue((unsigned char*)var, 16);

  peripheral.setLocalName("BLE Device");
  peripheral.begin();

  Wire.begin();
}

void loop() {

BLECentral other_device = peripheral.central();

  if (other_device) {
    digitalWrite(LED_BUILTIN, LOW);

    while (other_device.connected()) {

      if (characteristic.written()) {
        if (characteristic.value()) {

           sprintf(var, "%16c", NULL);
           strncpy(var, (char*)characteristic.value(), characteristic.valueLength());

           Wire.beginTransmission(9);
           Wire.write(var);
           Wire.endTransmission();
        }
      }
    }
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
