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

/* This file contains the GUI primitives known by the LittleSmalltalk
 * system.
 */


#include "lst_settings.h"
#include "lst_os.h"
#include "memory.h"
#include "gui_primitives.h"

#if !defined(LST_USE_GUI) || LST_USE_GUI == 0

/* GUI primitives are not active.
 * Provide some dummy stuff instead...
 */

void guiInit() { }
void guiRelease() { }

void guiShowMessage(const char *title, const char *message)
{
  printf("LST message! Title: <%s>, Message: <%s>\n", title ? title : "undefined", message ? message : "undefined");
}

void sysError(char *a, int b)
{
  static char buf[1024];
  sprintf_s(buf, 1024, "Unrecoverable system error: %s (%d)", a, b);
  sysError2("LittleSmalltalk - System Error!", buf);
}

void sysError2(const char *title, const char *message)
{
  guiShowMessage("LittleSmalltalk - Error!", message);
  exit(1);
}

struct object *guiPrimitive(int primitiveNumber, struct object *arguments)
{
  return nilObject;
}


#else


#include <stdlib.h>
#include "iup.h"
#include "iupcontrols.h"
#include "iupim.h"
#include "gui_primitives.h"
#include "main.h"
#include "rss_queue.h"


static RSS_Queue eventQueue;


static struct object *createControl(struct object *arguments);
static struct object *composeElements(struct object *arguments);
static int iupCallback(Ihandle *iHandle, ...);
static int iupListCallback(Ihandle *iHandle, char *text, int index, int selectionFlag);


void guiInit()
{
  eventQueue = rss_queueCreate(31);
  IupOpen();
  IupControlsOpen();
  IupImageLibOpen();
}


void guiRelease()
{
  IupImageLibClose();
  IupControlsClose();
  IupClose();
  rss_queueRelease(eventQueue);
  eventQueue = 0;
}


void guiShowMessage(const char *title, const char *message)
{
  IupMessage((char *)title, (char *)message);
}


void sysError(char *a, int b)
{
  static char buf[1024];
  sprintf_s(buf, 1024, "Unrecoverable system error: %s (%d)", a, b);
  sysError2("LittleSmalltalk - System Error!", buf);
}


void sysError2(const char *title, const char *message)
{
  guiShowMessage("LittleSmalltalk - Error!", message);
  guiRelease();
  exit(1);
}


struct object *guiPrimitive(int primitiveNumber, struct object *arguments)
{
  struct object *result;
  char     buf[100];
  Ihandle *iHandle;
  int      i;

  result = nilObject;

