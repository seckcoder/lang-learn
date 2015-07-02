#include <unistd.h>
#include <stdio.h>


int main() {
  FILE* fout = fopen("test.txt", "w");
  pid_t pid = fork();
  if (pid == 0) {
    printf("child process\n");
    sleep(10);
    for (int i = 1; i <= 10; i++) {
      fprintf(fout, "%d\n", i);
    }
  } else {
    printf("parent process\n");
    // parent process
    for (int i = 11; i <= 20; i++) {
      fprintf(fout, "%d\n", i);
    }
  }
  printf("shared\n");
  for (int i = 21; i <= 30; i++) {
    fprintf(fout, "%d\n", i);
  }
  // parent process won't wait for child process
  fclose(fout);
  return 0;
}
