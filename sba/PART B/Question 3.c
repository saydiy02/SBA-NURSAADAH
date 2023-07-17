#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define maxBuffer_s 1024
#define TCP_port 6001

int main() {
	int sockfd, client_sockfd;
	char buff[maxBuffer_s];
	struct sockaddr_in saddr, caddr;
	socklen_t client_len;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("Error in socket");
		exit(EXIT_FAILURE);
	}

	memset(&saddr, 0, sizeof(saddr));
	memset(&caddr, 0, sizeof(caddr));

	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(TCP_port);

	if (bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr))<0){
		perror("error in bind");
		exit(EXIT_FAILURE);
	}

	if (listen(sockfd, 1) <0){
		perror("error in listen");
		exit(EXIT_FAILURE);
	}

	printf("TCP Server is running and waiting for client .....\n");
	while (1){
		client_len = sizeof (caddr);

		client_sockfd = accept(sockfd,(struct sockaddr*)&caddr, &client_len);
		if (client_sockfd < 0) {
			perror("Error in accept");
			exit(EXIT_FAILURE);
		}

		int randomNo = rand() % 80000 + 50000;
		sprintf(buff, "%d", randomNo);
		ssize_t send_len = send(client_sockfd, buff, strlen(buff), 0);
		if (send_len < 0){
			perror("Error in send");
			exit(EXIT_FAILURE);
		}
		close (client_sockfd);
	}
	close(sockfd);

	return 0;
}
