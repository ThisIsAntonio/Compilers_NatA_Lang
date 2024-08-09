:: ---------------------------------------------------------------------
:: COMPILERS COURSE - SCRIPT                                           -
:: SCRIPT A12 - CST8152 - Fall 2023                                    -
:: ---------------------------------------------------------------------

CLS
SET COMPILER=NatA.exe

SET NATAINPUT=input
SET FILE1=INPUT0_Empty
SET FILE2=INPUT1_Hello
SET FILE3=INPUT2_Volume
SET FILE4=INPUT3_Factorial
SET FILE5=INPUT4_Datatypes
SET FILE6=INPUT5_Big

SET ASSIGNMENT=A12
SET EXTENSION=nat
SET OUTPUT=out
SET ERROR=err

SET PARAM=r

:: ---------------------------------------------------------------------
:: Begin of Tests (A12 - F23) ------------------------------------------
:: ---------------------------------------------------------------------

@echo off

ECHO "=---------------------------------------="
ECHO "|  COMPILERS - ALGONQUIN COLLEGE (F23)  |"
ECHO "=---------------------------------------="
ECHO "|              ....                     |"
ECHO "|          ........::.::::::.           |"
ECHO "|        .:........::.:^^^~~~:          |"
ECHO "|        :^^::::::^^^::^!7??7~^.        |"
ECHO "|       .:^~~^!77777~~7?YY?7??7^.       |"
ECHO "|       :.^~!??!^::::^^~!?5PY??!~.      |"
ECHO "|       ~!!7J~.:::^^^^~!!~~?G5J?~       |"
ECHO "|       :^~?!~7?Y57^^?PP5YJ!J5Y?:       |"
ECHO "|       .~!!.:^!7!:.:7JYYJ7~7Y7^        |"
ECHO "|       .~77..    . .~^:^^^~7?:         |"
ECHO "|       .^!^~:::.:^!7?~^~!77J:          |"
ECHO "|        ^^!Y~^^^^~?YJ77??7JJ^          |"
ECHO "|       .^7J?~^~~^~7??7??7JY?~:         |"
ECHO "|        ::^^~^7?!^~~!7???J?J7~:.       |"
ECHO "|         ^~~!.^7YPPPP5Y?7J7777~.       |"
ECHO "|        ..:~..:^!JPP5YJ?!777!^.        |"
ECHO "| .~?JJJJJJJJJJYYYYYPPPPPPPPPPPP5PPYY~  |"
ECHO "|  :!Y5GGG.___ YYYYYY__._.PPGGGGGG5!.   |"
ECHO "|	    N    N  AAAAA  TTTTT  AAAAA	 |"
ECHO "|	    NN   N  A   A    T    A   A	 |"
ECHO "|	    N N  N  AAAAA    T    AAAAA	 |"
ECHO "|	    N  N N  A   A    T    A   A	 |"
ECHO "|	    N   NN  A   A    T    A   A	 |"
ECHO "|                                       |"
ECHO "=---------------------------------------="
ECHO "                                   "
ECHO "[READER SCRIPT .........................]"
ECHO "                                   "

::These ren commands were causing the batch file not to run, we commented them out
::ren *.exe %COMPILER%
::ren *.out
::ren *.err
::
:: BASIC TESTS  ----------------------------------------------------------
::
:: Basic Tests (A12 - F23) - - - - - - - - - - - - - - - - - - - - - -

%COMPILER% %PARAM% %NATAINPUT%/%FILE1%.%EXTENSION%	> %FILE1%-%ASSIGNMENT%.%OUTPUT%	2> %FILE1%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %NATAINPUT%/%FILE2%.%EXTENSION%	> %FILE2%-%ASSIGNMENT%.%OUTPUT%	2> %FILE2%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %NATAINPUT%/%FILE3%.%EXTENSION%	> %FILE3%-%ASSIGNMENT%.%OUTPUT%	2> %FILE3%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %NATAINPUT%/%FILE4%.%EXTENSION%	> %FILE4%-%ASSIGNMENT%.%OUTPUT%	2> %FILE4%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %NATAINPUT%/%FILE5%.%EXTENSION%	> %FILE5%-%ASSIGNMENT%.%OUTPUT%	2> %FILE5%-%ASSIGNMENT%.%ERROR%

::
:: ADVANCED TESTS  -------------------------------------------------------
::
:: Advanced Tests (A12 - F23) - - - - - - - - -- - - - - - - - - - - -
:: NOTE: For the .nat files, there are 5 general Files, the 6th file is the one with the large lorum ipsum file

%COMPILER% %PARAM% %FILE6%.%EXTENSION%	f 100 10	> %FILE6%-%ASSIGNMENT%-f-100-10.%OUTPUT%	2> %FILE6%-%ASSIGNMENT%-f-100-10.%ERROR%
%COMPILER% %PARAM% %FILE6%.%EXTENSION%	a 100 10	> %FILE6%-%ASSIGNMENT%-a-100-10.%OUTPUT%	2> %FILE6%-%ASSIGNMENT%-a-100-10.%ERROR%
%COMPILER% %PARAM% %FILE6%.%EXTENSION%	m 100 10	> %FILE6%-%ASSIGNMENT%-m-100-10.%OUTPUT%	2> %FILE6%-%ASSIGNMENT%-m-100-10.%ERROR%

:: SHOW OUTPUTS - - - - - - - - - - - - - - - - - - - - - - - - - - -
DIR *.OUT
DIR *.ERR

:: Marcos and I dislike having flashing batch file windows, this will prevent it from disappearing right away
:: We want to see it pop up, just incase there was a message that is important to view.
PAUSE
:: ---------------------------------------------------------------------
:: End of Tests (A12 - F23) --------------------------------------------
:: ---------------------------------------------------------------------
