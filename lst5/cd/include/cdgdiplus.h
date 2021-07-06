#ifndef _CD_GDIPLUS_
#define _CD_GDIPLUS_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
int cdUseContextPlus(int use);
void cdInitGdiPlus(void);
void cdInitGdiPlusIUP(void);
#else
#define cdUseContextPlus(x) (x)
#define cdInitGdiPlus() (0)
#define cdInitGdiPlusIUP() (0)
#endif

/* Windows GDI+ Adicional Polygons */
#define CD_SPLINE       (CD_POLYCUSTOM+0)
#define CD_FILLSPLINE   (CD_POLYCUSTOM+1)
#define CD_FILLGRADIENT (CD_POLYCUSTOM+2)

#ifdef __cplusplus
}
#endif

#endif /* ifndef _CD_GDIPLUS_ */

