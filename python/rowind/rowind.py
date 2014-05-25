import ctypes
from ctypes.util import find_library

class Wind(ctypes.Structure):
    _fields_ = [("direction", ctypes.c_double),
                ("speed", ctypes.c_double),
                ("valid", ctypes.c_int)]

librowind = ctypes.cdll.LoadLibrary('/usr/local/lib/librowind.so')

wind_pointer = ctypes.POINTER(Wind)

librowind.get_rowind_fd.argtypes = [ctypes.c_char_p]
librowind.get_rowind_fd.restype = ctypes.c_int
librowind.update_wind.argtypes = [ctypes.c_int, wind_pointer]


def get_file_descriptor(rowind_path):
    return librowind.get_rowind_fd(rowind_path)

class Rowind(object):
    def __init__(self, serial_port_name):
        self.port = serial_port_name
        self._fd = get_file_descriptor(self.port)
        self._wind = Wind()

        self.direction = -1
        self.speed = -1

    def update(self):
        '''Read from the sensor and update the direction and speed'''
        librowind.update_wind(self._fd, self._wind)

        if self._wind.valid == 1:
            self.direction = self._wind.direction
            self.speed = self._wind.speed

        return (self.direction, self.speed)

if __name__ == '__main__':
    r = Rowind('/dev/ttyUSB0')
    r.update()
