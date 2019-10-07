#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>


#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

typedef struct  {
    uint16_t ID;
    uint16_t protocol_ID;
    uint16_t len;
    uint8_t unit_ID;
}MBAP_struct;

int Send_Modbus_request(char *server_add, int port, uint8_t *APDU,unsigned int APDUlen, uint8_t *APDU_R);