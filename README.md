MPU6050
=======

This project is an experiment.

Requirements
============

Install development tools
-------------------------

```bash
sudo apt-get install libi2c-dev i2c-tools wiringpi cmake
```

Build
=====

```bash
cd build
cmake ..
make
```

Run
===

To start the MPU6050 module run

```bash
sudo ./testpi -m
```

Or view the help screen

```bash
sudo ./testpi --help
```

Links
=====

* [I2C Installation & Konfiguration][1]
* [Interfacing RaspberryPi and MPU-6050][2]
* [MPU6050 Datasheet][3]
* [MPU6050 Register Map][4]

[1]: http://www.netzmafia.de/skripten/hardware/RasPi/RasPi_I2C.html
[2]: http://blog.bitify.co.uk/2013/11/interfacing-raspberry-pi-and-mpu-6050.html
[3]: https://dl.dropboxusercontent.com/u/3162461/mcudocs/MPU-6050_DataSheet_V3%204.pdf
[4]: https://dl.dropboxusercontent.com/u/3162461/mcudocs/RM-MPU-60xxA_rev_4.pdf
