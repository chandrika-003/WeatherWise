
// bmp 108 sensor sda to d2 and scl d1

/*
 * #define BLYNK_TEMPLATE_ID "TMPL3i9rYcv95"
#define BLYNK_TEMPLATE_NAME "WEATHER IOT"
#define BLYNK_AUTH_TOKEN "328_suYKjXSV0bh7nGFSma4i4sapZa-C"
*/

#define rainPin 16        //D0 
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

#define BLYNK_TEMPLATE_ID           "TMPL3i9rYcv95"
#define BLYNK_TEMPLATE_NAME         "WEATHER IOT"
#define BLYNK_AUTH_TOKEN            "328_suYKjXSV0bh7nGFSma4i4sapZa-C"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include<BlynkSimpleEsp8266.h>

char auth[] =  BLYNK_AUTH_TOKEN; 
char ssid[] =    "SANKARAM";
char pass[] =    "00000000";

BlynkTimer timer;

void setup() 
{
  Serial.begin(9600);
  pinMode(rainPin , INPUT);
  Blynk.begin(auth,ssid,pass);
  if (!bmp.begin()) 
  {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) 
    {
    }
  }
}

void loop() 
{
  Blynk.run();
  int rainVal= analogRead(rainPin);
  //Serial.println(rainVal);
  if(rainVal<=1024 && rainVal>=600)
  {
    Serial.println("No rain");
  }
  if(rainVal<=600 && rainVal>=300)
  {
    Serial.println("Moderate rain");
  }
  if(rainVal<=300 && rainVal>=0)
  {
    Serial.println("Heavy rain");
  }
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Blynk.virtualWrite(V0,bmp.readTemperature());
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    
    Blynk.virtualWrite(V1,bmp.readPressure());

    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

    Blynk.virtualWrite(V2,bmp.readAltitude());

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");
    Blynk.virtualWrite(V3,bmp.readSealevelPressure());

 
    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(101500));
    Serial.println(" meters");
    Blynk.virtualWrite(V4,bmp.readAltitude(101500));
    
    Serial.println();
    delay(1500);
}
