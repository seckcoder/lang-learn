
/* implement soft-restart with sigsetjmp */

#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>


/*
 * Note: Using setjmp may still work here for some platforms.
 * But sigsetjmp is the cross-platform way.
 *
 *
There is a problem in calling longjmp, however. When a signal is caught, the signal-catching function is entered with the current signal automatically being added to the signal mask of the process. This prevents subsequent occurrences of that signal from interrupting the signal handler. If we longjmp out of the signal handler, what happens to the signal mask for the process? (The signal will be blocked for subsequent calls)

Under FreeBSD 5.2.1 and Mac OS X 10.3, setjmp and longjmp save and restore the signal mask. Linux 2.4.22 and Solaris 9, however, do not do this. FreeBSD and Mac OS X provide the functions _setjmp and _longjmp, which do not save and restore the signal mask.

To allow either form of behavior, POSIX.1 does not specify the effect of setjmp and longjmp on signal masks. Instead, two new functions, sigsetjmp and siglongjmp, are defined by POSIX.1. These two functions should always be used when branching from a signal handler.

...

The only difference between these functions and the setjmp and longjmp functions is that sigsetjmp has an additional argument. If savemask is nonzero, then sigsetjmp also saves the current signal mask of the process in env. When siglongjmp is called, if the env argument was saved by a call to sigsetjmp with a nonzero savemask, then siglongjmp restores the saved signal mask.

*/
sigjmp_buf buf;


void handler(int sig)
{
  /* Note in the handler, current signal will be automatically
   * being added to the signal mask of the process until the handler
   * returns(automatically removed from signal mask) */

  /* besides restoring calling env, we also restore sig mask */
  siglongjmp(buf, 1);
}


int main()
{
  struct sigaction action, old_action;
  
  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = SA_RESTART;

  sigaction(SIGINT, &action, &old_action);

  /* besides calling env, we also store sig mask */
  if (sigsetjmp(buf, 1) == 0) {
    printf("starting\n");
  } else {
    printf("restarting\n");
  }

  while (1) {
    sleep(1);
    printf("processing...\n");
  }
  
  return 0;
}
