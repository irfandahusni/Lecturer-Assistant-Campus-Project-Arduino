// Import Libraries :
#include <Wire.h>
#include <Adafruit_TCS34725.h> // RGB sensor library
#include <Servo.h> //Servo Motor Library

// Initialize Variables
Servo servo_var; //Servo Variable
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_1X); //RGB Sensor Variable (Including Sampling Time and Gain)

// Define the Parameter:
uint16_t r, g, b, c;

//Check if device is ready to use
void setup()
{
  servo_var.attach(10); //Servo Input Pin
  
  // Begin Serial communication:
  Serial.begin(9600);
  
  // Check if the sensor is wired correctly:
  if (tcs.begin()) 
  {
    Serial.println("Found sensor");
  }
  
  else {
    Serial.println("No TCS34725 found ... check your connections ");
    while (1);
  }
  
  Serial.println("Initialize Servo");
  servo_var.write (50 ); 
  delay(1000);
  servo_var.write (100 );
  delay(1000);
  servo_var.write (5); 
  delay(1000);
  Serial.println("Done");
}
void loop()
{
  // Get the raw sensor data for the red, green, blue:
  tcs.getRawData(&r, &g, &b, &c);
  
  // Print the data to the Serial Monitor:
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.println(" ");

  // Set Treshold
  int green_treshold= 300;
  int red_treshold = 400;
  int r2;

  //Mapping Treshold
  if (r>red_treshold and g<green_treshold) 
  {
    int r2 = 0;
  }
  if (r>red_treshold and g>green_treshold)
  {
    int r2 = 1;
  }
  
  // Program servo to open when treshold is fulfilled

  switch (r2)
  { 
    case 0:
     servo_var.write (120); // Opening Gate
     digitalWrite(2,HIGH);  // Green LED Lamp On
     delay(1000);
     digitalWrite(2,LOW);  //Green LED Lamp Off
     servo_var.write(5 );  // Closing Gate
     break;
      
    case 1:
     digitalWrite(3,HIGH); //RED LED Lamp On       
     delay(1000);
     digitalWrite(3,LOW); //RED LED Lamp Off
     break;
     
     }
     delay(1);
}
 
