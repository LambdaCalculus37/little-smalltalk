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


#include "lst_settings.h"
#include "lst_os.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef WIN32
#include <io.h>
#endif

#include "main.h"
#include "memory.h"
#include "interp.h"
#include "gui_primitives.h"
#include "sqlite_primitives.h"
#include "ffi_primitives.h"

/* # define COUNTTEMPS */

int debugging = 1;
int cacheHit = 0;
int cacheMiss = 0;
int gccount = 0;


struct object *nwInteger(unsigned int v)
{
  register struct integerObject * n;

  if (v < 10)
    return smallInts[v];
  if(v >= 1000)
    return nwInt(v);

  n = (struct integerObject *) gcialloc(BytesPerWord);
  n->class = SmallIntClass;
  n->value = v;
  return (struct object *) n;
}


struct object *staticInteger(int v)
{
  struct integerObject * n;

  n = (struct integerObject *) staticIAllocate(BytesPerWord);
  n->class = SmallIntClass;
  n->value = v;
  return (struct object *) n;
}


struct object *nwInt(unsigned int v)
{
  register struct integerObject * n;

  if (v < 10)
    return smallInts[v];
  n = (struct integerObject *) gcialloc(BytesPerWord);
  n->class = IntClass;
  n->value = v;
  return (struct object *) n;
}


struct object *staticInt(int v)
{
  struct integerObject * n;

  n = (struct integerObject *) staticIAllocate(BytesPerWord);
  n->class = IntClass;
  n->value = v;
  return (struct object *) n;
}


void backTrace(struct object *aContext)
{
  printf("back trace\n");
  while (aContext && (aContext != nilObject))
  {
    struct object * arguments; int i;
    printf("message %s ", bytePtr(aContext->data[methodInContext]->data[nameInMethod]));
    arguments = aContext->data[argumentsInContext];
    if(arguments && (arguments != nilObject))
    {
      printf("(");
      for(i = 0; i < (arguments->size >> 2); i++)
      {
        const char *name = bytePtr(arguments->data[i]->class->data[nameInClass]);
        printf("%s,", name ? name : "<unknown name!>");
      }
      printf(")");
    }
    printf("\n");
    aContext = aContext->data[previousContextInContext];
  }
}


#ifdef COUNTTEMPS
FILE * tempFile;
#endif

