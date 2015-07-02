#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void printProcessInfo() {
    pid_t pid = getpid();
    pid_t ppid = getppid();
    pid_t gid = getpgrp();
    printf("Process ID:%d\tParent ID: %d\tGroup ID: %d\n",
            pid, ppid, gid);
}

int main()
{
  if (fork() == 0) {
    printProcessInfo();
    if (fork() == 0) {
      printProcessInfo();
      printf("9");
      exit(1);
    } else {
      printf("5");
      sleep(1);
    }
  } else {
    pid_t pid;
    /* Children of child process are not the children
     * of current process. So the process won't wait
     * for them
     */
    if ((pid = waitpid(0, NULL, 0)) > 0) {
      printf("3");
    }
  }
  printf("0");

  return 0;
}

