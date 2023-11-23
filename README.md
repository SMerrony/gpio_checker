# gpio_checker
A simple diagnostic to check you haven't got your wires crossed when wiring up a Pico (or other RP2040 board).

I needed to be able to check that I had no solder bridges or dud connections on a PCB where I had a Pico project
in development.  This seems to do the trick.

## Successful run...
```
Welcome to gpio_checker
Starting test run
1. Testing all pull-downs...
2. Testing all pull-ups...
3. Pulling up each single pin and checking others remain low...
4. Pulling down each single pin and checking others remain high...

End of run, 0 error(s) detected
Starting test run
1. Testing all pull-downs...
2. Testing all pull-ups...
3. Pulling up each single pin and checking others remain low...
4. Pulling down each single pin and checking others remain high...

End of run, 0 error(s) detected
...
```
(Output is sent to the USB serial port.)

## Configuration and Build
Simply adjust `GPIOS_TO_TEST ` in  `config.h` to suit your needs.
By default, it tests all the exposed Pico GPIO pins.

Build via `cmake` in the usual manner.
```
cmake -S . -B build
cd build
make
```

