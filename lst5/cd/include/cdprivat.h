#ifndef CDPRIVATE_H
#define CDPRIVATE_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _CD_POLY_BLOCK 100

typedef struct _cdPoint 
{
  int x;     
  int y; 
} cdPoint; 

typedef struct _wdPoint 
{
  double x;     
  double y; 
} wdPoint; 

typedef struct _cdServerImage
{
  int w, h;
  void* img;
  void   (*GetImage)(void* image, int x, int y);
  void   (*PutImageRect)(void* image, int x, int y, int xmin, int xmax, int ymin, int ymax);
  void   (*KillImage)(void* image);
} cdServerImage;

typedef struct _cdAttribute
{
  char *name;
  void (*set)(char* data);
  char* (*get)(void);
} cdAttribute; 

typedef struct _cdPrivateCanvas
{
  /* see comments in "CD.C" at set_default_func */
  void   (*Flush)(void);
  void   (*Clear)(void);
  void   (*Pixel) (int x, int y, long int color);
  void   (*Mark)(int x, int y);
  void   (*Line)(int x1, int y1, int x2, int y2);
  void   (*Poly)(int mode, cdPoint* points, int n);
  void   (*Rect)(int xmin, int xmax, int ymin, int ymax);
  void   (*Box)(int xmin, int xmax, int ymin, int ymax);
  void   (*Arc)(int xc, int yc, int w, int h, double angle1, double angle2);
  void   (*Sector)(int xc, int yc, int w, int h, double angle1, double angle2);
  void   (*Chord)(int xc, int yc, int w, int h, double angle1, double angle2);
  void   (*Text)(int x, int y, char *s);
  void   (*FontDim)(int *max_width, int *height, int *ascent, int *descent);
  void   (*TextSize)(char *s, int *width, int *height);
  void   (*PutImageRectRGB)(int iw, int ih, unsigned char *r, unsigned char *g, unsigned char *b, int x, int y, int w, int h, int xmin, int xmax, int ymin, int ymax);
  void   (*PutImageRectMap)(int iw, int ih, unsigned char *index, long int *colors, int x, int y, int w, int h, int xmin, int xmax, int ymin, int ymax);
  void   (*ScrollArea)(int xmin, int xmax, int ymin, int ymax, int dx, int dy);
  void   (*VectorText)(int x, int y, char * s);
  void   (*MultiLineVectorText)(int x, int y, char * s);
  void   (*wMark)(double x, double y);
  void   (*wLine)(double x1, double y1, double x2, double y2);
  void   (*wPoly)(int mode, wdPoint* points, int n);
  void   (*wRect)(double xmin, double xmax, double ymin, double ymax);
  void   (*wBox)(double xmin, double xmax, double ymin, double ymax);
  void   (*wArc)(double xc, double yc, double w, double h, double angle1, double angle2);
  void   (*wSector)(double xc, double yc, double w, double h, double angle1, double angle2);
  void   (*wChord)(double xc, double yc, double w, double h, double angle1, double angle2);
  void   (*wText)(double x, double y, char *s);
  void   (*wVectorText)(double x, double y, char * s);
  void   (*wMultiLineVectorText)(double x, double y, char * s);

  int    (*Clip)(int mode);
  void   (*ClipArea)(int* xmin, int* xmax, int* ymin, int* ymax);
  void   (*NewRegion)(void);
  int    (*PointInRegion)(int x, int y);
  void   (*OffsetRegion)(int x, int y);
  void   (*RegionBox)(int *xmin, int *xmax, int *ymin, int *ymax);
  int    (*BackOpacity)(int opacity);
  int    (*WriteMode)(int mode);
  int    (*MarkType)(int type);
  int    (*MarkSize)(int size);
  int    (*LineStyle)(int style);
  int    (*LineWidth)(int width);
  int    (*LineJoin)(int join);
  int    (*LineCap)(int cap);
  int    (*InteriorStyle)(int style);
  int    (*Hatch)(int style);
  void   (*Stipple)(int w, int h, unsigned char *stipple);
  void   (*Pattern)(int w, int h, long int *pattern);
  void   (*Font)(int *type_face, int *style, int *size);
  void   (*NativeFont)(char* font);
  int    (*TextAlignment)(int alignment);
  double (*TextOrientation)(double angle);
  void   (*Palette)(int n, long int *palette, int mode);
  long int (*Background)(long int color);
  long int (*Foreground)(long int color);
  void   (*PutImageRectRGBA)(int iw, int ih, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *a, int x, int y, int w, int h, int xmin, int xmax, int ymin, int ymax);
  void   (*GetImageRGB)(unsigned char *r, unsigned char *g, unsigned char *b, int x, int y, int w, int h);
  void*  (*CreateImage)(int w, int h);
  void   (*GetImage)(void* image, int x, int y);
  void   (*PutImageRect)(void* image, int x, int y, int xmin, int xmax, int ymin, int ymax);
  void   (*KillImage)(void* image);
  void   (*Window)(double xmin, double xmax, double  ymin, double ymax);
  void   (*Viewport)(int xmin, int xmax, int ymin, int ymax);
  void   (*wClipArea)(double *xmin, double *xmax, double *ymin, double *ymax);
  char*  (*VectorFont)(char *file);
  void   (*VectorTextDirection)(int x1, int y1, int x2, int y2);
  void   (*VectorTextTransform)(double* matrix);
  void   (*VectorTextSize)(int size_x, int size_y, char *s);
  void   (*VectorCharSize)(int size);
  void   (*wVectorTextDirection)(double x1, double y1, double x2, double y2);
  void   (*wVectorTextSize)(double size_x, double size_y, char *s);
  void   (*wVectorCharSize)(double size);

  void   (*KillCanvas)(void *cnv); /* cnv here is the context_canvas */
  int    (*Activate)(void *cnv);
  int    (*Update)(void);
  void   (*Deactivate)(void);
  void   (*wdCall)(int usage);   /* Called before any WD function call with usage=1, if a CD call usage=0, 
                                    But it is called only once in a sequece of WD or CD functions.
                                    if wdWindow or wdViewport were changed it is called if during a WD sequence. */

  /* the driver must update these, when the canvas is created and
     whenever the canvas change its size or bpp. */
  int w,h;            /* size in pixels */              /****  pixel =   mm   * res  ****/
  double w_mm, h_mm;  /* size in mm */                  /****   mm   =  pixel / res  ****/
  double xres, yres;  /* resolution in pixels/mm */     /****   res  =  pixel / mm   ****/
  int bpp;            /* number of bits per pixel */
  int invert_yaxis;   /* the driver has the y axis from top to bottom */

  /* clipping attributes */
  int clip_mode;
  int clip_xmin, clip_xmax, clip_ymin, clip_ymax;
  int clip_poly_n, clip_wpoly_n;
  cdPoint* clip_poly;
  wdPoint* clip_wpoly;

  /* clipping region attributes */
  int new_region;
  int combine_mode;
  
  /* color attributes */
  long int foreground, background;
  int back_opacity, write_mode;

  /* primitive attributes */
  int mark_type, mark_size;
  int line_style, line_width;
  int line_cap, line_join;
  int* line_dashes;
  int line_dashes_count;
  int interior_style, hatch_style;
  int fill_mode;
  int font_type_face, font_style, font_size;
  int text_alignment;
  double text_orientation;

  /* attributes that do not necessarilly match the actual attribute */
  char native_font[1024];
  int pattern_w, pattern_h, pattern_size;
  long int* pattern;
  int stipple_w, stipple_h, stipple_size;
  unsigned char* stipple;

  /* origin */
  int origin;
  int origin_x, origin_y;

  /* last polygon */
  int poly_mode, poly_n, poly_size, wpoly_size;
  cdPoint* poly;
  wdPoint* wpoly;
  int wd_poly;

  /* simulation flags */
  int sim_mode;
  int sim_poly;
  void* sim_data;

  /* WC */
  int using_wd;
  double s, sx, tx, sy, ty;            /* Transformacao Window -> Viewport (scale+translation)*/
  double win_xmin, win_xmax, win_ymin, win_ymax;  /* Area da Window em WC */
  int view_xmin, view_xmax, view_ymin, view_ymax;     /* Area do Viewport em pixels */

  /* vector font */
  void* vector_font_data;

  cdAttribute* attrib_list[100];
  int attrib_n;

  void* context_canvas;
  cdContext* context;
  cdCanvas* canvas;
} cdPrivateCanvas;


