#define ESP_RESET_CMD "AT+RST\r"
#define ESP_CONNECT_CMD "AT+CWJAP=\"MY_SSID\",\"MY_PASSWORD\"\r"    // connect to wifi
#define ESP_SET_AS_CLIENT_CMD "AT+CWMODE=1\r"                       // configure as client
#define ESP_GET_IP_CMD "AT+CIFSR\r"                                 // get ip address
#define ESP_SINGLE_CONNECTION_CMD "AT+CIPMUX=0"                     // configure for single connection
