#include "HWDriver.h"

Motor motorLeft, motorRight;
BNO055 bno055;

void HWInit()
{
  motorInit(&motorLeft, MOT1_1, MOT1_2, MOT1_EN, MOT_FREQ, 16000);
  motorInit(&motorRight, MOT2_1, MOT2_2, MOT2_EN, MOT_FREQ, 16000);

  motorEnable(&motorLeft, true);
  motorEnable(&motorRight, true);

  bno055Init(&bno055, BNO055_ADDRESS);

  start1000Hz();
  start16000Hz();
}

void changeMotorPwmFrequency(int pwmFrequency)
{
  motorChangePwmFrequency(&motorLeft, pwmFrequency);
  motorChangePwmFrequency(&motorRight, pwmFrequency);
}

void setMotors(int speedLeft, int speedRight)
{
  motorSetSpeed(&motorLeft, speedLeft);
  motorSetSpeed(&motorRight, speedRight);
}


void interrupt1000Hz()
{
  
}

void interrupt16000Hz()
{
  motorUpdate(&motorLeft);
  motorUpdate(&motorRight);
}

int getHeading()
{
  bno055Update(&bno055);
  
  return bno055.heading;  
}

int getCompassCal()
{
  bno055Update(&bno055);
  
  return bno055.calibStat;
}

void moveHeading(int heading, int speedMax)
{
  int error = heading - getHeading();

  if(error > 180)
  {
    error = error - 360;
  }
  else if(error < -180)
  {
    error = error + 360;
  }

  int deltaSpeed = (int)(error * P_BNO055);

  int left = speedMax + deltaSpeed;
  int right = speedMax - deltaSpeed;

  if(left < 0)
  {
   left = 0;
  }
  else if(left > speedMax)
  {
    left = speedMax;
  }

  if(right < 0)
  {
   right = 0;
  }
  else if(right > speedMax)
  {
   right = speedMax;
  }

  setMotors(left, right);
}
