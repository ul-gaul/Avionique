#ifndef _TemperatureSensors_h
#define _TemperatureSensors_h

#include "Arduino.h"
#include "rocketData.h"
#include "DallasTemperature.h"
#include "OneWire.h"

//Addresses for the temperatures sensors
#define ADDRESS_TEMP1 { 0x28, 0xC1, 0x1E, 0x07, 0x07, 0x00, 0x00, 0x94 }
//#define ADDRESS_TEMP2 { 0x28, 0xDD, 0xF5, 0x06, 0x07, 0x00, 0x00, 0x97 }
#define ADDRESS_TEMP2 { 0x28, 0xE6, 0xF5, 0x06, 0x07, 0x00, 0x00, 0x82 }

#define SENSORS_RESOLUTION 10 // between 9 and 12 bits

class TemperatureSensors
{
    public:
		TemperatureSensors(int pinSensor);
    void init();
		RocketPacket getTemperatures(RocketPacket rocketPacket);
    DallasTemperature mSensors;
    const DeviceAddress mAddressSensor1 = ADDRESS_TEMP1;
    const DeviceAddress mAddressSensor2 = ADDRESS_TEMP2;

    private:
    int m_pinSensor;
    OneWire mOneWire = OneWire(0); //Initialized to zero because OneWire 
                                   //doesn't have a default constructor

};

#endif
