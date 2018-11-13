# RPi-pigpiod-BH1750
## Reading a BH1750 sensor (luminosity) using Raspberry Pi with the pigpiod library (pigpio daemon)

#### How To Use:
+ In the RPi-pigpiod-BH1750 directory:
  + To compile and build, run:
    + make
  + To launch, run:
    + ./BH1750 [-f]
##  
#### Reading can be performed in two modes:
+ Normal mode (±1 lux) takes ~175 ms. Run by default.
+ Fast mode (±4 lux) takes ~50 ms. Run with -f parameter ("./BH1750 -f").
##
#### I2C address:
By default using the I2C address equal 0x23. If you want to use the address equal 0x5C, you can change the address in the six line of BH1750.h (before compiling).
##
#### For use must be installed and running the pigpiod library:
+ To install the pigpiod in Raspbian, run:
  + sudo apt-get install pigpio
  
+ To launch, run (this operation requires user root permissions):
  + sudo pigpiod
  
+ To automate running the daemon at boot, run:
  + sudo systemctl enable pigpiod
