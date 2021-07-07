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

#line 26 "parser.y"
#include "env.h"
#include "drive.h"
#include "parser.h"

#line 31 "parser.y"
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
	/* enum pseuvars */ int  p;
	struct primlist 	*r;
	struct statestruct 	*s;
	struct litstruct 	*t;
	struct primstruct 	*u;
	} YYSTYPE;

#line 49 "parser.y"
extern struct blockstruct *mkblock();
extern struct classstruct *mkclass();
extern struct varstruct *mkvar(), *addvlist(), *invlist();
extern struct methodstruct *mkmethod();
extern struct exprstruct *mkexpr(), *mkkey();
extern struct keylist *mkklist();
extern struct statestruct *mkstate();
extern struct objstruct *mkobj();
extern struct primstruct *mkprim();
extern struct primlist *addprim();
extern struct litstruct *mklit();
extern struct litlist *addlit();
extern char *bincat();

struct varstruct *instvars;
struct varstruct *contextvars;

int bytetop = 0;
uchar bytearray[1000];

YYSTYPE e;
int errorcount = 0;
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern short yyerrflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
YYSTYPE yylval, yyval;
#define YYERRCODE 256

#line 348 "parser.y"

#include <stdio.h> 

char *filename;
FILE *fp;
FILE *ofd;
FILE *fdout;	/* added WMK */

#include "lex.yy.c" 

main(argc, argv) 
int argc;
char **argv;
{	
	long status;
	if (argc < 2) quiter("parser: wrong number of arguments");
	filename = argv[1];
	fp = fopen(filename, "r");
	if (fp == NULL) {
		yerr("cannot open input file %s", filename);
		quiter("parser quits");
		}
/* added by WMK */
	if (argc==3) {
		ofd = fopen(argv[2],"w");
		if (ofd==NULL) {
			yerr("Cannot open output file %s", argv[2]);
			quiter("parser quits");
		}
	}

	else ofd = stdout;
	status = (long)yyparse();
	if (argc==3) fclose(ofd);
	exit(status);
}

quiter(s) char *s; {
/* WMK changed this--was fprintf(stderr..) */
	printf("%s\n", s); exit(10);
}

yywarn(s, v) char *s, *v; {
/* WMK again */
	printf("%s: line %d: Warning ", filename, linenum);
	printf(s, v);
	printf("\n");
}

yyerror(s) char *s; {yerr(s, "");}

yerr(s, v) 
char *s, *v; 
{
/* WMK changed */
	printf("%s: line %d: ", filename, linenum);
	printf(s, v);
	printf("\n");
	if (errorcount++ > 10) quiter("too many errors, goodby");
}

expect(str) char *str;
{	char buffer[100];

	sprintf(buffer,"Expected %%s found %s", yytext);
	yerr(buffer, str);
}

int yywrap() { return(1);}

char *alloc(size) int size;		/* allocate a block of storage */
{  char *p, *malloc();

	p = malloc( (unsigned) size);
	if (p == (char *) 0) yyerror("out of free space");
	return(p);
}

char *bincat(s1, s2)
char *s1, *s2;
{	char *p;

	p = alloc(strlen(s1) + strlen(s2) + 1);
	strcpy(p, s1);
	strcat(p, s2);
	return(p);
}
short yyexca[] = {
	-1, 1,
	0, -1,
	-2, 0,
	};
