/*************************************************************************************************************************************************
 *  TITLE: Building A Air Quality Sensor Kit Using The SGP30 And Piksey Pico
 *  DESCRIPTION: This sketch obtains the eCO2 and TVOC readings from the SGP30 sensor and displays them to the serial port and OLED module.
 *
 *  By Frenoy Osburn
 *  YouTube Video: https://youtu.be/olL8ij2993E
 *  BnBe Post: https://www.bitsnblobs.com/air-quality-sensor-kit
 *************************************************************************************************************************************************/
 
#include "SparkFun_SGP30_Arduino_Library.h" 
#include <Wire.h>
#include <U8x8lib.h>

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ A3, /* data=*/ A2, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display

SGP30 mySensor; //create an object of the SGP30 class

void setup() 
{
  Serial.begin(9600);
  Wire.begin();  
  u8x8.begin();
  
  u8x8.setFont(u8x8_font_8x13B_1x2_f);
  u8x8.setCursor(0,0);
  u8x8.print("Air Quality");
   
  //Initialize sensor
  if (mySensor.begin() == false) 
  {
    Serial.println("No SGP30 Detected. Check connections.");
    while (1);
  }
  
  //Initializes sensor for air quality readings
  //measureAirQuality should be called in one second increments after a call to initAirQuality
  mySensor.initAirQuality();
}

void loop() 
{
  //First fifteen readings will be
  //CO2: 400 ppm  TVOC: 0 ppb
  delay(1000); //Wait 1 second
  
  //measure CO2 and TVOC levels
  mySensor.measureAirQuality();
  Serial.print("CO2: ");
  Serial.print(mySensor.CO2);
  Serial.print(" ppm\tTVOC: ");
  Serial.print(mySensor.TVOC);
  Serial.println(" ppb");

  char time_output[30];
  
  u8x8.setFont(u8x8_font_8x13B_1x2_f);
  u8x8.setCursor(0,3);
  sprintf(time_output, "CO2: %05d ppm", mySensor.CO2);
  u8x8.print(time_output);

  u8x8.setCursor(0,6);
  sprintf(time_output, "TVOC: %05d ppb", mySensor.TVOC);
  u8x8.print(time_output);
}
