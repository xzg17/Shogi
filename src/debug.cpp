#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "board.hpp"

typedef struct {
    
    PyObject_HEAD
    /* Type-specific fields go here. */
        Board *board;
} Py_Class_Board;

static int *Board_init(Py_Class_Board *self, PyObject *args);

static PyObject *my_debug(Py_Class_Board *self);


static PyMethodDef Py_Class_Board_methods[] = {
    {"debug", (PyCFunction)my_debug, METH_VARARGS, "(x_x)"},
    {NULL} /* Sentinel */
};


static PyTypeObject CustomType = {
    PyVarObject_HEAD_INIT(NULL, 0) "Shogi.Board", /* tp_name */
    sizeof(Py_Class_Board),                           /* tp_basicsize */
    0,                                              /* tp_itemsize */
    /* methods */
    0, /* tp_dealloc */
    0,                        /* tp_print */
    0,                        /* tp_getattr */
    0,                        /* tp_setattr */
    0,                        /* tp_reserved */
    0,                        /* tp_repr */
    0,                        /* tp_as_number */
    0,                        /* tp_as_sequence */
    0,                        /* tp_as_mapping */
    0,                        /* tp_hash */
    0,                        /* tp_call */
    0,                        /* tp_str */
    0,                        /* tp_getattro */
    0,                        /* tp_setattro */
    0,                        /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,       /* tp_flags */
    PyDoc_STR("Custom objects"),/* tp_doc */
    0,                        /* tp_traverse */
    0,                        /* tp_clear */
    0,                        /* tp_richcompare */
    0,                        /* tp_weaklistoffset */
    0,                        /* tp_iter */
    0,                        /* tp_iternext */
    Py_Class_Board_methods,     /* tp_methods */
    0,                        /* tp_members */
    0,                        /* tp_getset */
    0,                        /* tp_base */
    0,                        /* tp_dict */
    0,                        /* tp_descr_get */
    0,                        /* tp_descr_set */
    0,                        /* tp_dictoffset */
    (initproc)Board_init,     /* tp_init */
    0,                        /* tp_alloc */
    PyType_GenericNew,        /* tp_new */
};


static int Board_init(Py_Class_Board *self, PyObject *args){
    if(args != NULL){
        PyErr_SetString(PyExc_ValueError, "InitError1!");
        return -1;
    };
    self->board=new Board();
    return 0;
};


//一旦ここまで
static PyModuleDef custommodule = {
    PyModuleDef_HEAD_INIT,
    "Board",
    "Example module that creates an extension type.",
    -1,
    NULL
};

PyMODINIT_FUNC
PyInit_np_nd_DIDS(void){
    PyObject *m;
    
    m = PyModule_Create(&custommodule);
    if (m == NULL){
        return NULL;
    }
        
    if (PyType_Ready(&CustomType) < 0){
        return NULL;
    }

    Py_INCREF(&CustomType);
    PyModule_AddObject(m, "Board", (PyObject *) &CustomType);

    return m;
};
