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
#include "memory.h"

#if !defined(LST_USE_FFI) || LST_USE_FFI == 0

/* The FFI primitives are disabled.
 * Provide some dummy stuff instead...
 */

void ffiInit() { }
void ffiRelease() { }
struct object *ffiPrimitive(int primitiveNumber, struct object *args)
{
  return nilObject;
}


#else


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ffi_primitives.h"
#include "rss_dynload.h"
#include "main.h"
#include "memory.h"


#define LS_MAX_OPEN_LIBS 20
#define LS_MAX_FUNCTIONS 200

#define isValidSO(soIndex)               soIndex >= 0 && soIndex < LS_MAX_OPEN_LIBS && libs[soIndex].handle
#define isValidFunc(soIndex, funcIndex)  isValidSO(soIndex) && funcIndex >= 0 && funcIndex < LS_MAX_FUNCTIONS && libs[soIndex].functions[funcIndex]

static int getNextLibIndex();
static int getNextFunctionIndex(int handle);


struct LST_DL_Struct
{
  RSS_DL_Handle   handle;
  RSS_DL_Function functions[LS_MAX_FUNCTIONS];
};
typedef struct LST_DL_Struct LST_DL_Handle;


static LST_DL_Handle libs[LS_MAX_OPEN_LIBS];



void ffiInit()
{
  int i;
  for(i = 0; i < LS_MAX_OPEN_LIBS; i++)
  {
    int j;
    libs[i].handle = 0;
    for(j = 0; j < LS_MAX_FUNCTIONS; j++)
      libs[i].functions[j] = 0;
  }
}


void ffiRelease()
{
  int i;
  for(i = 0; i < LS_MAX_OPEN_LIBS; i++)
  {
    if(libs[i].handle)
      rss_dlClose(libs[i].handle);
  }
}


struct object *ffiPrimitive(int primitiveNumber, struct object *args)
{
  struct object   *result;
  char             buf[100];
  const char      *str;
  int              i;
  int              j;
  int              soIndex;
  int              funcIndex;
  RSS_DL_Function  func;

  result = nilObject;

  switch(primitiveNumber)
  {
    case 230:
      /* open or create a shared object (dll) */
      /* Return a handle (in fact an index to an array containing RSS_DL_Handle objects) for the lib */
      /* args->data[0]: (path)name of the library file */
      i = getNextLibIndex();
      if(i >= 0)
      {
        libs[i].handle = rss_dlOpen(charPtr(args->data[0]), RSS_DL_LAZY);
        if(libs[i].handle)
          result = nwInteger(i);
      }
      break;

    case 231:
      /* Close the specified database */
      /* args->data[0]: The handle of the database */
      soIndex = integerValue(args->data[0]);
      if(isValidSO(soIndex))
      {
        rss_dlClose(libs[soIndex].handle);
        libs[soIndex].handle = 0;
        for(funcIndex = 0; funcIndex < LS_MAX_FUNCTIONS; funcIndex++)
          libs[soIndex].functions[funcIndex] = 0;
      }
      break;

    case 232:
      /* Return a meaningful error message if something went wrong... */
      /* Returns the message of the last error that occured. */
      str = rss_dlError();
      if(str)
        result = newString(str);
      break;

    case 233:
      /* Tries to resolve a function symbol.*/
      /* args->data[0]: The handle of the shared object */
      /* args->data[1]: The name of the function */
      /* returns a function handle that can be used to call the function. */
      soIndex = integerValue(args->data[0]);
      if(isValidSO(soIndex))
      {
        func = rss_dlGetFunctionSymbol(libs[soIndex].handle, charPtr(args->data[1]));
        if(func)
        {
          funcIndex = getNextFunctionIndex(soIndex);
          libs[soIndex].functions[funcIndex] = func;
          result = nwInteger(funcIndex);
        }
      }
      break;

    case 234:
      /* Execute the specified function... */
      /* Attention: Currently only functions with prototype "int func(int);" are supported! */
      /* args->data[0]: The handle to the shared object that contains the function */
      /* args->data[1]: The handle of the function within the shared object */
      /* args->data[2]: The argument that should be passed to the function */
      /* Returns the return code of the function */
      soIndex   = integerValue(args->data[0]);
      funcIndex = integerValue(args->data[1]);
      i         = integerValue(args->data[2]);

      if(isValidFunc(soIndex, funcIndex))
      {
        j = libs[soIndex].functions[funcIndex](i);
        result = nwInteger(j);
      }

      break;


    default:
      sprintf_s(buf, 100, "Unknown FFI primitive number: <%d>", primitiveNumber);
      sysError2("Primitive not done!", buf);
  }

  return result;
}


static int getNextLibIndex()
{
  int i;
  for(i = 0; i < LS_MAX_OPEN_LIBS; i++)
  {
    if(!libs[i].handle)
      return i;
  }

  return -1;
}


static int getNextFunctionIndex(int handle)
{
  int i;
  if(!handle || !libs[handle].handle)
    return -1;

  for(i = 0; i < LS_MAX_FUNCTIONS; i++)
  {
    if(libs[handle].functions[i] == 0)
      return i;
  }

  return -1;
}


#endif

