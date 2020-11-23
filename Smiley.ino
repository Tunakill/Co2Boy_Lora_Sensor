#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define MATRIXPIN 19

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      64

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, MATRIXPIN, NEO_GRB + NEO_KHZ800);

int delayval = 10; // delay for half a second

void setupSmiley() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void goodsmile() {
  //Mund
  pixels.setPixelColor(2, pixels.Color(0, 128, 0));
  pixels.setPixelColor(3, pixels.Color(0, 128, 0));
  pixels.setPixelColor(4, pixels.Color(0, 128, 0));
  pixels.setPixelColor(5, pixels.Color(0, 128, 0));
  pixels.setPixelColor(9, pixels.Color(0, 128, 0));
  pixels.setPixelColor(10, pixels.Color(0, 128, 0));
  pixels.setPixelColor(11, pixels.Color(0, 128, 0));
  pixels.setPixelColor(12, pixels.Color(0, 128, 0));
  pixels.setPixelColor(13, pixels.Color(0, 128, 0));
  pixels.setPixelColor(14, pixels.Color(0, 128, 0));
  pixels.setPixelColor(16, pixels.Color(0, 128, 0));
  pixels.setPixelColor(17, pixels.Color(0, 128, 0));
  pixels.setPixelColor(22, pixels.Color(0, 128, 0));
  pixels.setPixelColor(23, pixels.Color(0, 128, 0));
  pixels.setPixelColor(24, pixels.Color(0, 128, 0));
  pixels.setPixelColor(31, pixels.Color(0, 128, 0));

  //Augen
  pixels.setPixelColor(57, pixels.Color(0, 128, 0));
  pixels.setPixelColor(62, pixels.Color(0, 128, 0));
  pixels.setBrightness(10);
  pixels.show();
}

void badsmile() {
  //Mund
  pixels.setPixelColor(0, pixels.Color(128, 0, 0));
  pixels.setPixelColor(7, pixels.Color(128, 0, 0));
  pixels.setPixelColor(8, pixels.Color(128, 0, 0));
  pixels.setPixelColor(9, pixels.Color(128, 0, 0));
  pixels.setPixelColor(14, pixels.Color(128, 0, 0));
  pixels.setPixelColor(15, pixels.Color(128, 0, 0));
  pixels.setPixelColor(17, pixels.Color(128, 0, 0));
  pixels.setPixelColor(18, pixels.Color(128, 0, 0));
  pixels.setPixelColor(19, pixels.Color(128, 0, 0));
  pixels.setPixelColor(20, pixels.Color(128, 0, 0));
  pixels.setPixelColor(21, pixels.Color(128, 0, 0));
  pixels.setPixelColor(22, pixels.Color(128, 0, 0));
  pixels.setPixelColor(26, pixels.Color(128, 0, 0));
  pixels.setPixelColor(27, pixels.Color(128, 0, 0));
  pixels.setPixelColor(28, pixels.Color(128, 0, 0));
  pixels.setPixelColor(29, pixels.Color(128, 0, 0));

  //Augen
  pixels.setPixelColor(57, pixels.Color(128, 0, 0));
  pixels.setPixelColor(62, pixels.Color(128, 0, 0));
  pixels.setBrightness(25);
  pixels.show();
}
