// send data to server = "hello client"

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
int main() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in address = {AF_INET, htons(6969), 0};

  if (bind(sockfd, (void *)&address, sizeof(address)) < 0) {
    printf("Failed to bind socket");
    return 1;
  };
  listen(sockfd, 10);
  int clientId = accept(sockfd, NULL, NULL);

  char buff[100];
  read(clientId, &buff, sizeof(buff));
  // while (*buff != '\0') {
  // }
  printf("fron client: %s\n", buff);
  char *message = "hello client yo yo ";
  write(clientId, message, strlen(message));
  close(sockfd);
  close(clientId);
  return 0;
}
