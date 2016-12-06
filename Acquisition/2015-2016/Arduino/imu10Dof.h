#ifndef _imu10Dof_h
#define _imu10Dof_h

#include "Arduino.h"
#include "rocketData.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_L3GD20_U.h> //librairie gyroscope
#include <Adafruit_LSM303_U.h> //librairie accel et magneto
#include <Adafruit_BMP085_U.h> //librairie altim�tre


#define TERM_BAUD 115200

class Imu10Dof
{
    public:
        Imu10Dof();
        void init();
        RocketPacket getPosition(RocketPacket rocketPacket);

    private:
        Adafruit_L3GD20_Unified m_gyroscope;
        Adafruit_LSM303_Accel_Unified m_accelerometer;
        Adafruit_LSM303_Mag_Unified m_magnetometer;
        Adafruit_BMP085_Unified m_altimeter;
        sensors_event_t m_event;

        float m_initialPressure;
};

#endif 
