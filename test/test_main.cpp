
#include "ConfigExample.h"
#include <Canaspad.h>
#include <unity.h>

Canaspad apiClient(api_host, api_username, api_password, gmt_offset_sec + daylight_offset_sec,
                   isrg_root_x1, client_cert, client_key);

float float_measured_value;
Tube float_voltage_sensor(&float_measured_value);

void test_login() { TEST_ASSERT_TRUE(apiClient.login()); }

void test_sync_float_tube_token() {
    TEST_ASSERT_TRUE(apiClient.connect(float_voltage_sensor, "float_ch_01", "float_name_01"));
}

void test_sync_float_tube_value() {
    float_measured_value = 2390.405273;
    apiClient.write(float_voltage_sensor, 2024, 4, 1, 7, 30, 12, apiClient.offset_hour);
    apiClient.send(float_voltage_sensor);
    float fresh_value;
    String fresh_timestamp;
    apiClient.fetch(float_voltage_sensor, &fresh_value, &fresh_timestamp);
    TEST_ASSERT_EQUAL_FLOAT(float_measured_value, fresh_value);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_login);
    RUN_TEST(test_sync_float_tube_token);
    RUN_TEST(test_sync_float_tube_value);
    UNITY_END();
}

void loop() {}