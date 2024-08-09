/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2023
* Author: David Burchat, Marcos Astudillo Carrasco
* Student Number: 040513895 & 041057439
* Lab Section: 011
* Date: NOV 12, 2023
* Professors: Paulo Sousa
************************************************************
=---------------------------------------=
|  COMPILERS - ALGONQUIN COLLEGE (F23)  |
=---------------------------------------=
|              ....                     |
|          ........::.::::::.           |
|        .:........::.:^^^~~~:          |
|        :^^::::::^^^::^!7??7~^.        |
|       .:^~~^!77777~~7?YY?7??7^.       |
|       :.^~!??!^::::^^~!?5PY??!~.      |
|       ~!!7J~.:::^^^^~!!~~?G5J?~       |
|       :^~?!~7?Y57^^?PP5YJ!J5Y?:       |
|       .~!!.:^!7!:.:7JYYJ7~7Y7^        |
|       .~77..    . .~^:^^^~7?:         |
|       .^!^~:::.:^!7?~^~!77J:          |
|        ^^!Y~^^^^~?YJ77??7JJ^          |
|       .^7J?~^~~^~7??7??7JY?~:         |
|        ::^^~^7?!^~~!7???J?J7~:.       |
|         ^~~!.^7YPPPP5Y?7J7777~.       |
|        ..:~..:^!JPP5YJ?!777!^.        |
| .~?JJJJJJJJJJYYYYYPPPPPPPPPPPP5PPYY~  |
|  :!Y5GGG.___ YYYYYY__._.PPGGGGGG5!.   |
|		N    N  AAAAA  TTTTT  AAAAA		|
|		NN   N  A   A    T    A   A		|
|		N N  N  AAAAA    T    AAAAA		|
|		N  N N  A   A    T    A   A		|
|		N   NN  A   A    T    A   A		|
|                                       |
=---------------------------------------=
*/

/*
************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011]
* Assignment: A22
* Date: NOV 12, 2023
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NATA_NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 28

/* TO_DO: Define Token codes - Create your token classes */
/* DONE: Kept the same as all exsist in Golang, but added the dot/period token */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (They end with a right parenthesis but its not apart of the method id*/
	INL_T,		/*  2: Integer literal token */
	STR_T,		/*  3: String literal token */
	LPR_T,		/*  4: Left parenthesis token */
	RPR_T,		/*  5: Right parenthesis token */
	LBR_T,		/*  6: Left brace token */
	RBR_T,		/*  7: Right brace token */
	KW_T,		/*  8: Keyword token */
	EOS_T,		/*  9: End of statement (newline) */
	RTE_T,		/* 10: Run-time error token */
	SEOF_T,		/* 11: Source end-of-file token */
	CMT_T,		/* 12: Comment token */
	DOT_T,       /* 13: Dot or period token for seperating import classes from functions */ /* NEW */
	VAR_T,
	ADD_T, 
	SUB_T, 
	MUL_T, 
	DIV_T,
	EQAS_T,
	COM_T,
	OPEQ_T, 
	OPNE_T, 
	OPGT_T,
	OPLT_T,
	OPAND_T,
	OPOR_T,
	OPNOT_T
};

/* TO_DO: Define the list of keywords */
/* DONE: Just added the Dot/Period Token and the Variable token */
static string tokenStrTable[NUM_TOKENS] = {
	"ERR_T",
	"MNID_T",
	"INL_T",
	"STR_T",
	"LPR_T",
	"RPR_T",
	"LBR_T",
	"RBR_T",
	"KW_T",
	"EOS_T",
	"RTE_T",
	"SEOF_T",
	"CMT_T",
	"DOT_T",  /* New, We implemented */
	"VAR_T",
	"ADD_T",
	"SUB_T", 
	"MUL_T", 
	"DIV_T",
	"EQAS_T",
	"COM_T",
	"OPEQ_T",
	"OPNE_T",
	"OPGT_T",
	"OPLT_T",
	"OPAND_T",
	"OPOR_T",
	"OPNOT_T"
};