#define YYNPROD 119
#define YYLAST 309
short yyact[]={

  81,  79,  75,  76,  77, 127,  92,  25, 157, 141,
 124, 123, 126, 125, 131, 156, 140, 155,  36,  26,
 152,  37,  28, 130, 132,  29,  81,  79,  75,  76,
  77, 127,  89,  25, 154, 149, 124, 123, 126, 125,
 131, 120,  10, 119,  34,  26, 114,  40,  28, 130,
 132,  29,  81,  79,  75,  76,  77,  15, 105,	9,
  71,  65,  14, 116,  32,  33,  67, 146,  72, 107,
 106,  35, 107,  43,  98,  78,  80, 147,  81,  79,
  75,  76,  77,  15,  48,  42,  71,  65,  14,  54,
  99,  84,  67,  91,  72, 143,  47, 109, 108, 102,
 138,  78,  80,  81,  79,  75,  76,  77,  15,  13,
   6,  71,  65,  14,  54,  15,   5,  67, 136,  72,
  14,  69,  62, 101,  58,  52,  78,  80,  81,  79,
  75,  76,  77,  15,  53,  60,  71,  65,  14,  54,
  24,  51,  67,  93,  72,  81,  79,  75,  76,  77,
  15,  78,  80,  71,  65,  14, 116,  31,  22,  67,
  83,  72,  94,  17, 129,  45,  25, 142,  78,  80,
  21,  20,  23,  25,  70,  41,  39,  25,  26,  95,
   2,  28,   7,  27,  29,  26,  34,  90,  28,  26,
  27,  29,  28,  34,  27,  29,  88,  46,  84,  44,
  20,  49, 100,  96,  86,  87,  32,  33,  30,	4,
  63,	8,   1,  32,  33,  12,  85,  66, 121,  64,
 117, 139,  97, 122, 135, 134, 113,  50, 133,  16,
 115, 112,   3, 118,  11,  19,  74, 103, 137, 144,
 110,  82, 104, 111,  38,  61,  59,  57,  55,  56,
  18,  73,  68, 145, 150,   0, 148,   0,   0,	0,
   0,	0,   0,	0, 128,	0,   0, 122,   0,   0,
 151,	0,   0, 153,   0,   0,   0,   0,   0,	0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,	0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,	0,
   0,   0,   0,   0,   0,   0,   0,   0, 128 };
short yypact[]={

-146,-146,-1000,-214,-147,-1000,-1000,-1000, -98,-1000,
-1000,-212,-198,-1000,-1000,-1000,-256,-1000,-212,-223,
-183,-1000,-1000,-183, -87,-1000,-1000,-1000,-1000,-1000,
-1000,-172,-1000,-1000,-1000,-1000,-1000, -98,-154,-177,
-183,-1000,-1000,-1000,-1000,-1000, -63,-1000,-1000,-1000,
-243,-1000,-129,-1000,-170,-272,-1000,-1000, -91, -91,
-194,-178,-1000,-1000,-1000,-1000,-1000,-129,-1000,-1000,
-1000,-158,-211,-1000,-1000,-1000,-1000,-1000,-201,-1000,
-160,-1000, -70,-1000,-1000,-1000,-1000,-1000,-1000,-154,
-1000,-129,-1000,-224,-112,-112,-224,-112,-1000,-1000,
-229,-231,-1000,-179,-260,-1000,-1000,-162,-1000,-1000,
-1000,-1000,-1000,-1000,-112,-194,-1000, -87,-194,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-204,-1000,-160,-205,-239,-179,-1000,-255,-129,-1000,
-1000,-1000,-240,-1000, -87,-257,-1000,-1000,-1000,-1000,
-1000,-267,-1000,-1000,-1000,-1000,-1000,-1000 };
short yypgo[]={

   0, 123, 252, 210, 162, 140, 251, 250, 249, 248,
 124, 135, 247, 246, 245, 244, 242, 241, 237, 236,
 235, 143, 234, 232, 163, 229, 122, 228, 227, 141,
 134, 225, 224, 118, 221, 219, 121, 218, 217, 212,
 180, 211, 209, 208, 157, 197, 196, 175, 160, 174,
 167, 164 };
short yyr1[]={

   0,  39,  39,  40,  41,  41,  23,  42,  42,  22,
  22,  22,   3,   3,  43,  43,  45,  45,  45,  25,
  25,  24,   7,	7,   7,	7,  20,  20,  47,  47,
  15,  15,  44,  44,  44,  17,  17,  48,  28,  28,
  46,  46,  29,  29,  30,  30,	9,   9,  12,  12,
  13,  13,  14,  14,   8,   8,  21,  21,  10,  10,
   4,   4,   5,   5,   5,   5,	5,  11,  11,  26,
  26,  26,  26,  26,  26,  26,  38,  27,  27,   2,
  18,  18,  16,  16,  31,  31,  33,  33,  34,  34,
  32,  32,  35,  35,  49,  36,  36,  36,  36,  36,
  36,	6,   6,  19,  19,  37,  37,  37,  37,  37,
  37,  37,  37,  51,  51,   1,	1,  50,  50 };
