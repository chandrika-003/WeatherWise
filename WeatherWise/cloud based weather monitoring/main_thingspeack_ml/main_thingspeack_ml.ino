#include <ESP8266WiFi.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
#define rainPin A0

const char* ssid = "SANKARAM";
const char* password = "00000000";
const char* server = "api.thingspeak.com";
const String apiKey = "GY15RVMCD8WXU1EQ";
const char* serverIP = "192.168.199.149"; 
const int serverPort = 12345;

WiFiClient client;
WiFiClient clientWifi;

void setup() {
  Serial.begin(9600);
  pinMode(rainPin, INPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  int rainVal = analogRead(rainPin);
  String rainIntensity;
  
  // Determine rain intensity based on analog reading
  if (rainVal <= 1024 && rainVal >= 600) 
  {
    rainIntensity = "No rain";
  } 
  else if (rainVal <= 600 && rainVal >= 300) 
  {
    rainIntensity = "Moderate rain";
  } 
  else if (rainVal <= 300 && rainVal >= 0) 
  {
    rainIntensity = "Heavy rain";
  }
  
 Serial.println(rainIntensity);
  
 Serial.print("Temperature = ");
 Serial.print(bmp.readTemperature());
 Serial.println(" *C");
    
 Serial.print("Pressure = ");
 Serial.print(bmp.readPressure());
 Serial.println(" Pa");
 
 Serial.print("Altitude = ");
 Serial.print(bmp.readAltitude());
 Serial.println(" meters");

 Serial.print("Pressure at sealevel (calculated) = ");
 Serial.print(bmp.readSealevelPressure());
 Serial.println(" Pa");
    
 Serial.print("Real altitude = ");
 Serial.print(bmp.readAltitude(101500));
 Serial.println(" meters");
 
 
  // Prepare data to send to ThingSpeak
  String postData = "field1=" + String(rainVal) +
                    "&field2=" + String(bmp.readTemperature()) +
                    "&field3=" + String(bmp.readPressure()) +
                    "&field4=" + String(bmp.readAltitude())+
                    "&field5=" + String(bmp.readSealevelPressure())+
                    "&field6=" + String(bmp.readAltitude(101500));
  
  // Send data to ThingSpeak
  if (client.connect(server, 80)) {
    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(postData.length()));
    client.println("X-THINGSPEAKAPIKEY: " + apiKey);
    client.println();
    client.println(postData);
  } else {
    Serial.println("Failed to connect to ThingSpeak");
  }
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure();
  float altitude = bmp.readAltitude();
  float seaLevelPressure = bmp.readSealevelPressure();
  float realAltitude = bmp.readAltitude(101500);

  // Send sensor data to computer for prediction
  if (clientWifi.connect(serverIP, serverPort)) {
    String sensorData = String(temperature) + "," + String(pressure) + "," + String(altitude) + "," + String(seaLevelPressure) + "," + String(realAltitude) + "," + String(rainVal);
    clientWifi.println(sensorData);
  } else {
    Serial.println("Failed to connect to server");
  }


  delay(20000); // Send data every 20 seconds
}
