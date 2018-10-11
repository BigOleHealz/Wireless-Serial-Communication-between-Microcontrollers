# **Introduction**

The purpose of this project is to wire a MDBT40 chip to wirelessly communicate with a MK20DX256VHL7 Cortex-M4 via Bluetooth 4.2, with the MK20 acting as the receiver ready to scroll text across an LED display while the MDBT40 acts as the remote writing characteristics to the receiver. To accomplish this, the MK20 is outfitted with a BT840 chip to handle Bluetooth communication.

In addition to the dedicated remote, a Bluetooth-enabled smart phone can be used to control the MK20 via our Android app. 

# **Usage**

### Mobile App
The app itself is rather intuitive. Upon first opening the app, the user will be shown a list of all device names within range that have a UUID matching one of the UUIDs in our predefined library. The predefined library ensures that the user will only be shown devices with BT840 chips with our software installed on them. At the time of pairing, the user's device will most likely be the only one within range so finding their device should be very straightforward. If another device is within range, the user may need to sort through the list to find theirs. The user only needs to complete this process once as the UUID of their device will be saved in the app for future use. After this, the phone will automatically connect to the BT840 chip upon launching of the app.

While connected, the user can send a message to the MK20 simply by tapping any of the buttons at the four corners of the screen. Obviously, the message sent will match the text on the button. The button text can be manually changed by long-pressing on the button itself, which clears the text from the button and raises the keyboard. 

In addition, voice functionality is available in the app by tapping the center button. If the message sends successfully, the car icon at the top of the display will zoom across the screen from right to left. If you do not see the car zoom across the screen, it is due to 1 of 3 reasons: either the mobile device is not properly paired to the display, the text input was determined to be aggressive and/or hostile, or the car raced across the screen so fast that you blinked and missed it.

### Remote
The remote features six buttons corresponding to six preset messages, as well as a central “confirm” or “send” button. It comes with an omni-directional swivel mount which allows users to adhere it to the dashboard or AC vent. It comes pre-paired with with BT840.

When one of the six buttons are pressed, a blue LED ring lights up next to the button to show the user which message has been activated. The user may then press the center button to send the message to the LED display. This 2-step process is designed mostly to prevent the user from accidentally sending the wrong message. Upon activation of the "send" button, the LED ring should sequentially light up blue until the entire ring is illuminated blue. The LEDs next to the activated button will turn to green and then fade away if the message sends successfully. However, they will turn red and fade away if an error was encountered.

### LED Display Board
Hardware installation of the LED display itself is fairly straightforward. Just mount it on your rear windshield by rotating the side panels 180° so that both suction cups face the same direction as the display. Simply place the suction cups against the inside of the rear windshield and lock the flaps on the opposite face of the panels. Then flip the switch on the rear of the enclosure to power on the device.

When the display board receives a message, it will display it for a maximum of 7 seconds so as not to distract the rear driver. However, the message will scroll faster for longer messages so that the rear driver gets to see the message twice before it disappears in case they missed it the first time.

# **Functionality**

### BT840
Using the BLEPeripheral, the BT840 is declared as a BLEPeripheral device named "peripheral" having BLEService named "service" with the UUID "19b11234e8f2537e4f6cd104768a1214" and a BLECharacteristic named "characteristic" with UUID "19b10000e8f2537e4f6cd104768a1214". Next, the advertisement UUID for peripheral is set to the UUID of service, the default value of characteristic is set to "BLE Character", and the device's local name is set to "BLE Device". Finally, we call Wire.begin() so that we can communicate with the MK20 via I2C.

In the loop() function a BLECentral named "other_device" is instantiated as a central to peripheral for each loop executed until a central is connected. While connected, LED_BUILTIN will light up and the BT840 will wait for the user to overwrite the value of characteristic. If overwritten, the string value of characteristic is converted into a char array and sent byte-by-byte to the MK20 via I2C over channel 9.

### MK20DX256VHL7
The script begins by setting all constants like the matrix height and width as well as instantiating an Adafruit_LIS3DH object named "lis". The Adafruit_LIS3DH library is for use with 3-axis accelerometers and present in this skit so that the text will scroll from right to left regardless of orientation. 

In the setup() function, a scrolling layer is added to the matrix so that the color, scroll speed, font size, etc. of the text can be customized. Constant settings are then set for matrix and scrollingLayer. Wire1 is instantiated on channel 9 to receive data from the BT840 (Wire1 because Wire is occupied by the accelerometer). Finally, the callback method receiveEvent is passed to Wire1.onReceive() to be executed any time the MK20 receives data from the BT840.

In loop() we simply call the setRotation() function which reads input from the accelerometer and sets the rotation accordingly, so that the text is right-side-up and scrolls from right to left.