short yyr2[]={

   0,   1,   2,   4,   1,   1,   3,   1,   1,	1,
   2,   1,   1,   1,   0,   3,   1,   2,   1,   1,
   3,   4,   1,   2,   1,   1,   2,   3,   1,	1,
   0,   3,   1,   1,   1,   1,   2,   1,   1,	3,
   0,   1,   2,   1,   3,   1,   1,   1,   1,	2,
   1,   3,   2,   2,   1,   2,   2,   3,   1,	3,
   1,   2,   1,   1,   1,   1,   1,   1,   2,	1,
   1,   1,   1,   1,   3,   1,   4,   0,   2,	4,
   0,   2,   1,   2,   2,   1,   2,   1,   0,	1,
   2,   3,   1,   3,   2,   1,   1,   1,   1,	1,
   4,   1,   2,   1,   2,   1,   1,   1,   1,	1,
   1,   1,   3,   2,   1,   0,   2,   1,   2 };
short yychk[]={

-1000, -39, -40, -23, -42, 262, 256, -40, -41, 273,
 256, -22,  -3, 256, 267, 262, -25, -24,  -7, -20,
  -4, 268, 256, 270,  -5, 264, 276, 281, 279, 282,
 -43, -44, 276, 277, 256, 269, 274, 277, -15, -44,
 270, -47, 268, 256, -47,  -5, -45, 268, 256, -24,
 -28, -29, 279, -30, 268,  -9,  -8, -12, -10, -13,
 -11, -14, -26,  -3, -35, 266, -38, 271,  -2, -36,
 -49, 265, 273,  -6, -19, 259, 260, 261, 280, 258,
 281, 257, -17, -48, 268, -47, -44, 268, -46, 275,
 -30, 263, 278, -21,  -4, 270, -21,  -4, 268, 268,
 -30,  -1, 257, -18, -16, 269, 271, 273, 258, 257,
 -44, -48, -29, -30, 270, -11, 268, -10, -11, 272,
 272, -37, -36, 268, 267, 270, 269, 262,  -4, -51,
 280, 271, 281, -27, -31, -32, -33, -30, 279, -34,
 276, 269, -50, 257, -10,  -1, 271, 282, -26, 274,
 -33, -30, 275, -30, 274, 257, 272, 275 };
short yydef[]={

   0,  -2,   1,   0,   0,   7,   8,   2,   0,	4,
   5,  14,   9,  11,  12,  13,   0,  19,  30,  22,
   0,  24,  25,   0,  60,  62,  63,  64,  65,  66,
   6,   0,  32,  33,  34,  10,   3,   0,   0,   0,
   0,  23,  28,  29,  26,  61,   0,  16,  18,  20,
  40,  38,   0,  43,  70,  45,  46,  47,  54,  48,
  58,  50,  67,  69,  71,  72,  73,   0,  75,  92,
 115,   0,  80,  95,  96,  97,  98,  99,   0, 101,
   0, 103,   0,  35,  37,  27,  15,  17,  21,  41,
  42,   0,  52,  55,   0,   0,  49,   0,  68,  53,
   0,   0,  77,  88,   0,  82,  94,   0, 102, 104,
  31,  36,  39,  44,   0,  59,  70,  56,  51,  74,
  93, 116, 105, 106, 107, 108, 109, 110, 111, 115,
   0, 114,  64,   0,   0,  88,  85,  89,   0,  87,
  81,  83,   0, 117,  57,   0, 113,  76,  78,  79,
  84,  89,  90,  86, 100, 118, 112,  91 };
#ifndef lint
static char yaccpar_sccsid[] = "@(#)yaccpar	4.1	(Berkeley)	2/11/83";
#endif not lint

#
#define YYFLAG -1000
#define YYERROR goto yyerrlab
#define YYACCEPT return(0)
#define YYABORT return(1)

/*	parser for yacc output	*/

