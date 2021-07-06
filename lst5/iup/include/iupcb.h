/** \file
 * \brief iupcolorbrowser control.
 *
 * See Copyright Notice in iup.h
 * $Id: iupcb.h,v 1.5 2005/09/13 13:24:47 scuri Exp $
 */
 
#ifndef __IUPCB_H 
#define __IUPCB_H

#ifdef __cplusplus
extern "C" {
#endif

Ihandle *IupColorBrowser(void);

#define IUP_RGB "RGB"
#define IUP_CHANGE_CB "CHANGE_CB"
#define IUP_DRAG_CB "DRAG_CB"

#ifdef __cplusplus
}
#endif

#endif

