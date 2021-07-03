# CPython

## Python/C API

The origin C++ source code implements the function.

```cpp
double tanh_impl(double x) {
    return sinh_impl(x) / cosh_impl(x);
}
```

The following is the transformation to implement the Python interpreter via C++ directly.

```cpp
/* step.1 Include the necessary library. */
include <Pathon.h>

/* step.2: Modify `tanh_impl` method to receive from and return to Python.
   In other words, they are `PyObject*`. */ 
PyObject* tanh_impl(PyObject*, PyObject* o) {
    double x = PyFloat_AsDouble(o);
    double tanh_x = sinh_impl(x) / cosh_impl(x);
    return PyFloat_FromDouble(tanh_x);
}

/* step.3 Define the structure for how to express C++ method to Python */
static PyMethodDef superfastcode_methods[] = {
    // The first property is the name exposed to Python, fast_tanh
    // The second is the C++ function with the implementation
    // METH_O means it takes a single PyObject argument
    { "fast_tanh", (PyCFunction)tanh_impl, METH_O, nullptr },

    // Terminate the array with an object containing nulls.
    { nullptr, nullptr, 0, nullptr }
};

/* step.4 Define another structure for how to import module in Python, 
   like `from ... import ...`*/
static PyModuleDef superfastcode_module = {
    PyModuleDef_HEAD_INIT,
    "superfastcode",                        // Module name to use with Python import statements
    "Provides some functions, but faster",  // Module description
    0,
    superfastcode_methods                   // Structure that defines the methods of the module
};

/* step.5 The way of loading modules in Python.
   Must name as `PyInit_<module-name>`.*/
PyMODINIT_FUNC PyInit_superfastcode() {
    return PyModule_Create(&superfastcode_module);
}
```

After transforming the function, creating a `setup.py` with `Extension` to create a module.

```cpp
from setuptools import setup, Extension

sfc_module = Extension('superfastcode', sources = ['mmth.cpp'])

setup(
    name='superfastcode',
    version='1.0',
    description='Python Package with superfastcode C++ extension',
    ext_modules=[sfc_module]
)
```

Now let's create a shared library (`*.so`) for Python.

```sh
# for example, superfastcode.cpython-37m-darwin.so
python3 setup.py build_ext --inplace
```

You can import the library and use like a normal one.

```python
import superfastcode
superfastcode.fast_tanh(3)
```
