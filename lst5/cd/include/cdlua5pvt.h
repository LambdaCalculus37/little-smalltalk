#ifndef _CDLUA5_PRIV_
#define _CDLUA5_PRIV_

/***************************************************************************\
* CDLua5 private data structure definitions. Used by libraries tighly       *
* integrated with CDLua5, such as IMLua5.                                   *
* Used by driver creators.                                                  *
* You must include "cd.h" before using this header.                         *
\***************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************\
* The userdata meta tables References                        *
**************************************************************/

/* there is no COLOR_TAG because color_tag is a lightuserdata */
#define CANVAS_TAG    "CDLUA_CANVAS_TAG"
#define STATE_TAG     "CDLUA_STATE_TAG"
#define BITMAP_TAG    "CDLUA_BITMAP_TAG"
#define IMAGE_TAG     "CDLUA_IMAGE_TAG"
#define IMAGERGB_TAG  "CDLUA_IMAGERGB_TAG"
#define IMAGERGBA_TAG "CDLUA_IMAGERGBA_TAG"
#define STIPPLE_TAG   "CDLUA_STIPPLE_TAG"
#define PATTERN_TAG   "CDLUA_PATTERN_TAG"
#define PALETTE_TAG   "CDLUA_PALETTE_TAG"
#define IMAGEMAP_TAG  "CDLUA_IMAGEMAP_TAG"
#define CHANNEL_TAG   "CDLUA_CHANNEL_TAG"


/* context management */

typedef struct _cdCallbackLUA {
  int lock;
  char *name;
  cdCallback func;
} cdCallbackLUA;

typedef struct _cdContextLUA {
  int id;
  char *name;
  cdContext* (*ctx)(void);
  void* (*checkdata)(lua_State * L,int param);
  cdCallbackLUA* cb_list;
  int cb_n;
} cdContextLUA;

typedef struct _cdlua_State {
  cdCanvas *void_canvas;            /* the VOID canvas to avoid a NULL active canvas */
  cdContextLUA* cdlua_drivers[50];  /* store the registered drivers, map integer values to cdContext */
  int cdlua_numdrivers;
} cdlua_State;

void cdlua_addcontext(lua_State* L, cdlua_State* cdL, cdContextLUA* luactx);
cdlua_State* cdlua_getstate(lua_State * L);


/* utility for cdPlay callbacks */
lua_State* cdlua_getplaystate(void);


/* tag management */

typedef struct _canvas_t {
  cdCanvas *cd_canvas;
} canvas_t;

typedef struct _state_t {
  cdState *state;
} state_t;

typedef struct _stipple_t {
  unsigned char *value;
  int width;
  int height;
  long int size;
} stipple_t;

typedef struct _pattern_t {
  long int *color;
  int width;
  int height;
  long int size;
} pattern_t;

/* this is the same declaration used in the IM toolkit for imPalette in Lua */
typedef struct _palette_t {
  long int *color;
  int size;
} palette_t;

typedef struct _image_t {
  void *cd_image;
} image_t;

typedef struct _imagergb_t {
  unsigned char *red;
  unsigned char *green;
  unsigned char *blue;
  int width;
  int height;
  long int size;
} imagergb_t;

typedef struct _imagergba_t {
  unsigned char *red;
  unsigned char *green;
  unsigned char *blue;
  unsigned char *alpha;
  int width;
  int height;
  long int size;
} imagergba_t;
         
typedef struct _imagemap_t {
  unsigned char *index;
  int width;
  int height;
  long int size;
} imagemap_t;

typedef struct _channel_t {
  unsigned char *value;
  long int size;
} channel_t;

typedef struct _bitmap_t {
  cdBitmap *image;
} bitmap_t;


#ifdef __cplusplus
}
#endif

#endif /* ifndef _CDLUA_PRIV_ */
