# JECCbot_HighPowerMotor_Software
This is the software implementation for the generationmake high power motor control board ( https://github.com/generationmake/HighPowerMotorFeatherWing ) to control the JECCbot mini  outdoor robot platform ( https://github.com/generationmake/JECCbot_mini ) with a ASCII based serial protocol. The base of the api software stack is implemented in ANSI C so the portation to other mikrocontroller based platforms is possible without major problems.

## API

The api is based on a state machine. The state and its specific input parameters can be manipulated with the virtual api register bank.

### Registers

| Address | Type | Function       |
| ------- | ---- | -------------- |
| 0x0000  | rw   | api state      |
| 0x0001  | r    | api version    |
| 0x0011  | rw   | speed left     |
| 0x0012  | r    | emergency stop |
| 0x0021  | rw   | speed right    |
| 0x0031  | r    | bno heading    |
| 0x0041  | rw   | avg speed      |
| 0x0042  | rw   | dest heading   |

### Description of implemented states

#### State 0 - Joydrive

The direction and speed of the motors can be manipulated with the registers ```speed left``` and ```speed right```. The value ranges are from -100% to 100%.

#### State 1 - Drive along compass heading

The robot can drive along a heading from -180° to 180° saved in the ```dest heading``` register with an average speed from 0% to 100% saved in ```avg speed```.

### Protocol format

The protocol is leaned on ASCII-Modbus and is register based. 

Every protocol instruction message begins with ```:```, which is followed with ```02``` for reading access or ```04``` for writing access. Then there is a 16 bit hex register address and then 16 bit hex register value ( interpreted as signed int ). Every message ends with ```\n```: ```:<02 / 04><hex address><hex value>\n```

The mikrocontroller answers with ```:```, the register, value and ```\n```;

#### Example

Set robot state to 1:
Instruction: ```:04000000001\n``` -> Response ```:00000001\n```.


#### Error Codes

Every error code starts with the command e and has a specific index ( %03d ) as parameter, e. g. ```:e001\n```.

| Index | Meaning |
| ----- | ------- |
| 000 | received data is no command |
| 001 | Command is not found |
| 002 | Syntax error in command |


## Supported Mikrocontrollers

| Mikrocontroller | Needed Libraries |
| --------------- | ---------------- |
| ATSAM21D/Adafruit Feather M0 ( https://www.adafruit.com/product/2772 ) | https://github.com/adafruit/Adafruit_ADS1X15 |
