MPU6050
=======

This project is an experiment.

Requirements
============

Install development tools
-------------------------

```bash
sudo apt-get install i2c-dev i2c-tools wiringpi cmake
```

Install library for Broadcom BCM 2835
-------------------------------------

```bash
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.50.tar.gz
tar -xzvf bcm2835-1.50.tar.gz && cd bcm2835-1.50
./configure
make
sudo make isntall
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

Run with sudo from build folder!!

```bash
sudo ./testpi
```

Links
=====

[I2C Installation & Konfiguration][1]

[1]: http://www.netzmafia.de/skripten/hardware/RasPi/RasPi_I2C.html
