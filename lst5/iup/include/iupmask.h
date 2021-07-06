/** \file
 * \brief iupmask functions.
 *
 * See Copyright Notice in iup.h
 * $Id: iupmask.h,v 1.7 2006/02/04 21:10:17 uid20021 Exp $
 */
 
#ifndef __IUPMASK_H 
#define __IUPMASK_H

#ifdef __cplusplus
extern "C" {
#endif

/* pre-defined masks */
#define IUPMASK_FLOAT      "[+/-]?(/d+/.?/d*|/./d+)"
#define IUPMASK_UFLOAT     "(/d+/.?/d*|/./d+)"
#define IUPMASK_EFLOAT		"[+/-]?(/d+/.?/d*|/./d+)([eE][+/-]?/d+)?"
#define IUPMASK_INT	      "[+/-]?/d+"
#define IUPMASK_UINT     	"/d+"


int  iupmaskSet     (Ihandle *h, char *mask, int autofill, int casei);
int  iupmaskSetInt  (Ihandle *h, int autofill, int   min , int   max);
int  iupmaskSetFloat(Ihandle *h, int autofill, float min , float max);
void iupmaskRemove   (Ihandle *h);

int  iupmaskCheck   (Ihandle *h);

int  iupmaskGet      (Ihandle *h, char   **val);
int  iupmaskGetFloat (Ihandle *h, float  *fval);
int  iupmaskGetDouble(Ihandle *h, double *dval);
int  iupmaskGetInt   (Ihandle *h, int    *ival);



int  iupmaskMatSet     (Ihandle *h, char *mask, int autofill, int casei, int lin, int col);
int  iupmaskMatSetInt  (Ihandle *h, int autofill, int   min, int   max, int lin, int col);
int  iupmaskMatSetFloat(Ihandle *h, int autofill, float min, float max, int lin, int col);
void iupmaskMatRemove  (Ihandle *h, int lin, int col);

int  iupmaskMatCheck   (Ihandle *h, int lin, int col);

int  iupmaskMatGet      (Ihandle *h, char   **val, int lin, int col);
int  iupmaskMatGetFloat (Ihandle *h, float  *fval, int lin, int col);
int  iupmaskMatGetDouble(Ihandle *h, double *dval, int lin, int col);
int  iupmaskMatGetInt   (Ihandle *h, int    *ival, int lin, int col);

#ifdef __cplusplus
}
#endif

#endif
