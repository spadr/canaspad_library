#include "Element.h"

Element::Element() {
    timestamp_tz_t unix = "1970-01-01 00:00:00+09";
    this->timestamp = unix;
}

Element::~Element() {}

bool Element::append(float* add_value, timestamp_tz_t timestamp_add) {
    timestamp = timestamp_add;
    nucleus.put_float(*add_value);
    // DONE : Test code is in "/examples"
    return true;
}

bool Element::append(int* add_value, timestamp_tz_t timestamp_add) {
    timestamp = timestamp_add;
    nucleus.put_int(*add_value);
    // DONE : Test code is in "/examples"
    return true;
}

bool Element::append(long* add_value, timestamp_tz_t timestamp_add) {
    timestamp = timestamp_add;
    nucleus.put_long(*add_value);
    // DONE : Test code is in "/examples"
    return true;
}

bool Element::append(unsigned int* add_value, timestamp_tz_t timestamp_add) {
    timestamp = timestamp_add;
    nucleus.put_unsigned_int(*add_value);
    // DONE : Test code is in "/examples"
    return true;
}

bool Element::append(unsigned long* add_value, timestamp_tz_t timestamp_add) {
    timestamp = timestamp_add;
    nucleus.put_unsigned_long(*add_value);
    // DONE : Test code is in "/examples"
    return true;
}

bool Element::saved_value(float* _value) {
    *_value = nucleus.get_float();
    return true;
}

bool Element::saved_value(int* _value) {
    *_value = nucleus.get_int();
    return true;
}

bool Element::saved_value(long* _value) {
    *_value = nucleus.get_long();
    return true;
}

bool Element::saved_value(unsigned int* _value) {
    *_value = nucleus.get_unsigned_int();
    return true;
}

bool Element::saved_value(unsigned long* _value) {
    *_value = nucleus.get_unsigned_long();
    return true;
}

timestamp_tz_t Element::saved_timestamp() { return timestamp; }

bool Element::saved_value_is(float value) { return value == nucleus.get_float(); }

bool Element::saved_value_is(int value) { return value == nucleus.get_int(); }

bool Element::saved_value_is(long value) { return value == nucleus.get_long(); }

bool Element::saved_value_is(unsigned int value) { return value == nucleus.get_unsigned_int(); }

bool Element::saved_value_is(unsigned long value) { return value == nucleus.get_unsigned_long(); }

bool Element::saved_timestamp_is(timestamp_tz_t timestamp) { return timestamp == this->timestamp; }