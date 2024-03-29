#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "board.hpp"

typedef struct {
    
    PyObject_HEAD
    /* Type-specific fields go here. */
        Board *board;
} Py_Class_Board;

static int Board_init(Py_Class_Board *self, PyObject *args);

static PyObject *Board_ply(Py_Class_Board *self){
    return Py_BuildValue("i", self->board->ply());
};

static PyObject *is_end(Py_Class_Board *self){
    std::set<int*> c_moves = self->board->legal_moves();
    if(c_moves.size() == 0){
        return Py_BuildValue("i", 1);
    }else{
        return Py_BuildValue("i", 0);
    };
};

static PyMethodDef Py_Class_Board_methods[] = {
    {"ply", (PyCFunction)Board_ply, METH_VARARGS, "(^o^)v"},
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
    if(!PyArg_ParseTuple(args, "")){
        PyErr_BadArgument();
        //PyErr_SetString(PyExc_ValueError, "InitError1!");
        return -1;
    };
    self->board = new Board(); // Allocate memory for a new Board object

    return 0;
};


static PyModuleDef custommodule = {
    PyModuleDef_HEAD_INIT,
    "_board",
    "Example module that creates an extension type.",
    -1,
    NULL
};

PyMODINIT_FUNC
PyInit__board(void){
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
