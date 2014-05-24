librowind
=========

Read data from the [RO Wind](http://www.busse-yachtshop.de/pdf/ROWind.pdf) wind sensor.

Installing
----------

```bash
$ git clone https://github.com/kragniz/librowind.git
$ cd librowind
$ make
$ sudo make install
```

Usage
-----

Run `rowind` with the name of the serial device the rowind is attached to as
the first argument.

```bash
$ rowind /dev/ttyUSB0
{"direction": 95.000000, "speed": 6.700000, "valid": true}
```
