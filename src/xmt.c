//#define DEBUG
#include "common.h"
#include "xmt.h"

char *strreplace(char *str, char *oldstr, char *newstr)
{
  char *bstr = (char *)malloc(strlen(str));
  memset(bstr, 0, sizeof(bstr));
  for(int i = 0;i < strlen(str);i++)
  {
    if(!strncmp(str+i, oldstr, strlen(oldstr)))
    {
      strcat(bstr,newstr);
      i += strlen(oldstr) - 1;
    }
    else
    {
      strncat(bstr, str + i,1);
    }
  }
  strcpy(str,bstr);
  return str;
}

void error(int errid, char const *word)
{
  printf("\nfatal error %d: ", errid);
  if (errid == 1)
  {
    printf("no input file given.\n");
  }
  else if (errid == 2)
  {
    printf("unable to open specified file `%s'.\n", word);
  }
  else if (errid == 3)
  {
    printf("error while reading file.\n");
  }
  else if (errid == 4)
  {
    printf("not a ELF file.\n");
  }
  else if (errid == 5)
  {
    printf("analyze error: %s\n", word);
  }
  else
  {
    printf("unknown error.\n");
  }

  exit(errid);
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    error(1, NULL);
  }

  readbin86_main(argv[1]);

  dump_main(argv[1]);
  //clean_dump_dir();

  return 0;
}