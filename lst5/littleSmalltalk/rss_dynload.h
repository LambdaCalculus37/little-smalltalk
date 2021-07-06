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
 * Platform independent runtime access to shared
 * objects (DLLs)...
 */


#ifndef RSS_DYNLOAD_H
#define RSS_DYNLOAD_H

#ifdef __cplusplus
extern "C"
{
#endif


struct RSS_DL_Handle_Struct;
typedef struct RSS_DL_Handle_Struct *RSS_DL_Handle;

typedef int (*RSS_DL_Function)(int);


typedef
  enum
  {
    RSS_DL_LAZY,
    RSS_DL_NOW
  }
RSS_DL_Mode;


RSS_DL_Handle rss_dlOpen(const char *pathname, RSS_DL_Mode mode);
int rss_dlClose(RSS_DL_Handle handle);


/* Attention: On Windows rss_dlGetDataSymbol() always returns 0, because
 * DLLs cannot export data symbols on Windows...
 */
void *rss_dlGetDataSymbol(RSS_DL_Handle handle, const char *symbol);
RSS_DL_Function rss_dlGetFunctionSymbol(RSS_DL_Handle handle, const char *symbol);

const char *rss_dlError(void);


#ifdef __cplusplus
}
#endif

#endif

