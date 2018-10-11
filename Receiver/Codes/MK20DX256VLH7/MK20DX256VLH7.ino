#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined (_VARIANT_ARDUINO_ZERO_)
#include <SoftwareSerial.h>
#endif

/*------------------------------------------------------------
 *                          Imports
------------------------------------------------------------*/

#define BUFSIZE 128   // Size of the read buffer for incoming data

//-------------------------- LED Matrix Stuff -------------------------
#include <SmartMatrix3.h>

//--------------------------- Accelerometer Stuff ---------------------
#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

/*------------------------------------------------------------
*         Define Constants and Initialize Components
------------------------------------------------------------*/

//-------------------------- LED Matrix Stuff -------------------------
#define COLOR_DEPTH 24                  // known working: 24, 48 - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24
const uint8_t kMatrixWidth = 128;       // known working: 32, 64, 96, 128
const uint8_t kMatrixHeight = 32;       // known working: 16, 32, 48, 64
const uint8_t kRefreshDepth = 36;       // known working: 24, 36, 48
const uint8_t kDmaBufferRows = 4;       // known working: 2-4, use 2 to save memory, more to keep from dropping frames and automatically lowering refresh rate
const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN;   // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels
const uint8_t kMatrixOptions = (SMARTMATRIX_OPTIONS_NONE);      // see http://docs.pixelmatix.com/SmartMatrix for options
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);
const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);
const uint8_t kIndexedLayerOptions = (SM_INDEXED_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(scrollingLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);

// ------------------------ Acceleromter Stuff ------------------------
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup(void) {
  Serial.begin(9600);

  //-------------------------- LED Matrix Stuff  -------------------------------------
  matrix.addLayer(&scrollingLayer); 
  matrix.begin();
  matrix.setBrightness(255);

  scrollingLayer.setMode(wrapForward);
  scrollingLayer.setColor({0xff, 0xff, 0xff});
  scrollingLayer.setSpeed(30);
  scrollingLayer.setFont(gohufont14);
  scrollingLayer.setOffsetFromTop((kMatrixHeight/2) - 5);

  Wire1.begin(9);                // join i2c bus with address #9
  Wire1.onReceive(receiveEvent);

  // -------------------------- Accelerometer Stuff -----------------------------------
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }

  lis.setRange(LIS3DH_RANGE_4_G);
  Serial.println("Fuck");
}

void loop(void) {
  setRotation();
}

void setRotation() {

  lis.read();
  sensors_event_t event; 
  lis.getEvent(&event);

  if (event.acceleration.y >= 0) {
    matrix.setRotation(rotation0);
  } else {
    matrix.setRotation(rotation180);
  }
}

void receiveEvent(int howMany) {

  String msg = "";
  while(Wire1.available() > 1) {  // loop through all but the last
    char c = Wire1.read();        // receive byte as a character
    msg += c;
  }
  const char * message = msg.c_str();
  scrollingLayer.start(message, 2);
}

void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}
