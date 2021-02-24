/*
    Simple udp server
*/
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
 
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data
 
void die(char *s)
{
    perror(s);
    exit(1);
}
 
int main(void)
{
    struct sockaddr_in si_me, si_other;
     
    int s, i, slen = sizeof(si_other) , recv_len;
    char buf[BUFLEN];

    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
     
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
     
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }
     
    //keep listening for data
    while(1)
    {
        printf("Waiting for data...\n");
        fflush(stdout);
        
        memset(buf,'\0', BUFLEN);

        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }

        int rlen = strlen(buf);
        char c = buf[rlen-1];

        printf("Received: %s\n", buf);
        printf("Rec len: %d\n", rlen);
        printf("Rec char: %c\n", c);
        
        int i = 0, cnt = 0;

        while (buf[i] != '\0')
        {
            if (buf[i] == c)
            {
                cnt++;
            }

            i++;
        }
        cnt--;

        printf("Count: %d\n", cnt);

        char x1 = cnt/10 + '0';
        char x2 = cnt%10 + '0';
        
        printf("i2c: %c%c\n", x1, x2);
        buf[rlen-1] = x1;
        buf[rlen] = x2;
        printf("Modified: %s\n", buf);

        int mlen = strlen(buf);


        //print details of the client/peer and the data received
        // printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        // printf("Data: %s\n" , buf);
        
        //now reply the client with the same data
        if (sendto(s, buf, mlen, 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }
    }
 
    close(s);
    return 0;
}