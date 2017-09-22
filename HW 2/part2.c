#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  int a = 10, b = 25, fq = 0, fr = 0;

  fq = fork(); // for a child - call it Process Q

  if (fq == 0)
    {
       a += b;
       printf("a: %d b: %d process_id: %d\n", a, b, getpid());

       fr = fork(); // fork another child - call it Process R
       if (fr != 0)
         {
           b += 20;
           printf("a: %d b: %d, process_id: %d\n", a, b, getpid());
         }
       else
         {
           a = (a * b) + 30;
           printf("a: %d b: %d, process_id: %d\n", a, b, getpid());
         }
    }
  else
    {
      b = a + b - 5;
      printf("a: %d b: %d, process_id: %d\n", a, b, getpid());
    }

  return 0;
}
