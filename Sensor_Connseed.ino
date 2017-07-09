#include <BH1750.h>
#include <DHT.h>
#include <DHT_U.h>
#include "MQ135.h"

 
#define RZERO 206.85    //  Define RZERO Calibration Value

String message;
int mf1 = 0;

BH1750 lightMeter;
MQ135 Gas = MQ135(A1);
DHT dht1(2, DHT11);
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lightMeter.begin();
  pinMode(A0, INPUT);
}
 
void loop() {
  int wtr = analogRead(A0);
  float ppm = Gas.getPPM();
  float tmp = dht1.readTemperature();
  float hum = dht1.readHumidity();
  uint16_t lux = lightMeter.readLightLevel();
  
  message = String(tmp)+"/"+String(hum)+"/"+String(lux)+"/"+String(wtr)+"/"+String(ppm);
  Serial.println(message);
  
  delay(2000);
}

