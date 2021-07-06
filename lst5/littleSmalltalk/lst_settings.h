/*
 * lst_settings.h
 *
 * This module provides default values for several preprocessor
 * symbols that may affect the compilation procedure.
 * You can override these defaults by specifying the symbols
 * during compilation (for example: "-DLST_USE_GUI=0" etc.).
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

#ifndef LST_SETTINGS_H
#define LST_SETTINGS_H

/* Shall the VM provide GUI primitives? */
#ifndef LST_USE_GUI
#define LST_USE_GUI 1
#endif

/* Shall the VM provide SQLite primitives? */
#ifndef LST_USE_SQLITE
#define LST_USE_SQLITE 1
#endif

/* Shall the VM provide FFI primitives? */
#ifndef LST_USE_FFI
#define LST_USE_FFI 1
#endif

#if !defined(LST_USE_GUI) || LST_USE_GUI == 0
#define DefaultImageFile "./LittleSmalltalk_nogui.image"
#else
#define DefaultImageFile "./LittleSmalltalk.image"
#endif

/* The default static size is the size of the non garbage collected
 * memory area that gets populated with the objects in the initial image.
 * The size is specified not in bytes, but in units of sizeof(struct object)
 */
#define DefaultStaticSize  400000

/* The initial size of the dynamic memory spaces.
 * Two spaces of size DefaultDynamicSize * sizeof(struct object)
 * are created at startup and used by the garbage collector.
 * The size of these spaces may be changed by the garbage collector
 * when garbage collecting doesn't free enough memory for a new object
 * allocation.
 */
#define DefaultDynamicSize 400000


#define MAX_OBJECT_SIZE 100000
#define ROOTSTACKLIMIT 1024
#define STATICROOTLIMIT 4096


#endif


