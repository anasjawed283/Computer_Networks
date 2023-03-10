//SERVER-------------------------------------------------------------------
//This code is contributed by Anas Jawed
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int sd, sd2, clilen,sport,i,connect,count=0,val;
    int port;
    int window_size;
    int ACK,client_socket,frame;
    char data[50], senderdata[50];
    struct sockaddr_in servaddr,cliaddr;
    printf("enter the server port\n");
    scanf("%d\n",&sport);
    printf("%d\n",sport);
    sd=socket(AF_INET,SOCK_STREAM,0);
    if(sd<0)
            printf("can't create\n");
    else
            printf("socket created\n");
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(sport);
    sd2=bind(sd,(struct sockaddr*)&servaddr, sizeof(servaddr));
    if(sd2<0)
            printf("can't bind\n");
    else
            printf("binded\n");
    listen(sd,5);
    
    clilen=sizeof(cliaddr);
    connect=accept(sd,(struct sockaddr*)&cliaddr,&clilen);
    if(connect<0)
        printf("can't accept\n");
    else
        printf("Accepted\n");

    recv(client_socket,&window_size,sizeof(window_size),0);
    
    while(frame<window_size){
        for(i=0;i<window_size;i++){
            recv(client_socket,&frame,sizeof(frame),0);
            printf("Transmitted Frames Received from the client is %d\n",frame);
            frame++;
            if(frame==window_size)
            break;    
        }
        printf("Enter the negative Acknowledgement to be sent to the client\n");
        scanf("%d",&ACK);
        send(client_socket,&ACK,sizeof(ACK),0);
        if(ACK==window_size)
        break;
        else
        frame=ACK;
    }
    return 0;
}
