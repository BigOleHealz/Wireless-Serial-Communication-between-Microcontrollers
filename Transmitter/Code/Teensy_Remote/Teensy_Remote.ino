#include <SPI.h>
#include <stdio.h>
#include <RF24.h>
#include <Adafruit_NeoPixel.h>

//------------------ RF stuff ---------------------------

RF24 radio(0, 1);
byte addresses[][6] = {"1Node"};
unsigned long option = 0;
unsigned long scrool = 0;

//------------- Hardware Setup --------------------------
const int button1 = 18;
const int button2 = 17;
const int button3 = 14;
const int button4 = 15;
const int button5 = 23;
const int button6 = 19;
const int send_button = 2;
unsigned long msg = 0;

//------------------ NeoPixel Ring stuff ---------------------------

int num_pixels = 12;
int phase_shift = 4;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(num_pixels, 21, NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {}
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  pinMode(button6, INPUT_PULLUP);
  pinMode(send_button, INPUT_PULLUP);

    //--------------------------- RF Setup ---------------------------

  radio.begin();
  radio.setPayloadSize(8);
  radio.setChannel(0x4c);
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(addresses[0]);

  // Receiver :     radio.openReadingPipe(1,addresses[0]);

    //---------------------------- NeoPixel Ring stuff ---------------------------
  strip.begin();
  strip.setBrightness(100);
  strip.show();
  Serial.println("End of Startup. Starting Loop...");

  // Clear LED Ring
  blankStrip();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if ( digitalRead(button1) == LOW) {
    Serial.println("Button 1 Pressed");
    option = 1;
    selectLED(option);
  }
  if ( digitalRead(button2) == LOW) {
    Serial.println("Button 2 Pressed");
    option = 2;
    selectLED(option);
  }
  if ( digitalRead(button3) == LOW) {
    Serial.println("Button 3 Pressed");
    option = 3;
    selectLED(option);
  }
  if ( digitalRead(button4) == LOW) {
    Serial.println("Button 4 Pressed");
    option = 4;
    selectLED(option);
  }
  if ( digitalRead(button5) == LOW) {
    Serial.println("Button 5 Pressed");
    option = 5;
    selectLED(option);
  }
  if ( digitalRead(button6) == LOW) {
    Serial.println("Button 6 Pressed");
    option = 6;
    selectLED(option);
  }

// ------------------- On Send -----------------------
  if ( digitalRead(send_button) == LOW) {
    Serial.print("Send Button Pressed: ");
    Serial.println(option);
    
    sendLED(option);
    msg = option;

    //option = 0;

    if( radio.write(&option, sizeof(unsigned long))){
      confirmLED(option);
    } else {
      failLED(option);
    }
  }

  radio.write(&scrool, sizeof(unsigned long));
}



void blankStrip() {
  for (uint16_t i = 0; i < num_pixels; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}

// Select the 2 circles corresponding to the button

void selectLED(unsigned long option) {
  blankStrip();
  int start_light = (2 * option + phase_shift) % 12;
  strip.setPixelColor((start_light + 12 - 1) % 12, strip.Color(0, 0, 47));
  strip.setPixelColor(start_light, strip.Color(0, 0, 255));
  strip.setPixelColor(start_light + 1, strip.Color(0, 0, 47));
  strip.show();
}

// Fill circle with green to signify success

void confirmLED(unsigned long option) {
  blankStrip();
  int start_light = ((2 * option + phase_shift) % 12);
  strip.setPixelColor((start_light + 12 - 1) % 12, strip.Color(0, 47, 0));
  strip.setPixelColor(start_light, strip.Color(0, 255, 0));
  strip.setPixelColor(start_light + 1, strip.Color(0, 47, 0));
  strip.show();

  for (int i = 255; i > 0; i--) {
    strip.setPixelColor((start_light + 12 - 1) % 12, strip.Color(0, i, 0));
    strip.setPixelColor(start_light, strip.Color(0, i, 0));
    strip.setPixelColor(start_light + 1, strip.Color(0, i, 0));
    strip.show();
    delay(10);
  }
}

// Fill circle with red to signify failure

void failLED(unsigned long option) {
  blankStrip();
  int start_light = (2 * option + phase_shift) % 12;
  strip.setPixelColor((start_light + 12 - 1) % 12, strip.Color(47, 0, 0));
  strip.setPixelColor(start_light, strip.Color(255, 0, 0));
  strip.setPixelColor(start_light + 1, strip.Color(47, 0, 0));
  strip.show();

  for (int i = 255; i > 47; i--){
    strip.setPixelColor(start_light, strip.Color(i, 0, 0));
    strip.show();
    delay(10);
  }

  for (int i = 47; i > 0; i--) {
    strip.setPixelColor((start_light + 12 - 1) % 12, strip.Color(i, 0, 0));
    strip.setPixelColor(start_light, strip.Color(i, 0, 0));
    strip.setPixelColor(start_light + 1, strip.Color(i, 0, 0));
    strip.show();
    delay(10);
  }
}

// Fill circle with blue

void sendLED(unsigned long option) {
  int start_light = ((2 * option + phase_shift) % 12);

  for (int i = start_light; i < num_pixels + start_light; i++) {
    strip.setPixelColor(i % num_pixels, strip.Color(0, 0, 127));
    strip.show();
    delay(50);
    strip.setPixelColor(i % num_pixels, strip.Color(0, 0, 255));
    strip.show();
    delay(50);
  }

  // If message sent successfully...
  blankStrip();
  option = 50;
}




