#include "imu10Dof.h"

Imu10Dof::Imu10Dof()
{

}

void Imu10Dof::init()
{
   Adafruit_L3GD20_Unified m_gyroscope(20);
   Adafruit_LSM303_Accel_Unified m_accelerometer(54321);
   Adafruit_LSM303_Mag_Unified m_magnetometer(12345);
   Adafruit_BMP085_Unified m_altimeter(10085);
  
  m_altimeter.begin();
  m_altimeter.getEvent(&m_event);
  m_initialPressure = m_event.pressure;
  delay(500);
  m_magnetometer.enableAutoRange(true);
  m_magnetometer.begin();

  delay(500);
  m_accelerometer.begin();
  m_accelerometer.setAccelFullScale(16);

  delay(500);
  m_gyroscope.begin();
  digitalWrite(11, 1);
  m_gyroscope.enableAutoRange(true);
  delay(500);

}


/*
Returns a RocketPacket at the time the function was called
*/
RocketPacket Imu10Dof::getPosition(RocketPacket rocket_packet)
{
    //Update m_gyro
    m_gyroscope.getEvent(&m_event);
    rocket_packet.rocketData.angSpeedX = m_event.gyro.x;
    rocket_packet.rocketData.angSpeedY = m_event.gyro.y;
    rocket_packet.rocketData.angSpeedZ = m_event.gyro.z;

    //Update m_accel
    m_accelerometer.getEvent(&m_event);
    rocket_packet.rocketData.accelX = m_event.acceleration.x;
    rocket_packet.rocketData.accelY = m_event.acceleration.y;
    rocket_packet.rocketData.accelZ = m_event.acceleration.z;

    //Update m_mag
    m_magnetometer.getEvent(&m_event);
    rocket_packet.rocketData.magnetX = m_event.magnetic.x;
    rocket_packet.rocketData.magnetY = m_event.magnetic.y;
    rocket_packet.rocketData.magnetZ = m_event.magnetic.z;

    //Update m_altitude
    m_altimeter.getEvent(&m_event);
    rocket_packet.rocketData.altitude = m_altimeter.pressureToAltitude(m_initialPressure, m_event.pressure);


    //return updated rocket_packet
    return rocket_packet;
}
