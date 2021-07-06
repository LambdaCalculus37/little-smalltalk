#ifndef _CD_IRGB_
#define _CD_IRGB_

#ifdef __cplusplus
extern "C" {
#endif

cdContext* cdContextImageRGB(void);

#define CD_IMAGERGB cdContextImageRGB()

unsigned char* cdRedImage(cdCanvas* cnv);
unsigned char* cdGreenImage(cdCanvas* cnv);
unsigned char* cdBlueImage(cdCanvas* cnv);


#ifdef __cplusplus
}
#endif

#endif /* ifndef _CD_IRGB_ */
