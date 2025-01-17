#include <arpa/inet.h>
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

  int socketFD = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddress;

  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(portNum);
  inet_pton(AF_INET, IpAddr, &serverAddress.sin_addr);

  int connectResult = connect(socketFD, (struct sockaddr *)&serverAddress,
                              sizeof(serverAddress));

  if (connectResult == 0) {
    printf("Succesfully connected to server! \nIP: %s, Port: %i\n", IpAddr,
           portNum);
  } else {
    printf("Error connecting to %s:%i \n Error: %s \n", IpAddr, portNum,
           strerror(errno));
    close(socketFD);
    return 1;
  }

  char *messageBuf = "GET /index.html";
  int sendResult = send(socketFD, messageBuf, strlen(messageBuf), 0);

  if (sendResult > 0) {
    printf("Succesfully sent %i bytes, message: %s \n", sendResult, messageBuf);
  } else {
    printf("Error: %s", strerror(errno));
    close(socketFD);
    return 1;
  }

  printf("waiting for server response...\n");
  char resultBuf[1024];
  int recieveResult = recv(socketFD, &resultBuf, sizeof(resultBuf), 0);

  if (recieveResult < 0) {
    printf("Error: %s\n", strerror(errno));
  } else if (recieveResult == 0) {
    printf("Server Disconnected\n");
  } else {

    printf("Server Response: %s \n", resultBuf);
  }

  printf("closing connection \n");
  close(socketFD);

  return 0;
}
