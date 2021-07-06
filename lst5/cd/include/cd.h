#ifndef CD_H
#define CD_H


#ifdef __cplusplus
extern "C" {
#endif



/* context structure */
typedef struct _cdContext {
  void *ctx;
} cdContext;


/* canvas structure */
typedef struct _cdCanvas {
  void *cnv;
} cdCanvas;


/* state structure */
typedef struct _cdState {
  void *ste;
} cdState;


#define CD_COPYRIGHT    "Copyright (C) 1994-2005 Tecgraf/PUC-Rio and PETROBRAS S/A"
#define CD_VERSION "4.4.0"
#define CD_VERSION_DATE "2005/12/12"
#define CD_VERSION_NUMBER 404000

char*         cdVersion(void);
char*         cdVersionDate(void);
int           cdVersionNumber(void);

/* control */
cdCanvas*     cdCreateCanvas(cdContext *context, void *data);
cdCanvas*     cdCreateCanvasf(cdContext *context, char* format, ...);
void          cdKillCanvas(cdCanvas *canvas);
cdContext*    cdGetContext(cdCanvas *canvas);
unsigned long cdContextCaps(cdContext *context);
int           cdActivate(cdCanvas *canvas);
cdCanvas*     cdActiveCanvas(void);
int           cdSimulate(int mode);
void          cdFlush(void);
void          cdClear(void);
cdState*      cdSaveState(void);
void          cdRestoreState(cdState* state);
void          cdReleaseState(cdState* state);
void          cdSetAttribute(char* name, char* data);
void          cdSetfAttribute(char* name, char* format, ...);
char*         cdGetAttribute(char* name);


/* interpretation */
typedef int (*cdCallback)(cdContext *context, ...);
int  cdRegisterCallback(cdContext *context, int cb, cdCallback func);
int  cdPlay(cdContext *context, int xmin, int xmax, int ymin, int ymax, void *data);


/* coordinate transformation */
void cdGetCanvasSize(int *width, int *height, double *width_mm, double *height_mm);
void cdUpdateYAxis(int* y);
void cdMM2Pixel(double mm_dx, double mm_dy, int *dx, int *dy);
void cdPixel2MM(int dx, int dy, double *mm_dx, double *mm_dy);
void cdOrigin(int x, int y);

/* clipping */
int   cdClip(int mode);
void  cdClipArea(int xmin, int xmax, int ymin, int ymax);
int * cdGetClipPoly(int *n);
int   cdGetClipArea(int *xmin, int *xmax, int *ymin, int *ymax);

/* clipping region */
int  cdPointInRegion(int x, int y);
void cdOffsetRegion(int x, int y);
void cdRegionBox(int *xmin, int *xmax, int *ymin, int *ymax);
int  cdRegionCombineMode(int mode);

/* primitives */
void cdPixel(int x, int y, long int color);
void cdMark(int x, int y);
void cdLine(int x1, int y1, int x2, int y2);
void cdBegin(int mode);
void cdVertex(int x, int y);
void cdEnd(void);
void cdRect(int xmin, int xmax, int ymin, int ymax);
void cdBox(int xmin, int xmax, int ymin, int ymax);
void cdArc(int xc, int yc, int w, int h, double angle1, double angle2);
void cdSector(int xc, int yc, int w, int h, double angle1, double angle2);
void cdChord(int xc, int yc, int w, int h, double angle1, double angle2);
void cdText(int x, int y, char *s);


/* attributes */
long cdBackground(long int color);
long cdForeground(long int color);
int  cdBackOpacity(int opacity);
int  cdWriteMode(int mode);
int  cdLineStyle(int style);
void cdLineStyleDashes(int* dashes, int count);
int  cdLineWidth(int width);
int  cdLineJoin(int join);
int  cdLineCap(int cap);
int  cdInteriorStyle(int style);
int  cdHatch(int style);
void cdStipple(int w, int h, unsigned char *stipple);
unsigned char* cdGetStipple(int* n, int* m);
void   cdPattern(int w, int h, long int *pattern);
long*  cdGetPattern(int* n, int* m);
int    cdFillMode(int mode);
void   cdFont(int type_face, int style, int size);
void   cdGetFont(int *type_face, int *style, int *size);
char*  cdNativeFont(char* font);
int    cdTextAlignment(int alignment);
double cdTextOrientation(double angle);
int    cdMarkType(int type);
int    cdMarkSize(int size);


/* vector text */
void cdVectorText(int x, int y, char * s);
void cdMultiLineVectorText(int x, int y, char * s);


/* vector text attributes */
char *cdVectorFont(char *file);
void cdVectorTextDirection(int x1, int y1, int x2, int y2);
double* cdVectorTextTransform(double* matrix);
void cdVectorTextSize(int size_x, int size_y, char *s);
int  cdVectorCharSize(int size);


/* vector text properties */
void cdGetVectorTextSize(char * s, int *x, int *y);
void cdGetVectorTextBounds(char *s, int x, int y, int *rect);


/* properties */
void cdFontDim(int *max_width, int *height, int *ascent, int *descent);
void cdTextSize(char *s, int *width, int *height);
void cdTextBox(int x, int y, char *s, int *xmin, int *xmax, int *ymin, int *ymax);
void cdTextBounds(int x, int y, char *s, int *rect);
int  cdGetColorPlanes (void);


/* color */
long int cdEncodeColor(unsigned char red, unsigned char green, unsigned char blue);
void cdDecodeColor(long int color, unsigned char *red, unsigned char *green, unsigned char *blue);
unsigned char cdDecodeAlpha(long int color);
long int cdEncodeAlpha(long int color, unsigned char alpha);
void cdPalette(int n, long int *palette, int mode);

#define cdReserved(_) (unsigned char)( ((_) >> 24) & 0xFF )
#define cdRed(_)      (unsigned char)( ((_) >> 16) & 0xFF )
#define cdGreen(_)    (unsigned char)( ((_) >>  8) & 0xFF )
#define cdBlue(_)     (unsigned char)( ((_) >>  0) & 0xFF )


/* client images */
void cdGetImageRGB(unsigned char *r, unsigned char *g, unsigned char *b, int x, int y, int w, int h);
void cdPutImageRectRGB(int iw, int ih, unsigned char *r, unsigned char *g, unsigned char *b, int x, int y, int w, int h, int xmin, int xmax, int ymin, int ymax);
void cdPutImageRectRGBA(int iw, int ih, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *a, int x, int y, int w, int h, int xmin, int xmax, int ymin, int ymax);
void cdPutImageRectMap(int iw, int ih, unsigned char *index, long int *colors, int x, int y, int w, int h, int xmin, int xmax, int ymin, int ymax);
void cdRGB2Map(int width, int height, unsigned char *red, unsigned char *green, unsigned char *blue, unsigned char *map_data, int pal_size, long *color);

/* defined for backward compatibility */
#define cdPutImageRGB(iw, ih, r, g, b, x, y, w, h) cdPutImageRectRGB((iw), (ih), (r), (g), (b), (x), (y), (w), (h), 0, 0, 0, 0)
#define cdPutImageRGBA(iw, ih, r, g, b, a, x, y, w, h) cdPutImageRectRGBA((iw), (ih), (r), (g), (b), (a), (x), (y), (w), (h), 0, 0, 0, 0)
#define cdPutImageMap(iw, ih, index, colors, x, y, w, h) cdPutImageRectMap((iw), (ih), (index), (colors), (x), (y), (w), (h), 0, 0, 0, 0)
#define cdPutImage(image, x, y) cdPutImageRect((image), (x), (y), 0, 0, 0, 0)


/* server images */
void *cdCreateImage(int w, int h);
void cdGetImage(void* image, int x, int y);
void cdPutImageRect(void* image, int x, int y, int xmin, int xmax, int ymin, int ymax);
void cdKillImage(void* image);
void cdScrollArea(int xmin, int xmax, int ymin, int ymax, int dx, int dy);


/* client images using bitmap structure */
typedef struct _cdBitmap {
  int w;
  int h;
  int type;
  void *data;
} cdBitmap;

cdBitmap* cdCreateBitmap(int w, int h, int type);
cdBitmap* cdInitBitmap(int w, int h, int type, ...);
void cdKillBitmap(cdBitmap* image);
unsigned char* cdBitmapGetData(cdBitmap* image, int dataptr);
void cdBitmapSetRect(cdBitmap* image, int xmin, int xmax, int ymin, int ymax);
void cdPutBitmap(cdBitmap* image, int x, int y, int w, int h);
void cdGetBitmap(cdBitmap* image, int x, int y);
void cdBitmapRGB2Map(cdBitmap* image_rgb, cdBitmap* image_map);



/* CD Values */


#define CD_QUERY -1             /* query value */


enum {                        /* bitmap type */
 CD_RGB,                      /* these definitions are compatible with the IM library */
 CD_MAP,
 CD_RGBA = 0x100 
};

enum {                         /* bitmap data */
 CD_IRED,
 CD_IGREEN,
 CD_IBLUE,
 CD_IALPHA,
 CD_INDEX,
 CD_COLORS
};

enum {                          /* status report */
 CD_ERROR = -1,
 CD_OK    =  0
};

enum {                          /* clip mode */
 CD_CLIPOFF,
 CD_CLIPAREA,
 CD_CLIPPOLYGON,
 CD_CLIPREGION
};

enum {                          /* region combine mode */
 CD_UNION,
 CD_INTERSECT,
 CD_DIFFERENCE,
 CD_NOTINTERSECT
};

enum {                          /* polygon mode (begin...end) */
 CD_FILL,
 CD_OPEN_LINES,
 CD_CLOSED_LINES,
 CD_CLIP,
 CD_BEZIER,
 CD_REGION
};

#define CD_POLYCUSTOM 10

enum {                          /* fill mode */
 CD_EVENODD,
 CD_WINDING
};

enum {                          /* line join  */
 CD_MITER,
 CD_BEVEL,
 CD_ROUND
};  

enum {                          /* line cap  */
 CD_CAPFLAT,  
 CD_CAPSQUARE,
 CD_CAPROUND
};  

enum {                          /* background opacity mode */
 CD_OPAQUE,
 CD_TRANSPARENT
};

enum {                          /* write mode */
 CD_REPLACE,
 CD_XOR,
 CD_NOT_XOR
};

enum {                          /* color allocation mode (palette) */
 CD_POLITE,
 CD_FORCE
};

enum {                          /* line style */
 CD_CONTINUOUS,
 CD_DASHED,
 CD_DOTTED,
 CD_DASH_DOT,
 CD_DASH_DOT_DOT,
 CD_CUSTOM
};

enum {                          /* marker type */
 CD_PLUS,
 CD_STAR,
 CD_CIRCLE,
 CD_X,
 CD_BOX,
 CD_DIAMOND,
 CD_HOLLOW_CIRCLE,
 CD_HOLLOW_BOX,
 CD_HOLLOW_DIAMOND
};

enum {                          /* hatch type */
 CD_HORIZONTAL,
 CD_VERTICAL,
 CD_FDIAGONAL,
 CD_BDIAGONAL,
 CD_CROSS,
 CD_DIAGCROSS
};

enum {                          /* interior style */
 CD_SOLID,
 CD_HATCH,
 CD_STIPPLE,
 CD_PATTERN,
 CD_HOLLOW
};

enum {                          /* text alignment */
 CD_NORTH,
 CD_SOUTH,
 CD_EAST,
 CD_WEST,
 CD_NORTH_EAST,
 CD_NORTH_WEST,
 CD_SOUTH_EAST,
 CD_SOUTH_WEST,
 CD_CENTER,
 CD_BASE_LEFT,
 CD_BASE_CENTER,
 CD_BASE_RIGHT
};

enum {                          /* type face */
 CD_SYSTEM,
 CD_COURIER,
 CD_TIMES_ROMAN,
 CD_HELVETICA,
 CD_NATIVE
};

enum {                          /* style */
 CD_PLAIN,
 CD_BOLD,
 CD_ITALIC,
 CD_BOLD_ITALIC
};

enum {                          /* font size */
 CD_SMALL    =  8,
 CD_STANDARD = 12,
 CD_LARGE    = 18
};


/* Canvas Capabilities */
#define CD_CAP_NONE             0x00000000
#define CD_CAP_FLUSH            0x00000001
#define CD_CAP_CLEAR            0x00000002
#define CD_CAP_PLAY             0x00000004
#define CD_CAP_YAXIS            0x00000008
#define CD_CAP_CLIPAREA         0x00000010
#define CD_CAP_CLIPPOLY         0x00000020
#define CD_CAP_MARK             0x00000040
#define CD_CAP_RECT             0x00000080
#define CD_CAP_VECTORTEXT       0x00000100
#define CD_CAP_IMAGERGB         0x00000200
#define CD_CAP_IMAGERGBA        0x00000400
#define CD_CAP_IMAGEMAP         0x00000800
#define CD_CAP_GETIMAGERGB      0x00001000
#define CD_CAP_IMAGESRV         0x00002000
#define CD_CAP_BACKGROUND       0x00004000
#define CD_CAP_BACKOPACITY      0x00008000
#define CD_CAP_WRITEMODE        0x00010000
#define CD_CAP_LINESTYLE        0x00020000
#define CD_CAP_LINEWITH         0x00040000
#define CD_CAP_WD               0x00080000
#define CD_CAP_HATCH            0x00100000
#define CD_CAP_STIPPLE          0x00200000
#define CD_CAP_PATTERN          0x00400000
#define CD_CAP_FONT             0x00800000
#define CD_CAP_FONTDIM          0x01000000
#define CD_CAP_TEXTSIZE         0x02000000
#define CD_CAP_TEXTORIENTATION  0x04000000
#define CD_CAP_PALETTE          0x08000000
#define CD_CAP_LINECAP          0x10000000
#define CD_CAP_LINEJOIN         0x20000000
#define CD_CAP_REGION           0x40000000
#define CD_CAP_CHORD            0x80000000
#define CD_CAP_ALL              0xFFFFFFFF


/* cdPlay definitions */
#define CD_SIZECB 0        /* size callback */
typedef int(*cdSizeCB)(cdContext *ctx, int w, int h, double w_mm, double h_mm);
#define CD_ABORT 1
#define CD_CONTINUE 0


/* simulation flags */
#define CD_SIM_NONE         0x0000
#define CD_SIM_CLIPAREA     0x0001
#define CD_SIM_CLIPPOLY     0x0002
#define CD_SIM_TEXT         0x0004
#define CD_SIM_MARK         0x0008
#define CD_SIM_LINE         0x0010
#define CD_SIM_RECT         0x0020
#define CD_SIM_ARC          0x0040
#define CD_SIM_POLYLINE     0x0080
#define CD_SIM_BOX          0x0100
#define CD_SIM_SECTOR       0x0200
#define CD_SIM_POLYGON      0x0400
#define CD_SIM_WD           0x0800 
#define CD_SIM_VECTORTEXT   0x1000
#define CD_SIM_CHORD        0x2000
#define CD_SIM_ALL          0xFFFF

#define CD_SIM_LINES (CD_SIM_LINE | CD_SIM_RECT | CD_SIM_ARC | CD_SIM_POLYLINE)
#define CD_SIM_FILLS (CD_SIM_BOX | CD_SIM_SECTOR | CD_SIM_POLYGON)
#define CD_SIM_CLIP  (CD_SIM_CLIPAREA | CD_SIM_CLIPPOLY)


/* some predefined colors for convenience */
#define  CD_RED           0xFF0000L   /* 255,  0,  0 */
#define  CD_DARK_RED      0x800000L   /* 128,  0,  0 */
#define  CD_GREEN         0x00FF00L   /*   0,255,  0 */
#define  CD_DARK_GREEN    0x008000L   /*   0,128,  0 */
#define  CD_BLUE          0x0000FFL   /*   0,  0,255 */
#define  CD_DARK_BLUE     0x000080L   /*   0,  0,128 */

#define  CD_YELLOW        0xFFFF00L   /* 255,255,  0 */
#define  CD_DARK_YELLOW   0x808000L   /* 128,128,  0 */
#define  CD_MAGENTA       0xFF00FFL   /* 255,  0,255 */
#define  CD_DARK_MAGENTA  0x800080L   /* 128,  0,128 */
#define  CD_CYAN          0x00FFFFL   /*   0,255,255 */
#define  CD_DARK_CYAN     0x008080L   /*   0,128,128 */

#define  CD_WHITE         0xFFFFFFL   /* 255,255,255 */
#define  CD_BLACK         0x000000L   /*   0,  0,  0 */

#define  CD_DARK_GRAY     0x808080L   /* 128,128,128 */
#define  CD_GRAY          0xC0C0C0L   /* 192,192,192 */


/* some conversion factors */
#define CD_MM2PT     2.834645669   /* milimeters to points (pt = CD_MM2PT * mm) */
#define CD_RAD2DEG  57.295779513   /* radians to degrees (rad = CD_RAD2DEG * deg) */
#define CD_DEG2RAD  0.01745329252

/* OLD definitions, defined for backward compatibility */
#define CD_CLIPON       CD_CLIPAREA   
#define CD_CENTER_BASE  CD_BASE_CENTER
#define CD_LEFT_BASE    CD_BASE_LEFT
#define CD_RIGHT_BASE   CD_BASE_RIGHT
#define CD_ITALIC_BOLD  CD_BOLD_ITALIC
#define cdScrollImage cdScrollArea
#define cdCanvas2Raster(x, y) {(void)x; cdUpdateYAxis(y);}



#ifdef __cplusplus
}
#endif


#endif /* ifndef CD_H */

