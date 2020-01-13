# JECCbot_feather_m0
This is the software implementation for https://github.com/generationmake/HighPowerMotorFeatherWing to control the JECCbot mini  outdoor robot platform ( https://github.com/generationmake/JECCbot_mini ) with a ASCII based UART protocol. The base of the software stack is implemented in ANSI C so the portation to other mikrocontroller based platforms is possible without major problems.

## Protocol format

Every protocol message begins with ```:``` and ends with ```\n```. Between there is following a specific command and its optional parameters:

```:<command><parameter0><parameter1>...<parameter n>\n```

If the command was executed correctly, the board will answer with the same command and optional set or read parameters or an error code.

### Commands

| Command | Parameters | Response parameters | Format | Example |
| ------- | -------- | ----------------- | ------ | ------- |
| s       | [-]speedLeft[-]speedRight | [-]speedLeft[-]speedRight | %03d, -100% to 100% | ```:s100-050``` |
| f       | frequency | frequency | 0 Hz to 16000 Hz, %05d | ```:f08000``` |


### Error Codes

Every error code startd with the command e and has a specific index ( %03d ) as parameter, e. g. ```:e001\n```.

| Index | Meaning |
| ----- | ------- |
| 000 | UART data is no command |
| 001 | Command is not found |
| 002 | Syntax error in command |