  switch(primitiveNumber)
  {
    case 160:
      /* show a simple message */
      /* arguments->data[0]: title
       * arguments->data[1]: text */
      IupMessage(charPtr(arguments->data[0]), charPtr(arguments->data[1]));
      break;

    case 161:
      result = createControl(arguments);
      break;

    case 162:
      result = composeElements(arguments);
      break;

    case 163:
      /* append element */
      /* arguments->data[0]: id of the box element
       * arguments->data[1]: id of the element to add
       */
      IupAppend(IupGetHandle(charPtr(arguments->data[0])), IupGetHandle(charPtr(arguments->data[1])));
      break;

    case 164:
      /* Detach element */
      /* arguments->data[0]: the element that shall be detached */
      IupDetach(IupGetHandle(charPtr(arguments->data[0])));
      break;

    case 165:
      /* Show interface element */
      /* arguments->data[0]: id of the interface element */
      iHandle = IupGetHandle(charPtr(arguments->data[0]));
      IupShow(iHandle);
      break;

    case 170:
      /* register an event */
      /* arguments->data[0]: the action to register */
      IupSetFunction(charPtr(arguments->data[0]), iupCallback);
      break;

    case 171:
      /* get next event (non blocking event polling) */
      i = rss_queueSize(eventQueue);
      if(i <= 0)
        IupLoopStep();
      if(rss_queueSize(eventQueue) > 0)
      {
        char *str = (char *)rss_queueGet(eventQueue);
        if(str)
        {
          result = (struct object *)newString(str);
          free(str);
        }
      }
      break;

    case 172:
      /* just for testing... */
      IupMainLoop();
      break;

    case 173:
      /* Wait for a short amount of time */
      /* arguments->data[0]: milli seconds */
      Sleep(integerValue(arguments->data[0]));
      break;

    case 174:
      /* Destroy a GUI element */
      IupDestroy(IupGetHandle(charPtr(arguments->data[0])));
      break;

    case 175:
      /* Set an attribute of a GUI element */
      /* arguments->data[0]: The GUI element's name */
      /* arguments->data[1]: The attribute to set   */
      /* arguments->data[2]: The value as a string  */
      IupStoreAttribute(IupGetHandle(charPtr(arguments->data[0])), charPtr(arguments->data[1]), charPtr(arguments->data[2]));
      break;

    case 176:
      /* Read the value of a widget's attribute */
      /* arguments->data[0]: The widget's name */
      /* arguments->data[1]: The attribute     */
      result = newString(IupGetAttribute(IupGetHandle(charPtr(arguments->data[0])), charPtr(arguments->data[1])));
      break;

    case 177:
      /* register a list event */
      /* arguments->data[0]: the action to register */
      IupSetFunction(charPtr(arguments->data[0]), (Icallback)iupListCallback);
      break;

    case 178:
      /* Delete an attribute (by setting its value to 0). */
      /* arguments->data[0]: The widget's name */
      /* arguments->data[1]: The attribute     */
      IupSetAttribute(IupGetHandle(charPtr(arguments->data[0])), charPtr(arguments->data[1]), 0);
      break;

    case 179:
      /* Popup interface element */
      /* arguments->data[0]: id of the interface element */
      iHandle = IupGetHandle(charPtr(arguments->data[0]));
      IupPopup(iHandle, IUP_MOUSEPOS, IUP_MOUSEPOS);
      break;

    case 180:
      /* Save an image into a file */
      /* arguments->data[0]: The id of the IupImage object
       * arguments->data[1]: The new pathname
       * arguments->data[2]: The format descriptor
       * Returns 0 on failure.
       */
      iHandle = IupGetHandle(charPtr(arguments->data[0]));
      i = IupSaveImage(iHandle, charPtr(arguments->data[1]), charPtr(arguments->data[2]));
      result = nwInteger(i);
      break;

    default:
      sprintf_s(buf, 100, "Unknown primitive number: <%d>", primitiveNumber);
      sysError2("Primitive not done!", buf);
  }

  return result;
}


static struct object *createControl(struct object *arguments)
{
  struct object *result;
  int            controlType;
  Ihandle       *iHandle = 0;

  result = nilObject;

