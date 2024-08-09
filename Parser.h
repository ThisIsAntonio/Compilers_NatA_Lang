/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2023
* Author: TO_DO
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
|   :!Y5G / __| ___ / _(_)__ _ PGP5.    |
|    :~75 \__ \/ _ \  _| / _` | 5?.     |
|     7~7 |___/\___/_| |_\__,_| Y5?.    |
|    .^~!~.....................P5YY7.   |
|   .:::::::::::::?JJJJYYYYYYYYYJJJJ7.  |
|                                       |
=---------------------------------------=
*/

/*
************************************************************
* File name: Parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A32.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
************************************************************
*/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token			lookahead;
extern BufferPointer	stringLiteralTable;
extern int				line;
extern Token			tokenizer(void);
extern string			keywordTable[KWT_SIZE];
static int				syntaxErrorNumber = 0;

#define LANG_WRTE		"Println"
#define LANG_READ		"input"
#define LANG_MAIN		"func"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_PACKAGE,    /* "package" */
	KW_FUNC,       /* "func" */
	KW_INT,        /* "int" */
	KW_BYTE,       /* "byte" */
	KW_STRING,     /* "string" */
	KW_IF,         /* "if" */
	KW_THEN,       /* "then" */
	KW_ELSE,       /* "else" */
	KW_WHILE,      /* "while" */
	KW_DO,         /* "do" */
	KW_FOR,        /* "for" */
	KW_RETURN,     /* "return" */
	KW_IMPORT,     /* "import" */
	KW_CONST,      /* "const" */
	KW_TRUE,       /* "true" */
	KW_FALSE       /* "false" */
};

/* TO_DO: Define the number of BNF rules */
#define NUM_BNF_RULES 32

/* Parser */
typedef struct parserData {
	int parsHistogram[NUM_BNF_RULES];	/* Number of BNF Statements */
} ParserData, * pParsData;

/* Number of errors */
int numParserErrors;

/* Scanner data */
ParserData psData;

/* Function definitions */
void startParser();
void matchToken(int, int);
void syncErrorHandler(int);
void printError();
void printBNFData(ParserData psData);

/* List of BNF statements */
enum BNF_RULES {
	BNF_error,										/*  0: Error token */
	BNF_codeSession,								/*  1 */
	BNF_comment,									/*  2 */
	BNF_dataSession,								/*  3 */
	BNF_optVarListDeclarations,						/*  4 */
	BNF_optionalStatements,							/*  5 */
	BNF_outputStatement,							/*  6 */
	BNF_outputVariableList,							/*  7 */
	BNF_program,									/*  8 */
	BNF_statement,									/*  9 */
	BNF_statements,									/* 10 */
	BNF_statementsPrime,								/* 11 */
	BNF_funcDeclaration,
	BNF_varListDeclarations,
	BNF_varListDeclaration,
	BNF_arithmeticExpression,
	BNF_unaryArithmeticExpression,
	BNF_additiveArithmeticExpression,
	BNF_multiplicativeArithmeticExpression,
	BNF_primaryArithmeticExpression,
	BNF_conditionalExpression,
	BNF_logicalOrExpression,
	BNF_logicalAndExpression,
	BNF_logicalNotExpression,
	BNF_relationalExpression,
	BNF_primaryArithmeticRelationalExpression,
	BNF_ifStatement,
	BNF_whileStatement,
	BNF_doStatement,
	BNF_forStatement,
	BNF_assignmentStatement,
	BNF_parameter,
	BNF_logicalEqualsExpression
};


/* TO_DO: Define the list of keywords */
static string BNFStrTable[NUM_BNF_RULES] = {
	"BNF_error",
	"BNF_codeSession",
	"BNF_comment",
	"BNF_dataSession",
	"BNF_optVarListDeclarations",
	"BNF_optionalStatements",
	"BNF_outputStatement",
	"BNF_outputVariableList",
	"BNF_program",
	"BNF_statement",
	"BNF_statements",
	"BNF_statementsPrime",
	"BNF_funcDeclaration",
	"BNF_varListDeclarations",
	"BNF_varListDeclaration",
	"BNF_arithmeticExpression",
	"BNF_unaryArithmeticExpression",
	"BNF_additiveArithmeticExpression",
	"BNF_multiplicativeArithmeticExpression",
	"BNF_primaryArithmeticExpression",
	"BNF_conditionalExpression",
	"BNF_logicalOrExpression",
	"BNF_logicalAndExpression",
	"BNF_logicalNotExpression"
	"BNF_relationalExpression",
	"BNF_primaryArithmeticRelationalExpression",
	"BNF_ifStatement",
	"BNF_whileStatement",
	"BNF_doStatement",
	"BNF_forStatement",
	"BNF_assignmentStatement",
	"BNF_parameter",
	"BNF_logicalEqualsExpression"
};

/* TO_DO: Place ALL non-terminal function declarations */
void codeSession();
void comment();
void dataSession();
void optVarListDeclarations();
void optionalStatements();
void outputStatement();
//void outputVariableList();
void program();
void statement();
void statements();
void statementsPrime();
/* <== Added == */
void funcDeclaration();
void varListDeclarations();
void varListDeclaration();
void assignmentStatement();
void arithmeticExpression();
void unaryArithmeticExpression();
void additiveArithmeticExpression();
void multiplicativeArithmeticExpression();
void primaryArithmeticExpression();
void logicalEqualsExpression();
void logicalOrExpression();
void logicalAndExpression();
void logicalNotExpression();
void relationalExpression();
void primaryArithmeticRelationalExpression();

void ifStatement();
void whileStatement();
void doStatement();
void forStatement();
#endif
