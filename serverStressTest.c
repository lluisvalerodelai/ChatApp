#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  // create a socket
  // bind our socket to a port?
  // connect to an address and a port
  // send info with send()
  // recieve with recv()

  int portNum = 42069;
  char *IpAddr = "127.0.0.1";
  int REQUESTNUMS = 15;
  int Connections[REQUESTNUMS];

  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(portNum);
  inet_pton(AF_INET, IpAddr, &serverAddress.sin_addr);

  // first create all the sockets
  for (int i = 0; i < REQUESTNUMS; i++) {
    Connections[i] = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(Connections[i], F_SETFL, O_NONBLOCK);
  }

  // then connect them all

  for (int i = 0; i < REQUESTNUMS; i++) {
    int connectResult =
        connect(Connections[i], (struct sockaddr *)&serverAddress,
                sizeof(serverAddress));

    if (connectResult == 0) {
      printf("Succesfully connected to server \nIP: %s, Port: %i\n", IpAddr,
             portNum);
    } else {
      printf("FAILURE Error connecting to Server %s:%i \n Error: %s \n", IpAddr, portNum,
             strerror(errno));
    }
  }


  return 0;
}
