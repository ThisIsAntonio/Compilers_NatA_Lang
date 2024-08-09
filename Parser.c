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
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A32.
* Date: May 01 2023
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/* Parser data */
extern ParserData psData; /* BNF statistics */

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

void startParser() {
	/* TO_DO: Initialize Parser data */
	int i = 0;
	for (i = 0; i < NUM_BNF_RULES; i++) {
		psData.parsHistogram[i] = 0;
	}
	/* Proceed parser */
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
void matchToken(int tokenCode, int tokenAttribute) {
	int matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
void syncErrorHandler(int syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
void printError() {
	extern numParserErrors;			/* link to number of errors (defined in Parser.h) */
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case EOS_T:
		printf("NA\n");
		break;
	case CMT_T:
		printf("CMT_T\n");
		break;
	case DOT_T:
		printf("DOT_T\n");
		break;
	case VAR_T:
		printf("VAR_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case INL_T:
		printf("INL_T\t\t%d\n", t.attribute.intValue);
		break;
	case ADD_T:
		printf("ADD_T\n");
		break;
	case SUB_T:
		printf("SUB_T\n");
		break;
	case MUL_T:
		printf("MUL_T\n");
		break;
	case DIV_T:
		printf("DIV_T\n");
		break;
	case EQAS_T:
		printf("EQAS_T\n");
		break;
	case COM_T:
		printf("COM_T\n");
		break;
	case OPEQ_T:
		printf("OPEQ_T\n");
		break;
	case OPNE_T:
		printf("OPNE_T\n");
		break;
	case OPGT_T:
		printf("OPGT_T\n");
		break;
	case OPLT_T:
		printf("OPLT_T\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
		numParserErrors++; // Updated parser error
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {CMT_T, MNID_T (main&), SEOF_T}.
 ***********************************************************
 */
void program() {
	/* Update program statistics */
	psData.parsHistogram[BNF_program]++;
	/* Program code */
	switch (lookahead.code) {
	case KW_T:
		dataSession();
		codeSession();
	//case MNID_T:
	//	codeSession();
	case SEOF_T:
		matchToken(SEOF_T, NO_ATTR);
		; // Empty
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * comment
 * BNF: comment
 * FIRST(<comment>)= {CMT_T}.
 ***********************************************************
 */
void comment() {
	psData.parsHistogram[BNF_comment]++;
	matchToken(CMT_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Comment parsed");
}

/*
 ************************************************************
 * dataSession
 * BNF: <dataSession> -> data { <opt_varlist_declarations> }
 * FIRST(<program>)= {KW_T (KW_data)}.
 ***********************************************************
 */
void dataSession() {
	psData.parsHistogram[BNF_dataSession]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	default:
		matchToken(KW_T, KW_PACKAGE);
		//matchToken(LBR_T, NO_ATTR);
		optVarListDeclarations();
		//matchToken(RBR_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": Data Session parsed");
	}
}

/*
 ************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_real), KW_T (KW_string)}.
 ***********************************************************
 */
void optVarListDeclarations() {
	psData.parsHistogram[BNF_optVarListDeclarations]++;
	varListDeclarations();
	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}

/*
 ************************************************************
 * codeSession statement
 * BNF: <codeSession> -> code { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 ***********************************************************
 */
void codeSession() {
	psData.parsHistogram[BNF_codeSession]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	default:
		while (lookahead.code  == KW_T) {
			matchToken(KW_T, KW_FUNC);
			//Call declarations 
			funcDeclaration();
			matchToken(LBR_T, NO_ATTR);
			while (lookahead.code != RBR_T) {
				optVarListDeclarations();
				optionalStatements();
				if (lookahead.attribute.codeType == KW_RETURN) {
					matchToken(KW_T, KW_RETURN);
					matchToken(VAR_T, NO_ATTR);
				}
			}
			matchToken(RBR_T, NO_ATTR);
			/*if (lookahead.code != KW_T) {
				break;
			}*/
		}
		printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
	}
}

/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(Println), MNID_T(input) }
 ***********************************************************
 */
void optionalStatements() {
	psData.parsHistogram[BNF_optionalStatements]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	case MNID_T:
		if ((strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 7) == 0) ||
			(strncmp(lookahead.attribute.idLexeme, LANG_READ, 5) == 0)) {
			statements();
			break;
		}
	case VAR_T:
		varListDeclarations();
		break;
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
void statements() {
	psData.parsHistogram[BNF_statements]++;
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
void statementsPrime() {
	psData.parsHistogram[BNF_statementsPrime]++;
	switch (lookahead.code) {
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 7) == 0) {
			statements();
			break;
		}
	default:
		; //empty string
	}
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
void statement() {
	psData.parsHistogram[BNF_statement]++;
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case KW_IF:
			ifStatement();
			break;
		case KW_WHILE:
			whileStatement();
			break;
		case KW_DO:
			doStatement();
			break;
		case KW_FOR:
			forStatement();
			break;
		default:
			printError();
		}
		break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 7) == 0) {
			outputStatement();
		}
		break;
	case VAR_T: /* < ================================================= check */
		varListDeclaration();
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> Println (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(Println) }
 ***********************************************************
 */
void outputStatement() {
	psData.parsHistogram[BNF_outputStatement]++;
	matchToken(MNID_T, NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	optVarListDeclarations();
	if (lookahead.code == COM_T) {
		matchToken(COM_T, NO_ATTR);
		optVarListDeclarations();
	}
	matchToken(RPR_T, NO_ATTR);
	//matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
//void outputVariableList() {
//	psData.parsHistogram[BNF_outputVariableList]++;
//	switch (lookahead.code) {
//	case STR_T:
//		matchToken(STR_T, NO_ATTR);
//	case INL_T:
//		matchToken(INL_T, NO_ATTR);
//	case ADD_T:
//		matchToken(ADD_T, NO_ATTR);
//	default:
//		;
//	}
//	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
//}

/*
 ************************************************************
 * The function prints statistics of BNF rules
 * Param:
 *	- Parser data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
/*
void printBNFData(ParserData psData) {
}
*/
void printBNFData(ParserData psData) {
	/* Print Parser statistics */
	printf("Statistics:\n");
	printf("----------------------------------\n");
	int cont = 0;
	for (cont = 0; cont < NUM_BNF_RULES; cont++) {
		if (psData.parsHistogram[cont] > 0)
			printf("%s%s%s%d%s", "Token[", BNFStrTable[cont], "]=", psData.parsHistogram[cont], "\n");
	}
	printf("----------------------------------\n");
}


/* <==================== ADDED ================== */
void funcDeclaration() {
	psData.parsHistogram[BNF_optVarListDeclarations]++;
	if (lookahead.code == MNID_T) {
		matchToken(MNID_T, NO_ATTR);
	}
	else {
		matchToken(VAR_T, NO_ATTR);
	}
		matchToken(LPR_T, NO_ATTR);
		if (lookahead.code != RPR_T) {
			while (lookahead.code != RPR_T) {
				//parameter();
				optVarListDeclarations();
			}
		}
		matchToken(RPR_T, NO_ATTR);
		if (lookahead.code == KW_T) {
			matchToken(KW_T, KW_INT);
		}
	printf("%s%s\n", STR_LANGNAME, ": Function Declaration parsed");
}

void varListDeclarations() {
	psData.parsHistogram[BNF_varListDeclarations]++;
	varListDeclaration();
	//arithmeticExpression();
	printf("%s%s\n", STR_LANGNAME, ": Variable List Declarations parsed");
}

void varListDeclaration() {
	psData.parsHistogram[BNF_varListDeclaration]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
			break;
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		switch (lookahead.code) {
		case COM_T:
			matchToken(COM_T, NO_ATTR);
			break;
		case ADD_T:
		case SUB_T:
		case MUL_T:
		case DIV_T:
		case LPR_T:
			arithmeticExpression();
		}
		break;
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		if (lookahead.code == EQAS_T) {
			assignmentStatement();
		}
		if (lookahead.code == OPEQ_T) {
			logicalEqualsExpression();
		}
		if (lookahead.attribute.codeType == KW_INT) {
			matchToken(KW_T, KW_INT);
		}

		if (lookahead.code == COM_T) {
			matchToken(COM_T, NO_ATTR);
		}
		break;
	case KW_T:
		statements();
		break;
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Variable List Declaration parsed");
}


void assignmentStatement() {
	psData.parsHistogram[BNF_assignmentStatement]++;
	switch (lookahead.code) {
	case EQAS_T:
			matchToken(EQAS_T,NO_ATTR);
			if (lookahead.code != MNID_T) {
				arithmeticExpression();
			}
			else {
				funcDeclaration();
			}

		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Assignment Statement parsed");
}

void logicalEqualsExpression() {
	psData.parsHistogram[BNF_logicalEqualsExpression]++;
	while (lookahead.code == OPEQ_T) {
		matchToken(OPEQ_T, NO_ATTR);
		relationalExpression();
	}

	printf("%s%s\n", STR_LANGNAME, ": Logical Equals Expression parsed");
}

void arithmeticExpression() { /* modified */
	psData.parsHistogram[BNF_arithmeticExpression]++;
	additiveArithmeticExpression();
	printf("%s%s\n", STR_LANGNAME, ": Arithmetic Expression parsed");
}

void unaryArithmeticExpression() { /* modified */
	psData.parsHistogram[BNF_unaryArithmeticExpression]++;
	if (lookahead.code == ADD_T || lookahead.code == SUB_T) {
		matchToken(lookahead.code, NO_ATTR);
	}
	primaryArithmeticExpression();
	printf("%s%s\n", STR_LANGNAME, ": Unary Arithmetic Expression parsed");
}

void additiveArithmeticExpression() { /* modified */
	psData.parsHistogram[BNF_additiveArithmeticExpression]++;
	multiplicativeArithmeticExpression();

	while (lookahead.code == ADD_T || lookahead.code == SUB_T) {
		matchToken(lookahead.code, NO_ATTR);
		multiplicativeArithmeticExpression();
	}
	printf("%s%s\n", STR_LANGNAME, ": Additive Arithmetic Expression parsed");
}

void multiplicativeArithmeticExpression() { /* modified */
	psData.parsHistogram[BNF_multiplicativeArithmeticExpression]++;
	unaryArithmeticExpression();

	while (lookahead.code == MUL_T || lookahead.code == DIV_T) {
		matchToken(lookahead.code, NO_ATTR);
		unaryArithmeticExpression();
	}
	printf("%s%s\n", STR_LANGNAME, ": Multiplicative Arithmetic Expression parsed");
}

void primaryArithmeticExpression() { /* modified */
	psData.parsHistogram[BNF_primaryArithmeticExpression]++;
	switch (lookahead.code) {
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		break;
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		break;
	case LPR_T:
		matchToken(LPR_T, NO_ATTR);
		arithmeticExpression();
		matchToken(RPR_T, NO_ATTR);
		break;
	default:
		// Syntaxis Error
		printError();
		break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Primary Arithmetic Expression parsed");
}

void conditionalExpression() {
	psData.parsHistogram[BNF_conditionalExpression]++;
	logicalOrExpression();

	printf("%s%s\n", STR_LANGNAME, ": Conditional Expression parsed");
}

void logicalOrExpression() {
	psData.parsHistogram[BNF_logicalOrExpression]++;
	logicalAndExpression();
	while (lookahead.code == OPOR_T) {
		matchToken(OPOR_T, NO_ATTR);
		logicalAndExpression();
	}
	printf("%s%s\n", STR_LANGNAME, ": Logical Or Expression parsed");
}

void logicalAndExpression() {
	psData.parsHistogram[BNF_logicalAndExpression]++;
	logicalNotExpression();
	while (lookahead.code == OPAND_T) {
		matchToken(OPAND_T, NO_ATTR);
		logicalNotExpression();
	}
	printf("%s%s\n", STR_LANGNAME, ": Logical And Expression parsed");
}

void logicalNotExpression() {
	psData.parsHistogram[BNF_logicalNotExpression]++;
	if (lookahead.code == OPNOT_T) {
		matchToken(OPNOT_T, NO_ATTR);
	}
	relationalExpression();
	printf("%s%s\n", STR_LANGNAME, ": Logical Not Expression parsed");
}

void relationalExpression() {
	psData.parsHistogram[BNF_relationalExpression]++;
	primaryArithmeticRelationalExpression();
	if (lookahead.code == OPEQ_T || lookahead.code == OPNE_T ||
		lookahead.code == OPGT_T || lookahead.code == OPLT_T) {
		matchToken(lookahead.code, NO_ATTR);
		primaryArithmeticRelationalExpression();
	}
	printf("%s%s\n", STR_LANGNAME, ": Relational Expression parsed");
}

void primaryArithmeticRelationalExpression() {
	psData.parsHistogram[BNF_primaryArithmeticRelationalExpression]++;
	if (lookahead.code == VAR_T) {
		matchToken(VAR_T, NO_ATTR);
	}
	else if (lookahead.code == INL_T) {
		matchToken(INL_T, NO_ATTR);
	}
	else {
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Primary Arithmetic Relational Expression parsed");
}


/* if, do, while and for statemens */

void ifStatement() {
	psData.parsHistogram[BNF_ifStatement]++;
	matchToken(KW_T, KW_IF); // 'if'
	matchToken(LPR_T, NO_ATTR); // '('

	conditionalExpression(); // Evaluate the condition

	matchToken(RPR_T, NO_ATTR); // ')'
	matchToken(LBR_T, NO_ATTR); // '{'

	optionalStatements(); // Handle statements within the 'if'

	matchToken(RBR_T, NO_ATTR); // '}'
	printf("%s%s\n", STR_LANGNAME, ": If statement parsed");
}

void whileStatement() {
	psData.parsHistogram[BNF_whileStatement]++;
	matchToken(KW_T, KW_WHILE); // 'while'
	matchToken(LPR_T, NO_ATTR); // '('

	conditionalExpression(); // Evaluate the condition

	matchToken(RPR_T, NO_ATTR); // ')'
	matchToken(LBR_T, NO_ATTR); // '{'

	optionalStatements(); // Handle statements within the 'while'

	matchToken(RBR_T, NO_ATTR); // '}'
	printf("%s%s\n", STR_LANGNAME, ": While statement parsed");
}

void doStatement() {
	psData.parsHistogram[BNF_doStatement]++;
	matchToken(KW_T, KW_DO); // 'do'
	matchToken(LBR_T, NO_ATTR); // '{'

	optionalStatements(); // Handle statements within the  'do'

	matchToken(RBR_T, NO_ATTR); // '}'
	matchToken(KW_T, KW_WHILE); // 'while'
	matchToken(LPR_T, NO_ATTR); // '('

	conditionalExpression(); // Evaluate the condition

	matchToken(RPR_T, NO_ATTR); // ')'
	matchToken(EOS_T, NO_ATTR); // ';'
	printf("%s%s\n", STR_LANGNAME, ": Do statement parsed");
}

void forStatement() {
	psData.parsHistogram[BNF_forStatement]++;
	matchToken(KW_T, KW_FOR); // 'for'
	matchToken(LPR_T, NO_ATTR); // '('

	if (lookahead.code == LBR_T) {
		// Infinite loop
		matchToken(LBR_T, NO_ATTR); // '{'
		optionalStatements();
		matchToken(RBR_T, NO_ATTR); // '}'
	}
	else {
		// Possible loop with initialization, condition and update
		if (lookahead.code != EOS_T) {
			// Initialization (if exists)
			statement();
		}
		if (lookahead.code != EOS_T) {
			// Condition (if exists)
			conditionalExpression();
		}
		if (lookahead.code != RPR_T) {
			// Update (if exists)
			statement();
		}
		matchToken(RPR_T, NO_ATTR); // ')'
		matchToken(LBR_T, NO_ATTR); // '{'
		optionalStatements();
		matchToken(RBR_T, NO_ATTR); // '}'
	}

	printf("%s%s\n", STR_LANGNAME, ": For statement parsed");
}



