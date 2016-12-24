#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdlib.h>
#define REFERENCE 2208988800     // 70 years = 2,208,988,800 seconds, 01-01-1900 00:00 to 01:01-1970 00:00

uint32_t swap_uint32( uint32_t val )
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF ); 
    return (val << 16) | (val >> 16);
}

int main(){
  int clientSocket, portNum, nBytes;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  int32_t serverTime;
  int32_t currentTime;
  time_t seconds;

  /*Create UDP socket*/
  clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(37); //  9876 // 37
  serverAddr.sin_addr.s_addr = inet_addr("192.168.117.1"); // 129.6.15.29 // 127.0.0.1 // 192.168.117.1 //http://tf.nist.gov/tf-cgi/servers.cgi
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverAddr;

  while(true){
    //std::cout<<"Send empty datagram "<<std::endl;
    /*Send empty message to server*/
    sendto(clientSocket,0,0,0,(struct sockaddr *)&serverAddr,addr_size);
    /*Receive message from server*/
    nBytes = recvfrom(clientSocket,&serverTime,4,0,NULL, NULL);
    currentTime = swap_uint32(serverTime) - REFERENCE;
     seconds = currentTime;
    tm* timeinfo = localtime(&seconds);
    std::cout<<"Current Datetime: "<<asctime(timeinfo)<<std::endl;
    std::cin.get();
  }

  return 0;
}