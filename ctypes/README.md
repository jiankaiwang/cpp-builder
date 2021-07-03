# Python/C API

## ctypes

Write the C++ body.

```cpp
#ifdef __cplusplus
extern "C"
#endif
const double e = 2.7182818284590452353602874713527;

#ifdef __cplusplus
extern "C"
#endif
double tanh_impl(double x);

#ifdef __cplusplus
extern "C"
#endif
void sort(double array[], const int size);
```

```cpp
double tanh_impl(double x) {
  return sinh_impl(x) / cosh_impl(x);
}

void sort(double array[], const int size) {
  std::sort(array, array + size);
}
```

Compile the shared library of C++ source code.

```sh
cd ./ctypes/srcs
g++ -shared -fPIC -o mmth.so mmth.cpp
```

Except the above compiling, you can also build the shared library via `bazel`.

```sh
cd ./ctypes
CC=g++ bazel build //srcs:mmth
```

After the bazel building, you can find the shared library at `bazel-bin/srcs/libmmth.so`.

Use `ctypes` library to access the shared library in Python.
The first example is to use the function defined in C++.

```python
# load the shared library
mmth = cdll.LoadLibrary("mmth.so")

# define the data types of function `tanh_impl` in the shared library
mmth.tanh_impl.argtypes = [c_double]

# define the returning data typs of function `tanh_impl` in the shared library
mmth.tanh_impl.restype = c_double

# access the function
print("Tanh(3): {}".format(mmth.tanh_impl(3)))
```

The second example is to access the global variable defined in C++.

```python
# load the shared library
mmth = cdll.LoadLibrary("mmth.so")

# access the global variable in C++
value = c_double.in_dll(mmth, "e").value
```

The third example is to pass the python list to C++ for sorting.

```python
# load the shared library
mmth = cdll.LoadLibrary("mmth.so")

# set the parameters for the function
mmth.sort.argtypes = [POINTER(c_double), c_int]

# set the return type for void function
mmth.sort.restype = None

# the array for sorting via shared library
array = np.array([2.0, -1.3, 1.6, 8.0, 7.0, 10.0, 9.8, -2.3])

# get the pointer to the array
arrayPtr = array.ctypes.data_as(POINTER(c_double))

# pass to the shared library
mmth.sort(arrayPtr, array.size)

print(array)
```
