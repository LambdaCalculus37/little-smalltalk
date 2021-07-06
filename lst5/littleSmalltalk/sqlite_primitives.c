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

#if !defined(LST_USE_SQLITE) || LST_USE_SQLITE == 0

/* The SQLite primitives are disabled.
 * Provide some dummy stuff instead...
 */

void sqliteInit() { }
void sqliteRelease() { }
struct object *sqlitePrimitive(int primitiveNumber, struct object *args)
{
  return nilObject;
}


#else


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_primitives.h"
#include "../sqlite3/sqlite3.h"
#include "gui_primitives.h"
#include "main.h"
#include "memory.h"

#define LS_MAX_OPEN_DATABASES 10
#define LS_MAX_RESULTS 50

static int getNextDBIndex();
static int getNextResultIndex();

static sqlite3 *dbs[LS_MAX_OPEN_DATABASES];


struct SQLiteResult
{
  int nofCols;
  int nofRows;
  char errMsg[4096];
  char **table;
};
static struct SQLiteResult dbResults[LS_MAX_RESULTS];


void sqliteInit()
{
  int i;
  for(i = 0; i < LS_MAX_OPEN_DATABASES; i++)
    dbs[i] = 0;
  for(i = 0; i < LS_MAX_RESULTS; i++)
    dbResults[i].table = 0;
}


void sqliteRelease()
{
  int i;
  for(i = 0; i < LS_MAX_OPEN_DATABASES; i++)
  {
    if(dbs[i])
      sqlite3_close(dbs[i]);
  }
}


struct object *sqlitePrimitive(int primitiveNumber, struct object *args)
{
  struct object *result;
  char     buf[100];
  int      i;
  int      j;
  int      x;
  int      y;
  char *errMsg = 0;
  int   err;

  result = nilObject;

  switch(primitiveNumber)
  {
    case 200:
      /* open or create a database file */
      /* Return a handle (in fact an index for the handle array) for the database */
      /* args->data[0]: name of the database file */
      i = getNextDBIndex();
      if(i >= 0)
      {
        if(sqlite3_open(charPtr(args->data[0]), &dbs[i]) == SQLITE_OK)
          result = nwInteger(i);
      }
      break;

    case 201:
      /* Close the specified database */
      /* args->data[0]: The handle of the database */
      i = integerValue(args->data[0]);
      if(i >= 0 && i < LS_MAX_OPEN_DATABASES && dbs[i])
      {
        sqlite3_close(dbs[i]);
        dbs[i] = 0;
      }
      break;

    case 202:
      /* Execute the specified SQL statament in the specified database */
      /* args->data[0]: The handle of the database */
      /* args->data[1]: The SQL statement */
      i = integerValue(args->data[0]);
      if(i >= 0 && i < LS_MAX_OPEN_DATABASES && dbs[i])
      {
        err = sqlite3_exec(dbs[i], charPtr(args->data[1]), 0, 0, &errMsg);
        if(err != SQLITE_OK)
        {
          result = newString(errMsg);
          sqlite3_free(errMsg);
        }
      }
      break;

    case 203:
      /* Returns the id of the last inserted row */
      /* args->data[0]: The handle of the database */
      i = integerValue(args->data[0]);
      if(i >= 0 && i < LS_MAX_OPEN_DATABASES && dbs[i])
        result = nwInteger((int)sqlite3_last_insert_rowid(dbs[i]));
      break;

    case 204:
      /* Execute a SQL query that can have a result table (a SELECT statement) */
      /* args->data[0]: The handle of the database */
      /* args->data[1]: The SQL query */
      /* This primitive returns a handle for the result table. */
      /* The results can be accessed with some other primitives */
      i = integerValue(args->data[0]);
      if(i >= 0 && i < LS_MAX_OPEN_DATABASES && dbs[i])
      {
        j = getNextResultIndex();
        if(j >= 0)
        {
          err = sqlite3_get_table(dbs[i], charPtr(args->data[0]), &(dbResults[j].table), &(dbResults[j].nofRows), &(dbResults[j].nofCols), &errMsg);
          if(err != SQLITE_OK)
          {
            dbResults[j].nofRows = 0;
            dbResults[j].nofCols = 0;
            dbResults[j].table = 0;
            strcpy_s(dbResults[j].errMsg, 4096, errMsg);
            sqlite3_free(errMsg);
          }

          result = nwInteger(j);
        }
      }
      break;

    case 205:
      /* Release a result set */
      /* args->data[0]: The handle of the result set */
      j = integerValue(args->data[0]);
      if(j >= 0 && j < LS_MAX_RESULTS && dbResults[j].table)
      {
        sqlite3_free_table(dbResults[j].table);
        dbResults[j].errMsg[0] = 0;
        dbResults[j].nofRows = 0;
        dbResults[j].nofCols = 0;
      }
      break;

    case 206:
      /* Returns the error message that is associated with a result set or nil if there was no error */
      /* args->data[0]: The handle of the result set */
      j = integerValue(args->data[0]);
      if(j >= 0 && j < LS_MAX_RESULTS && dbResults[j].errMsg[0])
      {
        result = newString(dbResults[j].errMsg);
      }
      break;

    case 207:
      /* Returns the number of rows in the specified result set */
      /* args->data[0]: The handle of the result set */
      j = integerValue(args->data[0]);
      if(j >= 0 && j < LS_MAX_RESULTS && dbResults[j].table)
        result = nwInteger(dbResults[j].nofRows);
      break;

    case 208:
      /* Returns the number of columns in the specified result set */
      /* args->data[0]: The handle of the result set */
      j = integerValue(args->data[0]);
      if(j >= 0 && j < LS_MAX_RESULTS && dbResults[j].table)
        result = nwInteger(dbResults[j].nofCols);
      break;

    case 209:
      /* Returns the value (as a string) in the result set at the given position */
      /* args->data[0]: The handle of the result set */
      /* args->data[1]: The column */
      /* args->data[2]: The row */
      j = integerValue(args->data[0]);
      x = integerValue(args->data[1]);
      y = integerValue(args->data[2]);
      if(j >= 0 && j < LS_MAX_RESULTS && dbResults[j].table)
        result = newString(dbResults[j].table[(y * dbResults[j].nofCols) + x]);

      break;

    default:
      sprintf_s(buf, 100, "Unknown SQLite primitive number: <%d>", primitiveNumber);
      sysError2("Primitive not done!", buf);
  }

  return result;
}


static int getNextDBIndex()
{
  int i;
  for(i = 0; i < LS_MAX_OPEN_DATABASES; i++)
  {
    if(!dbs[i])
      return i;
  }

  return -1;
}


static int getNextResultIndex()
{
  int i;
  for(i = 0; i < LS_MAX_RESULTS; i++)
  {
    if(!dbResults[i].table)
      return i;
  }

  return -1;
}


#endif

