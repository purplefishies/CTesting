#include <stdio.h>
#include "version.h"

int
main(int argc, char *argv[])
{
  printf("Ver=%s\n" ,libfive_git_version());
  printf("Rev=%s\n", libfive_git_revision());
  printf("Br=%s\n", libfive_git_branch() );

}
