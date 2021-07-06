/** \file
 * \brief iupspeech control.
 *
 * See Copyright Notice in iup.h
 * $Id: iupspeech.h,v 1.3 2003/07/10 19:44:48 mark Exp $
 */

#ifndef __IUPSPEECH_H
#define __IUPSPEECH_H

#ifdef __cplusplus
extern "C" {
#endif

int IupSpeechOpen(void);
void IupSpeechClose(void);
Ihandle *IupSpeech(void);

#ifdef __cplusplus
}
#endif

#endif

