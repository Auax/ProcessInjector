from ctypes import *
import os

# Test dll function call
path = os.path.abspath("dll-inject.dll")
dll = cdll.LoadLibrary(path)
