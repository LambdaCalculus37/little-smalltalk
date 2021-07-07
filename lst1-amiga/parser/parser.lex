%{
/*
        Little Smalltalk lexical analyzer
*/
# include <math.h>

# undef input
# undef unput

double atof();
int linenum = 1;
%}
%%
[ \t]+                          {;}
\n                              {linenum++;}
\"                              {readcomment();}
":="                            {return(ASSIGN);}
"<-"                            {return(ASSIGN);}
Class                           {return(lexsave(CLASS));}
self                            {yylval.p = selfvar;  return(PSEUDO);}
selfProcess			{yylval.p = procvar;  return(PSEUDO);}
super                           {yylval.p = supervar; return(PSEUDO);}
nil                             {yylval.p = nilvar;   return(PSEUDO);}
true                            {yylval.p = truevar;  return(PSEUDO);}
false                           {yylval.p = falsevar; return(PSEUDO);}
smalltalk                       {yylval.p = smallvar; return(PSEUDO);}
\$.                             {yylval.i = yytext[1]; return(LITCHAR);}
#                               {return(PS);}
[0-9]+r-?[0-9A-Z]+(\.[0-9A-Z]+)?(e[-+]?[0-9]+)? {return(lexsave(LITFNUM));}
[0-9]+                          {yylval.i = atoi(yytext); return(LITNUM);}
[0-9]+(\.[0-9]+)?(e[-+]?[0-9]+)?   {return(lexsave(LITFNUM));}
'[^']*'                         {char c; unput(c = input());
                                 if (c == '\'') yymore();
                                 else return(lexlstr());}
[a-zA-Z0-9]+:?                  {return(varlex());}
:[a-zA-Z0-9]+                   {return(slexsave(COLONVAR));}
#[^ \t\n.()\[]+                 {return(slexsave(LITSYM));}
"-"                             {return(lexsave(MINUS));}
"("                             {return(LP);}
")"                             {return(RP);}
"["                             {return(LB);}
"]"                             {return(RB);}
"."                             {return(PERIOD);}
^"|"				{return(lexsave(MBAR));}
^"!"				{return(lexsave(MBAR));}
"|"                             {return(lexsave(BAR));}
"!"                             {return(lexsave(BAR));}
";"                             {return(SEMI);}
"^"                             {return(lexsave(UPARROW));}
">"				{return(lexsave(PE));}
[^ \t\nA-Za-z0-9]               {return(lexsave(BINARY));}
"<primitive"   			{return(PRIMITIVE);}
%%
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
