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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011]
* Assignment: A12.
* Date: OCT 3, 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR		(-1)						/* General error message */
#define READER_TERMINATOR	'\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (NatA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10  [1] */
/* [2] */
#define FLAG_END 0x08 /* 0000 1000 in Base 2 */
#define FLAG_REL 0x04 /* 0000 0100 in Base 2 */
#define FLAG_EMP 0x02 /* 0000 0010 in Base 2 */
#define FLAG_FUL 0x01 /* 0000 0001 in Base 2 */

#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */
#define NATA_NULL			NULL			

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */


/* Offset declaration */
typedef struct position {
	int mark;			/* the offset to the mark position (in chars) */
	int read;			/* the offset to the get a char position (in chars) */
	int wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	string	content;			/* pointer to the beginning of character array (character buffer) */
	int		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	int		increment;			/* character array increment factor */
	int		mode;				/* operational mode indicator */
	byte		flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		position;				/* Offset / position field */
	int		histogram[NCHAR];	/* Statistics of chars */
	int		numReaderErrors;	/* Number of errors from Reader */
} Buffer, *BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
BufferPointer	readerCreate		(int, int, int);
BufferPointer	readerAddChar		(BufferPointer const, int8);
bool2		readerClear		    (BufferPointer const);
bool2		readerFree		    (BufferPointer const);
bool2		readerIsFull		(BufferPointer const);
bool2		readerIsEmpty		(BufferPointer const);
bool2		readerSetMark		(BufferPointer const, int);
int		readerPrint		    (BufferPointer const);
int		readerLoad			(BufferPointer const, FILE* const);
bool2		readerRecover		(BufferPointer const);
bool2		readerRetract		(BufferPointer const);
bool2		readerRestore		(BufferPointer const);
/* Getters */
int8		readerGetChar		(BufferPointer const);
string	readerGetContent	(BufferPointer const, int);
int		readerGetPosRead	(BufferPointer const);
int		readerGetPosWrte	(BufferPointer const);
int		readerGetPosMark	(BufferPointer const);
int		readerGetSize		(BufferPointer const);
int		readerGetInc		(BufferPointer const);
int		readerGetMode		(BufferPointer const);
byte		readerGetFlags		(BufferPointer const);
void		readerPrintStat		(BufferPointer const);
int		readerNumErrors		(BufferPointer const);

#endif
