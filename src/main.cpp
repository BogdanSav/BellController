#include <Arduino.h>
#define channelL A0
#define channelR A1
#define outPin 5
uint32_t curMillis, lastTick;
int processingTime = 15, count; //processingTime in seconds
int testValue = 80;
int sleepTime = 10; //in seconds
float soundValue(int precision = 10);

void setup()
{

  Serial.begin(9600);
  pinMode(channelR, INPUT);
  pinMode(channelL, INPUT);
  pinMode(outPin, OUTPUT);
}

void loop()
{
  Serial.println(soundValue());
  if (soundValue() >= 50)
  {
    curMillis = millis();
    Serial.println("CurMillis");
    Serial.println(curMillis);
    if (curMillis - lastTick >= (processingTime * 1000))
    {
      Serial.println("Count:");
      Serial.println(count);
      if (count >= 100)
      {
        digitalWrite(outPin, HIGH);
        delay(5000);
        digitalWrite(outPin, LOW);
        count = 0;
        Serial.println("Delay");
        delay(sleepTime * 1000);
        Serial.println("stop delay");
        
      }
      lastTick = millis();
      
    }
    else if (soundValue() > 70)
    {
      count++;
      // Serial.println(count);
    }
    else if (soundValue() < 50)
    {
      count = 0;
    }
  }
}

float soundValue(int precision)
{
  float valueL = 0;
  float valueR = 0;
  float result = 0;

  for (int i = 0; i < precision; i++)
  {
    valueL = analogRead(channelL);
    valueR = analogRead(channelR);
    result += valueL + valueR;
  }

  return result / precision;
}