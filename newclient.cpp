#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    struct sockaddr_in peer;
    int s, t, t1;
    int rc;
    char buf[256], p, p1, b[256];
    ;
    peer.sin_family = AF_INET;
    peer.sin_port = htons(7500);
    peer.sin_addr.s_addr = inet_addr("127.0.0.1");
    s = socket(AF_INET, SOCK_STREAM, 0);
    rc = connect(s, (struct sockaddr *)&peer, sizeof(peer));
    
}