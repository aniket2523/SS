#include <stdio.h>  
    #include <string.h>  
      
    #define SUCCESS 1  
    #define FAILED 0  
      
    int E(), Edash(), T(), Tdash(), F();  
      
    const char *cursor;  
    char string[64];  
      
    int main()  
    {  
        puts("Enter the string");  
        // scanf("%s", string);  
        sscanf("i+(i+i)*i", "%s", string);  
        cursor = string;  
        puts("");  
        puts("Input      Action");  
        puts("--------------------------------");  
      
        if (E() && *cursor == '\0') {  
            puts("--------------------------------");  
            puts("String is successfully parsed");  
            return 0;  
        } else {  
            puts("--------------------------------");  
            puts("Error in parsing String");  
            return 1;  
        }  
    }  
      
    int E()  
    {  
        printf("%-16s E -> T E'\n", cursor);  
        if (T()) {  
            if (Edash())  
                return SUCCESS;  
            else  
                return FAILED;  
        } else  
            return FAILED;  
    }  
      
    int Edash()  
    {  
        if (*cursor == '+') {  
            printf("%-16s E' -> + T E'\n", cursor);  
            cursor++;  
            if (T()) {  
                if (Edash())  
                    return SUCCESS;  
                else  
                    return FAILED;  
            } else  
                return FAILED;  
        } else {  
            printf("%-16s E' -> $\n", cursor);  
            return SUCCESS;  
        }  
    }  
      
    int T()  
    {  
        printf("%-16s T -> F T'\n", cursor);  
        if (F()) {  
            if (Tdash())  
                return SUCCESS;  
            else  
                return FAILED;  
        } else  
            return FAILED;  
    }  
      
    int Tdash()  
    {  
        if (*cursor == '*') {  
            printf("%-16s T' -> * F T'\n", cursor);  
            cursor++;  
            if (F()) {  
                if (Tdash())  
                    return SUCCESS;  
                else  
                    return FAILED;  
            } else  
                return FAILED;  
        } else {  
            printf("%-16s T' -> $\n", cursor);  
            return SUCCESS;  
        }  
    }  
      
    int F()  
    {  
        if (*cursor == '(') {  
            printf("%-16s F -> ( E )\n", cursor);  
            cursor++;  
            if (E()) {  
                if (*cursor == ')') {  
                    cursor++;  
                    return SUCCESS;  
                } else  
                    return FAILED;  
            } else  
                return FAILED;  
        } else if (*cursor == 'i') {  
            cursor++;  
            printf("%-16s F ->i\n", cursor);  
            return SUCCESS;  
        } else  
            return FAILED;  
    }  





    This code is a recursive descent parser for a simple arithmetic expression grammar. It parses input strings that consist of identifiers (`i`), addition (`+`), multiplication (`*`), and parentheses (`(` and `)`). The parser follows a specific grammar and prints the parsing steps. Let's go through the code step by step.

### Includes and Defines

```c
#include <stdio.h>
#include <string.h>

#define SUCCESS 1
#define FAILED 0
```
- **`#include <stdio.h>`**: Includes the standard I/O library for input and output functions.
- **`#include <string.h>`**: Includes the standard library for string handling functions.
- **`#define SUCCESS 1`**: Defines `SUCCESS` as `1` to indicate a successful parsing step.
- **`#define FAILED 0`**: Defines `FAILED` as `0` to indicate a failed parsing step.

### Function Prototypes

```c
int E(), Edash(), T(), Tdash(), F();
```
- These are function prototypes for the parser functions corresponding to the grammar rules:
  - `E()`: Parses expressions.
  - `Edash()`: Parses the rest of an expression after a term.
  - `T()`: Parses terms.
  - `Tdash()`: Parses the rest of a term after a factor.
  - `F()`: Parses factors.

### Global Variables

```c
const char *cursor;
char string[64];
```
- **`const char *cursor`**: A pointer to the current position in the input string.
- **`char string[64]`**: A buffer to store the input string (with a maximum length of 64 characters).

### Main Function

```c
int main()  
{  
    puts("Enter the string");  
    // scanf("%s", string);  
    sscanf("i+(i+i)*i", "%s", string);  
    cursor = string;  
    puts("");  
    puts("Input      Action");  
    puts("--------------------------------");  

    if (E() && *cursor == '\0') {  
        puts("--------------------------------");  
        puts("String is successfully parsed");  
        return 0;  
    } else {  
        puts("--------------------------------");  
        puts("Error in parsing String");  
        return 1;  
    }  
}
```
- **`puts("Enter the string");`**: Prompts the user to enter a string.
- **`// scanf("%s", string);`**: Commented out code for reading user input. Instead:
- **`sscanf("i+(i+i)*i", "%s", string);`**: Initializes `string` with a sample input `"i+(i+i)*i"`.
- **`cursor = string;`**: Sets `cursor` to point to the beginning of the input string.
- **`puts(""); puts("Input      Action"); puts("--------------------------------");`**: Prints headers for the parsing trace.
- **`if (E() && *cursor == '\0')`**: Calls the `E()` function to start parsing and checks if the entire string has been consumed (`*cursor == '\0'`).
  - **`puts("String is successfully parsed");`**: Prints a success message if parsing is successful.
  - **`puts("Error in parsing String");`**: Prints an error message if parsing fails.

