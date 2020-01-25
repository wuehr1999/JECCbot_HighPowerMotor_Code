# JECCbot_HighPowerMotor_Software
This is the software implementation for the generationmake high power motor control board ( https://github.com/generationmake/HighPowerMotorFeatherWing ) to control the JECCbot mini  outdoor robot platform ( https://github.com/generationmake/JECCbot_mini ) with a ASCII based UART protocol. The base of the software stack is implemented in ANSI C so the portation to other mikrocontroller based platforms is possible without major problems.

## Protocol format

Every protocol message begins with ```:``` and ends with ```\n```. Between there is following a specific command and its optional parameters:

```:<command><parameter0><parameter1>...<parameter n>\n```

If the command was executed correctly, the board will answer with the same command and optional set or read parameters or an error code.

The default protocol baudrate is 115200.

### Commands

| Command | Meaning | Parameters | Response parameters | Format | Example |
| ------- | ------- | -------- | ----------------- | ------ | ------- |
| s       | set speeds | [-]speedLeft[-]speedRight | [-]speedLeft[-]speedRight | %03d, -100% to 100% | ```:s100-050\n``` |
| f       | motors pwm frequency | frequency | frequency | 0 Hz to 16000 Hz, %05d | ```:f08000\n``` |
| c       | bno 055 calibration | - | | calibration status | %03d, -100% to 100% | ```:s\n``` |


### Error Codes
the high power motor control board ( https://github.com/generationmake/HighPowerMotorFeatherWing )
Every error code startd with the command e and has a specific index ( %03d ) as parameter, e. g. ```:e001\n```.

| Index | Meaning |
| ----- | ------- |
| 000 | received data is no command |
| 001 | Command is not found |
| 002 | Syntax error in command |

## Supported Mikrocontrollers

| Mikrocontroller | Needed Libraries |
| --------------- | ---------------- |
| ATSAM21D/Adafruit Feather M0 ( https://www.adafruit.com/product/2772 ) | https://github.com/adafruit/Adafruit_ADS1X15 |
