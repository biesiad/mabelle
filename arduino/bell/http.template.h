#define ESP_TCP_START_CMD "AT+CIPSTART=\"TCP\",\"myserver.com/bell\",80\r"   // connect with service
#define ESP_TCP_SEND_CMD "AT+CIPSEND=54\r"
#define ESP_TCP_CONTENT "GET / HTTP/1.1\r\nHost: myserver.com/bell\r\n"      // sent a GET /
