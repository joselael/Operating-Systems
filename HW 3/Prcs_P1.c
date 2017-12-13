#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  int dest1 = open("destination1.txt", O_RDWR | O_CREAT, 0700),
    dest2 = open("destination2.txt", O_RDWR | O_CREAT, 0700);

  close(dest1);
  close(dest2);
  return 0;
}