/* TO_DO: Operators token attributes */
/* DONE: Kept the Same, as all of these exsist in Golang */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
/* DONE: Kept the same, however we are not implmenting the fp literal */
typedef union TokenAttribute {
	int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	int intValue;				/* integer literal attribute (value) */
	int keywordIndex;			/* keyword index in the keyword table */
	int contentString;			/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	float32 floatValue;				/* floating-point literal attribute (value) */
	int8 idLexeme[VID_LEN + 1];	/* variable identifier token attribute */
	int8 errLexeme[ERR_LEN + 1];	/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
/* Symbol table is being implemented */
typedef struct idAttibutes {
	byte flags;			/* Flags information */
	union {
		int intValue;				/* Integer value */
		float32 floatValue;			/* Float value */
		string stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	int scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */

/* TO_DO: Define lexeme FIXED classes */
/* REVIEW AND AMEND */
/* These constants will be used on nextClass */
	#define CHRCOL2 '\n'
	#define CHRCOL3 '/'
	#define CHRCOL4 '\"'
    #define CHRCOL5 '('
	#define CHRCOL6 '_'


/* These constants will be used on VID / MID function */

	#define MNID_SUF '&'
    #define COMM_SYM '//'

/* TO_DO: Error states and illegal state */
/* REVIEW AND AMEND */
#define ESNR	9		/* Error state with no retract */
#define ESWR	10		/* Error state with retract */
#define FS		11		/* Illegal state */

 /* TO_DO: State transition table definition */
/* REVIEW AND AMEND */
#define NUM_STATES		13
#define CHAR_CLASSES	9


//=================================================================================================================
/* TO_DO: Transition table - type of states defined in separate table */
/* REVIEW AND AMEND */
static int transitionTable[NUM_STATES][CHAR_CLASSES] = {
/*    [A-z],[0-9],   /n,   /,	  ",    (,    _,  EOF,  other,
	   L(0), D(1), N(2), F(3), Q(4), B(5), U(6),  E(7)  E(8) */
	{     1,    2, ESNR,    4,    3, ESWR,	  5,   13, ESWR	},	  // S0: NOFS
	{     1,    1, ESNR, ESNR, ESNR,   10,    1, ESWR,	  9	},	  // S1: NOFS
	{  ESNR,    2, ESNR, ESNR, ESWR, ESWR, ESWR, ESWR,	  6	},	  // S2: NOFS
	{     3,    3,    3,    3,    7,    3,	  3, ESWR,	  3	},	  // S3: NOFS
	{  ESNR, ESNR,    4,    8, ESNR, ESWR, ESWR, ESWR, ESWR	},	  // S4: NOFS
	{     5,    5, ESWR, ESWR, ESWR,   10,	  5, ESWR,	  9	},	  // S5: NOFS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,	 FS	},	  // S6: FSWR (Integer Literal)
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,	 FS	},	  // S7: FSNR (String Literal)
	{     8,    8,   11,    8,    8,    8,	  8, ESWR, ESWR },	  // S8: NOFS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,	 FS	},    // S9: FSWR (Variable or Keyword)
	{	 FS,   FS,	 FS,   FS,	 FS,   FS,	 FS,   FS,	 FS	},    // S10: FSWR (Method ID)
	{	 FS,   FS,	 FS,   FS,	 FS,   FS,	 FS,   FS,	 FS	},    // S11: FSNR (Single Line Comment)
	{	 FS,   FS,	 FS,   FS,	 FS,   FS,	 FS,   FS,	 FS	}     // S12: FSNR (EOF)
};
//=================================================================================================================

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
/* REVIEW AND AMEND */
static int stateType[NUM_STATES] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	NOFS, /* 02 */
	NOFS, /* 03 */
	NOFS, /* 04 */
	NOFS, /* 05 */
	FSWR, /* 06 Integer Literal */
	FSNR, /* 07 String Literal */
	NOFS, /* 08 */
	FSWR, /* 09 Variable or Key */
	FSWR, /* 10 Method */
	FSNR, /* 11 Single Line Comment */
	FSNR  /* 12 End of File */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
int			startScanner(BufferPointer psc_buf);
static int	nextClass(int8 c);					/* character class function */
static int	nextState(int, int8);		/* state machine function */
void		printScannerData(ScannerData scData);
Token				tokenizer(void);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(string lexeme);

/* Declare accepting states functions */
Token funcSL	(string lexeme);
Token funcIL	(string lexeme);
Token funcID	(string lexeme);
Token funcCMT   (string lexeme);
Token funcMETH	(string lexeme);
Token funcKEY	(string lexeme);
Token funcErr	(string lexeme);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
/* REVIEW AND AMEND */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NATA_NULL,		/* -    [00] */
	NATA_NULL,		/* -    [01] */
	NATA_NULL,		/* -    [02] */
	NATA_NULL,		/* -    [03] */
	NATA_NULL,		/* -    [04] */
	NATA_NULL,		/* -    [05] */
	funcIL,			/* Integer Literal [06] */
	funcSL,			/* String Literal [07]  */
	NATA_NULL,		/* - [08]   */
	funcID,			/* Key or Variable ID [09]   */ /* funcID checks funcKEY*/
	funcMETH,
	funcCMT,		/* Single Line Comment - [11]   */
	NATA_NULL		/* End of File - [12]   */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
/* DONE: updated to 16 keywords */
#define KWT_SIZE 16

/* TO_DO: Define the list of keywords */
/* DONE: Added standard small sub-set of keywords for golang*/
static string keywordTable[KWT_SIZE] = {
	"package",		/* KW00 */
	"func",		/* KW01 */
	"int",		/* KW02 */
	"byte",		/* KW03 */
	"string",	/* KW04 */
	"if",		/* KW05 */
	"then",		/* KW06 */
	"else",		/* KW07 */
	"while",	/* KW08 */
	"do",		/* KW09 */
	"for",      /* KW10 */
	"return",   /* KW11 */
	"import",   /* KW12 */
	"const",	/* KW13 */
	"true",     /* KW14 */
	"false"    /* KW15 */
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data )
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
/* DONE: Symbol table is being implemented */
typedef struct languageAttributes {
	int8 indentationCharType;
	int indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
	/* DONE:  No extra attributes being added */
} LanguageAttributes;

/* Number of errors */
int numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif
