# **Introduction**

>The purpose of this project is to wire two Teensy 3.2 boards to communicate with one another wirelessly, with one Teensy acting as a receiver ready to scroll text across an LED screen while the other Teensy acts as a remote telling the receiver what text to display. To accomplish this, both boards were outfitted with nRF24l01 transceiver modules to communicate via RF.

>In addition to the dedicated remote, an Android app allows the LED display to be controlled via Bluetooth LE. This requires the receiver Teensy to be equipped with a BLE UART module in addition to the RF transceiver.

# **Usage**

### Mobile App
The app itself is rather intuitive. No pairing is necessary as the phone pairs automatically to the nearest Bluefruit device upon opening the app. A message can be sent to the display board by simply clicking either button at each of the four corners of the screen. Obviously, the message sent will be the same as the text on the button. The text on the button can be manually changed by long-pressing on the button itself, which clears the text from the button and brings up the keyboard. 

In addition, voice functionality is available in the app by clicking the center button. If the message sends successfully, the car at the top of the display will scroll across the screen from right to left. If the car does not scroll across the screen, it is due to 1 of 3 reasons: either the mobile device is not properly paired to the display, the text input was determined to be aggressive and/or hostile, or the car raced across the screen so fast that you blinked and missed it.

### Remote
The remote features six buttons corresponding to six preset messages, as well as a central “confirm” or “send” button. It comes with an omni-directional swivel mount which allows users to adhere it to the dashboard or AC vent. 

When one of the six buttons are pressed, a blue LED ring lights up next to it to show the user which message has been activated. The user may then press the center button to send the message to the LED display. This 2-step process is designed mostly to prevent the user from accidentally sending the wrong message. Upon activation of the center button, the LED ring should sequentially light up blue until the entire ring is illuminated blue. The LEDs next to the activated button will turn to green and then fade away if the message sends successfully or turn to red and fade away if an error was encountered.

### LED Display Board
>The LED display itself is fairly straightforward. Just mount it on your rear windshield by rotating the side panels 180° so that both suction cups face the same direction as the display. Simply place the suction cups against the inside of the rear windshield and lock the flaps on the opposite face of the panels. Then flip the switch on the rear of the enclosure to power on the device.

>When the display board receives a message, it will display it for a maximum of 7 seconds so as not to distract the rear driver. However, the message will scroll faster for longer messages so that the rear driver gets to see the message twice before it disappears in case they missed it the first time.

# **Features**
>The mobile app blocks any inflammatory statements from being sent to the board. It does so using a library full of aggressive and/or hostile terms is stored locally within the app. This library includes everything from benign but negative adjectives like “dumb” and “stupid”, to curse words, to straight-up homophobic and racial slurs… Drivers shouldn’t need these words while trying to de-escalate aggressive situations. 

>The app also features Google’s voice recognition software, allowing drivers to operate the device while keeping both hands on the wheel and their eyes on the road. Again, the voice functionality will not let you send any aggressive or inflammatory messages.


# **Software, Hardware Components, & Wiring**
### Arduino Libraries Required

