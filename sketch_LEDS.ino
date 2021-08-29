#include <IRremote.h>
#include <FastLED.h>

#define DATA_PIN    13
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    36
#define BRIGHTNESS          10
#define FRAMES_PER_SECOND  120


CRGB leds[NUM_LEDS]; //array of type CRGB with length # leds
int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

 
void setup() {
  // put your setup code here, to run once:
  delay(3000); // 3 second delay for recovery
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); // tell FastLED about the LED strip configuration
  FastLED.setBrightness(BRIGHTNESS); // set master brightness control
  irrecv.enableIRIn(); // Start the receiver
  Serial.begin(9600);  

  //Initial color (purple)
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = 0x800080;
    
    FastLED.setBrightness(10);
    FastLED.show();
  }
}

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
 
  
  if (irrecv.decode(&results)){ // have we received an IR signal?

      //Changing the color of the LEDS
      switch(results.value){
        case 0xFFA25D: //Power button is pressed - OFF
          FastLED.clear(); 
          FastLED.show();
          break;
          
        case 0XFF6897: //0 button is pressed - RED  
          for(int i=0; i<NUM_LEDS; i++){
            leds[i] = CRGB(255,0,0);
            FastLED.setBrightness(10);
            FastLED.show();
          }
          delay(1000);
          break;

        
        case 0xFF30CF: //1 button is pressed - BLUE
          for(int i=0; i<NUM_LEDS; i++){
            leds[i] = CRGB(0,0,255);
            FastLED.setBrightness(10);
            FastLED.show();
          }
          delay(1000);
          break;

        case 0xFF18E7: //2 button is pressed - PURPLE
          for(int i=0; i<NUM_LEDS; i++){
            leds[i] = CRGB(255,0,255);
            FastLED.setBrightness(10);
            FastLED.show();
          }
          delay(1000);
          break;

        case 0xFF7A85: //3 button is pressed - GREEN
          for(int i=0; i<NUM_LEDS; i++){
              leds[i] = CRGB(0,255,0);
              FastLED.setBrightness(10);
              FastLED.show();
            }
          delay(1000);
          break;

        case 0xFF10EF: //4 button is pressed - YELLOW
          for(int i=0; i<NUM_LEDS; i++){
              leds[i] = CRGB(255,255,0);
              FastLED.setBrightness(10);
              FastLED.show();
            }
          delay(1000);
          break;
          
        case 0xFF42BD: //7 - GRADIENT PATTERN 
          gradient(); 

        /*case 0xFF4AB5: //8 - START FROM THE MIDDLE 
          startFromMiddle();
          */
      }
        
      irrecv.resume(); // receive the next value
      
  }    
}

/*
void startFromMiddle(){
  int x = 1;
    while(x==1){
      for (int i=0; i<NUM_LEDS; i++) {
          leds[5+i] = CRGB(255, 0, 255);
          leds[5-i] = CRGB(255, 0, 255);
          FastLED.show();
          delay(500);
          FastLED.clear();
      } 
  }
}
*/

void gradient(){
  int x = 0;
  while(x==0){

    for (int i=0; i<30; i++) {
      FastLED.setBrightness(i);
      delay(20);
      FastLED.show();
    }
    
    delay(2000);
    
    for (int i=30; i>0; i--) {
      FastLED.setBrightness(i);
      delay(20);
      FastLED.show();
    }
    
    delay(2000);
    
    if (irrecv.decode(&results)){
    
      if(results.value==0xFF02FD){ //pause
        //x=1;
        break;
      }  

      irrecv.resume();
    }
    
    delay(1000);
       
 
  }
}




  
