#define LITNUM 257
#define LITFNUM 258
#define LITCHAR 259
#define LITSTR 260
#define LITSYM 261
#define CLASS 262
#define ASSIGN 263
#define BINARY 264
#define PRIMITIVE 265
#define PSEUDO 266
#define UPPERCASEVAR 267
#define LOWERCASEVAR 268
#define COLONVAR 269
#define KEYWORD 270
#define LP 271
#define RP 272
#define LB 273
#define RB 274
#define PERIOD 275
#define BAR 276
#define MBAR 277
#define SEMI 278
#define UPARROW 279
#define PS 280
#define MINUS 281
#define PE 282

typedef union {
	struct litlist 		*a;
	struct blockstruct 	*b;
	char 			*c;
	struct exprstruct 	*e;
	int			 i;
	struct keylist 		*k;
	struct classstruct 	*l;
	struct methodstruct 	*m;
	struct objstruct 	*o;
	/* enum pseuvars */ int	 p;
	struct primlist 	*r;
	struct statestruct 	*s;
	struct litstruct 	*t;
	struct primstruct 	*u;
	} YYSTYPE;
extern YYSTYPE yylval;
