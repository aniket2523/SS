%{
#include "y.tab.h"
#include<stdio.h>
#include<math.h>
%}
%%
[0-9]+(\.[0-9]*)?    {yylval.dval=atof(yytext); return NUMBER;}
[ \t] ;
\n   return 0;
.    return yytext[0];
sin  return SINE;
log  return nLOG;
sqrt return SQRT;
%%
int yywrap()
{
 return 1;
 }


This code combines Lex and Yacc (or Flex and Bison) to build a simple calculator that can evaluate arithmetic expressions and functions like sine, logarithm, and square root. Here is a detailed explanation of each part of the code:

### Lex (Lexer)

```c
%{
#include "y.tab.h"
#include<stdio.h>
#include<math.h>
%}
%%
[0-9]+(\.[0-9]*)?    {yylval.dval=atof(yytext); return NUMBER;}
[ \t] ;
\n   return 0;
.    return yytext[0];
sin  return SINE;
log  return nLOG;
sqrt return SQRT;
%%
int yywrap()
{
 return 1;
}
```

#### Lex Definitions and Rules

1. **Header Section** (`%{ ... %}`):
    - **`#include "y.tab.h"`**: Includes the Yacc-generated header file to use token definitions and the `yylval` union.
    - **`#include<stdio.h>`**: Standard input/output library.
    - **`#include<math.h>`**: Math library for mathematical functions.

2. **Rules Section** (`%% ... %%`):
    - **`[0-9]+(\.[0-9]*)? {yylval.dval=atof(yytext); return NUMBER;}`**:
        - Matches numbers, both integers and floating points.
        - Converts the matched text to a double using `atof` and assigns it to `yylval.dval`.
        - Returns the `NUMBER` token.
    - **`[ \t] ;`**:
        - Matches spaces and tabs, but does nothing (effectively skips whitespace).
    - **`\n return 0;`**:
        - Matches newlines and signals the end of input by returning 0.
    - **`. return yytext[0];`**:
        - Matches any single character and returns it as its ASCII value.
    - **`sin return SINE;`**:
        - Matches the keyword `sin` and returns the `SINE` token.
    - **`log return nLOG;`**:
        - Matches the keyword `log` and returns the `nLOG` token.
    - **`sqrt return SQRT;`**:
        - Matches the keyword `sqrt` and returns the `SQRT` token.

3. **Auxiliary Section** (`%{ ... %}`):
    - **`int yywrap()`**: 
        - Function required by Flex, indicating the end of input. Returns 1 to indicate no more input.

### Yacc (Parser)

```c
%{
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int yylex();
int yyerror();
%}

%union
{
 double dval;
}

%token <dval> NUMBER
%token NAME SINE nLOG SQRT
%left '+''-'
%left '*''/'
%left SINE nLOG SQRT
%right '^'
%type <dval> E
%%
S : NAME '=' E
  | E                         {printf("=%g\n",$1);}
  ;
E : E '+' E    {$$=$1+$3;}
  | E '-' E    {$$=$1-$3;}
  | E '*' E    {$$=$1*$3;}
  | E '/' E    {$$=$1/$3;}
  | NUMBER     {$$=$1;}
  ;
E : SINE E     {$$=sin($2 * 3.14/180);}
  | nLOG E     {$$=log($2);}
  | E '^' E    {$$=pow($1,$3);}
  | SQRT E     {$$=sqrt($2);}
  ;
%%
int main()
{
 yyparse();
 return 0;
}
int yyerror()
{
 printf("\n Syntax error");
}
```

#### Yacc Definitions and Rules

1. **Header Section** (`%{ ... %}`):
    - **`#include<stdio.h>`**: Standard input/output library.
    - **`#include<stdlib.h>`**: Standard library for general-purpose functions.
    - **`#include<math.h>`**: Math library for mathematical functions.
    - **`int yylex();`**: Prototype for the lexer function.
    - **`int yyerror();`**: Prototype for the error handling function.

2. **Union Definition** (`%union { ... }`):
    - **`double dval;`**: Defines a union member `dval` to hold double values returned by the lexer and used in parsing.

3. **Token Definitions** (`%token`):
    - **`%token <dval> NUMBER`**: Token for numbers, associated with the `dval` union member.
    - **`%token NAME SINE nLOG SQRT`**: Tokens for variable names and functions.

4. **Precedence and Associativity**:
    - **`%left '+''-'`**: Defines `+` and `-` as left-associative operators.
    - **`%left '*''/'`**: Defines `*` and `/` as left-associative operators.
    - **`%left SINE nLOG SQRT`**: Defines `SINE`, `nLOG`, and `SQRT` with same precedence.
    - **`%right '^'`**: Defines `^` as right-associative.

5. **Type Declaration** (`%type`):
    - **`%type <dval> E`**: Declares that the non-terminal `E` uses the `dval` union member.

6. **Grammar Rules** (`%% ... %%`):
    - **`S`**:
        - **`S : NAME '=' E`**: Rule to handle assignment (not fully implemented).
        - **`S : E {printf("=%g\n",$1);}`**: Rule to print the result of an expression.
    - **`E`**:
        - **`E : E '+' E {$$=$1+$3;}`**: Rule for addition.
        - **`E : E '-' E {$$=$1-$3;}`**: Rule for subtraction.
        - **`E : E '*' E {$$=$1*$3;}`**: Rule for multiplication.
        - **`E : E '/' E {$$=$1/$3;}`**: Rule for division.
        - **`E : NUMBER {$$=$1;}`**: Rule to handle numbers.
        - **`E : SINE E {$$=sin($2 * 3.14/180);}`**: Rule to handle sine function (converting degrees to radians).
        - **`E : nLOG E {$$=log($2);}`**: Rule to handle natural logarithm.
        - **`E : E '^' E {$$=pow($1,$3);}`**: Rule to handle exponentiation.
        - **`E : SQRT E {$$=sqrt($2);}`**: Rule to handle square root.

7. **Auxiliary Functions**:
    - **`int main()`**:
        - Calls `yyparse()` to start parsing.
        - Returns 0 on success.
    - **`int yyerror()`**:
        - Prints "Syntax error" if an error occurs.
    - **`int yywrap()`**:
        - Indicates the end of input.

### Summary

- The **lexer** (Lex) matches numbers, operators, function names (`sin`, `log`, `sqrt`), and ignores whitespace.
- The **parser** (Yacc) uses these tokens to evaluate arithmetic expressions, including function calls, following the rules defined.
- The **parser rules** handle expressions, terms, and factors, including handling operator precedence and associativity correctly.
- The **functions** handle parsing errors and provide a main entry point for starting the parser.