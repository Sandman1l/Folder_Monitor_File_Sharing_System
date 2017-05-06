
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PORT_NUMBER 5000
#define SERVER_ADDRESS  "10.15.127.52"
#define FILE_NAME  "hello.c"
#define LENGTH 512
#define FOLDER_EXTENSION "/Users/LuisSFU/Desktop/Mission7/"

int main(int argc, char **argv)
{
        int server_socket;
        int peer_socket;
        struct sockaddr_in server_addr;
        struct sockaddr_in peer_addr;
        struct stat file_stat;
        socklen_t socket_size;
        int socket_fd;
        char buffer[LENGTH];
        //Create server socket
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket == -1)
        {
                fprintf(stderr, "Error: Failed to create socket.");

                exit(EXIT_FAILURE);
        }
        /* Zeroing server_addr struct */
        memset(&server_addr, 0, sizeof(server_addr));
        /* Construct server_addr struct */
        server_addr.sin_family = AF_INET;
        inet_pton(AF_INET, SERVER_ADDRESS, &(server_addr.sin_addr));
        server_addr.sin_port = htons(PORT_NUMBER);

        /* Bind */
        if ((bind(server_socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))) == -1)
        {
                fprintf(stderr, "Error: Failed to bind.");

                exit(EXIT_FAILURE);
        }

        /* Listening to incoming connections */
        if(listen(server_socket,5) == -1){
	         printf("Error: Failed to listen Port.\n");
           exit(EXIT_FAILURE);
	        }else{
		          printf ("SUCCESS: Listening the port %d.\n", PORT_NUMBER);
            }
	           int success = 0;
	           while(success == 0){
	            socket_size = sizeof(struct sockaddr_in);
	           //Wait a connection
	            if ((socket_fd = accept(server_socket, (struct sockaddr *)&server_addr, &socket_size)) == -1){
	                printf("Error:  Failed to Obtain new Socket Despcritor.\n");
		            }else{
			               printf("NOTICE: Server has got connected from %s.\n", inet_ntoa(server_addr.sin_addr));
                   }
		               //Recieve file
		               char* file_name = "/Users/LuisSFU/Desktop/Mission7/foo.c";
		               FILE *file = fopen(file_name, "a");
		               if(file == NULL){
			             printf("File %s Cannot be opened file.\n", file_name);
                    }else{
			                bzero(buffer, LENGTH);
                    }
			            int blockSize = 0;
                  int writeSize;
			            while((blockSize = recv(server_socket, buffer, LENGTH, 0))){
			                 if(blockSize < 0){
			                   printf("Error receiving file.\n");
			                 }
			                   writeSize = fwrite(buffer, sizeof(char), blockSize, file);
			                   if(writeSize < blockSize){
			                       printf("File write failed.\n");
                           }else if(blockSize){
						                    break;
                              }
  			       bzero(buffer, LENGTH);
			    }
			    printf("Ok received new File!\n");
			    fclose(file);
			//}
		}

}
