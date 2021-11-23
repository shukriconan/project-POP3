#include<stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<string.h> // starlen
#include<unistd.h> // write
#include<net/if_arp.h>
#include<sys/ioctl.h>
#include<arpa/inet.h>

#define SIZE 1024
#define PORT 110

int main(int argc, char*argv[])
{
	int sockt_desc;
	struct sockaddr_in server;
	char command[50];
	char server_reply[2000];
	
	//create socket
	sockt_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(sockt_desc == -1)
	{
		printf("could not create socket");
	}
	else
	{
		printf("socket created");
	}
	
	//ip address of vm server
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = inet_addr("192.168.56.5");	

	//connect to remote server
	if(connect(sockt_desc, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		puts("\nconnect error");
		return 1;
	}
	
	puts("\nconnected");
	
	//send some data
	

	printf("Do you want to retrive emails from server? (yes/no) : ");
	scanf("%s", command);
    send(sockt_desc, command, sizeof(command), 0);

	int i;
	FILE *fp;
	char *filename = "popclientemail.txt";
	char buffer[SIZE];

	fp = fopen(filename, "w");

    //Receive a reply from the server
    if( recv(sockt_desc, server_reply , 2000 , 0) < 0)
    {
        puts("recv failed");
    }
    fprintf(fp, "%s", server_reply);

    puts("Reply received\n");
    puts(server_reply);
	
	printf("Disconnecting...");
	close(sockt_desc);
}