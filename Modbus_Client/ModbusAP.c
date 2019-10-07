#include "ModbusAP.h"
#define INT_LIMIT 65.535

//16 bits
//code: 16 | 10(hex)
/*                                                    registo inicial, comprimento, valores*/
int Write_multiple_regs (char *server_add, unsigned int port, int st_r, int n_r, char *val){
    if(n_r + st_r > INT_LIMIT)
        return -1;
    uint16_t APDU_len = n_r;
    uint16_t *APDU = (uint16_t*)calloc(APDU_len, sizeof(uint16_t));
    // Write header
    APDU[0] = 0x10;



   //Send_Modbus_request(server_add, port, APDU, APDUlen, APDU_R);
}