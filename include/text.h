#ifndef TEXT_LIB_H
#define TEXT_LIB_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define MAX_TEXT_BUFFER_LENGTH 1024

const char* TextFormat(const char* text, ...);

#endif // TEXT_LIB_H