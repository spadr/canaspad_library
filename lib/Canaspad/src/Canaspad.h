#ifndef Canaspad_h
#define Canaspad_h

#include "ApiEndPoint.h"
#include "DataModel/Tube.h"
#include <ArduinoJson.h>
#include <Supabase.h>


class Canaspad {
  protected:
    CanaspadEndPoint canaspad_api_end_point;
    Supabase supabase;

  private:
    const char* api_host;
    const char* api_username;
    const char* api_password;

    String error_message;


  public:
    Canaspad(const char* host, const char* username, const char* password, const long offset_sec,
             const char* root_ca = nullptr, const char* client_cert = nullptr,
             const char* client_key = nullptr);
    ~Canaspad();

    int offset_hour;

    bool login();
    bool token(Tube& sensor, String const channel, String const name);
    bool createToken(Tube& sensor, String const channel, String const name);
    bool write(Tube& sensor, int year, int month, int day, int hour, int minute, int second,
               int utc_offset_hour);
    bool send(Tube& sensor);
    bool fetch(Tube& sensor, float* fresh_value_p, String* fresh_timestamp_p = nullptr);
    bool fetch(Tube& sensor, int* fresh_value_p, String* fresh_timestamp_p = nullptr);
    bool fetch(Tube& sensor, long* fresh_value_p, String* fresh_timestamp_p = nullptr);
    bool fetch(Tube& sensor, unsigned int* fresh_value_p, String* fresh_timestamp_p = nullptr);
    bool fetch(Tube& sensor, unsigned long* fresh_value_p, String* fresh_timestamp_p = nullptr);


    String makeTimestampTz(int year, int month, int day, int hour, int minute, int second,
                           int utc_offset_hour);
    String makeTimestamp(int year, int month, int day, int hour, int minute, int second);

    String checkErrorMessage() { return error_message; }
};

#endif
