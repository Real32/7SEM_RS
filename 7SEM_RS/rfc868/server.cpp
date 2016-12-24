#include <ctime>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#define REFERENCE 2208988800

uint32_t swap_uint32( uint32_t val )
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF ); 
    return (val << 16) | (val >> 16);
}

int main(){
  int udpSocket, nBytes;
  char buffer[32];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  time_t seconds;
  int32_t currentTime;
  /*Create UDP socket*/
  udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(9876);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*Bind socket with address struct*/
  bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverStorage;

  while(true){
    /* Try to receive any incoming UDP datagram. Address and port of 
      requesting client will be stored on serverStorage variable */
    nBytes = recvfrom(udpSocket,buffer,32,0,(struct sockaddr *)&serverStorage, &addr_size);
	//std::cout<<nBytes<<std::endl;
    if(nBytes==0){  /* Check that received datagram is empty */
		seconds = time(NULL);
		std::cout<<seconds<<std::endl;
    }

    /*Send time message back to client, using serverStorage as the address*/
    currentTime =  seconds + REFERENCE;
    currentTime = swap_uint32(currentTime);
    sendto(udpSocket,&currentTime,4,0,(struct sockaddr *)&serverStorage,addr_size);
  }

  return 0;
}