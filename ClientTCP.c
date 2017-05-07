#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <signal.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 20000
#define LENGTH 512


void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	/* Variable Definition */
	int sockfd;
	int nsockfd;
	char revbuf[LENGTH];
	struct sockaddr_in remote_addr;

	/* Get the Socket file descriptor */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
	    error("ERROR: Failed to obtain Socket Descriptor!\n");
	}

	/* Fill the socket address struct */
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = htons(PORT);
	inet_pton(AF_INET, "10.15.127.52", &remote_addr.sin_addr);
	bzero(&(remote_addr.sin_zero), 8);

	/* Try to connect the remote */
	if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
	{
	    error("ERROR: Failed to connect to the host!\n");
	}
	else
		printf("[Client] Connected to server at port %d...ok!\n", PORT);

	/* Send File to Server */
	//if(!fork())
	//{
		char* fs_name = "/Users/LuisSFU/Desktop/Mission7/hello.c";
		char sdbuf[LENGTH];
		printf("[Client] Sending %s to the Server...\n", fs_name);
		FILE *fs = fopen(fs_name, "r");
		if(fs == NULL)
		{
		    printf("ERROR: File %s not found.\n", fs_name);
			exit(1);
		}

		bzero(sdbuf, LENGTH);
		int fs_block_sz;
		//int success = 0;
		while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs))>0)
	    {
	        if(send(sockfd, sdbuf, fs_block_sz, 0) < 0)
	        {
	            printf("ERROR: Failed to send file %s.\n", fs_name);
	            break;
	        }
	        bzero(sdbuf, LENGTH);
	    }
	    printf("Ok File %s from Client was Sent!\n", fs_name);
	    //success = 1;
	//}
	close(sockfd);
	printf("[Client] Connection lost.\n");
	return (0);
}
