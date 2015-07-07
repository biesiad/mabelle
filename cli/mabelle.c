#include <stdio.h>
#include <curl/curl.h>
#include "host.h"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

int main(void) {
  CURL *curl;
  CURLcode res;
  char url[256];

  curl_global_init(CURL_GLOBAL_ALL);

  curl = curl_easy_init();
  if(curl) {
    sprintf(url, "%s/bell", HOST);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 0);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
      printf("Ring!\n");
    }
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();
  return 0;
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
  // Do nothing. Using the callback only to prevent from spitting out the response to stdout.
  return nmemb;
}