### Parsing Functions

#### E() - Expression

```c
int E()  
{  
    printf("%-16s E -> T E'\n", cursor);  
    if (T()) {  
        if (Edash())  
            return SUCCESS;  
        else  
            return FAILED;  
    } else  
        return FAILED;  
}
```
- **`printf("%-16s E -> T E'\n", cursor);`**: Prints the current state and the production rule being applied.
- **`if (T()) { if (Edash()) return SUCCESS; else return FAILED; } else return FAILED;`**:
  - Tries to parse a term (`T()`) followed by `Edash()`.
  - Returns `SUCCESS` if both `T()` and `Edash()` succeed; otherwise, returns `FAILED`.

#### Edash() - Expression Dash (for handling `+`)

```c
int Edash()  
{  
    if (*cursor == '+') {  
        printf("%-16s E' -> + T E'\n", cursor);  
        cursor++;  
        if (T()) {  
            if (Edash())  
                return SUCCESS;  
            else  
                return FAILED;  
        } else  
            return FAILED;  
    } else {  
        printf("%-16s E' -> $\n", cursor);  
        return SUCCESS;  
    }  
}
```
- **`if (*cursor == '+') { ... }`**: Checks if the current character is `+`.
  - Prints the current state and rule, advances `cursor`, and tries to parse `T()` and `Edash()`.
- **`else { printf("%-16s E' -> $\n", cursor); return SUCCESS; }`**:
  - If no `+`, considers `E'` (Edash) as an empty production (`$`) and returns `SUCCESS`.

#### T() - Term

```c
int T()  
{  
    printf("%-16s T -> F T'\n", cursor);  
    if (F()) {  
        if (Tdash())  
            return SUCCESS;  
        else  
            return FAILED;  
    } else  
        return FAILED;  
}
```
- **`printf("%-16s T -> F T'\n", cursor);`**: Prints the current state and the production rule.
- **`if (F()) { if (Tdash()) return SUCCESS; else return FAILED; } else return FAILED;`**:
  - Tries to parse a factor (`F()`) followed by `Tdash()`.
  - Returns `SUCCESS` if both succeed; otherwise, returns `FAILED`.

#### Tdash() - Term Dash (for handling `*`)

```c
int Tdash()  
{  
    if (*cursor == '*') {  
        printf("%-16s T' -> * F T'\n", cursor);  
        cursor++;  
        if (F()) {  
            if (Tdash())  
                return SUCCESS;  
            else  
                return FAILED;  
        } else  
            return FAILED;  
    } else {  
        printf("%-16s T' -> $\n", cursor);  
        return SUCCESS;  
    }  
}
```
- **`if (*cursor == '*') { ... }`**: Checks if the current character is `*`.
  - Prints the current state and rule, advances `cursor`, and tries to parse `F()` and `Tdash()`.
- **`else { printf("%-16s T' -> $\n", cursor); return SUCCESS; }`**:
  - If no `*`, considers `T'` (Tdash) as an empty production (`$`) and returns `SUCCESS`.

#### F() - Factor

```c
int F()  
{  
    if (*cursor == '(') {  
        printf("%-16s F -> ( E )\n", cursor);  
        cursor++;  
        if (E()) {  
            if (*cursor == ')') {  
                cursor++;  
                return SUCCESS;  
            } else  
                return FAILED;  
        } else  
            return FAILED;  
    } else if (*cursor == 'i') {  
        cursor++;  
        printf("%-16s F ->i\n", cursor);  
        return SUCCESS;  
    } else  
        return FAILED;  
}
```
- **`if (*cursor == '(') { ... }`**: Checks if the current character is `(`.
  - Prints the current state and rule, advances `cursor`, and tries to parse an expression (`E()`) followed by `)`.
  - If the closing `)` is found, advances `cursor` and returns `SUCCESS`; otherwise, returns `FAILED`.
- **`else if (*cursor == 'i') { cursor++; printf("%-16s F ->i\n", cursor); return SUCCESS; }`**:
  - Checks if the current character is `i`, advances `cursor`, prints the rule, and returns `SUCCESS`.
- **`else return FAILED;`**:
  - If neither `(` nor `i`, returns `FAILED`.

### Summary
This code implements a recursive descent parser for the following grammar:

```
E  -> T E'
E' -> + T E' | ε
T  -> F T'
T' -> * F T' | ε
F  -> ( E ) | i
```
- **`E`**: An expression is a term followed by the rest of the expression.
- **`E'`**: The rest of an expression is `+` followed by a term and the rest of the expression, or empty.
- **`T`**: A term is a factor followed by the rest of the term.
- **`T'`**: The rest of a term is `*` followed by a factor and the rest of the term, or empty.
- **`F`**: A factor is an expression in parentheses or an identifier (`i`).

The program parses an input string according to this grammar, printing the steps taken, and indicating whether the string is successfully parsed or contains errors.