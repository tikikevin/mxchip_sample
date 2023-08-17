#include <Arduino.h>
#include <AZ3166SPI.h>
#include <AZ3166WiFi.h>
#include <HTS221Sensor.h>
#include <IoT_DevKit_HW.h>
#include <AzureIotHub.h>

DevI2C *i2c;
HTS221Sensor *sensor;
float humidity = 0;
float temperature = 0;
unsigned char id;

void setup()
{
  // put your setup code here, to run once:
  Screen.print(0, "MXChip Demo");

  WiFi.begin();
  if (WiFi.status() == WL_CONNECTED)
  {
    Screen.print(1, "Connected!");
  }
  else
  {
    Screen.print(1, "No WiFi!");
  }

  i2c = new DevI2C(D14, D15);
  sensor = new HTS221Sensor(*i2c);
  // init the sensor
  sensor->init(NULL);
}

void loop()
{
  // put your main code here, to run repeatedly:
  // enable
  sensor->enable();
  // read id
  sensor->readId(&id);
  Serial.printf("ID: %d\r\n", id);
  // get humidity
  sensor->getHumidity(&humidity);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  // get temperature
  sensor->getTemperature(&temperature);
  Serial.print("Temperature: ");
  Serial.println(temperature);
  // disable the sensor
  sensor->disable();
  // reset
  sensor->reset();
  delay(1000);
}
