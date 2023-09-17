#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define MAX_BUFFER_SIZE 1024
int main()
{
	int clientSocket;
	struct sockaddr_in serverAddr;
	char buffer[MAX_BUFFER_SIZE];
	//create socket
	clientSocket = socket(AF_INET,SOCK_STREAM,0);
	if(clientSocket == -1)
	{
		perror("Error creating socket..");
		exit(EXIT_FAILURE);
	}
	//configure server address
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	inet_pton(AF_INET, SERVER_IP, &(serverAddr.sin_addr));
	//connet to server
	if(connect(clientSocket,(struct sockaddr *)&serverAddr, sizeof(serverAddr)) ==-1)
	{
		perror("Error connecting to server");
		exit(EXIT_FAILURE);
	}
	//read file to send
	FILE *file = fopen("dummy_file.txt","rb");
	if(!file)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		ssize_t bytesRead = fread(buffer, 1, sizeof(buffer),file);
		if(bytesRead <=0)
		{
			break;
		}
		send(clientSocket, buffer, bytesRead, 0);
	}
	fclose(file);
	close(clientSocket);
	printf("File sent successfully..\n");
	return 0;
}


