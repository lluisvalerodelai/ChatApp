#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {

  int portNum = 42069;

  int serverFD = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(portNum);
  serverAddress.sin_addr.s_addr = INADDR_ANY; // listen on all interfaces

  int bindResult =
      bind(serverFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

  if (bindResult == 0) {
    printf("Socket bound to port: %i\n", portNum);
  } else {
    printf("Error in binding socket to port %i \n Error: %s \n", portNum,
           strerror(errno));
    close(serverFD);
    return 1;
  }

  int listenResult = listen(serverFD, 10);

  if (listenResult == 0) {
    printf("socket set to listening\n");
  } else {
    printf("ERROR in setting socket to listening mode\nError: %s\n",
           strerror(errno));
    close(serverFD);
    return 1;
  }

  struct sockaddr_in clientAddr;
  socklen_t clientSize = sizeof(clientAddr);

  int clientFD = accept(serverFD, (struct sockaddr *)&clientAddr, &clientSize);

  if (clientFD < 0) {
    printf("Failed to accept \nERROR: %s", strerror(errno));
    close(clientFD);
    return 1;
  } else {

    printf("---------------------CLIENT CONNECTED---------------------\n");
    printf("                     %s:%i                                \n",
           inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
  }

  char dataBuffer[1024];

  while (1) {

    printf("recieving... \n");
    int recvResult = recv(clientFD, &dataBuffer, sizeof(dataBuffer), 0);

    if (recvResult > 0) {
      printf("succesfully recieved %i bytes of data\n\t%s", recvResult,
             dataBuffer);
    } else {
      printf("ERROR in recieving data\nError: %s\n", strerror(errno));
      close(serverFD);
      // return 1;
    }
  }

  return 0;
}
