/*
 * lst_os_IRIX64_6.5.h
 *
 * Provides SGI Irix dependent stuff.
 *
 * LittleSmalltalk system
 * Originally written by Timothy Budd.
 * Timothy Budd allowed me (Danny Reinhold) to replace
 * his original copyright notice and to push a
 * LittleSmalltalk project.
 *
 * The new LittleSmalltalk distribution is licensed
 * as follows:
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions: 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software. 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE. 
 *
 * Author of the original version: Timothy Budd
 * Maintainer after version 4: Danny Reinhold
 *
 * For more detailed information visit our web site:
 * http://www.littlesmalltalk.org
 */

#ifndef LST_OS_IRIX64_6_5_H
#define LST_OS_IRIX64_6_5_H


#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <stdio.h>

typedef int errno_t;
#define BytesPerWord sizeof(int)

#define sprintf_s snprintf
#define _strdup(X) strdup((X) ? (X) : "NULL POINTER!")
#define Sleep(X) usleep(1000L * (X))
#define strcpy_s(X,Y,Z) strncpy((X), (Z), (size_t)(Y))
#define strcat_s(X,Y,Z) strncat((X), (Z), (size_t)(Y))
#define _mktemp_s(X, S) { strncpy((X), "/tmp/lsteditXXXXXX", (size_t)S); mkstemp(X); }
#define _unlink unlink

#ifndef max
#define max(A,B) ((A)>(B) ? (A) : (B))
#endif

errno_t fopen_s(FILE **fp, const char *pathname, const char *mode);


#endif

