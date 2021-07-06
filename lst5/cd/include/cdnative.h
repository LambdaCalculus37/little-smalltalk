#ifndef _CD_NATIVE_
#define _CD_NATIVE_

#ifdef __cplusplus
extern "C" {
#endif

cdContext* cdContextNativeWindow(void);

#define CD_NATIVEWINDOW cdContextNativeWindow()

void cdGetScreenSize(int *width, int *height, double *width_mm, double *height_mm);
int cdGetScreenColorPlanes(void);

#ifdef __cplusplus
}
#endif

#endif /* ifndef _CD_NATIVE_ */

