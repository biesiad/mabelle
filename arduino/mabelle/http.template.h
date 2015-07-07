#define ESP_TCP_START_CMD "AT+CIPSTART=\"TCP\",\"localhost\",80\r"   // connect with service
#define ESP_TCP_SEND_CMD "AT+CIPSEND=54\r"
#define ESP_TCP_CONTENT "GET /bell HTTP/1.1\r\nHost: localhost\r\n"      // sent a GET /
