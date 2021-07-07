/* # include "stdio.h" */
# define U(x) x
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# define YYLMAX 200
# define output(c) putc(c,yyout)
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
# define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng; extern char yytext[];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;
FILE *yyin = {stdin}, *yyout = {stdout};
extern int yylineno;
struct yysvf { 
	int yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;
/*
        Little Smalltalk lexical analyzer
*/
# include <math.h>

# undef input
# undef unput

double atof();
int linenum = 1;
# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:
                       {;}
break;
case 2:
                             {linenum++;}
break;
case 3:
                             {readcomment();}
break;
case 4:
                           {return(ASSIGN);}
break;
case 5:
                           {return(ASSIGN);}
break;
case 6:
                          {return(lexsave(CLASS));}
break;
case 7:
                           {yylval.p = selfvar;  return(PSEUDO);}
break;
case 8:
		{yylval.p = procvar;  return(PSEUDO);}
break;
case 9:
                          {yylval.p = supervar; return(PSEUDO);}
break;
case 10:
                            {yylval.p = nilvar;   return(PSEUDO);}
break;
case 11:
                           {yylval.p = truevar;  return(PSEUDO);}
break;
case 12:
                          {yylval.p = falsevar; return(PSEUDO);}
break;
case 13:
                      {yylval.p = smallvar; return(PSEUDO);}
break;
case 14:
                            {yylval.i = yytext[1]; return(LITCHAR);}
break;
case 15:
                              {return(PS);}
break;
case 16:
{return(lexsave(LITFNUM));}
break;
case 17:
                         {yylval.i = atoi(yytext); return(LITNUM);}
break;
case 18:
  {return(lexsave(LITFNUM));}
break;
case 19:
                        {char c; unput(c = input());
                                 if (c == '\'') yymore();
                                 else return(lexlstr());}
break;
case 20:
                 {return(varlex());}
break;
case 21:
                  {return(slexsave(COLONVAR));}
break;
case 22:
                {return(slexsave(LITSYM));}
break;
case 23:
                            {return(lexsave(MINUS));}
break;
case 24:
                            {return(LP);}
break;
case 25:
                            {return(RP);}
break;
case 26:
                            {return(LB);}
break;
case 27:
                            {return(RB);}
break;
case 28:
                            {return(PERIOD);}
break;
case 29:
			{return(lexsave(MBAR));}
break;
case 30:
			{return(lexsave(MBAR));}
break;
case 31:
                            {return(lexsave(BAR));}
break;
case 32:
                            {return(lexsave(BAR));}
break;
case 33:
                            {return(SEMI);}
break;
case 34:
                            {return(lexsave(UPARROW));}
break;
case 35:
			{return(lexsave(PE));}
break;
case 36:
              {return(lexsave(BINARY));}
break;
case 37:
  			{return(PRIMITIVE);}
break;
case -1:
break;
default:
fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */
static int ocbuf = 0;
static int pbbuf[400];

static int input()
{	int c;

	if (ocbuf) {c = pbbuf[--ocbuf]; }
	else {
		c = getc(fp);
		if (c == EOF) c = 0;
		}
	return(c);
}

static unput(c)
char c;
{
	if (c) pbbuf[ocbuf++] = c;
}

# include <ctype.h>

static readcomment()
{  char c;

   while ((c = input()) && c != '\"')
	if (c == '\n') linenum++;
   if (!c) yyerror("unterminated comment");
}

char *walloc(s) char *s;
{  char *p, *malloc();

   p = malloc((unsigned) (strlen(s) + 1));
   if (p == (char *) 0) yyerror("out of variable string space");
   strcpy(p, s);
   return(p);
}

static int slexsave(type)
int type;
{

	yylval.c = walloc(&yytext[1]);
	if (yylval.c == 0) yerr("cannot create symbol %s", yytext);
	return(type);
}

static int lexsave(type)
int type;
{

	yylval.c = walloc(yytext);
	if (yylval.c == 0) yerr("cannot create string %s", yytext);
	return(type);
}

static int varlex()
{  

   lexsave(0);
   if (yytext[yyleng-1] == ':') return(KEYWORD);
   else if (islower(yytext[0])) return(LOWERCASEVAR);
   else return(UPPERCASEVAR);
}

static int lexlstr()
{  char *p, *q;

   yylval.c = p = walloc(&yytext[1]);
   *(p + yyleng -2) = '\0';
   return(LITSTR);
}
int yyvstop[] = {
0,

36,
0,

1,
0,

2,
0,

1,
36,
0,

32,
36,
0,

3,
36,
0,

15,
36,
0,

36,
0,

36,
0,

24,
36,
0,

25,
36,
0,

23,
36,
0,

28,
36,
0,

17,
18,
20,
0,

36,
0,

33,
36,
0,

36,
0,

35,
36,
0,

20,
0,

20,
0,

26,
36,
0,

27,
36,
0,

34,
36,
0,

20,
0,

20,
0,

20,
0,

20,
0,

31,
36,
0,

30,
32,
36,
0,

29,
31,
36,
0,

22,
0,

14,
0,

19,
0,

20,
0,

20,
0,

20,
0,

21,
0,

4,
0,

5,
0,

20,
0,

20,
0,

20,
0,

20,
0,

20,
0,

20,
0,

20,
0,

18,
0,

18,
20,
0,

16,
20,
0,

20,
0,

20,
0,

10,
20,
0,

20,
0,

20,
0,

20,
0,

20,
0,

18,
0,

16,
0,

20,
0,

20,
0,

20,
0,

7,
20,
0,

20,
0,

20,
0,

11,
20,
0,

16,
0,

16,
20,
0,

6,
20,
0,

12,
20,
0,

20,
0,

20,
0,

9,
20,
0,

16,
0,

20,
0,

20,
0,

20,
0,

20,
0,

20,
0,

20,
0,

20,
0,

13,
20,
0,

37,
0,

20,
0,

8,
20,
0,
0};
# define YYTYPE char
struct yywork { YYTYPE verify, advance; } yycrank[] = {
0,0,	0,0,	1,3,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,4,	1,5,	
0,0,	0,0,	1,6,	4,4,	
0,0,	0,0,	0,0,	4,4,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,7,	1,8,	
1,9,	1,10,	4,4,	0,0,	
1,11,	1,12,	1,13,	0,0,	
1,3,	0,0,	1,14,	1,15,	
19,43,	1,16,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	1,17,	
1,18,	1,19,	0,0,	1,20,	
0,0,	0,0,	1,21,	0,0,	
1,22,	0,0,	0,0,	65,53,	
0,0,	65,53,	0,0,	2,31,	
2,8,	2,9,	2,10,	0,0,	
0,0,	9,33,	0,0,	2,13,	
0,0,	0,0,	0,0,	2,14,	
2,15,	9,0,	9,0,	0,0,	
1,23,	9,33,	1,24,	1,25,	
0,0,	0,0,	1,21,	26,46,	
2,17,	2,18,	2,19,	1,26,	
2,20,	45,58,	0,0,	27,47,	
49,62,	2,22,	22,45,	1,27,	
9,0,	46,59,	47,60,	19,44,	
1,28,	1,29,	29,51,	9,33,	
9,0,	9,0,	10,34,	9,33,	
28,48,	1,30,	9,0,	44,57,	
9,33,	48,61,	10,34,	10,0,	
28,49,	2,23,	10,34,	2,24,	
2,25,	50,63,	51,64,	52,65,	
28,50,	11,35,	57,70,	58,71,	
2,26,	9,33,	59,72,	61,73,	
62,74,	11,35,	11,35,	63,75,	
2,27,	11,35,	64,76,	70,81,	
71,82,	2,28,	2,29,	72,83,	
10,34,	10,34,	67,68,	73,84,	
10,34,	74,85,	2,32,	75,86,	
78,77,	10,34,	81,88,	9,0,	
84,89,	85,90,	88,91,	89,92,	
90,93,	9,33,	91,94,	11,36,	
11,35,	92,95,	93,96,	11,35,	
94,97,	95,98,	10,34,	96,99,	
11,35,	37,52,	37,52,	37,52,	
37,52,	37,52,	37,52,	37,52,	
37,52,	37,52,	37,52,	97,100,	
98,101,	39,53,	101,102,	39,53,	
0,0,	11,35,	39,54,	39,54,	
39,54,	39,54,	39,54,	39,54,	
39,54,	39,54,	39,54,	39,54,	
0,0,	67,77,	10,34,	16,37,	
0,0,	16,16,	16,16,	16,16,	
16,16,	16,16,	16,16,	16,16,	
16,16,	16,16,	16,16,	16,38,	
0,0,	0,0,	0,0,	0,0,	
0,0,	11,35,	16,21,	16,21,	
16,21,	16,21,	16,21,	16,21,	
16,21,	16,21,	16,21,	16,21,	
16,21,	16,21,	16,21,	16,21,	
16,21,	16,21,	16,21,	16,21,	
16,21,	16,21,	16,21,	16,21,	
16,21,	16,21,	16,21,	16,21,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	16,21,	16,21,	
16,21,	16,21,	16,39,	16,21,	
16,21,	16,21,	16,21,	16,21,	
16,21,	16,21,	16,21,	16,21,	
16,21,	16,21,	16,21,	16,40,	
16,21,	16,21,	16,21,	16,21,	
16,21,	16,21,	16,21,	16,21,	
17,41,	17,41,	17,41,	17,41,	
17,41,	17,41,	17,41,	17,41,	
17,41,	17,41,	0,0,	0,0,	
0,0,	17,42,	0,0,	0,0,	
0,0,	17,41,	17,41,	17,41,	
17,41,	17,41,	17,41,	17,41,	
17,41,	17,41,	17,41,	17,41,	
17,41,	17,41,	17,41,	17,41,	
17,41,	17,41,	17,41,	17,41,	
17,41,	17,41,	17,41,	17,41,	
17,41,	17,41,	17,41,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	17,41,	17,41,	17,41,	
17,41,	17,41,	17,41,	17,41,	
17,41,	17,41,	17,41,	17,41,	
17,41,	17,41,	17,41,	17,41,	
17,41,	17,41,	17,41,	17,41,	
17,41,	17,41,	17,41,	17,41,	
17,41,	17,41,	17,41,	21,21,	
21,21,	21,21,	21,21,	21,21,	
21,21,	21,21,	21,21,	21,21,	
21,21,	21,38,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
21,21,	21,21,	21,21,	21,21,	
21,21,	21,21,	21,21,	21,21,	
21,21,	21,21,	21,21,	21,21,	
21,21,	21,21,	21,21,	21,21,	
21,21,	21,21,	21,21,	21,21,	
21,21,	21,21,	21,21,	21,21,	
21,21,	21,21,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
21,21,	21,21,	21,21,	21,21,	
21,21,	21,21,	21,21,	21,21,	
21,21,	21,21,	21,21,	21,21,	
21,21,	21,21,	21,21,	21,21,	
21,21,	21,21,	21,21,	21,21,	
21,21,	21,21,	21,21,	21,21,	
21,21,	21,21,	33,0,	33,0,	
53,66,	53,66,	53,66,	53,66,	
53,66,	53,66,	53,66,	53,66,	
53,66,	53,66,	54,54,	54,54,	
54,54,	54,54,	54,54,	54,54,	
54,54,	54,54,	54,54,	54,54,	
0,0,	33,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	33,0,	33,0,	0,0,	
0,0,	40,55,	0,0,	33,0,	
40,56,	40,56,	40,56,	40,56,	
40,56,	40,56,	40,56,	40,56,	
40,56,	40,56,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	40,56,	40,56,	40,56,	
40,56,	40,56,	40,56,	40,56,	
40,56,	40,56,	40,56,	40,56,	
40,56,	40,56,	40,56,	40,56,	
40,56,	40,56,	40,56,	40,56,	
40,56,	40,56,	40,56,	40,56,	
40,56,	40,56,	40,56,	0,0,	
33,0,	41,41,	41,41,	41,41,	
41,41,	41,41,	41,41,	41,41,	
41,41,	41,41,	41,41,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	41,41,	41,41,	
41,41,	41,41,	41,41,	41,41,	
41,41,	41,41,	41,41,	41,41,	
41,41,	41,41,	41,41,	41,41,	
41,41,	41,41,	41,41,	41,41,	
41,41,	41,41,	41,41,	41,41,	
41,41,	41,41,	41,41,	41,41,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	41,41,	41,41,	
41,41,	41,41,	41,41,	41,41,	
41,41,	41,41,	41,41,	41,41,	
41,41,	41,41,	41,41,	41,41,	
41,41,	41,41,	41,41,	41,41,	
41,41,	41,41,	41,41,	41,41,	
41,41,	41,41,	41,41,	41,41,	
55,67,	55,67,	55,67,	55,67,	
55,67,	55,67,	55,67,	55,67,	
55,67,	55,67,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	55,67,	55,67,	55,67,	
55,67,	55,67,	55,67,	55,67,	
55,67,	55,67,	55,67,	55,67,	
55,67,	55,67,	55,67,	55,67,	
55,67,	55,67,	55,67,	55,67,	
55,67,	55,67,	55,67,	55,67,	
55,67,	55,67,	55,67,	56,68,	
0,0,	56,56,	56,56,	56,56,	
56,56,	56,56,	56,56,	56,56,	
56,56,	56,56,	56,56,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	56,56,	56,56,	
56,56,	56,56,	56,56,	56,56,	
56,56,	56,56,	56,56,	56,56,	
56,56,	56,56,	56,56,	56,56,	
56,56,	56,56,	56,56,	56,56,	
56,56,	56,56,	56,56,	56,56,	
56,56,	56,56,	56,56,	56,56,	
68,78,	68,78,	68,78,	68,78,	
68,78,	68,78,	68,78,	68,78,	
68,78,	68,78,	56,69,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	68,78,	68,78,	68,78,	
68,78,	68,78,	68,78,	68,78,	
68,78,	68,78,	68,78,	68,78,	
68,78,	68,78,	68,78,	68,78,	
68,78,	68,78,	68,78,	68,78,	
68,78,	68,78,	68,78,	68,78,	
68,78,	68,78,	68,78,	69,79,	
0,0,	69,79,	0,0,	0,0,	
69,80,	69,80,	69,80,	69,80,	
69,80,	69,80,	69,80,	69,80,	
69,80,	69,80,	77,79,	0,0,	
77,79,	0,0,	0,0,	77,87,	
77,87,	77,87,	77,87,	77,87,	
77,87,	77,87,	77,87,	77,87,	
77,87,	79,87,	79,87,	79,87,	
79,87,	79,87,	79,87,	79,87,	
79,87,	79,87,	79,87,	80,80,	
80,80,	80,80,	80,80,	80,80,	
80,80,	80,80,	80,80,	80,80,	
80,80,	0,0,	0,0,	0,0,	
0,0};
struct yysvf yysvec[] = {
0,	0,	0,
-1,	0,		0,	
-42,	yysvec+1,	0,	
0,	0,		yyvstop+1,
6,	0,		yyvstop+3,
0,	0,		yyvstop+5,
0,	yysvec+4,	yyvstop+7,
0,	0,		yyvstop+10,
0,	0,		yyvstop+13,
-80,	0,		yyvstop+16,
-121,	0,		yyvstop+19,
-140,	0,		yyvstop+21,
0,	0,		yyvstop+23,
0,	0,		yyvstop+26,
0,	0,		yyvstop+29,
0,	0,		yyvstop+32,
173,	0,		yyvstop+35,
248,	0,		yyvstop+39,
0,	0,		yyvstop+41,
3,	0,		yyvstop+44,
0,	0,		yyvstop+46,
323,	0,		yyvstop+49,
2,	yysvec+21,	yyvstop+51,
0,	0,		yyvstop+53,
0,	0,		yyvstop+56,
0,	0,		yyvstop+59,
2,	yysvec+21,	yyvstop+62,
2,	yysvec+21,	yyvstop+64,
23,	yysvec+21,	yyvstop+66,
4,	yysvec+21,	yyvstop+68,
0,	0,		yyvstop+70,
0,	0,		yyvstop+73,
0,	0,		yyvstop+77,
-437,	yysvec+9,	yyvstop+81,
0,	0,		yyvstop+83,
0,	yysvec+11,	0,	
0,	0,		yyvstop+85,
141,	0,		0,	
0,	0,		yyvstop+87,
158,	yysvec+21,	yyvstop+89,
436,	yysvec+21,	yyvstop+91,
481,	0,		yyvstop+93,
0,	0,		yyvstop+95,
0,	0,		yyvstop+97,
13,	0,		0,	
8,	yysvec+21,	yyvstop+99,
5,	yysvec+21,	yyvstop+101,
6,	yysvec+21,	yyvstop+103,
21,	yysvec+21,	yyvstop+105,
11,	yysvec+21,	yyvstop+107,
25,	yysvec+21,	yyvstop+109,
21,	yysvec+21,	yyvstop+111,
38,	yysvec+37,	yyvstop+113,
400,	0,		0,	
410,	yysvec+21,	yyvstop+115,
556,	0,		0,	
601,	yysvec+21,	yyvstop+118,
37,	0,		0,	
28,	yysvec+21,	yyvstop+121,
31,	yysvec+21,	yyvstop+123,
0,	yysvec+21,	yyvstop+125,
45,	yysvec+21,	yyvstop+128,
40,	yysvec+21,	yyvstop+130,
50,	yysvec+21,	yyvstop+132,
53,	yysvec+21,	yyvstop+134,
28,	yysvec+53,	0,	
0,	yysvec+53,	yyvstop+136,
116,	yysvec+55,	yyvstop+138,
644,	0,		0,	
692,	yysvec+21,	yyvstop+140,
46,	0,		0,	
41,	yysvec+21,	yyvstop+142,
58,	yysvec+21,	yyvstop+144,
83,	yysvec+21,	yyvstop+146,
57,	yysvec+21,	yyvstop+149,
53,	yysvec+21,	yyvstop+151,
0,	yysvec+21,	yyvstop+153,
707,	0,		0,	
67,	yysvec+68,	yyvstop+156,
717,	0,		0,	
727,	yysvec+21,	yyvstop+158,
65,	0,		0,	
0,	yysvec+21,	yyvstop+161,
0,	yysvec+21,	yyvstop+164,
58,	yysvec+21,	yyvstop+167,
57,	yysvec+21,	yyvstop+169,
0,	yysvec+21,	yyvstop+171,
0,	yysvec+79,	yyvstop+174,
58,	0,		0,	
64,	yysvec+21,	yyvstop+176,
79,	yysvec+21,	yyvstop+178,
73,	0,		0,	
82,	yysvec+21,	yyvstop+180,
74,	yysvec+21,	yyvstop+182,
66,	0,		0,	
84,	yysvec+21,	yyvstop+184,
80,	yysvec+21,	yyvstop+186,
98,	0,		0,	
85,	yysvec+21,	yyvstop+188,
0,	yysvec+21,	yyvstop+190,
0,	0,		yyvstop+193,
87,	yysvec+21,	yyvstop+195,
0,	yysvec+21,	yyvstop+197,
0,	0,	0};
struct yywork *yytop = yycrank+784;
struct yysvf *yybgin = yysvec+1;
char yymatch[] = {
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,011 ,012 ,01  ,01  ,015 ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
011 ,01  ,01  ,01  ,01  ,01  ,01  ,047 ,
'(' ,'(' ,01  ,'+' ,01  ,'+' ,'(' ,01  ,
'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,
'0' ,'0' ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'(' ,01  ,01  ,01  ,01  ,
01  ,'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,
'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,
'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,
'a' ,'a' ,'a' ,01  ,01  ,01  ,01  ,01  ,
0};
char yyextra[] = {
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
/* UNISRC_ID	@(#)27.2   85/07/11  */
int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
char yytext[YYLMAX];
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
yylook(){
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych, yyfirst;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	yyfirst=1;
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = &yycrank[yystate->yystoff];
			if(yyt == yycrank && !yyfirst){  /* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == 0)break;
				}
			*yylastch++ = yych = input();
			yyfirst=0;
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (long)yyt > (long)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((long)yyt < (long)yycrank) {		/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt = &yycrank[yystate->yystoff]) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
yyback(p, m)
	int *p;
{
if (p==0) return(0);
while (*p)
	{
	if (*p++ == m)
		return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
yyinput(){
	return(input());
	}
yyoutput(c)
  int c; {
	output(c);
	}
yyunput(c)
   int c; {
	unput(c);
	}
