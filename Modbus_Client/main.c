#include <netdb.h> 
#include <netinet/in.h> 
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include "ModbusTCP.h"
#include "ModbusAP.h"
#define MYPORT 502
#define IP "127.0.0.1"
int* user_input(int *port, char *ip, int *st_r, int *n_r){
    printf("Ip: ");
    fgets(ip, 50, stdin);
    ip[strlen(ip)-1]='\0';
    printf("Port: ");
    scanf("%d", port);
    printf("registo inicial: ");
    scanf("%d", st_r);
    printf("Numero de registos: ");
    scanf("%d", n_r);
    int *vetor = (int*)calloc((*n_r), sizeof(int*));
    for(int i=0; i< (*n_r); i++){
        printf("Registo %d: ", i+1);
        scanf("%d", &vetor[i]);
    }
    return vetor;
}
int main(){
    uint8_t apdu[26]={0x10,0x00,0x00,0x00,0x0a,0x14,0x00,0x01,0x00,0x06,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t APDU_R[255];
    
    int port;
    int st_r;
    int n_r;
    char ip[50];
    int *data=user_input(&port, ip, &st_r, &n_r);
    printf("ip: %s\tport:%d\tRegisto inicial: %d\tNumero de registos: %d\n",  ip,port, st_r, n_r );
        for(int i=0; i< n_r; i++){
    printf("%d\n", data[i]);
        }
    //Send_Modbus_request(IP,MYPORT,apdu, 26,APDU_R);
    return 1;
}