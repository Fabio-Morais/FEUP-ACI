#include "ModbusTCP.h"
#define BUF_LEN 1000

int create_socket(char *server_add, int port,  uint8_t *PDU, unsigned int APDUlen)
{
    int sock, len;
    struct sockaddr_in serv;
    socklen_t addlen = sizeof(serv);
    char buf[BUF_LEN];
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    inet_aton(server_add, &serv.sin_addr);
    if (connect(sock, (struct sockaddr *)&serv, addlen) != 0)
    {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("Server connected");

    write(sock, PDU, APDUlen +7);

}

void insert_MBAP_to_PDU(MBAP_struct *mbap, uint8_t *pdu)
{
    pdu[0] = (uint8_t)(mbap->ID) >> 8;
    pdu[1] = (uint8_t)(mbap->ID) & 0xFF;
    pdu[2] = (uint8_t)(mbap->protocol_ID) >> 8;
    pdu[3] = (uint8_t)(mbap->protocol_ID) & 0xFF;
    pdu[4] = (uint8_t)(mbap->len) >> 8;
    pdu[5] = (uint8_t)(mbap->len) & 0xFF;
    pdu[6] = (uint8_t)(mbap->unit_ID);
}
void insert_APDU_to_PDU(uint8_t *pdu, uint8_t *apdu, unsigned int APDUlen)
{
    int j = 0;
    for (int i = 7; i < APDUlen; i++)
        pdu[i] = apdu[j++];
}
int ID_Mbap = 1;
int Send_Modbus_request(char *server_add, int port, uint8_t *APDU, unsigned int APDUlen, uint8_t *APDU_R)
{
    MBAP_struct *mbap = malloc(sizeof(MBAP_struct));
    mbap->ID = ID_Mbap;
    mbap->protocol_ID = 0;
    mbap->len = APDUlen + 1;
    mbap->unit_ID = 1;

    uint8_t *PDU = (uint8_t *)calloc(255, sizeof(uint8_t));
    insert_MBAP_to_PDU(mbap, PDU);
    insert_APDU_to_PDU(PDU, APDU, APDUlen);
    for(int i=0; i< APDUlen; i++)
        printf("%x  ", APDU[i]);
    int sock=create_socket(server_add, port, PDU, APDUlen);

    close(sock);

    free(PDU);
}