typedef struct _cdPrivateContext
{
  unsigned long caps;
  void (*CreateCanvas)(cdPrivateCanvas* cnv, void *data);
  void (*InitTable)(cdPrivateCanvas* cnv);
  int  (*Play)(int xmin, int xmax, int ymin, int ymax, void *data); /* can be NULL */
  int  (*RegisterCallback)(int cb, cdCallback func);                /* can be NULL */
} cdPrivateContext;


/***************/
/* attributes  */
/***************/

void cdRegisterAttribute(cdPrivateCanvas *private_canvas, cdAttribute* attrib);

/***************/
/* vector font */
/***************/
void* cdCreateVectorFont(void);
void cdKillVectorFont(void* vector_font_data);
void cdActivateVectorFont(cdPrivateCanvas* cnv);


/**********/
/*   WC   */
/**********/
void wdCall(int usage);
void wdSetDefaults(cdPrivateCanvas* cnv);
void wdUpdateActive(cdPrivateCanvas* cnv);


/*************/
/* utilities */
/*************/
void cdMakeStretchTable(int dx, int p, int *x);
int cdCalcZoom(int canvas_size, int cnv_rect_pos, int cnv_rect_size, 
               int *new_cnv_rect_pos, int *new_cnv_rect_size, 
               int img_rect_pos, int img_rect_size, 
               int *new_img_rect_pos, int *new_img_rect_size, int is_horizontal);
