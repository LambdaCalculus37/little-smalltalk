/** \file
 * \brief iupgetparam dialog.
 *
 * See Copyright Notice in iup.h
 * $Id: iupgetparam.h,v 1.4 2005/09/26 18:02:41 scuri Exp $
 */
 
#ifndef __IUPGETPARAM_H 
#define __IUPGETPARAM_H

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*Iparamcb)(Ihandle* dialog, int param_index, void* user_data);

int IupGetParam(const char* title, Iparamcb action, void* user_data, const char* format,...);
int IupGetParamv(const char* title, Iparamcb action, void* user_data, const char* format, int param_count, int param_extra, void** param_data);

/* Utility functions to parse one param line string. Used by the Lua binding. */
int IupGetParamCount(const char *format, int *param_extra);
char *IupGetParamType(const char* format, int *line_size);

#ifdef __cplusplus
}
#endif

#endif
