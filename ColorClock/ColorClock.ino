#include <avr/pgmspace.h>
//#include <Wire.h>
//#include <RTClib.h>


#include <G35.h>
#include <G35String.h>
#include <G35StringGroup.h>

#include <G35String.h>

// global clock variable
//RTC_DS1307 RTC;
//DateTime time_now;
//DateTime time_prev;

unsigned long int b1_time;
unsigned long int b2_time;
unsigned long int b3_time;
unsigned long int b4_time;

// Total # of lights on string (usually 50, 48, or 36). Maximum is 63, because
// the protocol uses 6-bit addressing and bulb #63 is reserved for broadcast
// messages.
#define LIGHT_COUNT (36)

// Arduino pin number. Pin 13 will blink the on-board LED.
#define G35_PIN (13)

G35String lights(G35_PIN, LIGHT_COUNT);

unsigned long thisMilli=0;
int second=0, minute=0, hour=0, prev_bulb = 0, next_bulb = 0; //start the time on 00:00:00
unsigned int target_intensity = 0;
unsigned int this_prev_intensity = 204, next_prev_intensity = 204;
int start = 0;
int endt = 0;
int loopFreq = 0;
int delayInMicroseconds = 0;
float update_freq = 204.0;

float thisFactor = 0.0;
unsigned long lastTick = millis();
void setup() {
  Serial.begin(9600);
  
  lights.enumerate();
  lights.fill_color(0, LIGHT_COUNT, G35::MAX_INTENSITY, COLOR_BLACK);
  
  start = micros();
  lights.fill_color(second, 1, (unsigned char)204, COLOR_RED);  
  int endt = micros();
  delayInMicroseconds = ((1000000/204) - (endt - start) * 2);
  
  //lights.do_test_patterns();
//  RTC.begin();
}

void loop() {

  thisMilli = millis();
  
  if (thisMilli - lastTick >= 1000) {
   lastTick = thisMilli;
   // turn off the current bulb.
//   lights.fill_color(second-1, 1, G35::MAX_INTENSITY, COLOR_BLACK);

   //update seconds, next bulb becomes this bulb.
   second ++;
  }
  
  thisFactor = (thisMilli - lastTick) / (1000.0 / update_freq);
//  Serial.print(second);
//  Serial.print("\t");
//  Serial.print(thisFactor);
//  Serial.print("\t");
//  Serial.println(update_freq - thisFactor);
  // current bulb
//  target_intensity = floor((204.0 * abs(1.0 - thisFactor) + 0.5);
//  lights.fill_color(second, 1, (unsigned char)thisFactor, COLOR_RED);
//  lights.fill_color(second-1, 1, (unsigned char)(update_freq - thisFactor), COLOR_RED);
//  moveIntensity(3,this_prev_intensity, thisFactor, COLOR_RED);
//  moveIntensity(second+1,this_prev_intensity, thisFactor, COLOR_RED);
//  moveIntensity(3, this_prev_intensity, target_intensity, COLOR_RED);
//  this_prev_intensity = target_intensity;
/*
  // next bulb  
  target_intensity = floor(204.0 * thisFactor);
  moveIntensity(second + 1, next_prev_intensity, target_intensity, COLOR_RED);
  next_prev_intensity = target_intensity;  
  */
//  Serial.print(thisMilli);
//  Serial.print("\t");
//  Serial.print(lastTick);
//  Serial.print("\t");
//  Serial.println(thisFactor);

//  Serial.print(start);
//  Serial.print("\t");
//  Serial.println(endt);
    
    
  for (int i = 1; i <= 204; i++) {
//    start = millis();
    lights.fill_color(second-1, 1, (unsigned char)204 - i, COLOR_RED);  
    lights.fill_color(second, 1, (unsigned char)i, COLOR_RED);  
//    endt = millis();
    delayMicroseconds(  delayInMicroseconds );
  }


  
  // move forward one minute every 60 seconds
  
  if (second >= 60) {
    minute++;
    second = 0; // reset seconds to zero
  }

  // move forward one hour every 60 minutes
  if (minute >=60) {
    hour++;
    minute = 0; // reset minutes to zero
  }
  
  if (hour >=24) {
    hour=0;
    minute = 0; // reset minutes to zero
  }    
  //delay(5);
}

void moveIntensity(int bulb, int previous_intensity, int target_intensity, unsigned color) {
//  Serial.print(bulb);
//  Serial.print("\t");
//  Serial.print(previous_intensity);
//  Serial.print("\t");
//  Serial.print(target_intensity);
//  Serial.print("\n");
  lights.fill_color(bulb, 1, (unsigned char)target_intensity, color);
/*
  int movement = ( target_intensity - previous_intensity );
  
  if ( movement == 0) {
    return;
  }
  else if ( abs(movement) == 1) {
    lights.fill_color(bulb, 1, (unsigned char)target_intensity, color);
  }
  else if ( movement < 0) {
    
    lights.fill_color(bulb, 1, (unsigned char)(previous_intensity - 1), color);
    moveIntensity(bulb, previous_intensity - 1, target_intensity, color);
  }
  else if ( movement > 0) {
    lights.fill_color(bulb, 1, (unsigned char)(previous_intensity + 1), color);
    moveIntensity(bulb, previous_intensity + 1, target_intensity, color);
  }
  */
}

