#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  pid_t child1, child2;
  //  int * nullptr = 0;
  child1 = fork();
  if (child1 == 0)
    {
      execv("Prcs_P1", (char *) NULL);
      printf("%s\n", "FATAL ERROR: Failed to execute Prcs_P1");
      return EXIT_SUCCESS;
    }
  child2 = fork();

  if (child2 == 0)
    {
      waitpid(child1, NULL, 0);
      execv("Prcs_P2", &argv[0]);
      printf("%s\n", "FATAL ERROR: Failed to execute Prcs_P2");
      return EXIT_SUCCESS;
    }

  return 0;
}
