/* docs
 * https://www.gnu.org/software/libc/manual/html_node/Sockets.html
 * https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_chapter/libc_16.html
 * https://www.man7.org/linux/man-pages/man0/sys_socket.h.0p.html
 * https://www.youtube.com/watch?v=gGfTjKwLQxY&list=PL0tgH22U2S3Giz-IxVQTEKIZpMBP0tMf&index=9
 * https://i.sstatic.net/YQ5ES.png
 * https://beej.us/guide/bgnet/html//index.html#client-server-background
 */
#include <stdio.h>
#include <sys/poll.h>
#include <sys/socket.h>
// socket() sys call
// _un = unix
// 1. instantiate ;create an endpoint for communication
int socket(int domain, int type, int protocol);
// domain = AF_UNIX(same host), AF_INET(ipv_4), AF_INET(ipv_6)
// type = stream or datagram , SOCK_STREAM, SOCK_DGRAM,SOCK_RAW
// protocol = 0(for stream & datagram), IPPROTO_RAW(for raw)
// return socket_fd fd= file descriptor

// 2. bind  =   assigns the address
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
// return -1(fail)
//  sockaddr_in -> Describes an IPv4 Internet domain socket address.
// struct sockaddr_in {
//   sa_family_t sin_family;  /* AF_INET */
//   in_port_t sin_port;      /* Port number */
//   struct in_addr sin_addr; /* IPv4 address */
// };
//
// htons(9999) = host-to-network short
// The htons() function makes sure that numbers are stored in memory in
// network byte order,little-endian format -> most significance byte first
// This function swaps the endianness of a short.
//
// AF = address format;
// INET = internet protocol family(ipv4)
// INET6 = version 6(ipv6)

// 3.  listen for connection
int listen(int server_socket_fd, int backlog);
// succeed return 0;
// server_socket_fd =file descriptor : process-unique identifier
// backlog = paramater in queue

// recieve from client
// ssize_t recv(int sockfd, void buf[.len], size_t len, int flags);

// 4. accept the connection
int accept(int fd, struct sockaddr *restrict addr,
           socklen_t *restrict addr_len);

// 5 . Server I/O on a socket
// read( accept_socket_fd, input_buffer, BUFFER_SIZE );
// write( accept_socket_fd, output_buffer, strlen( output_buffer ) + 1);

// 6. Server close a connection;
//  close( accept_socket_fd );

//  Extra
//  poll = wait for some event on a file descriptor
int poll(struct pollfd *fds, nfds_t nfds, int timeout);

int main() {
  printf("hello learn ");
  return 0;
}
