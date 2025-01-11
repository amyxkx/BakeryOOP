#ifndef OOP_ENV_FIXES_H
#define OOP_ENV_FIXES_H

#ifdef __linux__
#include <X11/Xlib.h>
#endif

void init_threads() {
#ifdef __linux__
    XInitThreads();
#endif
}

#endif
