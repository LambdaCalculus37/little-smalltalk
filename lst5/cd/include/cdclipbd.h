#ifndef _CD_CLIPBOARD_
#define _CD_CLIPBOARD_


#ifdef __cplusplus
extern "C" {
#endif

cdContext* cdContextClipboard(void);

#define CD_CLIPBOARD cdContextClipboard()

#ifdef __cplusplus
}
#endif

#endif
