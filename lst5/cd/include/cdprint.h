#ifndef _CD_PRINTER_
#define _CD_PRINTER_

#ifdef __cplusplus
extern "C" {
#endif

cdContext* cdContextPrinter(void);

#define CD_PRINTER cdContextPrinter()

#ifdef __cplusplus
}
#endif

#endif /* ifndef _CD_PRINTER_ */

