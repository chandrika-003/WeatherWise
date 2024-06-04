#define rainPin 16        //D0 
void setup() 
{
  pinMode(rainPin , INPUT);
}

void loop() 
{
  int rainVal= analogRead(rainPin);
  Serial.begin(9600);
  //Serial.println(rainVal);
  if(rainVal<=1024 && rainVal>=600)
  {
    Serial.println("Heavy rain");
  }
  if(rainVal<=600 && rainVal>=300)
  {
    Serial.println("Moderate rain");
  }
  if(rainVal<=300 && rainVal>=0)
  {
    Serial.println("No rain");
  }
  delay(1000);
}
