#include <sys/select.h>

int main(int argc, const char *argv[])
{
  int listenfd, connfd;
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in servaddr;
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
  listen(listenfd, LISTENQ);

  for(;;) {
    int connfd = accept(listenfd, (SA*)&cliaddr,
  }
  return 0;
}
