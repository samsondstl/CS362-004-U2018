#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
   int i;

   do
   {
      i = rand() % 128;
   } while (i == 5); // In PuTTY, character code 5 causes "PuTTY" to be printed. So, it is skipped.

   return (char)i;
}

char *testStr;

char *inputString()
{  
   char chars[10] = {'r', 'e', 's', 't', 'a', 'Q', '4', '%', '\0'};
   
   int lengths[3] = {5, 6, 7};

   int length = lengths[rand() % 3];
   
   if (testStr != NULL)
   {
      free(testStr);
   }
   testStr = (char *)malloc(length * sizeof(char));
   if (testStr == NULL)
   {
      exit(1);
   }  

   int i; 
   for (i = 0; i < length - 1; i++)
   {
      testStr[i] = chars[rand() % 10];
   }
   testStr[length - 1] = '\0'; // ensure the string ends with a null character
      
   return testStr;
}

void testme()
{
   int tcCount = 0;
   char *s;
   char c;
   int state = 0;
   while (1)
   {
      tcCount++;
      c = inputChar();
      s = inputString();
      printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
      
      if (c == '[' && state == 0) state = 1;
      if (c == '(' && state == 1) state = 2;
      if (c == '{' && state == 2) state = 3;
      if (c == ' ' && state == 3) state = 4;
      if (c == 'a' && state == 4) state = 5;
      if (c == 'x' && state == 5) state = 6;
      if (c == '}' && state == 6) state = 7;
      if (c == ')' && state == 7) state = 8;
      if (c == ']' && state == 8) state = 9;
      if (s[0] == 'r' && s[1] == 'e'
         && s[2] == 's' && s[3] == 'e'
         && s[4] == 't' && s[5] == '\0'
         && state == 9)
      {
        printf("error ");
        exit(200);
      }
   }
}


int main(int argc, char *argv[])
{
   srand(time(NULL));
   testme();
   return 0;
}
