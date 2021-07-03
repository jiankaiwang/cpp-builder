import os
import numpy as np
from ctypes import cdll, c_int, c_double, POINTER

def findSOLib():
  soPaths = ["mmth.so", \
             "bazel-bin/srcs/libmmth.so", \
             "../bazel-bin/srcs/libmmth.so"]
  for path in soPaths:
    if os.path.exists(path):
      print("Load the shared library at {}.".format(path))
      return path
  raise FileNotFoundError("Can't find the proper the shared library.")

def func():
  try:
    soFile = findSOLib()

    # load the shared library
    mmth = cdll.LoadLibrary(soFile)

    # define the data types of function `tanh_impl` in the shared library
    mmth.tanh_impl.argtypes = [c_double]

    # define the returning data typs of function `tanh_impl` in the shared library
    mmth.tanh_impl.restype = c_double

    # access the function
    print("Tanh(3): {}".format(mmth.tanh_impl(3)))
  except Exception as err:
    print("Error: {}".format(err))

def const():
  try:
    soFile = findSOLib()

    # load the shared library
    mmth = cdll.LoadLibrary(soFile)

    # access the global variable in C++
    value = c_double.in_dll(mmth, "e").value
    
    print("Const e: {}".format(value))
  except Exception as err:
    print("Error: {}".format(err))

def listOpt():
  try:
    soFile = findSOLib()

    # load the shared library
    mmth = cdll.LoadLibrary(soFile)

    # set the parameters for the function
    mmth.sort.argtypes = [POINTER(c_double), c_int]

    # set the return type for void function
    mmth.sort.restype = None

    # the array for sorting via shared library
    array = np.array([2.0, -1.3, 1.6, 8.0, 7.0, 10.0, 9.8, -2.3])
    print("Before sorting: {}".format(array))

    # get the pointer to the array
    arrayPtr = array.ctypes.data_as(POINTER(c_double))

    # pass to the shared library
    mmth.sort(arrayPtr, array.size)

    # get the result
    print("After sorting: {}".format(array))
  except Exception as err:
    print("Error: {}".format(err))  

if __name__ == "__main__":
  func()
  const()
  listOpt()