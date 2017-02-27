/*
Vincent Rocheleau
17-03-2016
Class for the temperature sensors
 */
#include "TemperatureSensors.h"

TemperatureSensors::TemperatureSensors(int pinSensor): m_pinSensor(pinSensor)
{
}

void TemperatureSensors::init()
{
  mOneWire = OneWire(m_pinSensor);
  mSensors = DallasTemperature(&mOneWire);
  mSensors.begin();
  mSensors.setResolution(mAddressSensor1, SENSORS_RESOLUTION);
  mSensors.setResolution(mAddressSensor2, SENSORS_RESOLUTION);
}

//Returns a rocketPacket with the updated temperature values
RocketPacket TemperatureSensors::getTemperatures(RocketPacket rocketPacket)
{
  mSensors.requestTemperatures();

	rocketPacket.rocketData.temperature1 = mSensors.getTempC(mAddressSensor1);
  rocketPacket.rocketData.temperature2 = mSensors.getTempC(mAddressSensor2);

	return rocketPacket;
}
