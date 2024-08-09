/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2023
* Author: David Burchat, Marcos Astudillo Carrasco
* Student Number: 040513895 & 041057439
* Lab Section: 011
* Date: OCT 3, 2023
* Professors: Paulo Sousa
* References:
* [1] 	Wikipedia, "Wikipedia - Bit field," 23 Sept 2023. [Online]. 
*		Available: https://en.wikipedia.org/wiki/Bit_field. [Accessed 02 Oct 2023].
* [2] 	Flexera, "Using Bit Flags," Jan 2018. [Online]. 
		Available: https://docs.revenera.com/installshield24helplib/installshield24helplib.htm#helplibrary/BitFlags.htm. [Accessed 02 Oct 2023].
* [3] 	D. Tack, "Using bit flags in C++," 26 Nov 2020. [Online]. 
		Available: https://dietertack.medium.com/using-bit-flags-in-c-d39ec6e30f08. [Accessed 02 Oct 2023].
* [4] 	G. Team, "The GO Programming Language Specification," 02 Aug 2023. [Online]. 
		Available: https://go.dev/ref/spec#Operators. [Accessed 02 Oct 2023].
* [5] 	S. users, "Understanding Double Buffering in Lexical Analyzer," 12 Dec 2021. [Online]. 
		Available: https://stackoverflow.com/questions/70321679/understanding-double-buffering-in-lexical-analyzer. [Accessed 02 Oct 2023].
* [6] 	G. User, "Input Buffering in Compiler Design," 18 Apr 2023. [Online]. 
		Available: https://www.geeksforgeeks.org/input-buffering-in-compiler-design/. [Accessed 02 Oct 2023].
* [7] 	M. Cobb, "Buffer Overflow," Jul 2021. [Online]. 
		Available: https://www.techtarget.com/searchsecurity/definition/buffer-overflow. [Accessed 02 Oct 2023].
* [8] 	T. Plum and D. M. Keaton, "Samate - Eliminating Buffer Overflows, Using the Compiler or a Standalone Tool," Nov 2005. [Online]. 
		Available: https://samate.nist.gov/SSATTM_Content/papers/Eliminating%20Buffer%20Overflows%20-%20Plum%20-%20Keaton.pdf. [Accessed 02 Oct 2023].
* [9] 	F. Users, "Input Buffering," 02 Oct 2023. [Online]. 
		Available: http://www.faadooengineers.com/online-study/post/cse/compiler-design/224/input-buffering#!. [Accessed 02 Oct 2023].

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
* File name: compilers.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011]
* Assignment: A12, A22, A32.
* Date: OCT 3, 2023
* Professor: Paulo Sousa
* Purpose: This file is the main program of Compilers Project
* Function list: main().
************************************************************
*/


#include <stdio.h>
#include <stdlib.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif


/*
***********************************************************
* Function name: main
* Purpose: Main function
* Author: Paulo Sousa
* History/Versions: Ver F22
* Called functions: mainReader(), mainScanner(), mainParser()
* Parameters: Command line arguments - argc, argv
* Return value: Status
*************************************************************
*/

int main(int argc, string* argv) {
	int i;
	printLogo();
	if (DEBUG) {
		for (i = 0; i < argc; ++i)
			printf("argv[%d] = %s\n", i, argv[i]);
	}
	if (argc < 2) {
		printf("%s%c%s%c%s%c%s", "OPTIONS:\n* [",
			PGM_READER, "] - Reader\n* [",
			PGM_SCANNER, "] - Scanner\n* [",
			PGM_PARSER, "] - Parser\n");
		return EXIT_FAILURE;
	}
	int8 option = argv[1][0];
	switch (option) {
	case PGM_READER:
		printf("%s%c%s", "\n[Option '", PGM_READER, "': Starting READER .....]\n\n");
		mainReader(argc, argv);
		break;
		/* TO_DO: Include later SCANNER (A22) and PARSER (A32) */
	case PGM_SCANNER:
		printf("%s%c%s", "\n[Option '", PGM_SCANNER, "': Starting SCANNER .....]\n\n");
		mainScanner(argc, argv);
		break;

	case PGM_PARSER:
		printf("%s%c%s", "\n[Option '", PGM_PARSER, "': Starting PARSER .....]\n\n");
		mainParser(argc, argv);
		break;
	default:
		printf("%s%c%s%c%s%c%s", "* OPTIONS:\n- [",
			PGM_READER, "] - Reader\n- [",
			PGM_SCANNER, "] - Scanner\n- [",
			PGM_PARSER, "] - Parser\n");
		break;
	}
	return EXIT_SUCCESS;
}

/*
***********************************************************
* Function name: printLogo
* Purpose: Print Logo
* Author: Paulo Sousa
* History/Versions: Ver S23
* Called functions: -
* Parameters: -
* Return value: (Null)
*************************************************************
*/
/* Disregard warning, arguments for printf match the amount of strings.*/
void printLogo() {
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
		"\t=---------------------------------------=\n",
		"\t|  COMPILERS - ALGONQUIN COLLEGE (F23)  |\n",
		"\t=---------------------------------------=\n",
		"\t|              ....                     |\n",
		"\t|          ........::.::::::.           |\n",
		"\t|        .:........::.:^^^~~~:          |\n",
		"\t|        :^^::::::^^^::^!7??7~^.        |\n",
		"\t|       .:^~~^!77777~~7?YY?7??7^.       |\n",
		"\t|       :.^~!??!^::::^^~!?5PY??!~.      |\n",
		"\t|       ~!!7J~.:::^^^^~!!~~?G5J?~       |\n",
		"\t|       :^~?!~7?Y57^^?PP5YJ!J5Y?:       |\n",
		"\t|       .~!!.:^!7!:.:7JYYJ7~7Y7^        |\n",
		"\t|       .~77..    . .~^:^^^~7?:         |\n",
		"\t|       .^!^~:::.:^!7?~^~!77J:          |\n",
		"\t|        ^^!Y~^^^^~?YJ77??7JJ^          |\n",
		"\t|       .^7J?~^~~^~7??7??7JY?~:         |\n",
		"\t|        ::^^~^7?!^~~!7???J?J7~:.       |\n",
		"\t|         ^~~!.^7YPPPP5Y?7J7777~.       |\n",
		"\t|        ..:~..:^!JPP5YJ?!777!^.        |\n",
		"\t| .~?JJJJJJJJJJYYYYYPPPPPPPPPPPP5PPYY~  |\n",
		"\t|	 N    N  AAAAA  TTTTT  AAAAA	|\n",
		"\t|	 NN   N  A   A    T    A   A	|\n",
		"\t|	 N N  N  AAAAA    T    AAAAA	|\n",
		"\t|	 N  N N  A   A    T    A   A	|\n",
		"\t|	 N   NN  A   A    T    A   A	|\n",
		"\t|                                       |\n",
		"\t=---------------------------------------=\n"
	);
}
