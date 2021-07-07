/*
	Little Smalltalk

        defines used by both parser and driver

*/

# define TWOBIT         0
# define PUSHINSTANCE   1
# define PUSHTEMP       2
# define PUSHLIT        3
# define PUSHCLASS      4
# define PUSHSPECIAL    5
# define POPINSTANCE    6
# define POPTEMP        7
# define SEND           8
# define SUPERSEND      9
# define UNSEND        10
# define BINSEND       11
# define ARITHSEND     12
# define KEYSEND       13
# define BLOCKCREATE   14
# define SPECIAL       15

/* arguments for special */

# define NOOP           0
# define DUPSTACK       1
# define POPSTACK       2
# define RETURN         3
# define BLOCKRETURN    4
# define SELFRETURN     5
# define SKIPTRUEPUSH   6
# define SKIPFALSEPUSH  7
# define SKIPFORWARD    8
# define SKIPBACK       9
# define PRIMCMD       10
# define SKIPT         11
# define SKIPF         12

/* enum pseuvars {nilvar, truevar, falsevar, selfvar, supervar, smallvar,
		procvar};*/
#define nilvar 0
#define truevar 1
#define falsevar 2
#define selfvar 3
#define supervar 4
#define smallvar 5
#define procvar 6

# define streq(a,b) (strcmp(a,b) == 0)

/* only include driver code in driver, keeps both lint and the 11/70 quiet */
# ifdef DRIVECODE

/* enum lextokens { nothing, LITNUM , LITFNUM , LITCHAR , LITSTR , LITSYM , 
	LITARR , LITBYTE , ASSIGN , BINARY , PRIMITIVE , PSEUDO , 
	UPPERCASEVAR , LOWERCASEVAR , COLONVAR , KEYWORD ,
 	LP , RP , LB , RB , PERIOD , BAR , SEMI , PS , MINUS , PE , NL }; */

#define nothing 0
#define LITNUM 1
#define LITFNUM  2
#define LITCHAR 3
#define LITSTR 4
#define LITSYM 5
#define LITARR 6
#define LITBYTE 7
#define ASSIGN 8
#define BINARY 9
#define PRIMITIVE 10
#define PSEUDO 11
#define UPPERCASEVAR 12
#define LOWERCASEVAR 13
#define COLONVAR 14
#define KEYWORD 15
#define LP 16
#define RP 17
#define LB 18
#define RB 19
#define PERIOD 20
#define BAR 21
#define SEMI 22
#define PS 23
#define MINUS 24
#define PE 25
#define NL 26

typedef union  {
	char 		*c;
	double 		 f;
	int  		 i;
	/* enum pseuvars */ int 	 p;
	} tok_type;

extern tok_type t;

# endif
