/** \file
 * \brief initializes iupdial, iupgauge, iuptabs, iupcb, iupgc and iupval controls.
 *
 * See Copyright Notice in iup.h
 * $Id: iupcontrols.h,v 1.17 2005/12/07 17:53:16 scuri Exp $
 */
 
#ifndef __IUPCONTROLS_H 
#define __IUPCONTROLS_H

#include "iupdial.h"
#include "iupgauge.h"
#include "iuptabs.h"
#include "iupval.h"
#include "iupmatrix.h"
#include "iuptree.h"
#include "iupsbox.h"
#include "iupmask.h"
#include "iupgc.h"
#include "iupcb.h"
#include "iupspin.h"
#include "iupcolorbar.h"
#include "iupgetparam.h"
#include "iupcbox.h"
#include "iupcells.h"

#ifdef __cplusplus
extern "C" {
#endif

int IupControlsOpen(void);
void IupControlsClose(void);

void IupImageLibOpen (void);
void IupImageLibClose (void);

#ifdef __cplusplus
}
#endif

#endif
