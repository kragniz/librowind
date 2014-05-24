import ctypes
from ctypes.util import find_library

librowind = ctypes.cdll.LoadLibrary('/usr/local/lib/librowind.so')
librowind.get_rowind_fd.argtypes = [ctypes.c_char_p]
librowind.get_rowind_fd.restype = ctypes.c_int

def get_file_descriptor(rowind_path):
    return librowind.get_rowind_fd(rowind_path)
