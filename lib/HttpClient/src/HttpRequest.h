#ifndef HttpRequest_h
#define HttpRequest_h

#if defined(USE_MOCK_CLIENT)
#include "MockWiFiClientSecure.h"
#else
#include <WiFiClientSecure.h>
#endif

#include "HttpResponse.h"
#include <memory>

struct Result {
    bool ok = false;
    String http_message = "";
    String http_version = "";
    int status_code = 0;
    String reason_phrase = "";
    HttpHeader headers;
    String message_body = "";
    bool network_error = false;
    String error_message = "";
};

class HttpRequest {
  protected:
  private:
    String host = "";
    unsigned int port = 0;

    std::unique_ptr<WiFiClientSecure> _client_ptr =
        std::unique_ptr<WiFiClientSecure>(new WiFiClientSecure());
    WiFiClientSecure* client_ptr = _client_ptr.get();

    HttpResponse* response_ptr;

    String path = "/";
    String params = "?";
    String header = "";
    String body = "";
    String request_line = "";
    uint8_t* file_data = nullptr;
    size_t file_size = 0;
    bool file_mode = false;

    unsigned long timeout = 50000;


  public:
    HttpRequest(HttpResponse* response_ptr);
    ~HttpRequest();

    bool setCACert(const char* root_ca);
    bool setCertificate(const char* client_cert);
    bool setPrivateKey(const char* client_key);
    bool setInsecure();

    bool setHost(String host);
    bool setPort(unsigned int port);
    bool setPath(String path);

    bool addParameter(String key, String value);
    bool addHeader(String key, String value);
    bool setBody(String body);
    bool setFile(uint8_t* payload, size_t size);

    bool methodIsGet();
    bool methodIsPost();
    bool methodIsPut();
    bool methodIsPatch();
    bool methodIsDelete();
    bool methodIsHead();

    Result send();

    bool end();

    // Test
    String checkHost() const { return this->host; }
    unsigned int checkPort() const { return this->port; }
    String checkPath() const { return this->path; }
    String checkParams() const { return this->params; }
    String checkRequestLine() const { return this->request_line; }
    String checkHeader() const { return this->header; }
    String checkBody() const { return this->body; }
};

#endif
