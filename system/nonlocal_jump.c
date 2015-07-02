#include <setjmp.h>
#include <stdio.h>

jmp_buf buf;


int error1 = 0;
int error2 = 1;

void foo(void), bar(void);

int main()
{
  int rc;

  /* setjmp saves calling env(pc,stack pointer, and register) in buf */
  rc = setjmp(buf);
  if (rc == 0)
    foo();
  else if (rc == 1)
    printf("Error 1\n");
  else if (rc == 2)
    printf("Error 2\n");
  else
    printf("Unknown error\n");
  return 0;
}


void foo()
{
  if (error1)
    /* long jmp restores calling env and returns from
     * the most recent setjmp call. */
    longjmp(buf, 1);
  /* if error1 enabled, bar will never be called since
   * longjmp never returns */
  bar();
}

void bar()
{
  if (error2)
    longjmp(buf, 2);
  foo();
}
