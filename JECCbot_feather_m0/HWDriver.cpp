#include "HWDriver.h"

Motor motorLeft, motorRight;

ResponseMessage initJECCbot()
{
  motorInit(&motorLeft, MOT1_1, MOT1_2, MOT1_EN, MOT_FREQ, 16000);
  motorInit(&motorRight, MOT2_1, MOT2_2, MOT2_EN, MOT_FREQ, 16000);

  motorEnable(&motorLeft, true);
  motorEnable(&motorRight, true);
  
  start1000Hz();
  start16000Hz();  

  ResponseMessage message;
  message.length = sprintf(message.message, ":init\n");
  message.error = false;

  return message;
}

ResponseMessage errorMessage(int error)
{
  ResponseMessage m;
  
  m.error = true;
  m.length = sprintf(m.message, ":e%03d\n", error);

  return m;
}

ResponseMessage processCommand(char *command)
{
  char *msg = new char[strlen(command)+1];
  strcpy(msg, command);
  
  ResponseMessage message;
  
  if(msg[0] == ':')
  {
    if(msg[1] == MSG_DRV_SPEED)
    {
      int left, right, messageLen;
      
      if(msg[2]=='-')
      {
        left = -(100*((int)msg[3]-48) + 10*((int)msg[4]-48) + 1*((int)msg[5]-48));
        if(msg[6]=='-')
        {
          right = -(100*((int)msg[7]-48) + 10*((int)msg[8]-48) + 1*((int)msg[9]-48));
          messageLen = 10;
        }
        else
        {
          right = (100*((int)msg[6]-48) + 10*((int)msg[7]-48) + 1*((int)msg[8]-48));
          messageLen = 9;      
        }
      }
      else
      {
        left = (100*((int)msg[2]-48) + 10*((int)msg[3]-48) + 1*((int)msg[4]-48));      
        if(msg[5]=='-')
        {
          right = -(100*((int)msg[6]-48) + 10*((int)msg[7]-48) + 1*((int)msg[8]-48));
          messageLen = 9;
        }
        else
        {
          right = (100*((int)msg[5]-48) + 10*((int)msg[6]-48) + 1*((int)msg[7]-48));      
          messageLen = 8;
        }
      }
   
      if(msg[messageLen] == '\n')
      {
        setMotors(left, right);
        if(left>0)
        {
          if(right>0)
          {
            message.length = sprintf(message.message, ":%s%03d%03d\n", MSG_DRV_SPEED, left, right);            
          }
          else
          {
            message.length = sprintf(message.message, ":%cs%03d-%03d\n", MSG_DRV_SPEED, left, -right);
          }
        }
        else
        {
          if(right>0)
          {
            message.length = sprintf(message.message, ":%s-%03d%03d\n", MSG_DRV_SPEED, -left, right);            
          }
          else
          {
            message.length = sprintf(message.message, ":-%s03d-%03d\n", MSG_DRV_SPEED, -left, -right);
          }
        }
        message.error = false;
      }
      else
      {
        message = errorMessage(MSG_ERROR_SYNTAX);
      }
 
    }
    else if(msg[1] == MSG_DRV_FREQ)
    {
      int freq = 10000*((int)msg[2]-48) + 1000*((int)msg[3]-48) + 100*((int)msg[4]-48) + 10*((int)msg[5]-48) + 1*((int)msg[6]-48);
      if(msg[7] == '\n')
      {
        changeMotorPwmFrequency(freq);
        
        message.length = sprintf(message.message, ":%f%05d\n", MSG_DRV_FREQ, freq);     
        message.error = false; 
      }
      else
      {
        message = errorMessage(MSG_ERROR_SYNTAX);
      }
    }
    else
    {
      message = errorMessage(MSG_ERROR_NOTFOUND);
    }
  }
  else
  {
    message = errorMessage(MSG_ERROR_NOCOMMAND);
  }

  return message;
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
