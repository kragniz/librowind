import ctypes
from ctypes.util import find_library

librowind = ctypes.cdll.LoadLibrary('/usr/local/lib/librowind.so')
librowind.get_rowind_fd.argtypes = [ctypes.c_char_p]
librowind.get_rowind_fd.restype = ctypes.c_int

class Wind(ctypes.Structure):
    _fields_ = [("direction", ctypes.c_double),
                ("speed", ctypes.c_double),
                ("valid", ctypes.c_int)]

def get_file_descriptor(rowind_path):
    return librowind.get_rowind_fd(rowind_path)

class Rowind(object):
    def __init__(self, serial_port_name):
        self.port = serial_port_name
        self.fd = get_file_descriptor(self.port)
        self.wind = Wind()
        self.wind_ptr = ctypes.pointer(self.wind)

if __name__ == '__main__':
    print get_file_descriptor('/dev/ttyUSB0')
    r = Rowind('/dev/ttyUSB0')
