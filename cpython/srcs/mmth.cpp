#include <cmath>

// step.1: include `Python.h`
#include <Python.h>

#include "mmth.hpp"

double sinh_impl(double x) {
    return (1 - pow(e, (-2 * x))) / (2 * pow(e, -x));
}

double cosh_impl(double x) {
    return (1 + pow(e, (-2 * x))) / (2 * pow(e, -x));
}

// double tanh_impl(double x) {
//     return sinh_impl(x) / cosh_impl(x);
// }

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