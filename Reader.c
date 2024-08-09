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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011]
* Assignment: A12.
* Date: OCT 3, 2023
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to initial (default) values.

*************************************************************
*/

BufferPointer readerCreate(int size, int increment, int mode) {
	BufferPointer readerPointer;
	/* Defensive programming */
	if (size < 0 || increment < 0 || (mode != MODE_FIXED && mode != MODE_ADDIT && mode != MODE_MULTI)) {
		fprintf(stderr, "Error: Invalid Parameters.\n");
		return NATA_NULL;
	}

	/* Assigning default values as necessary */
	if (size == 0) {
		size = READER_DEFAULT_SIZE;
		increment = READER_DEFAULT_INCREMENT;
	}
	if (increment == 0) {
		mode = MODE_FIXED;
	}
	/* Adjust the values according to parameters */
	readerPointer = (BufferPointer)calloc(1, sizeof(Buffer));
	if (!readerPointer) {
		fprintf(stderr, "Error: Cannot add memory to the Reader.\n");
		return NATA_NULL;
	}
	readerPointer->content = (string)malloc(size);
	/* Defensive programming */
	if (!readerPointer->content) {
		fprintf(stderr, "Error: Cannot add memory of the content of Reader.\n");
		free(readerPointer); // Avoid memory leaks
		return NATA_NULL;
	}

	/* Initialize the histogram */
	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;

	/* Initialize flags */
	readerPointer->flags = READER_DEFAULT_FLAG;

	/*The created flag must be signalized as EMP */
	readerPointer->flags |= FLAG_EMP;

	/* NEW: Cleaning the content */
	if (readerPointer->content)
		readerPointer->content[0] = READER_TERMINATOR;

	readerPointer->position.wrte = 0;
	readerPointer->position.mark = 0;
	readerPointer->position.read = 0;
	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
*************************************************************
*/

BufferPointer readerAddChar(BufferPointer const readerPointer, int8 ch) {
	string tempReader = NATA_NULL;
	int newSize = 0;

	/* Defensive programming */
	if (!readerPointer || ch<0) {
		return NATA_NULL; // Return if the buffer pointer is NULL or the character is not valid
	}

	/* Update histogram */
	readerPointer->histogram[(int)ch]++;

	/* Reset Realocation */
	readerPointer->flags &= ~FLAG_REL;

	/* Test the inclusion of chars */
	if (readerPointer->position.wrte * (int)sizeof(int8) < readerPointer->size) {
		/* This buffer is NOT full */
		readerPointer->content[readerPointer->position.wrte++] = ch;
		/* Reset EMP flag */
		readerPointer->flags &= ~FLAG_EMP;
	}
	else {
		switch (readerPointer->mode) {
		case MODE_FIXED:
			/* Set FUL flag */
			readerPointer->flags |= FLAG_FUL;
			return NATA_NULL;
		case MODE_ADDIT:
			newSize = readerPointer->size + readerPointer->increment;
			break;
		case MODE_MULTI:
			newSize = readerPointer->size * readerPointer->increment;
			break;
		default:
			return NATA_NULL;
		}

		/* Defensive programming */
		if (newSize < 0 || newSize > READER_MAX_SIZE) {
			/* Set FUL flag */
			readerPointer->flags |= FLAG_FUL;
			return NATA_NULL;
		}

		/* New reader allocation */
		tempReader = (string)realloc(readerPointer->content, newSize);
		if (!tempReader) {
			/* Set FUL flag */
			readerPointer->flags |= FLAG_FUL;
			return NATA_NULL;
		}

		/* Check Relocation */
		if (tempReader != readerPointer->content) {
			readerPointer->flags |= FLAG_REL;
		}

		readerPointer->content = tempReader;
		readerPointer->size = newSize;

		/* Add the char */
		readerPointer->content[readerPointer->position.wrte++] = ch;

		/* Check if buffer is now full */
		if (readerPointer->position.wrte * (int)sizeof(int8) >= readerPointer->size) {
			/* Set FUL flag */
			readerPointer->flags |= FLAG_FUL;
		}
	}

	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool2 readerClear(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return FALSE;
	}

	/* Adjust flags to original */
	readerPointer->flags = READER_DEFAULT_FLAG;

	/* Reset all positions */
	readerPointer->position.wrte = readerPointer->position.mark = readerPointer->position.read = 0;

	return TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool2 readerFree(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return FALSE;
	}

	/* Free pointers */
	free(readerPointer->content);
	free(readerPointer);

	return TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool2 readerIsFull(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return FALSE;
	}

	/* Check flag if buffer is FUL */
	if (readerPointer->flags & FLAG_FUL) {
		return TRUE;
	}

	return FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool2 readerIsEmpty(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return FALSE;
	}

	/* Check flag if buffer is EMP */
	if (readerPointer->flags & FLAG_EMP) {
		return TRUE;
	}

	return FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
bool2 readerSetMark(BufferPointer const readerPointer, int mark) {
	/* Defensive programming */
	if (readerPointer == NATA_NULL) {
		return FALSE; // Return False if the buffer pointer is NULL
	}

	/* Check if the flag is valid, it must be between 0 and the write position */
	if (mark < 0 || mark > readerPointer->position.wrte) {
		return FALSE; // Retorna falso si la marca no es válida
	}

	/* Adjust the Mark */
	readerPointer->position.mark = mark;
	return TRUE;
}

/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
*************************************************************
*/
int readerPrint(BufferPointer const readerPointer) {
	int cont = 0;
	int8 c;
	/* Defensive programming */
	if (readerPointer == NATA_NULL) {
		return READER_ERROR; // Return error is the buffer pointer is NULL
	}

	c = readerGetChar(readerPointer);
	/* Check flag if buffer EOB has achieved */
	while (cont < readerPointer->position.wrte && !(readerPointer->flags & FLAG_END)) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
*************************************************************
*/
int readerLoad(BufferPointer const readerPointer, FILE* const fileDescriptor) {
	int size = 0;
	int8 c;
	/* Defensive programming */
	if (readerPointer == NATA_NULL || fileDescriptor == NATA_NULL) {
		return READER_ERROR; // Return error if the buffer pointer or the file descriptor is NUll
	}
	c = (int8)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
*************************************************************
*/
bool2 readerRecover(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (readerPointer == NATA_NULL) {
		return FALSE; // Return FALSE is the buffer pointer is NULL
	}
	/* Recover positions */
	readerPointer->position.read = 0;
	readerPointer->position.mark = 0;
	return TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool2 readerRetract(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (readerPointer == NATA_NULL) {
		return FALSE; // Return FALSE is the buffer pointer is NULL
	}
	/* Retract (return 1 pos read) */
	if (readerPointer->position.read > 0) {
		readerPointer->position.read--;
	}
	return TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool2 readerRestore(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (readerPointer == NATA_NULL) {
		return FALSE; // Return FALSE is the buffer pointer is NULL
	}
	/* Restore positions (read/mark) */
	readerPointer->position.read = readerPointer->position.mark;
	return TRUE;
}


/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
*************************************************************
*/
int8 readerGetChar(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (readerPointer == NATA_NULL) {
		return READER_TERMINATOR; // Returns the terminator if the buffer pointer is NULL
	}
	/* Check condition to read/write */
	if (readerPointer->position.read == readerPointer->position.wrte) {
		/* Set EOB flag */
		readerPointer->flags |= FLAG_END;
		return READER_TERMINATOR;
	}
	/* Reset EOB flag */
	readerPointer->flags &= ~FLAG_END;
	return readerPointer->content[readerPointer->position.read++];
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
*************************************************************
*/
string readerGetContent(BufferPointer const readerPointer, int pos) {
	/* Defensive programming */
	if (readerPointer == NATA_NULL || pos < 0 || pos >= readerPointer->position.wrte) {
		return NATA_NULL; // Returns NULL if the buffer pointer is NULL or the position is invalid
	}
	/* Return content (string) */
	return readerPointer->content + pos;
}

/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
*************************************************************
*/
int readerGetPosRead(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (readerPointer == NATA_NULL) {
		return -1; // Returns -1 if the buffer pointer is NULL
	}
	/* Return read */
	return readerPointer->position.read;
}



/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
*************************************************************
*/
int readerGetPosWrte(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (readerPointer == NATA_NULL) {
		return -1; // Returns -1 if the buffer pointer is NULL
	}
	/* Return wrte */
	return readerPointer->position.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
*************************************************************
*/
int readerGetPosMark(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (readerPointer == NATA_NULL) {
		return -1; // Returns -1 if the buffer pointer is NULL
	}
	/* Return mark */
	return readerPointer->position.mark;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
*************************************************************
*/
int readerGetSize(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (readerPointer == NATA_NULL) {
		return -1; // Returns -1 if the buffer pointer is NULL
	}
	/* Return size */
	return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
*************************************************************
*/
int readerGetInc(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (readerPointer == NATA_NULL) {
		return -1; // Returns -1 if the buffer pointer is NULL
	}
	/* Return increment */
	return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
*************************************************************
*/
int readerGetMode(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (readerPointer == NATA_NULL) {
		return -1; // Returns - 1 if the buffer pointer is NULL
	}
	/* Return mode */
	return readerPointer->mode;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
*************************************************************
*/
byte readerGetFlags(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (readerPointer == NATA_NULL) {
		return 0; // Returns - 1 if the buffer pointer is NULL
	}
	/* Return flags */
	return readerPointer->flags;
}



/*
***********************************************************
* Function name: readerPrintStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
*************************************************************
*/
void readerPrintStat(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (readerPointer == NATA_NULL) {
		return; // Return if the buffer pointer is NULL
	}
	/* Print the histogram */
	int count = 0;
	for (int i = 0; i < NCHAR; i++) {
		if (readerPointer->histogram[i] > 0 && (i >= 32 && i <= 126)) {
			printf("%c[%d]\t", i, readerPointer->histogram[i]);
			count++;
			if (count % 10 == 0) { // If 10 values have been printed, print a line break
				printf("\n");
			}
		}
	}
	if (count % 10 != 0) { // If the last line printed does not contain 10 values, print a line break
		printf("\n");
	}
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
*************************************************************
*/
int readerNumErrors(BufferPointer const readerPointer) {
	/* Defensive programming */
	if (readerPointer == NATA_NULL) {
		return READER_ERROR; // Return an error if the buffer pointer is NULL
	}
	/* Returns the number of errors */
	return readerPointer->numReaderErrors;
}
