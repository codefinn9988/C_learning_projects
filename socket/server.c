/* this is server
 * 1. socket()
 * 2. bind()
 * 3. listen()
 * 4. accept() (get clientFd)
 * 5. read()
 * 6. write()
 * 7. close()
 */
#include <arpa/inet.h>
#include <poll.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
int main() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in address = {AF_INET, htons(6969), 0};
  if (bind(sockfd, (void *)&address, sizeof(address)) < 0) {
    printf("No bind");
  }
  if (listen(sockfd, 10)) {
    printf("No listen");
  }
  int clientFd = accept(sockfd, NULL, NULL);
  // POLLIN = there is data to read
  // 0 -> stdin
  struct pollfd pfd[2] = {{0, POLLIN, 0}, {clientFd, POLLIN, 0}};
  for (;;) {
    // put all address value to 0 or empty string buffer[0] = buffer[1] = 0
    char buffer[256] = {0};
    poll(pfd, 2, 50000);
    if (pfd[0].revents & POLLIN) {
      // if the data in available read and put in buffer
      read(0, buffer, 255);
      // send data to client from buffer
      send(clientFd, buffer, 255, 0);
    } else if (pfd[1].revents & POLLIN) {
      // if client close the connection
      if (recv(clientFd, buffer, 255, 0) == 0) {
        return 0;
      };
      // if connection is still open
      printf("%s\n", buffer);
    }
  }
  close(sockfd);
  close(clientFd);
  return 0;
}
