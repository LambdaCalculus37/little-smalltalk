/*
	Little Smalltalk
		definitions used by parser
*/


/* enum vartypes {instvar, argvar, tempvar}; */
#define	instvar 0
#define	argvar 1
#define tempvar 2

struct varstruct {
	struct varstruct *nextvar;
	int vtype;
	char *text;
	short position;
	};

/* enum objtypes {classobj, varobj, instvarobj, contvarobj, 
	litobj, pseuobj, primobj, exprobj, blockobj}; */
#define classobj	0
#define varobj		1
#define instvarobj	2
#define contvarobj	3
#define litobj		4
#define pseuobj		5
#define primobj		6
#define exprobj		7
#define blockobj	8

struct objstruct {
	int objtype;
	union {
		char *varname;
		int varoffset;
		struct litstruct *litinfo;
		/* enum	pseuvars */ int pseuinfo;
		struct primstruct *priminfo;
		struct statestruct *stateinfo;
		struct blockstruct *blockinfo;
		 } ee;
	};

struct blockstruct {
	int arglocation;
	int numargs;
	struct statestruct *bstates;
	};

/* enum littypes {numlit, fnumlit, charlit, strlit, symlit, arlit, bytelit}; */
#define numlit	0
#define fnumlit 1
#define charlit 2
#define strlit	3
#define symlit	4
#define arlit	5
#define bytelit 6

struct litstruct {
	/* enum littypes */ int littype;
	union {
		int litint;
		char litchar;
		char *litstr;
		char *litsym;
		struct litlist *litarry;
		} ll;
	};

struct litlist {
	struct litstruct *litele;
	struct litlist *nextlit;
	int litposition;
	};

struct primstruct {
	int primnumber;
	struct primlist *plist;
	} ;

struct primlist {
	struct primlist *nextprim;
	struct objstruct *pobject;
	};

/* enum cmdtypes {reccmd, uncmd, bincmd, keycmd, semistart, semiend}; */
#define reccmd		0
#define uncmd		1
#define bincmd		2
#define keycmd		3
#define semistart	4
#define semiend		5

struct exprstruct {
	/* enum	cmdtypes */ int cmdtype;
	char *cmdname;
	struct exprstruct *receiver;
	union {
		struct exprstruct *argument;
		struct keylist *keys;
		struct objstruct *recobj;
		} cc;
	struct exprstruct *nextcmd;
	};

/* enum statetypes {blkupar, upar, asgn, iasgn, casgn, expr}; */
#define blkupar 0
#define upar	1
#define asgn	2
#define iasgn	3
#define casgn	4
#define expr	5

struct statestruct {
	/* enum statetypes */ int statetype;
	struct statestruct *nextstate;
	union {
		struct varstruct *variable;
		int varpos;
		} mm;
	union {
		struct statestruct *stateexpr;
		struct exprstruct *cmd;
		} nn;
	};

struct keylist {
	char *keyword;
	struct exprstruct *arg;
	struct keylist *nextkey;
	};

struct methodstruct {
	struct exprstruct *pattern;
	int numtempvars;
	struct statestruct *states;
	struct methodstruct *nextmethod;
	};

struct classstruct {
	char *name;
	char *super;
	};

#define structalloc(type) (struct type *) alloc(sizeof (struct type ))

extern struct varstruct *instvars;
extern struct varstruct *contextvars;

#define addinst(x) (instvars = addvlist(mkvar(x, instvar), instvars))

extern char *walloc();
