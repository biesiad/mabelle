#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */
#include <unistd.h> /* read, write, close */


void error(const char *msg) { perror(msg); exit(0); }

int main(int argc, char *argv[])
{
    /* first what are we going to send and where are we going to send it? */
    int port = 80;
    char *host = "weheartit-bell.herokuapp.com";
    char *message = "POST / HTTP/1.1\r\nHost: weheartit-bell.herokuapp.com\r\nConnection: close\r\n\r\n";

    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total;
    char response[256];

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    /* lookup the ip address */
    server = gethostbyname(host);
    if (server == NULL) error("ERROR, no such host");

    /* fill in the structure */
    memset(&serv_addr, 0, sizeof(serv_addr)); // fill strusture with zeros
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    /* connect the socket */
    if (connect(sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) error("ERROR connecting");

    /* send the request */
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd, message + sent, total - sent);
        if (bytes < 0) error("ERROR writing message to socket");
        if (bytes == 0) break;

        sent += bytes;
    } while (sent < total);

    /* receive the response */
    memset(response, 0, sizeof(response));
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(sockfd, response + received, total - received);
        if (bytes < 0) error("ERROR reading response from socket");
        if (bytes == 0) break;

        received += bytes;
    } while (received < total);

    if (received == total) error("ERROR storing complete response from socket");

    /* close the socket */
    close(sockfd);

    return 0;
}