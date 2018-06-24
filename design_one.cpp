#include <Adafruit_NeoPixel.h>
#define PIN 6 //for neopixels datapin
#define NUMPIXELS 4
const int vibPad = 9 ; // the number of the pad reading our vibration sensor
int vibState; //holds our vibState
bool triggered = false; //Is the pin triggered?
boolean dir = true;
int count = 0;
//setup our NeoPixel strand
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB +
                                             NEO_KHZ800);

void setup() {
        Serial.begin(9600);
        pinMode(vibPad, INPUT_PULLUP);
        pixels.begin(); // This initializes the NeoPixel library.
}
void loop() {
        //Read value of sensor
        vibState = digitalRead(vibPad); //set value of vibState to value read

        if (vibState == LOW) {
                triggered = true; //if reading received, triggered = true
        } else {
          //do nothing
        }
        if (triggered == true) {
                Serial.println("Triggered!!!"); //confirmation of trigger
                rainbowCycle(20);  //neopixel does its thing
                delay(50);         //let aftershock subside
                triggered = false; //reset
        } else {
                                 for (int i = 0; i < NUMPIXELS; i++) {
                         //tell pixels to set their color via the .Color() function
                         pixels.setPixelColor(i, pixels.Color(0, 15, 30));         // Orange-ish
                         pixels.show();         // This sends the updated pixel color to the strand
                }
        }
}

//void countdown(){
//        //a function that flashes all 4 neopixels then 3-2-1 before the rainbowCycle
//        //simulating a "blast off"
//}

void rainbowCycle(uint8_t wait) {
        uint16_t i, j;

        for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
                for(i=0; i< pixels.numPixels(); i++) {
                        pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
                }
                pixels.show();
                delay(wait);
        }
}

// The colours are a transition r - g - b - back to r.
//from strandtest example for rainbowCycle func
uint32_t Wheel(byte WheelPos) {
        WheelPos = 255 - WheelPos;
        if(WheelPos < 85) {
                return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
        }
        if(WheelPos < 170) {
                WheelPos -= 85;
                return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
        }
        WheelPos -= 170;
        return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
