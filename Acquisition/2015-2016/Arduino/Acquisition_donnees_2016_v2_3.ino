#include "rocketData.h"
#include "serialPort.h"
#include "transceiver.h"
#include "GPS.h"
#include "imu10Dof.h"
#include "acquisitionLogger.h"
#include "TemperatureSensors.h"


#define RFD_PORT_NB 3
#define RFD_BAUDRATE 57600

#define GPS1_PORT_NB 1
#define GPS1_BAUDRATE 9600
#define GPS1_ID 1

#define LOG_TIME_INTERVAL_SENDING  1000 // ms
#define GPS_LOG_ITERATIONS 10 // nb of period before GPS 

#define SD_CS_PIN 6
#define SYSTEM_TYPE "acq"

#define LED_PIN 13

#define TEMPERATURE_SENSORS_PIN 10

RocketPacket rocketPacket;
SerialPort rfdPort(RFD_PORT_NB, RFD_BAUDRATE);
Transceiver transceiver;
GPS gps1(GPS1_ID);
SerialPort gps1Port(GPS1_PORT_NB, GPS1_BAUDRATE);
Imu10Dof imu;
AcquisitionLogger sdLogger(SD_CS_PIN, SYSTEM_TYPE);
TemperatureSensors temperatureSensors(TEMPERATURE_SENSORS_PIN);

char gpsIterator = 0;

long actualTime = 0;
long lastTime = 0;

void setup() 
{ 
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  rfdPort.begin();
  delay(1000);
  gps1Port.begin();
  delay(1000);
  
  digitalWrite(12, 1);
  imu.init();
  digitalWrite(13, 1);

  delay(1000);
  temperatureSensors.init();
  delay(1000);
  sdLogger.initCard();
  sdLogger.writeHeader();
  digitalWrite(11, 1);
  digitalWrite(12, 0);
  digitalWrite(13, 0);
  delay(1000);
}

void loop() 
{
  actualTime = millis();
  if (actualTime - lastTime >= LOG_TIME_INTERVAL_SENDING)
  {
    digitalWrite(11, !digitalRead(11));
    rocketPacket.rocketData.timeStamp = actualTime/1000.0;
    transceiver.sendRocketPacket(rocketPacket, rfdPort);
    sdLogger.writeRocketData(rocketPacket);
    lastTime = actualTime;
    gpsIterator += 1;
    if (gpsIterator > GPS_LOG_ITERATIONS)
    {
      digitalWrite(12,!digitalRead(12));
      rocketPacket = gps1.getLocation(rocketPacket, gps1Port);
      rocketPacket = temperatureSensors.getTemperatures(rocketPacket);
    }
  }
  digitalWrite(13, !digitalRead(13));
  rocketPacket = imu.getPosition(rocketPacket);
  digitalWrite(11, !digitalRead(11));
  
}
