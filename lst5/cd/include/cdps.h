#ifndef _CD_PS_
#define _CD_PS_

#ifdef __cplusplus
extern "C" {
#endif

cdContext* cdContextPS(void);

#define CD_PS cdContextPS()

#ifndef CD_PAPERSIZE
#define CD_PAPERSIZE
enum {                          /* paper sizes */
  CD_A0,
  CD_A1,
  CD_A2,
  CD_A3,
  CD_A4,
  CD_A5,
  CD_LETTER,
  CD_LEGAL
};
#endif

#ifdef __cplusplus
}
#endif

#endif /* ifndef _CD_PS_ */

