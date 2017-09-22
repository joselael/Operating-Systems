#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  pid_t childOne, childTwo;

  if((childOne = fork()))
    if((childTwo = fork()))
      ;

  if (childOne == 0) printf("I am child one, my pid is: %d\n", getpid());

  else if (childTwo == 0) printf("I am child two, my pid is: %d\n", getpid());

  waitpid(childOne, NULL, 0);
  waitpid(childTwo, NULL, 0);
  
  return 0;
}
