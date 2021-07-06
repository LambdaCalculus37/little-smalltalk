#ifndef _CD_DBUF_
#define _CD_DBUF_

#ifdef __cplusplus
extern "C" {
#endif

cdContext* cdContextDBuffer(void);

#define CD_DBUFFER cdContextDBuffer()

#ifdef __cplusplus
}
#endif

#endif /* ifndef _CD_DBUF_ */

