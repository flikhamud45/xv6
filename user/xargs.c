#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

void print(char* l[], int size) {
  for(int i = 0; i < size; i++) {
    printf("%s, ", l[i]);
  }
  printf("\n");
}

int
main(int argc, char *argv[])
{
  
  char line[MAXARG];
  char* argv2[argc+1];
  //memcpy(argv2, argv+1, argc-1);
  for(int i = 1; i < argc; i++) {
    argv2[i-1] = argv[i];
  }
  argv2[argc-1] = line;
  argv2[argc] = 0;
  char* s = gets(line, MAXARG);

  //print(argv, argc);
  while(s != 0 && strcmp(s, "") != 0) {
    line[strlen(line)-1] = 0;
    //printf(s);
    //print(argv2, argc);
    int pid = fork();
    if(pid == 0) {
      exec(argv2[0], argv2);
      exit(0);
    }
    else{
      wait(0);
    }
    s = gets(line, MAXARG);
  }
  exit(0);
}

