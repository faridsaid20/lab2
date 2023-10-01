/* emitter.c */

#include "global.h"
#include <errno.h>
#include <stdbool.h>

char* RED = "\033[0;31m";
char* RESET = "\033[0m";

char print_buffer[100][100];
int print_buffer_index = 0;
int tokenValue = 0;

void emit(int token_type, int token_value) /*  generates output  */
{
   char str[20];
   switch (token_type)
   {
   case '+':
   case '-':
   case '*':
   case '/':
   case '=':
   case '^':
      sprintf(str, "%c", token_type);
      strcpy(print_buffer[print_buffer_index++], str);
      break;
   case DIV:
      printf("DIV\n");
      strcpy(print_buffer[print_buffer_index++], "DIV");
      break;
   case MOD:
      printf("MOD\n");
      strcpy(print_buffer[print_buffer_index++], "MOD");
      break;
   case NUM:
      sprintf(str, "%d", token_value);
      strcpy(print_buffer[print_buffer_index++], str);
      break;
   case ID:
      strcpy(print_buffer[print_buffer_index++], symtable[token_value].lexeme);
      break;
   case RESULT:
   {
      tokenValue = token_value;
      printPostfix();
      int result = calculateResult();
      saveResultInSymtable(result);
      printResult(result);
   }
   break;
   default:
      printf("[Unknown token %d, with value %d]\n", token_type, token_value);
   }
}

void printPostfix()
{
   int index = 0;
   printf("postfix: ");
   while (index < print_buffer_index)
   {
      printf("%s", print_buffer[index++]);
   }
}

int calculateResult()
{
   int resultStack[100];
   int stack_index = 0;
   for (int i = 1; i < print_buffer_index; i++)
   {
      if (isOperator(print_buffer[i]))
      {
         int right = resultStack[--stack_index];
         int left = resultStack[--stack_index];
         int result = performOperation(left, right, print_buffer[i]);

         resultStack[stack_index++] = result;
         continue;
      }
      if (strcmp(print_buffer[i], "=") == 0)
      {
         continue;
      }
      bool isOk = false;
      int res = charToInt(print_buffer[i], &isOk);
      if (isOk)
      {
         resultStack[stack_index++] = res;
      }
   }
   print_buffer_index = 0;
   return resultStack[0];
}

bool isOperator(const char* str)
{
   return strcmp(str, "+") == 0 || strcmp(str, "-") == 0
          || strcmp(str, "*") == 0 || strcmp(str, "/") == 0
          || strcmp(str, "^") == 0;
}

void saveResultInSymtable(int result)
{
   const int resSize = sizeof(result);
   if (symtable[tokenValue].value == NULL)
   {
      symtable[tokenValue].value = malloc(resSize);
   }
   else if (strlen(symtable[tokenValue].value) < resSize)
   {
      symtable[tokenValue].value = realloc(symtable[tokenValue].value, resSize);
   }
   sprintf(symtable[tokenValue].value, "%d", result);
}

void printResult(int result)
{
   printf("\n%s = %d\n", symtable[tokenValue].lexeme, result);
}

int performOperation(int a, int b, const char* op)
{
   switch (op[0])
   {
   case '+':
      return a + b;
   case '-':
      return a - b;
   case '*':
      return a * b;
   case '/':
      return a / b;
   case '^':
      return exponent(a, b);
   default:
      return 0;
   }
}

int exponent(int base, int exp)
{
   int result = 1;
   while (exp)
   {
      if (exp & 1)
      {
         result *= base;
      }
      exp >>= 1;
      base *= base;
   }

   return result;
}

int charToInt(char* str, bool* isOk)
{
   *isOk = true;
   if (strcmp(str, "") == 0)
   {
      return 0;
   }

   char* endptr;
   // first check if the string is a symbol in the table, if yes it can be a
   // variable that holds number value
   int position = lookup(str);
   if (position != -1 && symtable[position].value != NULL)
   {
      return strtol(symtable[position].value, &endptr, 10);
   }
   // now that we know it is not a variable, we can check if it is a number
   long num = -1;
   errno = 0; // Reset errno before calling strtol
   num = strtol(str, &endptr, 10);
   if (errno == ERANGE)
   {
      *isOk = false;
      printf(
         "\n%sThe number is out of range for a long integer.%s\n", RED, RESET);
   }
   else if (endptr == str)
   {
      *isOk = false;
      printf("\n%sNo valid conversion could be performed for %s.%s\n",
             RED,
             str,
             RESET);
   }
   else if (*endptr != '\0')
   {
      *isOk = false;
      printf(
         "\n%sThe conversion stopped at the first non-numeric character: "
         "%c%s",
         RED,
         *endptr,
         RESET);
   }
   return num;
}
