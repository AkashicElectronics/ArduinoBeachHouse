//ARDUINO BEACHHOUSE SKETCH FOR JOSIAH
//Akashic Electronics, July 2020 -EL

//Bluetooth stuff
char val; 
unsigned long BTInterval = 3000; //show blueetooth message for 3 seconds
unsigned long previousMillisBT = 0;

//Button stuff
const int button = 7;
int buttonState = 0; 

//Servo stuff.  Note that PWMServo.h gets less interupts than Servo.h so thats my preferred library
#include <PWMServo.h>
PWMServo servo1; //attached in pin 9 in setup
PWMServo servo2; //attached to pin 10 in setup
unsigned long previousMillisServo = 0;
int pos = 0;  
unsigned long servoInterval = 15;
unsigned long currentMillis = 0;
//end servo stuff

//FastLED stuff
#include <FastLED.h>
FASTLED_USING_NAMESPACE
#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif
#define DATA_PIN    6
//#define CLK_PIN   4
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    64
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          96 //on a scale of 0-255
#define FRAMES_PER_SECOND  120
//endFastLED stuff


//LCD Screen stuff
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
char * phrases[] = {"Noodles", "Bells", "Accorns", "Flippers", "Rain dances", "Cherry cola", "Limbo sticks", "Beep-boop-bop"};

void setup() {

  currentMillis = millis();
  
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  lcd.print("what up josiah!"); // Print a message to the LCD.
  
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  LEDS.setBrightness(BRIGHTNESS);
  
  servo1.attach(9);
  servo2.attach(10);

  pinMode(button, INPUT_PULLUP); //IMPORTANT note that the button Pin must be defined as INPUT_PULLUP.  Arduino activates internal resistor.

  randomSeed(analogRead(A0)); //randomSeed is a command required to use the random function.  A0 will read some random value from the atmosphere.
  
  Serial.begin(9600); 
}
//End Setup


//Some FastLED stuff that must be declared BEFORE the loop function.  From the Demo100 code.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
//End FastLED stuff


// time is circular:
void loop() {
  currentMillis = millis();               
  
  buttonState = digitalRead(button);
  
  if (buttonState == HIGH){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("what up josiah!");
  lcd.setCursor(0, 1); // set the cursor to column 0, line 1
  lcd.print(millis() / 1000); // print the number of seconds since reset:
 
  gPatterns[gCurrentPatternNumber]();  //Call the current pattern function once, updating the 'leds' array
  FastLED.show();  //send the 'leds' array out to the actual LED strip
  FastLED.delay(1000/FRAMES_PER_SECOND); //send the 'leds' array out to the actual LED strip.  Dunno if this is a real "delay" or not.
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // update every 20 ms -- slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 10 ) { nextPattern(); } // update every 10ms -- change patterns periodically
  }

  if (buttonState == LOW) {
    //fadeToBlackBy(leds, NUM_LEDS, 40);
    //FastLED.show();
    digitalWrite(DATA_PIN, LOW);
    randoPhrase();
    servoSweep();
    
  }
  
  if( Serial.available() )       // if data is available to read
  {;}
    val = Serial.read();         // read it and store it in 'val'
    if( val == '1' )               // 

    {
   lcd.clear();   
   lcd.setCursor(0, 0);         
   //lcd.clear;
   lcd.print("Bluetoof is truf");                      
   Serial.println("Message Sent");
  previousMillisBT = millis();
  //delay for 3 secs:
   while ((millis() - previousMillisBT) < BTInterval) ;}

 
}
//End loop


//Servo Function:
void servoSweep() {
  for (pos = 0; pos <= 175; pos += 1) { 
    servo1.write(pos);   
    servo2.write(pos);           

    previousMillisServo = millis();

    // delay for the servoInterval
    while ((millis() - previousMillisServo) < servoInterval) ;
  }

  for (pos = 175; pos >= 0; pos -= 1) { 
    servo1.write(pos);              
    servo2.write(pos);
    
    previousMillisServo = millis();

    // delay for the servoInterval
    while ((millis() - previousMillisServo) < servoInterval) ;
  }
}

//Random phrase generator
void randoPhrase(){
   byte index = random(0, 8);  //get a number between 0 and 4 :D
   lcd.setCursor(0, 0);
   lcd.clear();
   lcd.print(phrases[index]); //use it as the index to the array of phrases
}

//---------------------------------------------------------------
//begin FastLED "Demo Reel 100" Code --- a bunch of functions for addressable LEDs
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}
void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}
void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}
void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}
void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}
void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}
void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}
void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
//END FastLED Demo Reel 100 Functions
//--------------------------------------------------------------------