int main(int argc, char **argv)
{
  struct object * aProcess;
  struct object * aContext;
  int size, i;
  int staticSize, dynamicSize;
  FILE * fp;
#define MAX_IMAGE_PATHNAME_LENGTH 120
  char imageFileName[MAX_IMAGE_PATHNAME_LENGTH];
  errno_t fileError;

  guiInit();
  sqliteInit();
  ffiInit();

  strcpy_s(imageFileName, MAX_IMAGE_PATHNAME_LENGTH, DefaultImageFile);
  staticSize = DefaultStaticSize;
  dynamicSize = DefaultDynamicSize;

  /* first parse arguments */
  for(i = 1; i < argc; i++)
  {
    if(strcmp(argv[i], "-v") == 0)
      printf("Little Smalltalk, version 5.00\n");
    else if(strcmp(argv[i], "-s") == 0)
      staticSize = atoi(argv[++i]);
    else if(strcmp(argv[i], "-d") == 0)
      dynamicSize = atoi(argv[++i]);
    else
      strcpy_s(imageFileName, MAX_IMAGE_PATHNAME_LENGTH, argv[i]);
  }

#ifdef COUNTTEMPS
  tempFile = fopen("/usr/tmp/counts", "w");
#endif

  gcinit(staticSize, dynamicSize);

  /* read in the method from the image file */
  fileError = fopen_s(&fp, imageFileName, "rb");
  if(fileError || !fp)
  {
    fprintf(stderr,"cannot open image file: %s\n", imageFileName);
    /* FIXME: guiRelease(); etc. */
    exit(1);
  }

  printf("%d objects in image\n", fileIn(fp));
  fclose(fp);

  /* build a context around it */

  aProcess = staticAllocate(3);
  /* context should be dynamic */
  aContext = gcalloc(contextSize);

  aProcess->data[contextInProcess] = aContext;
  size = integerValue(initialMethod->data[stackSizeInMethod]);
  aContext->data[argumentsInContext] = staticAllocate(2);
  aContext->data[stackInContext] = staticAllocate(size);
  aContext->data[argumentsInContext] = staticAllocate(2);

  aContext->data[temporariesInContext] = staticAllocate(19);
  aContext->data[bytePointerInContext] = staticInteger(0);
  aContext->data[stackTopInContext] = staticInteger(0);
  aContext->data[previousContextInContext] = nilObject;
  aContext->data[methodInContext] = initialMethod;

  /* now go do it */
  rootStack[rootTop++] = aProcess;

  switch(execute(aProcess))
  {
    case 2:
      printf("User defined return\n");
      break;

    case 3:
      printf("can't find method in call\n");
      aProcess = rootStack[--rootTop];
      aContext = aProcess->data[contextInProcess];
      backTrace(aContext);
      break;

    case 4:
      printf("\nnormal return\n");
      break;

    case 5:
      printf("time out\n");
      break;

    default:
      printf("unknown return code\n");
      break;
  }

  printf("cache hit %d miss %d ratio %f\n", cacheHit, cacheMiss, 100.0 * ((double) cacheHit) / ((double) cacheHit + cacheMiss));
  printf("%d garbage collections\n", gccount);

  ffiRelease();
  sqliteRelease();
  guiRelease();

  return 0;
}


/*
 * primitive handler
 * (note that many primitives are handled in the interpreter)
 * (GUI primitives are handled in gui_primitives.c)
 */

#define FILEMAX 10
FILE *filePointers[FILEMAX];
int fileTop = 0;

void getUnixString(char *to, int size, struct object *from)
{
  int i;
  int fsize = from->size >> 2;
  struct byteObject * bobj = (struct byteObject *) from;

  if(fsize > size)
    sysError("error converting text into unix string", fsize);
  for(i = 0; i < fsize; i++)
    to[i] = bobj->bytes[i];
  to[i] = '\0';	/* put null terminator at end */
}


/* The result of this function is stored in a static buffer
 * to simplify memory management.
 * Since callers often do things like:
 * ......charPtr(...), ...,  charPtr(...) ....
 * in a single function call, the static buffer is organized
 * as a ring buffer so that more than one string can be stored
 * at each time...
 */
char *charPtr(struct object *from)
{
#define CHARPTR_STATIC_BUF_SIZE (10 * 1024)
#define CHARPTR_RINGBUF_LEN 10
  static char str[CHARPTR_RINGBUF_LEN][CHARPTR_STATIC_BUF_SIZE];

  static int currentRingBufIndex = 0;
  int i;
  int size;
  int minSize;
  struct byteObject *bobj = (struct byteObject *)from;
  currentRingBufIndex = (currentRingBufIndex + 1) % CHARPTR_RINGBUF_LEN;
  str[currentRingBufIndex][0] = 0;

  if(from)
  {
    size = from->size >> 2;
    minSize = size > CHARPTR_STATIC_BUF_SIZE - 1 ? CHARPTR_STATIC_BUF_SIZE - 1 : size;

    for(i = 0; i < minSize; i++)
      str[currentRingBufIndex][i] = bobj->bytes[i];
    str[currentRingBufIndex][i] = 0;
  }

  return str[currentRingBufIndex];
}


/* Attention: You have to set the string class explicitly by a primitive
 * call in a very early phase of execution!
 */
struct object *newString(const char *str)
{
  struct byteObject *result = (struct byteObject *)nilObject;
  int i;