* [NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
* [SmartMatrix](https://github.com/pixelmatix/SmartMatrix)
* [Software Serial](https://github.com/PaulStoffregen/SoftwareSerial)
* [SPI](https://github.com/PaulStoffregen/SPI)

### Components Required
* 2 x [Teensy 3.2]( https://www.pjrc.com/store/teensy32.html)
* 2 x [nRF24L01](https://www.amazon.com/Makerfire-Arduino-NRF24L01-Wireless-Transceiver/dp/B00O9O868G/ref=sr_1_2_sspa?ie=UTF8&qid=1521742726&sr=8-2-spons&keywords=nRF24L01&psc=1)
* [BLE UART Friend](https://www.amazon.com/Adafruit-Bluefruit-UART-Friend-Bluetooth/dp/B010M8UZPY/ref=sr_1_1_sspa?s=electronics&ie=UTF8&qid=1521743078&sr=1-1-spons&keywords=blue+uart+friend&psc=1)
* 2 x [64 x 32 LED Matrices](https://www.adafruit.com/product/2278)
* 2 x [TP4056 Charging Module](https://www.amazon.com/McIgIcM-Lithium-Charging-Protection-Functions/dp/B06XQRQR3Q/ref=sr_1_1_sspa?s=electronics&ie=UTF8&qid=1521743259&sr=1-1-spons&keywords=tp4056+charging+module&psc=1)
* [LM2596 XL6009](https://www.amazon.com/gp/product/B0129HYAW0/ref=oh_aui_search_detailpage?ie=UTF8&psc=1)
* 2 x [10uF Polarized Capacitor](https://www.amazon.com/uxcell-10uF-Radial-Electrolytic-Capacitor/dp/B00W8YAJ2A/ref=sr_1_3?s=electronics&ie=UTF8&qid=1521743487&sr=1-3&keywords=10uf+capacitor)
* [LiPo Battery - 4000mAh](https://www.amazon.com/Ofeely-4000mah-Polymer-Battery-Rechargeable/dp/B00U8GFKR4)
* [LiPo Battery - 500 mAh](https://www.amazon.com/ADAFRUIT-INDUSTRIES-1578-Lithium-Polymer/dp/B00L0W61VO/ref=sr_1_5?ie=UTF8&qid=1521839930&sr=8-5&keywords=battery+500mah)
* [16-Pin Ribbon Cable](https://www.amazon.com/Pc-Accessories-Connectors-2-Pack-Silver/dp/B01J4NN9LK/ref=sr_1_11?s=electronics&ie=UTF8&qid=1522098852&sr=1-11&keywords=16+pin+ribbon+cable)
* [12 LED NeoPixel Ring](https://www.amazon.com/Pc-Accessories-Connectors-2-Pack-Silver/dp/B01J4NN9LK/ref=sr_1_11?s=electronics&ie=UTF8&qid=1522098852&sr=1-11&keywords=16+pin+ribbon+cable)
* 7 x [Buttons](https://www.amazon.com/OCR-Tactile-Button-Momentary-Assortment/dp/B01MRP025V/ref=sr_1_1?ie=UTF8&qid=1521743850&sr=8-1&keywords=electronic+buttons)

#### **Remote/Transmitter:**
![Remote Breadboard DGM](https://github.com/BigOleHealz/Wireless-Serial-Communication-between-Microcontrollers/blob/master/Transmitter/PCB/Images/Breadboard%20Diagram.JPG?raw=true)

![Remote Schematic DGM](https://github.com/BigOleHealz/Wireless-Serial-Communication-between-Microcontrollers/blob/master/Transmitter/PCB/Images/Schematic.JPG?raw=true)

![Remote PCB DGM](https://github.com/BigOleHealz/Wireless-Serial-Communication-between-Microcontrollers/blob/master/Transmitter/PCB/Images/PCB%20CAD.JPG?raw=true)

#### **Receiver:**
![Receiver Breadboard DGM](https://github.com/BigOleHealz/Wireless-Serial-Communication-between-Microcontrollers/blob/master/Receiver/PCB/Images/Breadboard%20Diagram.JPG?raw=true)

![Receiver Schematic DGM](https://github.com/BigOleHealz/Wireless-Serial-Communication-between-Microcontrollers/blob/master/Receiver/PCB/Images/Schematic.JPG?raw=true)

![Receiver PCB DGM](https://github.com/BigOleHealz/Wireless-Serial-Communication-between-Microcontrollers/blob/master/Receiver/PCB/Images/PCB%20CAD.JPG?raw=true)

![Receiver Prototype](https://github.com/BigOleHealz/Wireless-Serial-Communication-between-Microcontrollers/blob/master/Receiver/PCB/Images/PCB%20Prototype.jpg?raw=true)
