#include "KW_function.h"
#include "tm_stm32f4_delay.h"

#define CHIP "a123"


#define NET "AT+CIPSTART=\"TCP\",\"140.118.170.13\",80\r\n"
#define WIFILEN "AT+CIPSEND=%d\r\n"

#define HEAD_BUT    "POST /getstmb.php HTTP/1.1 \r\nHost: 140.118.170.13:80 \r\nContent-Length: 17 \r\nContent-Type: application/x-www-form-urlencoded \r\nConnection: keep-alive\r\n\r\nChip="
#define HEAD_LEV    "POST /getstmw.php HTTP/1.1 \r\nHost: 140.118.170.13:80 \r\nContent-Length: 17 \r\nContent-Type: application/x-www-form-urlencoded \r\nConnection: keep-alive\r\n\r\nChip="
#define HEAD_10m    "POST /getstm10.php HTTP/1.1 \r\nHost: 140.118.170.13:80 \r\nContent-Length: 89 \r\nContent-Type: application/x-www-form-urlencoded \r\nConnection: keep-alive\r\n\r\nChip="
#define HEAD_1h        "POST /getstmf.php HTTP/1.1 \r\nHost: 140.118.170.13:80 \r\nContent-Length: 22 \r\nContent-Type: application/x-www-form-urlencoded \r\nConnection: keep-alive\r\n\r\nChip="
#define HEAD_CHECKTIME  "GET /timerequest.php HTTP/1.1 \r\n Host: 140.118.170.13:80 \r\n Connection: keep-alive\r\n"



void wificommand_BUT();
void wificommand_LEV();
void wificommand_10m(int WTem, int Tem, int Hum, int Wet[]);
void wificommand_1h(float Flw_total);
void wificommand_checktime();