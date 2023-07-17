#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define maxBuffer_s 1024
#define TCP_SERVER_IP "127.0.0.1"
#define TCP_SERVER_PORT 6001

int main(){
	int sockfd;
	char buff[maxBuffer_s];
	struct sockaddr_in saddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("Error in socket");
		exit(EXIT_FAILURE);
	}
	
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
        saddr.sin_addr.s_addr = inet_addr(TCP_SERVER_IP);
        saddr.sin_port = htons(TCP_SERVER_PORT);

	if (connect(sockfd,(struct sockaddr*)&saddr, sizeof(saddr))<0){
		perror("Error in connect");
		exit(EXIT_FAILURE);
	}

	ssize_t recv_len = recv(sockfd, buff, sizeof(buff), 0);
	if (recv_len <0){
		perror("Error in recv");
		exit(EXIT_FAILURE);
	}

	buff[recv_len] = '\0';
	int randomNo = atoi(buff);

	printf("Client: Receive random number: %d\n", randomNo);
	close(sockfd);

	return 0;
}
