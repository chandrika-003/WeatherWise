#include <ESP8266WiFi.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
#define rainPin A0

const char* ssid = "SANKARAM";
const char* password = "00000000";
const char* serverIP = "192.168.199.149";  // Change this to your computer's IP address
const int serverPort = 12345;

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
  
  // Read sensor data
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