  if(str)
  {
    int len = strlen(str);
    result = (struct byteObject *)gcialloc(len);
    if(result)
    {
      result->class = StringClass;
      /* is set by gcalloc()... result->size = len <<2; */
      for(i = 0; i < len; i++)
        result->bytes[i] = str[i];
    }
  }

  return (struct object *)result;
}


struct object *primitive(int primitiveNumber, struct object *args)
{
  struct object *returnedValue = nilObject;
  int i, j;
  FILE *fp;
  char *p;
  struct byteObject *stringReturn;
  char nameBuffer[1024];
  char modeBuffer[80];
  errno_t fileError;

  switch(primitiveNumber)
  {
    case 30: 	/* open a file */
      getUnixString(nameBuffer, 1024, args->data[0]);
      getUnixString(modeBuffer, 10, args->data[1]);
      strcat_s(modeBuffer, 80, "b"); /* Switch to binary mode */
      fileError = fopen_s(&fp, nameBuffer, modeBuffer);
      if(fp && !fileError)
      {
        if(fileTop + 1 >= FILEMAX)
          sysError("too many open files", 0);
        returnedValue = nwInteger(fileTop);
        filePointers[fileTop++] = fp;
      }
      break;

    case 31:	/* read a single character from a file */
      i = integerValue(args->data[0]);
      i = fgetc(filePointers[i]);
      if(i != EOF)
        returnedValue = nwInteger(i);
      break;

    case 32:	/* write a single character to a file */
      fputc(integerValue(args->data[1]), filePointers[integerValue(args->data[0])]);
      break;

    case 33:	/* close file */
      i = integerValue(args->data[0]);
      fclose(filePointers[i]);
      if(i+1 == fileTop)
        fileTop--;
      break;

    case 34:	/* file out image */
      i = integerValue(args->data[0]);
      fileOut(filePointers[i]);
      break;

    case 35:	/* edit a string */
      /* first get the name of a temp file */
#ifdef WIN32
      strcpy_s(nameBuffer, 1024, "C:\\tmp\\lsteditXXXXXX");
#else
      strcpy_s(nameBuffer, 1024, "/tmp/lsteditXXXXXX");
#endif
      _mktemp_s(nameBuffer, 1024);
      /* copy string to file */
      fileError = fopen_s(&fp, nameBuffer, "w");
      if(fileError || !fp)
        sysError("cannot open temp edit file", 0);
      j = args->data[0]->size >> 2;
      p = ((struct byteObject *) args->data[0])->bytes;
      for(i = 0; i < j; i++)
        fputc(*p++, fp);
      fputc('\n', fp);
      fclose(fp);
      /* edit string */
#ifdef WIN32
      strcpy_s(modeBuffer, 80, "C:\\Programme\\Vim\\vim63\\gvim.exe ");
#else
      strcpy_s(modeBuffer, 80, "vi ");
#endif
      strcat_s(modeBuffer, 80, nameBuffer);
      system(modeBuffer);
      /* copy back to new string */
      fileError = fopen_s(&fp, nameBuffer, "r");
      if(fileError || !fp)
        sysError("cannot open temp edit file", 0);
      /* get length of file */
      fseek(fp, 0, 2);
      j = (int) ftell(fp);
      stringReturn = (struct byteObject *)gcialloc(j);
      returnedValue = (struct object *) stringReturn;
      returnedValue->class = args->data[0]->class;
      /* reset to beginning, and read values */
      fseek(fp, 0, 0);
      for(i = 0; i < j; i++)
        stringReturn->bytes[i] = fgetc(fp);
      /* now clean up files */
      fclose(fp);
      _unlink(nameBuffer);
      break;

    case 36:
      /* Convert a SmallInt object into an Int object */
      returnedValue = nwInt(integerValue(args->data[0]));
      break;

    case 37:
      /* Convert an Int object into a SmallInt object if possible */
      i = integerValue(args->data[0]);
      if(i >= 0 && i < 1000)
        returnedValue = nwInteger(i);
      break;
    
    case 38:
         /* Allocate some memory */
         /* args->data[0]: number of bytes
          */
         returnedValue = nwInt((unsigned int)malloc(integerValue(args->data[0])));
         break;
    
    case 39:
         /* Read a byte in memory */
         /* args->data[0]: address to read from */
         returnedValue = nwInt((unsigned int)(*(unsigned char *)integerValue(args->data[0])));
         break;
    
    case 40:
         /* Write one byte in memory */
         /* args->data[0]: address to write to */
         /* args->data[1]: byte to write */
         *((unsigned char *)integerValue(args->data[0])) = (unsigned char)(integerValue(args->data[1]));
         break;
    
    case 41:
         /* Reserve an int array in memory */
         /* args->data[0]: size of the attay */
         returnedValue = nwInt((unsigned int)malloc(sizeof(int) * integerValue(args->data[0])));
         break;
    
    case 42:
         /* Read an int value from memory */
         /* args->data[0]: address to read from */
         returnedValue = nwInt(*((unsigned int *)integerValue(args->data[0])));
         break;
    
    case 43:
         /* Write an int value to memory */
         /* args->data[0]: address to write to */
         /* args->data[1]: int value to write */
         *((unsigned int *)integerValue(args->data[0])) = integerValue(args->data[1]);
         break;
    
    case 44:
         /* Free some memory */
         /* args->data[0]: the memory base to free */
         free((void *)integerValue(args->data[0]));
         break;

    case 45: 	/* open a file with user defined mode */
      getUnixString(nameBuffer, 1024, args->data[0]);
      getUnixString(modeBuffer, 10, args->data[1]);
      fileError = fopen_s(&fp, nameBuffer, modeBuffer);
      if(fp && !fileError)
      {
        if(fileTop + 1 >= FILEMAX)
          sysError("too many open files", 0);
        returnedValue = nwInteger(fileTop);
        filePointers[fileTop++] = fp;
      }
      break;

    case 46: /* Write a complete string to an opened file */
      fprintf(filePointers[integerValue(args->data[0])], "%s", charPtr(args->data[1]));
      break;

    /* Primitives 70 to 99 are reserved for the extended primitives in interp.c */
    /* (We need more than 30 primitives there...) */

      /* Primitives 160 to 199 are reserved for the GUI system */
      /* Currently this subsystem which is based on IUP is disabled because
       * I did not get IUP to work with wx-devcpp...
       */
    case 160:
    case 161:
    case 162:
    case 163:
    case 164:
    case 165:
    case 166:
    case 167:
    case 168:
    case 169:
    case 170:
    case 171:
    case 172:
    case 173:
    case 174:
    case 175:
    case 176:
    case 177:
    case 178:
    case 179:
    case 180:
    case 181:
    case 182:
    case 183:
    case 184:
    case 185:
    case 186:
    case 187:
    case 188:
    case 189:
    case 190:
    case 191:
    case 192:
    case 193:
    case 194:
    case 195:
    case 196:
    case 197:
    case 198:
    case 199:
      /* a GUI primitive */
      returnedValue = guiPrimitive(primitiveNumber, args);
      break;

      /* Primitive Numbers 200 to 219 are reserved for the SQLite subsystem */
    case 200:
    case 201:
    case 202:
    case 203:
    case 204:
    case 205:
    case 206:
    case 207:
    case 208:
    case 209:
    case 210:
    case 211:
    case 212:
    case 213:
    case 214:
    case 215:
    case 216:
    case 217:
    case 218:
    case 219:
      returnedValue = sqlitePrimitive(primitiveNumber, args);
      break;

    /* Primitive Numbers 230 to 239 are reserved for the FFI subsystem */
    case 230:
    case 231:
    case 232:
    case 233:
    case 234:
    case 235:
    case 236:
    case 237:
    case 238:
    case 239:
      returnedValue = ffiPrimitive(primitiveNumber, args);
      break;

    default:
      sysError("unknown primitive", primitiveNumber);
  }

  return returnedValue;
}


