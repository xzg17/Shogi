#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "board.hpp"

typedef struct {
    
    PyObject_HEAD
    /* Type-specific fields go here. */
        Board *board;
} Py_Class_Board;

static int Board_init(Py_Class_Board *self, PyObject *args);

static PyObject *Board_ply(Py_Class_Board *self);
static PyObject *Board_legal_moves(Py_Class_Board *self);
static PyObject *Board_push(Py_Class_Board *self, PyObject *args);
static PyObject *Board_pop(Py_Class_Board *self);
static PyObject *Board_is_checked(Py_Class_Board *self);
static PyObject *Board_turn(Py_Class_Board *self);
static PyObject *Board_history(Py_Class_Board *self);
static PyObject *is_end(Py_Class_Board *self);

static PyObject *my_debug(Py_Class_Board *self);


static PyMethodDef Py_Class_Board_methods[] = {
    {"ply", (PyCFunction)Board_ply, METH_VARARGS, "(^o^)v"},
    {"legal_moves", (PyCFunction)Board_legal_moves, METH_VARARGS, "(ToT)"},
    {"push", (PyCFunction)Board_push, METH_VARARGS, "(^o^)v"},
    {"pop", (PyCFunction)Board_pop, METH_VARARGS, "(ToT)/\(^o^)v"},
    {"is_checked", (PyCFunction)Board_is_checked, METH_VARARGS, "{O_O}"},
    {"turn", (PyCFunction)Board_turn, METH_VARARGS, "\(-A-)/"},
    {"history", (PyCFunction)Board_history, METH_VARARGS, "v(^o^)"},
    {"is_end", (PyCFunction)is_end, METH_VARARGS, "v(^o^)"},
    //{"debug", (PyCFunction)my_debug, METH_VARARGS, "(x_x)"},
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


static PyObject *Board_ply(Py_Class_Board *self){
    return Py_BuildValue("i", self->board->ply());
};


static PyObject *Board_legal_moves(Py_Class_Board *self){
    std::set<int*> moves = self->board->legal_moves();
    int m = moves.size();
    PyObject *py_moves = PySet_New(NULL);
    for(auto move:moves){
        PyObject *py_move = Py_BuildValue("(iii)", move[0], move[1], move[2]);
        PySet_Add(py_moves, py_move);
    };
    return py_moves;
};

static PyObject *Board_get(Py_Class_Board *self, PyObject *args){
    int i;
    if(!PyArg_ParseTuple(args, "i", i)){
        PyErr_SetString(PyExc_TypeError, "Board.get() takes exactly one argument");
        return NULL;
    };
    return Py_BuildValue("i", -1);
};

static PyObject *Board_push(Py_Class_Board *self, PyObject *args){
    PyObject *move;
    if(!PyArg_ParseTuple(args, "O", &move)){
        PyErr_SetString(PyExc_TypeError, "Board.push() takes exactly one argument");
        return NULL;
    };
    if(PyList_Check(move)){
        if(PyList_Size(move) != 3){
            PyErr_SetString(PyExc_TypeError, "Invalid arguments");
            return NULL;
        };
        int c_move[3]={
            (int)PyLong_AsLong(PyList_GetItem(move, 0)),
            (int)PyLong_AsLong(PyList_GetItem(move, 1)),
            (int)PyLong_AsLong(PyList_GetItem(move, 2))
        };
        self->board->push(c_move);
    }else if(PyTuple_Check(move)){
        if(PyTuple_Size(move)!=3){
            PyErr_SetString(PyExc_TypeError, "InitError_list2!");
            return NULL;
        }
        int c_move[3]={
            (int)PyLong_AsLong(PyTuple_GetItem(move, 0)),
            (int)PyLong_AsLong(PyTuple_GetItem(move, 1)),
            (int)PyLong_AsLong(PyTuple_GetItem(move, 2))
        };
        self->board->push(c_move);
    };
    Py_INCREF(Py_None);
    return Py_None;
};

static PyObject *Board_pop(Py_Class_Board *self){
    int *c_move = self->board->pop();
    return Py_BuildValue("(iii)", c_move[0], c_move[1], c_move[2]);
};

static PyObject *Board_is_checked(Py_Class_Board *self){
    if(self->board->turn == 1){
        return Py_BuildValue("i", self->board->is_check_bking());
    }else if(self->board->turn == -1){
        return Py_BuildValue("i", self->board->is_check_wking());
    }
    return Py_BuildValue("i", -1);
};

static PyObject *Board_turn(Py_Class_Board *self){
    return Py_BuildValue("i", self->board->turn);
};

static PyObject *Board_history(Py_Class_Board *self){
    std::stack<int*> c_history = self->board->history;
    int m = c_history.size();
    PyObject *py_history = PyList_New(m);
    for(int i=0;i<m;i++){
        int *c_move = c_history.top();
        c_history.pop();
        PyObject *move = Py_BuildValue("(iii)", c_move[0], c_move[1], c_move[2]);
        PyList_SET_ITEM(py_history, i, move);
    }
    return py_history;
};
static PyObject *is_end(Py_Class_Board *self){
    std::set<int*> c_moves = self->board->legal_moves();
    if(c_moves.size() == 0){
        return Py_BuildValue("i", 1);
    }else{
        return Py_BuildValue("i", 0);
    };
};
static PyObject *my_debug(Py_Class_Board *self){
    return Py_BuildValue("i", 0);
};

static int Board_init(Py_Class_Board *self, PyObject *args){
    self->board=new Board();
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
