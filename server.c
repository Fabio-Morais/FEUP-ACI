#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define MYPORT 2220
#define BUF_LEN 1000
#define IP "127.0.0.1"
int main(){
    int so, sd, len;
    struct sockaddr_in loc, rem;
    socklen_t addlen = sizeof(loc);
    char buf[BUF_LEN];
    so = socket(PF_INET, SOCK_STREAM, 0);
    printf("SERVER\n");
    printf("IP: %s\tPORT: %d\n", IP, MYPORT);
    if(so == -1){
        printf("socket creation failed...\n"); 
        exit(0);
    }else
    {
       printf("Socket successfully created..\n");
    }
    
    loc.sin_family = AF_INET;
    loc.sin_port = htons(MYPORT);
    inet_aton( IP, &loc.sin_addr);
    
    if(bind(so, (struct sockaddr *) &loc, addlen) != 0){
        printf("socket bind failed...\n"); 
        exit(0); 
    }else
        printf("Socket successfully binded..\n"); 
    
    if(listen(so, 10) != 0){
        printf("Listen failed...\n"); 
        exit(0); 
    }else
        printf("Server listening..\n");
    sd=accept(so, (struct sockaddr *) &rem, &addlen);
    if (sd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server acccept the client...\n"); 
    while(1){
        len=recv(sd, buf, BUF_LEN, 0);    
        printf("Mensagem: %s\n", buf);
       
    }
 
    return 1;
}