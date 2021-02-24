/*
    C socket server example
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
     
    //Receive a message from client
    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {
        //Send the message back to client
        printf("Received Data: %s\n", client_message);
        
        int x = client_message[0];
        char o = client_message[1];
        int y = client_message[2];
        x = x - 48;
        y = y - 48;
        float z;

        if (o == '+')
           z = x + y;

        else if (o == '-')
           z = x - y;

        else if (o == '*')
           z = x * y;

        else if (o == '/')
           z = (float)x / y;


        //printf("xoy=z: %i %c %i  = %f\n", x, o ,y, z);

        memset(client_message,'\0', 2000);

        client_message[0] = x + '0';
        client_message[1] = o;
        client_message[2] = y + '0';
        client_message[3] = '=';

        if (z < 0)
        {
                client_message[4] = '-';
                z = 0-z;
        }
        else
                client_message[4] = ' ';


        client_message[5] = (int)z/10 + '0';
        client_message[6] = (int)z%10 + '0';
        client_message[7] = '.';
        z = z*10;
        client_message[8] = (int)z%10 + '0';

        write(client_sock , client_message , strlen(client_message));
        memset(client_message,'\0', 2000);
    }
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
     
    return 0;
}