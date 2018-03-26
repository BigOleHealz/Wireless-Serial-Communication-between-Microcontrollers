#PROJECT OVERVIEW
---
This purpose of this project is to wire two Teensy 3.2 boards to communicate with one another wirelessly, with one Teensy acting as a receiver ready to scroll text across an LED screen while the other Teensy acts as a remote telling the receiver what text to display. To accomplish this, both boards were outfitted with nRF24l01 transceiver modules to communicate via RF.

In addition to the dedicated remote, an Android app allows the LED display to be controlled via Bluetooth LE. This requires the receiver Teensy to be equipped with a BLE UART module in addition to the RF transceiver.

#REQUIRED COMPONENTS
-Teensy 3.2


##SUB-HEADING