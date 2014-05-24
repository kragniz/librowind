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

Include librowind:
```C
#include "librowind.h"
```

Get a file descriptor of the RO Wind's serial port:
```C
int ro_fd = get_rowind_fd("/dev/ttyUSB0");
```

Read data from the sensor:
```C
Wind* wind = get_wind(ro_fd);
```

Use the data:
```C
wind->direction // the direction the wind is coming from, 0-359.9
wind->speed     // the speed of the wind in knots
wind->valid     // whether the data from the sensor is valid
```


Demo client usage
-----------

Run `rowind` with the name of the serial device the rowind is attached to as
the first argument.

```bash
$ rowind /dev/ttyUSB0
{"direction": 95.000000, "speed": 6.700000, "valid": true}
```