  controlType = integerValue(arguments->data[0]);
  switch(controlType)
  {
    case 0:
      /* create a canvas */
      iHandle = IupCanvas(charPtr(arguments->data[2]));
      break;

    case 1:
      /* create a button */
      /* arguments->data[2]: title */
      iHandle = IupButton(charPtr(arguments->data[2]), charPtr(arguments->data[3]));
      break;

    case 2:
      /* create a toggle */
      /* arguments->data[2]: title */
      iHandle = IupToggle(charPtr(arguments->data[2]), charPtr(arguments->data[3]));
      break;

    case 3:
      /* create a label */
      /* arguments->data[2]: title */
      /* no action required! */
      iHandle = IupLabel(charPtr(arguments->data[2]));
      break;

    case 4:
      /* create a frame */
      /* arguments->data[2]: id of the contained gui element */
      iHandle = IupFrame(IupGetHandle(charPtr(arguments->data[2])));
      break;

    case 5:
      /* create a list */
      iHandle = IupList(charPtr(arguments->data[2]));
      break;

    case 6:
      /* create a multi line text control */
      iHandle = IupMultiLine(charPtr(arguments->data[2]));
      break;

    case 7:
      /* create an editable text field */
      iHandle = IupText(charPtr(arguments->data[2]));
      break;

    case 8:
      /* create an image */
      /* arguments->data[2]: width
       * arguments->data[3]: height
       * arguments->data[4]: string containing the bitmap */
      /* no action! */
      iHandle = IupImage(integerValue(arguments->data[2]), integerValue(arguments->data[3]), charPtr(arguments->data[4]));
      break;

    case 9:
      /* create a color */
      /* arguments->data[2]: red value (0 - 255)
       * arguments->data[3]: green value (0 - 255)
       * arguments->data[4]: blue value (0 - 255)
       * no action! */
      iHandle = IupColor(integerValue(arguments->data[2]), integerValue(arguments->data[3]), integerValue(arguments->data[4]));
      break;

    case 10:
      /* create a dialog */
      /* arguments->data[2]: the id of the contained gui element
       * no action! */
      iHandle = IupDialog(IupGetHandle(charPtr(arguments->data[2])));
      break;

    case 11:
      /* create a file dialog */
      /* no action! */
      iHandle = IupFileDlg();
      break;

    case 12:
      /* create a gauge dialog */
      /* no action! */
      iHandle = IupGauge();
      break;

    case 13:
      /* create a timer */
      /* no action! */
      iHandle = IupTimer();
      break;

    case 14:
      /* create a split box */
      /* arguments->data[2]: the id of the contained gui element (either a vbox or an hbox)
       * no action! */
      iHandle = IupSbox(IupGetHandle(charPtr(arguments->data[2])));
      break;

    case 15:
      /* create an image object from a file (open a file) */
      /* arguments->data[2]: The pathname */
      iHandle = IupLoadImage(charPtr(arguments->data[2]));
      break;

    default:
      sysError2("GUI Primitive Error", "Unknown control type specified!");
  }

  if(iHandle)
    IupSetHandle(charPtr(arguments->data[1]), iHandle);

  return result;
}


static struct object *composeElements(struct object *arguments)
{
  struct object *result;
  int            command;
  Ihandle       *iHandle = 0;

  result = nilObject;

  command = integerValue(arguments->data[0]);
  switch(command)
  {
    case 0:
      /* fill */
      iHandle = IupFill();
      break;

    case 1:
      /* hbox */
      iHandle = IupHbox(0);
      break;

    case 2:
      /* vbox */
      iHandle = IupVbox(0);
      break;

    case 3:
      /* zbox */
      iHandle = IupZbox(0);
      break;

    case 4:
      /* radio box */
      /* arguments->data[2]: the box element that shall be contained in the radio group */
      iHandle = IupRadio(IupGetHandle(charPtr(arguments->data[2])));
      break;

    default:
      sysError2("GUI primitive error", "Unknown composition command specified!");
  }

  if(iHandle)
    IupSetHandle(charPtr(arguments->data[1]), iHandle);

  return result;
}


static int iupCallback(Ihandle *iHandle, ...)
{
  rss_queuePut(eventQueue, (void *)(_strdup(IupGetActionName())));
  return IUP_DEFAULT;
}


static int iupListCallback(Ihandle *iHandle, char *text, int index, int selectionFlag)
{
  static char buf[128];
  rss_queuePut(eventQueue, (void *)_strdup("__list_event"));
  rss_queuePut(eventQueue, (void *)_strdup(IupGetActionName()));
  rss_queuePut(eventQueue, (void *)_strdup(text));
  sprintf_s(buf, 128, "%d", index);
  rss_queuePut(eventQueue, (void *)_strdup(buf));
  sprintf_s(buf, 128, "%d", selectionFlag);
  rss_queuePut(eventQueue, (void *)_strdup(buf));
  return IUP_DEFAULT;
}


#endif


