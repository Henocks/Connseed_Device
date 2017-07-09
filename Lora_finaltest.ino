#include <BH1750.h>
#include <DHT.h>
#include <DHT_U.h>
#include "MQ135.h"
#include <LoRaShield.h>


#define RZERO 206.85

BH1750 lightMeter;
DHT dht1(2, DHT11);
LoRaShield LoRa(10, 11);
MQ135 Gas = MQ135(A1);

String message;

void setup()
{
  Serial.begin(115200);
  LoRa.begin(38400);
  lightMeter.begin();
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(2, INPUT);
}

void loop()
{
  while (LoRa.available())
  {
    String s = LoRa.ReadLine();
    Serial.println(s);
  }

  if (Serial.available()) {
    int data = Serial.read();

    if (data == '1' ) {
      LoRa.getDevEUI();
    }
    if ( data == '2') {
      int wtr = analogRead(A0);
      float ppm = Gas.getPPM();
      float tmp = dht1.readTemperature();
      float hum = dht1.readHumidity();
      uint16_t lux = lightMeter.readLightLevel();

      message = String(tmp)+"/"+String(hum)+"/"+String(lux)+"/"+String(wtr)+"/"+String(ppm);
      Serial.println(message);
      LoRa.sendMessage(message);  
    }
  }


  delay(10);
}

