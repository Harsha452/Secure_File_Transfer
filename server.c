#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#define PORT 12345
#define MAX_BUFFER_SIZE 1024
int main()
{
	int serverSocket,clientSocket;
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);
	char buffer[MAX_BUFFER_SIZE];
	//create socket
	serverSocket = socket(AF_INET, SOCK_STREAM,0);
	if(serverSocket == -1)
	{
		perror("Error creating socket");
		exit(EXIT_FAILURE);
	}
	//configure server address
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(PORT);
	//Bind Socket
	if(bind(serverSocket,(struct sockaddr *)&serverAddr,sizeof(serverAddr)) == -1)
	{
		perror("Error binding socket");
		exit(EXIT_FAILURE);
	}
	//Listen for connections
	if(listen(serverSocket, 5) == -1)
	{
		perror("error listening");
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port %d....\n",PORT);
	//Accept client connection
	clientSocket = accept(serverSocket,(struct sockaddr *)&clientAddr, &clientAddrLen);
	if(clientSocket == -1)
	{
		perror("Error accepting client connections");
		exit(EXIT_FAILURE);
	}
	//Receive file data and save it
	FILE *file = fopen("received_file.txt","wb");
	if(!file)
	{
		perror("Error openong file");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		ssize_t bytesRead = recv(clientSocket, buffer,sizeof(buffer),0);
		if(bytesRead <=0)
		{
			break;
		}
		fwrite(buffer,1,bytesRead,file);
	}
	fclose(file);
	close(clientSocket);
	close(serverSocket);
	printf("File received successfully..\n");
	return 0;
		
}


