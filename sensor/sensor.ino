// This #include statement was automatically added by the Particle IDE.

/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor
  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650
  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing products
  from Adafruit!
  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/


#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <google-maps-device-locator.h>
#include <Adafruit_Sensor.h>

#define BME_SCK D0
#define BME_MISO D1
#define BME_MOSI D2
#define BME_CS D3

#define SEALEVELPRESSURE_HPA (1013.25)

// GoogleMapsDeviceLocator locator;

char publishString[40];

//Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);

void setup() {
  Serial.begin(9600);
  Serial.println(F("BME280 test"));

  // if (!bme.begin(0x76)) {
if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
  }
// locator.withLocatePeriodic(30);
}

void loop() {
    int temp = bme.readTemperature();
    sprintf(publishString,"%u", temp);
    Spark.publish("Temperature", publishString);

    int press = bme.readPressure() / 100.0F;
    sprintf(publishString,"%u", press);
    Spark.publish("Pressure", publishString);

    int alt = (pow(SEALEVELPRESSURE_HPA/press,1/5.257)-1)*(temp + 273.15)/.0065;
    // Source : https://keisan.casio.com/exec/system/1224585971
    int hum = bme.readHumidity();
    sprintf(publishString,"%u", hum);
    Spark.publish("Humidity", publishString);

    /*locator.loop();
    sprintf(publishString,"%u", lat);
    Spark.publish("Latitude", publishString);

    sprintf(publishString,"%u", lon);
    Spark.publish("Longitude", publishString);


    sprintf(publishString,"%u", accuracy);
    Spark.publish("Accuracy", publishString);
    */

    delay(1000);
}
