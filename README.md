librowind
=========

Read data from the [RO Wind](http://www.busse-yachtshop.de/pdf/ROWind.pdf) wind sensor.

Includes a C library along with a Python wrapper.


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

### With C

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

### With Python

Import the module:
```python
import rowind
```

Create an instance of a rowind object:
```python
wind = rowind.Rowind('/dev/ttyUSB0')
```
Read from the sensor:
```python
wind.update()
```

Use the values:
```python
print 'the wind is comming from', wind.direction
print 'with a speed of', wind.speed, 'knots'
```


### With demo client

Run `rowind` with the name of the serial device the rowind is attached to as
the first argument.

```bash
$ rowind /dev/ttyUSB0
{"direction": 95.000000, "speed": 6.700000, "valid": true}
```

License
-------

Librowind is free software: you can redistribute it and/or modify it under the
terms of the GNU Lesser General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option) any
later version.

See [COPYING](COPYING) for more information.
