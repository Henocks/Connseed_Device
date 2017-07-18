#include <BH1750.h>
#include <DHT.h>
#include <DHT_U.h>
#include "MQ135.h"
#include <LoRaShield.h>


#define RZERO 206.85

BH1750 lightMeter;
DHT dht1(2, DHT11);

MQ135 Gas = MQ135(A1);

LoRaShield LoRa(10, 11);

String message;
int wtr;
float ppm;
float tmp;
float hum;
uint16_t lux;

void setup()
{
  Serial.begin(115200);
  
  lightMeter.begin();
  pinMode(A0, INPUT);

  LoRa.begin(38400);
}

void loop()
{
  while (LoRa.available())
  {
    String s = LoRa.ReadLine();
    Serial.println(s);
  }
      wtr = analogRead(A0);
      ppm = Gas.getPPM();
      tmp = dht1.readTemperature();
      hum = dht1.readHumidity();
      lux = lightMeter.readLightLevel();

      message = String(tmp)+"/"+String(hum)+"/"+String(lux)+"/"+String(wtr)+"/"+String(ppm);
      Serial.println(message);
      delay(5000);

      //LoRa.sendMessage(message);
      LoRa.PrintTTV("01", tmp);
      LoRa.PrintTTV("02", hum);
      LoRa.PrintTTV("03", lux);
      LoRa.PrintTTV("04", wtr);
      LoRa.PrintTTV("05", ppm);
      LoRa.SendTTV();
}

