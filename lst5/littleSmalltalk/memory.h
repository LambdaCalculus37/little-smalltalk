/* $Id: $
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

/*
 * memory management for the Little Smalltalk system
 * Uses a variation on the Baker two-space algorithm
*/


/*
 * The fundamental data type is the object.
 *
 * The first field in an object is a size, the low order two
 * bits being used to maintain:
 *
 * * binary flag, used if data is binary
 * * indirection flag, used if object has been relocated
 *
 * The next data field is the class
 * The following fields are either objects, or character values
 * 
 * 
 * The initial image is loaded into static memory space --
 * space which is never garbage collected
 * This improves speed, as these items are not moved during GC
 */


#ifndef MEMORY_H
#define MEMORY_H

#include "lst_settings.h"
#include "lst_os.h"
#include <stdio.h>

/* The version of the image file format */
#define LS_IMAGE_VERSION 2



struct object
{
  int size;
  struct object * class;
  struct object * data [0];
};


/*
 * byte objects are used to represent strings and symbols
 * bytes per word must be correct
 */

struct byteObject
{
	int size;
	struct object *class;
	unsigned char bytes[0];
};

#define bytePtr(x) (((struct byteObject *) x)->bytes)


/*
 * integer objects are used to represent short unsigned integers
 */

struct integerObject
{
  int size;
  struct object * class;
  unsigned int value;
};

#define integerValue(x) (((struct integerObject *) x)->value)


/*
 * memoryBase holds the pointer to the current space,
 * memoryPointer is the pointer into this space.
 * To allocate, decrement memoryPointer by the correct amount.
 * If the result is less than memoryBase, then garbage collection
 * must take place
 */

extern struct object *memoryPointer;
extern struct object *memoryBase;

/*
 * roots for the memory space
 * these are traced down during memory management
 * rootStack is the dynamic stack
 * staticRoots are values in static memory that point to
 * dynamic values
 */
extern struct object *rootStack[];
extern int rootTop;
void staticRootAdd(struct object **obj);

/*
 * The following are roots for the file out 
 */

extern struct object *nilObject;
extern struct object *smallInts[10];
extern struct object *trueObject;
extern struct object *falseObject;
extern struct object *SmallIntClass;
extern struct object *IntClass;
extern struct object *ArrayClass;
extern struct object *StringClass;
extern struct object *BlockClass;
extern struct object *ContextClass;
extern struct object *globalsObject;
extern struct object *initialMethod;
extern struct object *binaryMessages[3];

/*
 * entry points
*/

int fileIn(FILE *fp);
int fileOut(FILE *fp);

void gcinit(int staticSize, int dynamicSize);
struct object *gcollect(int size);
struct object *staticAllocate(int size);
struct object *staticIAllocate(int size);
struct object *gcialloc(int size);

int isDynamicMemory(struct object *obj);

/*
#define gcalloc(sz) \
	(((memoryPointer-=(sz+2))<memoryBase) \
	   ? gcollect(sz):(memoryPointer->size=sz*BytesPerWord,memoryPointer))
*/

#ifndef gcalloc
extern struct object * gcalloc(int);
#endif


#endif

