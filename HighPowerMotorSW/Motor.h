#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

typedef struct Motor
{
  byte pinPwm1, pinPwm2, pinInhibit;
  int pwmFrequency;
  int pwm1Dutycycle, pwm2Dutycycle;
  
  int interruptBaseFrequency, interruptCycles, interruptCyclecounter;
  
}Motor;

void motorInit(Motor *motor, byte pinPwm1, byte pinPwm2, byte pinInhibit, int pwmFrequency, int interruptBaseFrequency);

void motorChangePwmFrequency(Motor *motor, int pwmFrequency);
void motorEnable(Motor *motor, bool enableState);
void motorSetSpeed(Motor *motor, int speed);
void motorBreak(Motor *motor);

void motorUpdate(Motor *motor);

#endif
