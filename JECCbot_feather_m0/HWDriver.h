#ifndef HW_DRIVER_H
#define HW_DRIVER_H

#include <Arduino.h>
#include "Timers.h"
#include "Motor.h"

#define MOT1_1 10
#define MOT1_2 9
#define MOT1_EN 11
#define MOT2_1 6
#define MOT2_2 5
#define MOT2_EN 12
#define MOT_FREQ 3000

#define MSG_ERROR_NOCOMMAND 000
#define MSG_ERROR_NOTFOUND 001
#define MSG_ERROR_SYNTAX 002
#define MSG_INIT ":init"
#define MSG_DRV_SPEED 's'
#define MSG_DRV_FREQ 'f'

extern Motor motorLeft, motorRight;

typedef struct ResponseMessage
{
char message[40];
int length;
bool error;
} ResponesMessage;

ResponseMessage initJECCbot();

ResponseMessage processCommand(char *command);

void changeMotorPwmFrequency(int pwmFrequency);

void setMotors(int speedLeft, int speedRight);

#endif
