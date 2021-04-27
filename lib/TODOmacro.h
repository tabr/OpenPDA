#ifndef TODO_MACRO_H
#define TODO_MACRO_H

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))
#define INFO(x) DO_PRAGMA(message ("INFO - " #x))

#endif