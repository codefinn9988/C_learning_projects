// send data to server = "hello server"

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
int main() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in address = {AF_INET, htons(6969), 0};

  if (connect(sockfd, (void *)&address, sizeof(address)) < 0) {
    printf("client cannot connect with the server");
  }
  char *message = "hellow server what's up";
  write(sockfd, message, strlen(message));
  char buff[100];
  read(sockfd, &buff, sizeof(buff));
  printf("from server: %s\n", buff);
  close(sockfd);
  return 0;
}
