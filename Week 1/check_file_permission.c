#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[])
{
  char* filepath = argv[1];
  int returnval;

  //check file existence
  returnval = access(filepath, F_OK);
  if (!returnval)
    printf("%s exists\n", filepath);
  else
    {
      if (errno == ENOENT)
	printf("%s does not exist\n", filepath);
      else if (errno == EACCES)
	printf("%s is not accessible\n", filepath);
      return 0;
    }
  // check read access
  returnval = access(filepath, R_OK);
  if (!returnval)
    printf("%s is readable\n", filepath);
  else
    printf("%s is not readable\n", filepath);

  // check write access
  returnval = access(filepath, W_OK);
  if(!returnval)
    printf("%s is writeable\n", filepath);
  else
    printf("%s is not writeable\n", filepath);

  return 0;
}
  
