#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
	char buffer[100];
	int sock_desc,t;
	struct sockaddr_in pelanggan;
	memset(&pelanggan,0,sizeof(pelanggan));

	sock_desc=socket(AF_INET,SOCK_STREAM,0);

	if(sock_desc==-1)
	{
	printf("Error in socket creation");
	exit(1);
	}

	pelanggan.sin_family = AF_INET;
	pelanggan.sin_addr.s_addr = inet_addr("192.168.1.14");
	pelanggan.sin_port = htons(8888);

	t = connect(sock_desc,(struct sockaddr*)&pelanggan,sizeof(pelanggan));
	if(t == -1)
	{
	printf("Error in connecting to server");
	exit(1);
	}

	while(1)
	{
		printf("Client: "); 
		fgets(buffer,100,stdin);
		if(strncmp(buffer,"bye",3) == 0)
		break;
		t = send(sock_desc,buffer,100,0);
		if(t == -1)
		{
			printf("Error in sending");
			exit(1);
		}
		t = recv(sock_desc,buffer,100,0);
		if(t == -1)
		{
			printf("Error in receiving");
			exit(1);
		}

		printf("\nServer: %s",buffer); 
	}

	close(sock_desc);
	exit(0);
	return 0;
}
