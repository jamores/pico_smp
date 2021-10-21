# pico_smp
FreeRTOS SMP on raspiberry pico

This is a minimal example to use FreeRTOS SMP with task affinity enabled.

Create TWO very simple tasks and run each on PICOs Cores:
- C0 : print message to console and blink an LED
- C1 : print message to console

note : use minicom to observe console messages
$ minicom -b 115200 -o -D /dev/ttyACM0

Both FreeRTOS and pico-sdk are linked as Git submodules
