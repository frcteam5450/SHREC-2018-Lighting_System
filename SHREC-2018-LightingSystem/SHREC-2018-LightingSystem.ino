#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

#define NUM_LEDS 60

int roboRio1 = 10;
int roboRio2 = 11;
int roboRio3 = 12;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setAll(int red , int green , int blue);
void multipleCylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int interim);
void catapultFire(byte red, byte green, byte blue, double pixelDelay, int beginLed, int endLed);
void showStrip();
void setPixel(int led, byte red, byte green, byte blue);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show();

  pinMode(roboRio1, INPUT);
  pinMode(roboRio2, INPUT);
  pinMode(roboRio3, INPUT);
}

int cLed = 0;
int cLed2 = NUM_LEDS - 1;

void loop() {
  
  if (digitalRead(10) == LOW && digitalRead(11) == LOW && digitalRead(12) == LOW) {
    setAll(0, 0, 255);
    showStrip();
  }
  
  if (digitalRead(10) == HIGH && digitalRead(11) == LOW && digitalRead(12) == LOW)
    multipleCylonBounce(0, 0, 255, 1, 50 , 10);

  if (digitalRead(10) == LOW && digitalRead(11) == HIGH && digitalRead(12) == LOW)
    multipleCylonBounce(0, 0, 255, 1, 20, 10);

  if (digitalRead(10) == HIGH && digitalRead(11) == HIGH && digitalRead(12) == HIGH) {
    catapultFire(255, 255, 0);
  }
}



void multipleCylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay , int interim){
int i = 0;
int i2 = NUM_LEDS;
for (int led = 0; led < interim; led++) {
  
  int check = i;
  int check2 = i2;
    setAll(0,5,0);
    setPixel(i, red/5, green/5, blue/5);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/5, green/5, blue/5);
    //showStrip();
    i = i + 10;

    
    setPixel(i, red/5, green/5, blue/5);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/5, green/5, blue/5);
    //showStrip();
    i = i + 10;

    
    setPixel(i, red/5, green/5, blue/5);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/5, green/5, blue/5);
    //showStrip();
    i = i + 10;

    
    setPixel(i2, red/5, green/5, blue/5);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i2+j, red, green, blue); 
    }
    setPixel(i2+EyeSize+1, red/5, green/5, blue/5);
    //showStrip();
    i2 = i2 - 10;

    
    setPixel(i2, red/5, green/5, blue/5);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i2+j, red, green, blue); 
    }
    setPixel(i2+EyeSize+1, red/5, green/5, blue/5);
    //showStrip();
    i2 = i2 - 10;


    setPixel(i2, red/5, green/5, blue/5);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i2+j, red, green, blue); 
    }
    setPixel(i2+EyeSize+1, red/5, green/5, blue/5);
    //showStrip();
    delay(SpeedDelay);
    showStrip();
    i = check + 1;
    i2 = check2 - 1;
  
}

}



void setAll(int red , int green , int blue) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i , strip.Color(red , green , blue));
  }
}



void showStrip() {
  strip.show();
}


void setPixel(int led, byte red, byte green, byte blue) {
  strip.setPixelColor(led , strip.Color(red , green , blue));
}



void catapultFire(byte red, byte green, byte blue) {
  if (cLed == 0)
    setAll(0 , 0 , 0);

  if (cLed < NUM_LEDS / 2) {
    setPixel(cLed , red , green , blue);
    setPixel(cLed2 , red , green , blue);
    delay(500 / 30);
    showStrip();
    cLed++;
    cLed2--;
  }
  else {
    cLed = 0;
    cLed2 = NUM_LEDS - 1;
  }
}

