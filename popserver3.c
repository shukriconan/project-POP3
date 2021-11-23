#include<stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<string.h> // starlen
#include<unistd.h> // write
#include<net/if_arp.h>
#include<sys/ioctl.h>
#include<arpa/inet.h>
#define PORT 110
#define SIZE 1024



int main(int argc, char*argv[])
{

	int socket_desc, new_socket, c;
	struct sockaddr_in  server, client;
	char*email = NULL;
	size_t n = 0;
	
	
	//create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1)
	{
		printf("could not create socket");
	}
	
	//prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);
	
	//bind
	if(bind(socket_desc,(struct sockaddr*)&server, sizeof(server)) < 0)
	{
		puts("bind failed");
        return 1;
	}
	puts("bind done");
	
	//listen
	listen(socket_desc, 3);char client_reply[500];
	c = sizeof(struct sockaddr_in);

    while(new_socket = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c))
    {
        
        if(recv(new_socket,&client_reply,sizeof(client),0))
        {
             
	         FILE *fp;
	         char*filename = "popserveremail.txt";
	         int i;
	         char data[SIZE] = {0};

	         fp = fopen(filename, "r");

	         fgets(data, SIZE, fp);
	         send(new_socket, data, sizeof(data), 0);  
        }
 
    }
    
	return 0;
}