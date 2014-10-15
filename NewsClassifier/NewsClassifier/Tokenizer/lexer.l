%option noyywrap
%{


#include <QtScript>
#include "tokens.h"

%}

letter [a-zA-ZŠšČčĆćŽžĐđ]
digit [0-9]
punct [,.:;!?]
spaces [ \t\n]
special_chars [\+\-\*\/\\\"\(\)\[\]\'\=\_\|]

/*
* Here is the list of special cases that I have run into during the testing:
*
* ignoring both single and double quotes. ex. "pera" = pera
* ignoring /. ex. pravi/prava = pravi prava
* ignoring parethesis. ex. (ni)je = nije ex. (pera) = pera
* B92 is recognized as B NUMBER
*/


%%
"> Izvor:".*\n  { return HEADER_SOURCE; }
"> Datum:".*\n  { return HEADER_DATE; }
"> Rubrika:".*\n   {
                        /* here is the calculation: string "> Rubrika: " has 11 characters
                        and at the end we have one more char \n */

                        int i = 0, j = 11;
                        while (yytext[j] != '\n')
                        {
                            yytext[i] = yytext[j];

                            i++;
                            j++;
                        }

                        for (; i < yyleng; i++)
                        {
                            yytext[i] = 0;
                        }
                        return HEADER_NEWS_GROUP;
                   }
"> Naslov:".*\n     { return HEADER_CAPTION; }
"> Članak:".*\n  { return HEADER_ARTICLE_BEGINNING; }

{letter}+   { return WORD; }
{punct}+    { return PUNCT; }
{digit}+    { return NUMBER; }
{spaces}+   { return SPACES; }

"B92"|"b92" { return WORD; }

{special_chars}+ ;
[^(letter|punct|digit|spaces|special_chars)] ;

%%