int cdInvertYAxis(int y);
int cdGetFileName(const char* strdata, char* filename);
void cdTextRotatePoint(int x, int y, int cx, int cy, int *rx, int *ry, double sin_teta, double cos_teta);
void cdTextTranslatePoint(int x, int y, int w, int h, int baseline, int *rx, int *ry);

#define CD_ALPHA_BLEND(_src,_dst,_alpha) (((_src) * (_alpha) + (_dst) * (255 - (_alpha))) / 255)

/**************/
/* simulation */
/**************/
void* cdCreateSimulation(cdPrivateCanvas* cnv);
void cdKillSimulation(void* sim_data);
void cdActivateSim(cdPrivateCanvas* cnv);
void cdSimUpdateFillLine(void);
void cdSimInitText(void* sim_data);
void cdSimPolyBezier(cdPoint* points, int n);

/* retornam o estado de visible=0 ou visible=1 */
int  cdSimClipPointInBox(int x, int y);
int  cdSimClipLineInBox(int* x1, int* y1, int* x2, int* y2); /* atualiza a linha se visible */
int  cdSimClipBoxInBox(int *xmin, int *xmax, int *ymin, int *ymax); /* atualiza o box se visible */
int  cdSimClipTextInBox(int x, int y,char * text);
int  cdSimClipPointInPoly(int x, int y);
void cdSimClipLineInPoly(int x1, int y1, int x2, int y2); /* clipa linha em poligono e desenha segmentos visiveis. */

void cdSimFontDimEx(int *max_width, int *height, int *ascent, int *descent);
void cdSimTextSizeEx(char *s, int *width, int *height);

void cdSimMark(int x, int y);
void cdSimRect(int xmin, int xmax, int ymin, int ymax);
void cdSimBox(int xmin, int xmax, int ymin, int ymax);
void cdSimLine(int x1, int y1, int x2, int y2);
void cdSimArc(int xc, int yc, int width, int height, double angle1, double angle2);
void cdSimSector(int xc, int yc, int width, int height, double angle1, double angle2);
void cdSimChord(int xc, int yc, int width, int height, double angle1, double angle2);
void cdSimPoly(int mode, cdPoint* points, int n);
void cdSimText(int x, int y, char *s);
void cdSimNativeFont(char* font_data);
void cdSimFont(int *type_face, int *style, int *size);
void cdSimFontDim(int *max_width, int *height, int *ascent, int *descent);
void cdSimTextSize(char *s, int *width, int *height);
void cdSimPutImageRectRGBA(int iw, int ih, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *a, int x, int y, int w, int h, int xmin, int xmax, int ymin, int ymax);

#ifdef __cplusplus
}
#endif

#endif
