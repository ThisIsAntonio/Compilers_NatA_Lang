/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2023
* Author: David Burchat, Marcos Astudillo Carrasco
* Student Number: 040513895 & 041057439
* Lab Section: 011
* Date: OCT 3, 2023
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
* File name: Compilers.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011]
* Assignment: A12, A22, A32.
* Date: OCT 3, 2023
* Professor: Paulo Sousa
* Purpose: This file defines the functions called by main function.
* Function list: mainReader(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/* Language name */
#define STR_LANGNAME	"NatA"

/* Logical constants - adapt for your language */
#define TRUE  1
#define FALSE 0

/*
------------------------------------------------------------
Keywords definitions
------------------------------------------------------------
*/

#define BREAK       "break"
#define DEFAULT     "default"
#define FUNC        "func"
#define INTERFACE   "interface"
#define SELECT      "select"
#define DEFER       "defer"
#define MAP         "map"
#define STRUCT      "struct"
#define ELSE        "else"
#define PACKAGE     "package"
#define CONST       "const"
#define FALLTHROUGH "fallthrough"
#define IF          "if"
#define RANGE       "range"
#define TYPE        "type"
#define CONTINUE    "continue"
#define FOR         "for"
#define IMPORT      "import"
#define RETURN      "return"
#define VAR         "var"

/*
------------------------------------------------------------
Data types definitions
NOTE: Some types may not be directly used by your language,
		but they can be necessary for conversions.
------------------------------------------------------------
*/


/* TypeDef's based on Go Lang [4]  */
typedef char			int8;
typedef char*			string;
typedef float			float32;
typedef unsigned char	byte;
/* No void type in Go, for .c and .h files, using c void keyword as needed */
typedef unsigned char	bool2; /* bool is the data type for go lang, however .h files think it is apart of C lang
but .c files do not. Will not allow to type def it in compilers.h but at the same time cannot use it in .h files
calling it bool2 for the purposes of this lab */


typedef long			int64;
typedef double			float64;

/*
------------------------------------------------------------
Programs:
1: Reader - invokes MainReader code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_READER	= 'r',
	PGM_SCANNER = 's',
	PGM_PARSER	= 'p'
};

/*
------------------------------------------------------------
Main functions signatures
(Code will be updated during next assignments)
------------------------------------------------------------
*/
int mainReader(int argc, string* argv);
int mainScanner(int argc, string* argv);

/* 
TO_DO: Include later mainScaner (A22) and mainParser (A32)
*/
void printLogo();

#endif