#ifdef YYDEBUG
int yydebug = 1; /* 1 for debugging */
#endif
YYSTYPE yyv[YYMAXDEPTH]; /* where the values are stored */
int yychar = -1; /* current input token number */
int yynerrs = 0;  /* number of errors */
short yyerrflag = 0;  /* error recovery flag */

yyparse() {

	short yys[YYMAXDEPTH];
	short yyj, yym;
	register YYSTYPE *yypvt;
	register short yystate, *yyps, yyn;
	register YYSTYPE *yypv;
	register short *yyxi;

	yystate = 0;
	yychar = -1;
	yynerrs = 0;
	yyerrflag = 0;
	yyps= &yys[-1];
	yypv= &yyv[-1];

 yystack:	 /* put a state and value onto the stack */

#ifdef YYDEBUG
	if( yydebug  ) printf( "state %d, char 0%o\n", yystate, yychar );
#endif
		if( ++yyps> &yys[YYMAXDEPTH] ) { yyerror( "yacc stack overflow" ); return(1); }
		*yyps = yystate;
		++yypv;
		*yypv = yyval;

 yynewstate:

	yyn = yypact[yystate];

	if( yyn<= YYFLAG ) goto yydefault; /* simple state */

	if( yychar<0 ) if( (yychar=yylex())<0 ) yychar=0;
	if( (yyn += yychar)<0 || yyn >= YYLAST ) goto yydefault;

	if( yychk[ yyn=yyact[ yyn ] ] == yychar ){ /* valid shift */
		yychar = -1;
		yyval = yylval;
		yystate = yyn;
		if( yyerrflag > 0 ) --yyerrflag;
		goto yystack;
		}

 yydefault:
	/* default state action */

	if( (yyn=yydef[yystate]) == -2 ) {
		if( yychar<0 ) if( (yychar=yylex())<0 ) yychar = 0;
		/* look through exception table */

		for( yyxi=yyexca; (*yyxi!= (-1)) || (yyxi[1]!=yystate) ; yyxi += 2 ) ; /* VOID */

		while( *(yyxi+=2) >= 0 ){
			if( *yyxi == yychar ) break;
			}
		if( (yyn = yyxi[1]) < 0 ) return(0);	/* accept */
		}

	if( yyn == 0 ){ /* error */
		/* error ... attempt to resume parsing */

		switch( yyerrflag ){

		case 0:	/* brand new error */

			yyerror( "syntax error" );
		yyerrlab:
			++yynerrs;

		case 1:
		case 2: /* incompletely recovered error ... try again */

			yyerrflag = 3;

			/* find a state where "error" is a legal shift action */

			while ( yyps >= yys ) {
				yyn = yypact[*yyps] + YYERRCODE;
				if( yyn>= 0 && yyn < YYLAST && yychk[yyact[yyn]] == YYERRCODE ){
					yystate = yyact[yyn];  /* simulate a shift of "error" */
					goto yystack;
					}
				yyn = yypact[*yyps];

				/* the current yyps has no shift onn "error", pop stack */

#ifdef YYDEBUG
				if( yydebug ) printf( "error recovery pops state %d, uncovers %d\n", *yyps, yyps[-1] );
#endif
				--yyps;
				--yypv;
				}

			/* there is no state on the stack with an error shift ... abort */

	yyabort:
			return(1);


		case 3:  /* no shift yet; clobber input char */

#ifdef YYDEBUG
			if( yydebug ) printf( "error recovery discards char %d\n", yychar );
#endif

			if( yychar == 0 ) goto yyabort; /* don't discard EOF, quit */
			yychar = -1;
			goto yynewstate;	/* try again in the same state */

			}

		}

	/* reduction by production yyn */

#ifdef YYDEBUG
		if( yydebug ) printf("reduce %d\n",yyn);
#endif
		yyps -= yyr2[yyn];
		yypvt = yypv;
		yypv -= yyr2[yyn];
		yyval = yypv[1];
		yym=yyn;
			/* consult goto table to find next state */
		yyn = yyr1[yyn];
		yyj = yypgo[yyn] + *yyps + 1;
		if( yyj>=YYLAST || yychk[ yystate = yyact[yyj] ] != -yyn ) yystate = yyact[yypgo[yyn]];
		switch(yym){
			
case 3:
#line 103 "parser.y"
{if (errorcount == 0) genclass(yypvt[-3].l, yypvt[-1].m);} break;
case 5:
#line 107 "parser.y"
{if ((yytext[0] == ':') ||
									  isalpha(yytext[0])) expect(":SuperClass");
								 else expect("open brace [");} break;
case 6:
#line 112 "parser.y"
{yyval.l = yypvt[-1].l;} break;
case 8:
#line 116 "parser.y"
{expect("keyword Class");} break;
case 9:
#line 119 "parser.y" 
{yyval.l = mkclass(yypvt[-0].c, (char *) 0);} break;
case 10:
#line 120 "parser.y" 
{yyval.l = mkclass(yypvt[-1].c, yypvt[-0].c);} break;
case 11:
#line 121 "parser.y" 
{expect("Classname :Superclass");
													  yyval.l = mkclass("Error", (char *) 0);} break;
case 16:
#line 133 "parser.y" 
{addinst(yypvt[-0].c);} break;
case 17:
#line 134 "parser.y"
{addinst(yypvt[-0].c);} break;
case 18:
#line 135 "parser.y"
{expect("instance variable");} break;
case 20:
#line 140 "parser.y"
{yypvt[-0].m->nextmethod = yypvt[-2].m; yyval.m = yypvt[-0].m;} break;
case 21:
#line 144 "parser.y"
{deltemps(yypvt[-2].i); yyval.m = mkmethod(yypvt[-3].e, yypvt[-2].i, yypvt[-1].s);} break;
case 22:
#line 148 "parser.y"
{yyval.e = mkkey((struct exprstruct *) 0, yypvt[-0].k);} break;
case 23:
#line 150 "parser.y"
{yyval.e = mkexpr((struct exprstruct *) 0, bincmd, yypvt[-1].c, (struct exprstruct *) 0);} break;
case 24:
#line 152 "parser.y"
{yyval.e = mkexpr((struct exprstruct *) 0, uncmd, yypvt[-0].c, (struct exprstruct *) 0);} break;
case 25:
#line 153 "parser.y"
{expect("method pattern");
yyval.e = mkexpr((struct exprstruct *) 0, uncmd, "", (struct exprstruct *) 0);} break;
case 26:
#line 158 "parser.y"
{yyval.k = mkklist((struct keylist *) 0, yypvt[-1].c, (struct exprstruct *) 0);} break;
case 27:
#line 160 "parser.y"
{yyval.k = mkklist(yypvt[-2].k, yypvt[-1].c, (struct exprstruct *) 0);} break;
case 28:
#line 163 "parser.y"
{addtemp(yypvt[-0].c, argvar);} break;
case 29:
#line 164 "parser.y"
{expect("argument variable");} break;
case 30:
#line 167 "parser.y"
{yyval.i = 0;} break;
case 31:
#line 168 "parser.y"
{yyval.i = yypvt[-1].i;} break;
case 34:
#line 173 "parser.y"
{expect("| (vertical bar)");} break;
case 35:
#line 176 "parser.y"
{yyval.i = 1;} break;
case 36:
#line 177 "parser.y"
{yyval.i = yypvt[-1].i + 1;} break;
case 37:
#line 180 "parser.y"
{addtemp(yypvt[-0].c, tempvar);} break;
case 38:
#line 183 "parser.y"
{yyval.s = yypvt[-0].s;} break;
case 39:
#line 184 "parser.y"
{yypvt[-0].s->nextstate = yypvt[-2].s; yyval.s = yypvt[-0].s;} break;
case 42:
#line 191 "parser.y"
{yyval.s = mkstate(upar, (char *) 0, yypvt[-0].s);} break;
case 44:
#line 196 "parser.y"
{yyval.s = mkstate(asgn, yypvt[-2].c, yypvt[-0].s);} break;
case 45:
#line 198 "parser.y"
{yyval.s = mkstate(expr, (char *) 0, (struct statestruct *) yypvt[-0].e);} break;
case 47:
#line 202 "parser.y"
{yyval.e = mkexpr(yypvt[-0].e, semiend, 0, 0);} break;
case 49:
#line 206 "parser.y"
{yyval.e = mkkey(yypvt[-1].e, yypvt[-0].k);} break;
case 51:
#line 211 "parser.y"
{yyval.e = mkexpr(yypvt[-2].e, bincmd, yypvt[-1].c, yypvt[-0].e);} break;
case 52:
#line 214 "parser.y"
{yyval.e = mkexpr(yypvt[-1].e, semistart, 0, 0);} break;
case 53:
#line 216 "parser.y"
{yyval.e = mkexpr(yypvt[-1].e, uncmd, yypvt[-0].c, (struct exprstruct *) 0);} break;
case 54:
#line 219 "parser.y"
{yyval.e = yypvt[-0].e;} break;
case 55:
#line 220 "parser.y"
{yyval.e = mkkey(yypvt[-1].e, yypvt[-0].k);} break;
case 56:
#line 224 "parser.y"
{yyval.k = mkklist((struct keylist *) 0, yypvt[-1].c, yypvt[-0].e);} break;
case 57:
#line 226 "parser.y"
{yyval.k = mkklist(yypvt[-2].k, yypvt[-1].c, yypvt[-0].e);} break;
case 58:
#line 229 "parser.y"
{yyval.e = yypvt[-0].e;} break;
case 59:
#line 230 "parser.y"
{yyval.e = mkexpr(yypvt[-2].e, bincmd, yypvt[-1].c, yypvt[-0].e);} break;
case 60:
#line 233 "parser.y"
{yyval.c = yypvt[-0].c;} break;
case 61:
#line 234 "parser.y"
{yyval.c = bincat(yypvt[-1].c, yypvt[-0].c);} break;
case 67:
#line 245 "parser.y"
{yyval.e = mkexpr((struct exprstruct *) 0, reccmd, (char *) 0, 
					(struct exprstruct *) yypvt[-0].o);} break;
case 68:
#line 248 "parser.y"
{yyval.e = mkexpr(yypvt[-1].e, uncmd, yypvt[-0].c, (struct exprstruct *) 0);} break;
case 69:
#line 251 "parser.y"
{e.c = yypvt[-0].c; yyval.o = mkobj(classobj, &e);} break;
case 70:
#line 252 "parser.y"
{e.c = yypvt[-0].c; yyval.o = mkobj(varobj, &e);} break;
case 71:
#line 253 "parser.y"
{e.t = yypvt[-0].t; yyval.o = mkobj(litobj, &e);} break;
case 72:
#line 254 "parser.y"
{e.p = yypvt[-0].p; yyval.o = mkobj(pseuobj, &e);} break;
case 73:
#line 255 "parser.y"
{e.u = yypvt[-0].u; yyval.o = mkobj(primobj, &e);} break;
case 74:
#line 256 "parser.y"
{e.s = yypvt[-1].s; yyval.o = mkobj(exprobj, &e);} break;
case 75:
#line 257 "parser.y"
{e.b = yypvt[-0].b; yyval.o = mkobj(blockobj, &e);} break;
case 76:
#line 261 "parser.y"
{yyval.u = mkprim(yypvt[-2].i, yypvt[-1].r);} break;
case 77:
#line 264 "parser.y"
{yyval.r = NULL;} break;
case 78:
#line 265 "parser.y"
{yyval.r = addprim(yypvt[-1].r, yypvt[-0].o);} break;
case 79:
#line 269 "parser.y"
{yyval.b = mkblock(yypvt[-2].i, yypvt[-1].s);
					deltemps(yypvt[-2].i);} break;
case 80:
#line 273 "parser.y"
{yyval.i = 0;} break;
case 81:
#line 274 "parser.y"
{yyval.i = yypvt[-1].i;} break;
case 82:
#line 277 "parser.y"
{addtemp(yypvt[-0].c, argvar); yyval.i = 1;} break;
case 83:
#line 278 "parser.y"
{addtemp(yypvt[-0].c, argvar); yyval.i = yypvt[-1].i + 1;} break;
case 84:
#line 281 "parser.y"
{yypvt[-0].s->nextstate = yypvt[-1].s; yyval.s = yypvt[-0].s;} break;
case 85:
#line 282 "parser.y"
{yyval.s = yypvt[-0].s;} break;
case 86:
#line 285 "parser.y"
{yyval.s = mkstate(blkupar, (char *) 0, yypvt[-0].s);} break;
case 87:
#line 286 "parser.y"
{yyval.s = mkstate(upar, (char *) 0, yypvt[-0].s);} break;
case 88:
#line 290 "parser.y"
{e.p = nilvar;
yyval.s = mkstate(expr, (char *) 0,
(struct statestruct *) mkexpr((struct exprstruct *) 0, reccmd, (char *) 0,
	(struct exprstruct *) mkobj(pseuobj, &e)));} break;
case 89:
#line 294 "parser.y"
{yyval.s = yypvt[-0].s;} break;
case 90:
#line 297 "parser.y"
{yyval.s = yypvt[-1].s;} break;
case 91:
#line 299 "parser.y"
{yypvt[-1].s->nextstate = yypvt[-2].s; yyval.s = yypvt[-1].s;} break;
case 92:
#line 302 "parser.y"
{yyval.t = yypvt[-0].t;} break;
case 93:
#line 303 "parser.y"
{e.a = yypvt[-1].a; yyval.t = mklit(arlit, &e);} break;
case 95:
#line 309 "parser.y"
{e.c = yypvt[-0].c; yyval.t = mklit(fnumlit, &e);} break;
case 96:
#line 310 "parser.y"
{e.i = yypvt[-0].i; yyval.t = mklit(numlit, &e);} break;
case 97:
#line 311 "parser.y"
{e.i = yypvt[-0].i; yyval.t = mklit(charlit, &e);} break;
case 98:
#line 312 "parser.y"
{e.c = yypvt[-0].c; yyval.t = mklit(strlit, &e);} break;
case 99:
#line 313 "parser.y"
{e.c = yypvt[-0].c; yyval.t = mklit(symlit, &e);} break;
case 100:
#line 314 "parser.y"
{bytearray[bytetop] = '\0';
													  yyval.t = mklit(bytelit, &e);} break;
case 101:
#line 318 "parser.y"
{yyval.c = yypvt[-0].c;} break;
case 102:
#line 319 "parser.y"
{yyval.c = bincat("-", yypvt[-0].c);} break;
case 103:
#line 322 "parser.y"
{yyval.i = yypvt[-0].i;} break;
case 104:
#line 323 "parser.y"
{yyval.i = - yypvt[-0].i;} break;
case 105:
#line 326 "parser.y"
{yyval.t = yypvt[-0].t;} break;
case 106:
#line 327 "parser.y"
{e.c = yypvt[-0].c; yyval.t = mklit(symlit, &e);} break;
case 107:
#line 328 "parser.y"
{e.c = yypvt[-0].c; yyval.t = mklit(symlit, &e);} break;
case 108:
#line 329 "parser.y"
{e.c = yypvt[-0].c; yyval.t = mklit(symlit, &e);} break;
case 109:
#line 330 "parser.y"
{e.c = yypvt[-0].c; yyval.t = mklit(symlit, &e);} break;
case 110:
#line 331 "parser.y"
{e.c = yypvt[-0].c; yyval.t = mklit(symlit, &e);} break;
case 111:
#line 332 "parser.y"
{e.c = yypvt[-0].c; yyval.t = mklit(symlit, &e);} break;
case 112:
#line 333 "parser.y"
{e.a = yypvt[-1].a; yyval.t = mklit(arlit, &e);} break;
case 115:
#line 340 "parser.y"
{yyval.a = NULL;} break;
case 116:
#line 341 "parser.y"
{yyval.a = addlit(yypvt[-1].a, yypvt[-0].t);} break;
case 117:
#line 344 "parser.y"
{bytetop = 0;
													  bytearray[bytetop++] = itouc(yypvt[-0].i);} break;
case 118:
#line 346 "parser.y"
{bytearray[bytetop++] = itouc(yypvt[-0].i);} break;
		}
		goto yystack;  /* stack new state and value */

	}