# **Features**
The mobile app blocks any inflammatory statements from being sent to the board. It does so using an exhaustive library of aggressive and/or hostile terms stored locally on the app. This library includes everything from benign but negative adjectives like “dumb” and “stupid”, to curse words, to homophobic and racial slurs… The is NO reason drivers should need these words while trying to de-escalate aggressive situations. 

The app also features Google’s voice recognition software, allowing drivers to operate the device while keeping both hands on the wheel and their eyes on the road. Again, the voice functionality will flag any aggressive or inflammatory messages.

# **Required Software, Hardware, & Wiring**
### Arduino Libraries Required

* [NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
* [SmartMatrix3](https://github.com/pixelmatix/SmartMatrix)
* [Software Serial](https://github.com/PaulStoffregen/SoftwareSerial)
* [BLEPeripheral](https://github.com/sandeepmistry/arduino-BLEPeripheral)
* [Wire](https://github.com/esp8266/Arduino/tree/master/libraries/Wire)
* [Adafruit_LIS3DH](https://github.com/adafruit/Adafruit_LIS3DH)
* [Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor)

### Components Required
* [Teensy 3.2]( https://www.pjrc.com/store/teensy32.html)
* [nRF52832 Development Kit](https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52-DK)



* 2 x [64 x 32 LED Matrices](https://www.adafruit.com/product/2278)
* 2 x [TP4056 Charging Module](https://www.amazon.com/McIgIcM-Lithium-Charging-Protection-Functions/dp/B06XQRQR3Q/ref=sr_1_1_sspa?s=electronics&ie=UTF8&qid=1521743259&sr=1-1-spons&keywords=tp4056+charging+module&psc=1)
* [LM2596 XL6009](https://www.amazon.com/gp/product/B0129HYAW0/ref=oh_aui_search_detailpage?ie=UTF8&psc=1)
* 2 x [10uF Polarized Capacitor](https://www.amazon.com/uxcell-10uF-Radial-Electrolytic-Capacitor/dp/B00W8YAJ2A/ref=sr_1_3?s=electronics&ie=UTF8&qid=1521743487&sr=1-3&keywords=10uf+capacitor)
* [LiPo Battery - 4000mAh](https://www.amazon.com/Ofeely-4000mah-Polymer-Battery-Rechargeable/dp/B00U8GFKR4)
* [LiPo Battery - 500 mAh](https://www.amazon.com/ADAFRUIT-INDUSTRIES-1578-Lithium-Polymer/dp/B00L0W61VO/ref=sr_1_5?ie=UTF8&qid=1521839930&sr=8-5&keywords=battery+500mah)
* [16-Pin Ribbon Cable](https://www.amazon.com/Pc-Accessories-Connectors-2-Pack-Silver/dp/B01J4NN9LK/ref=sr_1_11?s=electronics&ie=UTF8&qid=1522098852&sr=1-11&keywords=16+pin+ribbon+cable)
* [12 LED NeoPixel Ring](https://www.amazon.com/Pc-Accessories-Connectors-2-Pack-Silver/dp/B01J4NN9LK/ref=sr_1_11?s=electronics&ie=UTF8&qid=1522098852&sr=1-11&keywords=16+pin+ribbon+cable)
* 7 x [Buttons](https://www.amazon.com/OCR-Tactile-Button-Momentary-Assortment/dp/B01MRP025V/ref=sr_1_1?ie=UTF8&qid=1521743850&sr=8-1&keywords=electronic+buttons)


# **Remote/Transmitter:**

![Remote Breadboard DGM](https://github.com/BigOleHealz/Wireless-Serial-Communication-between-Microcontrollers/blob/master/Transmitter/PCB/Images/Breadboard%20Diagram.JPG?raw=true)


![Remote Schematic DGM](https://github.com/BigOleHealz/Wireless-Serial-Communication-between-Microcontrollers/blob/master/Transmitter/PCB/Images/Schematic.JPG)


![Remote PCB DGM](https://github.com/BigOleHealz/Wireless-Serial-Communication-between-Microcontrollers/blob/master/Transmitter/PCB/Images/PCB%20CAD.JPG?raw=true)


# **Receiver:**

![Receiver Schematic DGM](https://github.com/BigOleHealz/Wireless-Serial-Communication-between-Microcontrollers/blob/master/Receiver/PCB/Images/Schematic.JPG?raw=true)


![Receiver PCB DGM](https://github.com/BigOleHealz/Wireless-Serial-Communication-between-Microcontrollers/blob/master/Receiver/PCB/Images/ReceiverPCB.jpg)


![Receiver Prototype](https://github.com/BigOleHealz/Wireless-Serial-Communication-between-Microcontrollers/blob/master/Receiver/PCB/Images/PCB%20Prototype.jpg?raw=true)