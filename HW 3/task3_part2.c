/* Task 3 Part 1
 * Jose L. Louis
 * CSC 332 - Operating Systems - L2 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
  pid_t child_pid;
  int* nullptr = NULL;

  if (child_pid = fork())
    printf("%s: %jd \n", "Child process forked, pid", (intmax_t) child_pid);


  if (!child_pid) {
    argv[1] = "-la";
    argv[2] = NULL;
    execvp("ls", &argv[0]);
    printf("%s\n", "EXECL Failed");
  }

  return EXIT_SUCCESS;
}
