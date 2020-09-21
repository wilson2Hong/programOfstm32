/*! @file telemetry_sample.cpp
 *  @version 3.3
 *  @date Jun 05 2017
 *
 *  @brief
 *  Telemetry API usage in a Linux environment.
 *  Shows example usage of the new data subscription API.
 *
 *  @Copyright (c) 2016-2017 DJI
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "TelemetrySample.h"
#include "math.h"
#include "esc_control.hpp"
#include "dji_telemetry.hpp"

extern Vehicle  vehicle;
extern Vehicle* v;

using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

//用户定义的变量
	float x;
	float y;
	float z;
	float  NSV; 
	uint16_t GPScounter;
	
extern int CHANNEL_1_PULSE_WIDE;//TIM2_CH1 PWM OUT
extern int CHANNEL_2_PULSE_WIDE;//TIM2_CH2 PWM OUT

bool
getBroadcastData()
{
  // Counters
  int elapsedTimeInMs = 0;
  int timeToPrintInMs = 2000;

  // We will listen to five broadcast data sets:
  // 1. Flight Status
  // 2. Global Position
  // 3. RC Channels
  // 4. Velocity
  // 5. Quaternion

  // Please make sure your drone is in simulation mode. You can
  // fly the drone with your RC to get different values.

  Telemetry::Status         status;
  Telemetry::GlobalPosition globalPosition;
  Telemetry::RC             rc;
  Telemetry::Vector3f       velocity;
  Telemetry::Quaternion     quaternion;
  Telemetry::VelocityInfo   velocityinfo;//gps工作状态
  Telemetry::GPSFused    		gpsfused;//gps信息
  Telemetry::GPSInfo   			gpsinfo;//gps信息
  Telemetry::Battery   			Battery;//电池信息

  const int TIMEOUT = 20;

  // Re-set Broadcast frequencies to their default values
  // ACK::ErrorCode ack = v->broadcast->setBroadcastFreqDefaults(TIMEOUT);

//  // Print in a loop for 2 seconds
//  while (elapsedTimeInMs < timeToPrintInMs)
//  {
    // Matrice 100 broadcasts only flight status
    status         = v->broadcast->getStatus();
    globalPosition = v->broadcast->getGlobalPosition();
    rc             = v->broadcast->getRC();
    velocity       = v->broadcast->getVelocity();
    quaternion     = v->broadcast->getQuaternion();
		
    gpsinfo   	 	 = v->broadcast->getGPSInfo();
    Battery     	 = v->broadcast->getBatteryInfo();
		
//    printf("Counter = %d:\n", elapsedTimeInMs);
//    printf("-------\n");

    printf("\n飞行状态 = %d   ", (unsigned)status.flight);
    printf("相对位置= %.3f, %.3f, %.3f, %d   ", globalPosition.latitude,
           globalPosition.longitude, globalPosition.altitude, globalPosition.health);
    printf("相对距离= %.3f ", sqrt(globalPosition.latitude*globalPosition.latitude+globalPosition.longitude*globalPosition.longitude));
    printf("遥控数据= %d, %d, %d, %d   ", rc.roll, rc.pitch, rc.yaw, rc.throttle);
    printf("加速度(vx,vy,vz)= %.3f, %.3f, %.3f   ", velocity.x, velocity.y, velocity.z);
		printf("四元数= %.3f, %.3f, %.3f, %.3f   \n", quaternion.q0, quaternion.q1, quaternion.q2, quaternion.q3);
		printf("经度 %.3d, 纬度 %d, 海拔 %d, 卫星数量 %d, 卫星计时 %d,  \r\n",  gpsinfo.latitude, gpsinfo.longitude, gpsinfo.HFSL,
					gpsinfo.detail.NSV, gpsinfo.detail.GPScounter);
		printf("电池 %.3d   \r\n",Battery.voltage);
		printf("电调 %d, %d\r\n",CHANNEL_1_PULSE_WIDE,CHANNEL_2_PULSE_WIDE);
		
//    printf("-------\n\n");

//    elapsedTimeInMs += 5;
//  }

//  printf("Done printing!\n");
  return true;
}

bool
subscribeToData()
{

  // Counters
  int elapsedTimeInMs = 0;
  int timeToPrintInMs = 4000;

  // We will subscribe to six kinds of data:
  // 1. Flight Status at 1 Hz
  // 2. Fused Lat/Lon at 10Hz
  // 3. Fused Altitude at 10Hz
  // 4. RC Channels at 50 Hz
  // 5. Velocity at 50 Hz
  // 6. Quaternion at 200 Hz

  // Package 0: Subscribe to flight status at freq 1 Hz
  int       pkgIndex        = 0;
  int       freq            = 1;
  TopicName topicList1Hz[]  = { TOPIC_STATUS_FLIGHT };
  int       numTopic        = sizeof(topicList1Hz) / sizeof(topicList1Hz[0]);
  bool      enableTimestamp = false;

  bool pkgStatus = v->subscribe->initPackageFromTopicList(
    pkgIndex, numTopic, topicList1Hz, enableTimestamp, freq);
  if (!(pkgStatus))
  {
    return pkgStatus;
  }

  v->subscribe->startPackage(pkgIndex);
  delay_nms(500);
  /*ack = waitForACK();
  if(ACK::getError(ack))
  {
    ACK::getErrorCodeMessage(ack, func);

    // Cleanup
    v->subscribe->removePackage(pkgIndex);
    ack = waitForACK();
    if(ACK::getError(ack))
    {
      ACK::getErrorCodeMessage(ack, func);
    }

    return false;
  }*/

  // Package 1: Subscribe to Lat/Lon, and Alt at freq 10 Hz
  pkgIndex                  = 1;
  freq                      = 10;
  TopicName topicList10Hz[] = { TOPIC_GPS_FUSED };
  numTopic                  = sizeof(topicList10Hz) / sizeof(topicList10Hz[0]);
  enableTimestamp           = false;

  pkgStatus = v->subscribe->initPackageFromTopicList(
    pkgIndex, numTopic, topicList10Hz, enableTimestamp, freq);
  if (!(pkgStatus))
  {
    return pkgStatus;
  }

  v->subscribe->startPackage(pkgIndex);
  delay_nms(500);
  /*ack = waitForACK();
  if(ACK::getError(ack))
  {
    ACK::getErrorCodeMessage(ack, func);

    // Cleanup
    v->subscribe->removePackage(pkgIndex);
    ack = waitForACK();
    if(ACK::getError(ack))
    {
      ACK::getErrorCodeMessage(ack, func);
    }

    return false;
  }*/

  // Package 2: Subscribe to RC Channel and Velocity at freq 50 Hz
  pkgIndex                  = 2;
  freq                      = 50;
  TopicName topicList50Hz[] = { TOPIC_RC, TOPIC_VELOCITY };
  numTopic                  = sizeof(topicList50Hz) / sizeof(topicList50Hz[0]);
  enableTimestamp           = false;

  pkgStatus = v->subscribe->initPackageFromTopicList(
    pkgIndex, numTopic, topicList50Hz, enableTimestamp, freq);
  if (!(pkgStatus))
  {
    return pkgStatus;
  }

  v->subscribe->startPackage(pkgIndex);
  delay_nms(500);
  /*ack = waitForACK();
  if(ACK::getError(ack))
  {
    ACK::getErrorCodeMessage(ack, func);

    // Cleanup
    v->subscribe->removePackage(pkgIndex);
    ack = waitForACK();
    if(ACK::getError(ack))
    {
      ACK::getErrorCodeMessage(ack, func);
    }

    return false;
  }*/

  // Package 3: Subscribe to Quaternion at freq 200 Hz.
  pkgIndex                   = 3;
  freq                       = 200;
  TopicName topicList200Hz[] = { TOPIC_QUATERNION };
  numTopic        = sizeof(topicList200Hz) / sizeof(topicList200Hz[0]);
  enableTimestamp = false;

  pkgStatus = v->subscribe->initPackageFromTopicList(
    pkgIndex, numTopic, topicList200Hz, enableTimestamp, freq);
  if (!(pkgStatus))
  {
    return pkgStatus;
  }

  v->subscribe->startPackage(pkgIndex);
  delay_nms(500);
  /*ack = waitForACK();
  if(ACK::getError(ack))
  {
    ACK::getErrorCodeMessage(ack, func);

    // Cleanup
    v->subscribe->removePackage(pkgIndex);
    ack = waitForACK();
    if(ACK::getError(ack))
    {
      ACK::getErrorCodeMessage(ack, func);
    }

    return false;
  }*/

  // Wait for the data to start coming in.
  delay_nms(8000);

  // Get all the data once before the loop to initialize vars
  TypeMap<TOPIC_STATUS_FLIGHT>::type flightStatus;
  TypeMap<TOPIC_GPS_FUSED>::type     latLon;
  TypeMap<TOPIC_RC>::type            rc;
  TypeMap<TOPIC_VELOCITY>::type      velocity;
  TypeMap<TOPIC_QUATERNION>::type    quaternion;

  uint32_t PRINT_TIMEOUT = 4000; // milliseconds
  uint32_t RETRY_TICK    = 500;  // milliseconds
  uint32_t nextRetryTick = 0;    // millisesonds
  uint32_t timeoutTick;

  timeoutTick = v->protocolLayer->getDriver()->getTimeStamp() + PRINT_TIMEOUT;
  do
  {
    flightStatus = v->subscribe->getValue<TOPIC_STATUS_FLIGHT>();
    latLon       = v->subscribe->getValue<TOPIC_GPS_FUSED>();
    rc           = v->subscribe->getValue<TOPIC_RC>();
    velocity     = v->subscribe->getValue<TOPIC_VELOCITY>();
    quaternion   = v->subscribe->getValue<TOPIC_QUATERNION>();

    printf("Counter = %d:\n", elapsedTimeInMs);
    printf("-------\n");
    printf("Flight Status = %d\n", (int)flightStatus);
    printf("Position (LLA) = %.3f, %.3f, %.3f\n", latLon.latitude,
           latLon.longitude, latLon.altitude);
    printf("RC Commands (r/p/y/thr) = %d, %d, %d, %d\n", rc.roll, rc.pitch,
           rc.yaw, rc.throttle);
    printf("Velocity (vx,vy,vz) = %.3f, %.3f, %.3f\n", velocity.data.x,
           velocity.data.y, velocity.data.z);
    printf("Attitude Quaternion (w,x,y,z) = %.3f, %.3f, %.3f, %.3f\n",
           quaternion.q0, quaternion.q1, quaternion.q2, quaternion.q3);
    printf("-------\n\n");

    delay_nms(500);
    nextRetryTick = v->protocolLayer->getDriver()->getTimeStamp() + RETRY_TICK;
  } while (nextRetryTick < timeoutTick);

  printf("Done printing!\n");
  v->subscribe->removePackage(0);
  delay_nms(3000);
  v->subscribe->removePackage(1);
  delay_nms(3000);
  v->subscribe->removePackage(2);
  delay_nms(3000);
  v->subscribe->removePackage(3);
  delay_nms(3000);

  return true;
}