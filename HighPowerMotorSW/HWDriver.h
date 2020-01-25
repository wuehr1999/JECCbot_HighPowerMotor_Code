#ifndef HW_DRIVER_H
#define HW_DRIVER_H

#include <Arduino.h>

#include "Timers.h"
#include "Motor.h"
#include "BNO055.h"

#define MOT1_1 10
#define MOT1_2 9
#define MOT1_EN 11
#define MOT2_1 6
#define MOT2_2 5
#define MOT2_EN 12
#define MOT_FREQ 3000

#define BNO055_ADDRESS 0x28

extern Motor motorLeft, motorRight;
extern BNO055 bno055;

void HWInit();

void changeMotorPwmFrequency(int pwmFrequency);

void setMotors(int speedLeft, int speedRight);

#endif
