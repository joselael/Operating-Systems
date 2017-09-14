#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[])
{
  int fd = open(argv[1], O_RDONLY);
 
  if (fd == -1)
    {
      printf("open() failed with error [%s]\n", strerror(errno));
      return 1;
    }
  
  //printf("%s\n", "File opened successfully");
  char data[128];
  //  printf("Contents of data[0] %c\n", data[0]);

  if (read(fd, data, 128) < 0)
    {
      printf("An error has occured\n");
      perror("read");
    }
  
  printf("%s", data);
  close(fd);
    return 0;
}
