#include "Tube.h"

Tube::Tube(float *sensing_value)
{
    this->float_value_ptr = sensing_value;
    this->int_value_ptr = nullptr;
    this->long_value_ptr = nullptr;
    this->unsigned_int_value_ptr = nullptr;
    this->unsigned_long_value_ptr = nullptr;
    this->token = "init";
    this->channel = "init";
    this->name = "init";
    this->size = 0;
    this->element_empty = true;
    this->token_empty = true;
    this->timestamp_empty = true;
}

Tube::Tube(int *sensing_value)
{
    this->float_value_ptr = nullptr;
    this->int_value_ptr = sensing_value;
    this->long_value_ptr = nullptr;
    this->unsigned_int_value_ptr = nullptr;
    this->unsigned_long_value_ptr = nullptr;
    this->token = "init";
    this->channel = "init";
    this->name = "init";
    this->size = 0;
    this->element_empty = true;
    this->token_empty = true;
    this->timestamp_empty = true;
}

Tube::Tube(long *sensing_value)
{
    this->float_value_ptr = nullptr;
    this->int_value_ptr = nullptr;
    this->long_value_ptr = sensing_value;
    this->unsigned_int_value_ptr = nullptr;
    this->unsigned_long_value_ptr = nullptr;
    this->token = "init";
    this->channel = "init";
    this->name = "init";
    this->size = 0;
    this->element_empty = true;
    this->token_empty = true;
    this->timestamp_empty = true;
}

Tube::Tube(unsigned int *sensing_value)
{
    this->float_value_ptr = nullptr;
    this->int_value_ptr = nullptr;
    this->long_value_ptr = nullptr;
    this->unsigned_int_value_ptr = sensing_value;
    this->unsigned_long_value_ptr = nullptr;
    this->token = "init";
    this->channel = "init";
    this->name = "init";
    this->size = 0;
    this->element_empty = true;
    this->token_empty = true;
    this->timestamp_empty = true;
}

Tube::Tube(unsigned long *sensing_value)
{
    this->float_value_ptr = nullptr;
    this->int_value_ptr = nullptr;
    this->long_value_ptr = nullptr;
    this->unsigned_int_value_ptr = nullptr;
    this->unsigned_long_value_ptr = sensing_value;
    this->token = "init";
    this->channel = "init";
    this->name = "init";
    this->size = 0;
    this->element_empty = true;
    this->token_empty = true;
    this->timestamp_empty = true;
}

Tube::~Tube()
{
}

bool Tube::begin(String _channel, String _name, uuid_t _token)
{
    channel = _channel;
    name = _name;
    token = _token;
    token_empty = false;
    return true;
}

bool Tube::add(timestamp_tz_t timestamp)
{
    // TODO : Test
    if (float_value_ptr != nullptr)
    {
        size += 1;
        element_empty = false;
        timestamp_empty = false;
        return Element::append(float_value_ptr, timestamp);
    }
    else if (int_value_ptr != nullptr)
    {
        size += 1;
        element_empty = false;
        timestamp_empty = false;
        return Element::append(int_value_ptr, timestamp);
    }
    else if (long_value_ptr != nullptr)
    {
        size += 1;
        element_empty = false;
        timestamp_empty = false;
        return Element::append(long_value_ptr, timestamp);
    }
    else if (unsigned_int_value_ptr != nullptr)
    {
        size += 1;
        element_empty = false;
        timestamp_empty = false;
        return Element::append(unsigned_int_value_ptr, timestamp);
    }
    else if (unsigned_long_value_ptr != nullptr)
    {
        size += 1;
        element_empty = false;
        timestamp_empty = false;
        return Element::append(unsigned_long_value_ptr, timestamp);
    }
    else
    {
        // Error
        return false;
    }
}

void Tube::latest_value(float *pick_value)
{
    if (element_empty)
    {
        // Error
    }
    Element::pick_value(pick_value);
}

void Tube::latest_value(int *pick_value)
{
    if (element_empty)
    {
        // Error
    }
    Element::pick_value(pick_value);
}

void Tube::latest_value(long *pick_value)
{
    if (element_empty)
    {
        // Error
    }
    Element::pick_value(pick_value);
}

void Tube::latest_value(unsigned int *pick_value)
{
    if (element_empty)
    {
        // Error
    }
    Element::pick_value(pick_value);
}

void Tube::latest_value(unsigned long *pick_value)
{
    if (element_empty)
    {
        // Error
    }
    Element::pick_value(pick_value);
}

timestamp_tz_t Tube::latest_timestamp()
{
    if (timestamp_empty)
    {
        // Error
    }
    return Element::pick_timestamp();
}

/*
json_t Tube::json_parse()
{
    if (!token_empty)
    {
        // TODO: Post Tube record
        // use ArduinoJson

        if (float_value_ptr != nullptr)
        {
            Serial.println("float");
        }
        else if (int_value_ptr != nullptr)
        {
            Serial.println("int");
        }
        else if (long_value_ptr != nullptr)
        {
            Serial.println("long");
        }
        else if (unsigned_int_value_ptr != nullptr)
        {
            Serial.println("unsigned int");
        }
        else if (unsigned_long_value_ptr != nullptr)
        {
            Serial.println("unsigned long");
        }
        else
        {
            Serial.println("unknown");
        }

}
size = 0;
element_empty = true;
}
*/