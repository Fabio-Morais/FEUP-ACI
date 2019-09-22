#include <netdb.h> 
#include <netinet/in.h> 
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define MYPORT 2220
#define BUF_LEN 1000
#define IP "127.0.0.1"
int main(){
    int sock, len;
    struct sockaddr_in serv;
    socklen_t addlen = sizeof(serv);
    char buf[BUF_LEN];
    sock = socket(PF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(MYPORT);
    inet_aton( "127.0.0.1",&serv.sin_addr);
    if(connect(sock, (struct sockaddr *) &serv, addlen) != 0 ){
        printf("connection with the server failed...\n"); 
        exit(0); 
    }

    while(1){
        printf("Enviar mensagem: ");
        scanf("%s", buf);
        //fgets(buf,BUF_LEN, stdin);
        len=send(sock, buf, strlen(buf)+1, 0);
        if(!strcmp("exit", buf)){
            printf("Closed");
            break;
        }
    }
    close(sock); 
    return 1;
}