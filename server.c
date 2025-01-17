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

  int listenResult = listen(serverFD, 4);

  if (listenResult == 0) {
    printf("socket set to listening\n");
  } else {
    printf("ERROR in setting socket to listening mode\nError: %s\n",
           strerror(errno));
    close(serverFD);
    return 1;
  }

  while (1) {
    // accept a new client

    struct sockaddr_in clientAddr;
    socklen_t clientSize = sizeof(clientAddr);

    int clientFD =
        accept(serverFD, (struct sockaddr *)&clientAddr, &clientSize);

    if (clientFD < 0) {
      printf("Failed to accept \nERROR: %s", strerror(errno));
      close(clientFD);
      return 1;
    } else {

      printf("---------------------CLIENT CONNECTED---------------------\n");
      printf("                     %s:%i                                \n",
             inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
    }

    // poll(struct pollfd *fds, nfds_t nfds, int timeout);

    char dataBuffer[1024];
    while (1) {
      // recv()
      // print it out

      int recvResult = recv(clientFD, &dataBuffer, sizeof(dataBuffer), 0);

      if (recvResult > 0) {

        // null terminate buffer
        dataBuffer[recvResult] = '\0';

        printf("succesfully recieved %i bytes of data\n\t%s\n", recvResult,
               dataBuffer);


        if (strcmp("GET /index.html", dataBuffer) == 0) {
          // return index.html
          int sendResult = send(clientFD, "this is index.html",
                                sizeof("this is index.html"), 0);

          if (sendResult < 0) {
            printf("ERROR: %s\n", strerror(errno));
          } else {
            printf("Succesfully served index.html \n");
          }

        }
      } else {

        if (recvResult == 0) {
          printf("Client Disconnected... Now accepting new connections\n");
          close(clientFD);
          break;
        } else {

          printf("ERROR in recieving data\nError: %s\n", strerror(errno));
          close(clientFD);
        }
      }
    }
  }

  return 0;
}
