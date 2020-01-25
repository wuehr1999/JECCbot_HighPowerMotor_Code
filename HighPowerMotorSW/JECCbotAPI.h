#ifndef JECCBOT_API_H
#define JECCBOT_API_H

#include "HWDriver.h"

#define MSG_ERROR_NOCOMMAND 000
#define MSG_ERROR_NOTFOUND 001
#define MSG_ERROR_SYNTAX 002

#define MSG_INIT ":init"

#define MSG_DRV_SPEED 's'
#define MSG_DRV_FREQ 'f'
#define MSG_BNO055_HEADING 'h'
#define MSG_BNO055_CAL 'c'

typedef struct ResponseMessage
{
char message[40];
int length;
bool error;
} ResponseMessage;

ResponseMessage initJECCbot();

ResponseMessage processCommand(char *command);

#endif
