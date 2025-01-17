#include "Tube.h"

Tube::Tube(float* sensing_value) {
    this->float_value_ptr = sensing_value;
    this->int_value_ptr = nullptr;
    this->long_value_ptr = nullptr;
    this->unsigned_int_value_ptr = nullptr;
    this->unsigned_long_value_ptr = nullptr;
    this->token = "init";
    this->channel = "init";
    this->name = "init";
    this->token_empty = true;
    this->timestamp_empty = true;

    this->_element_ptr = std::unique_ptr<Element>(new Element());
    this->element_ptr = _element_ptr.get();
}

Tube::Tube(int* sensing_value) {
    this->float_value_ptr = nullptr;
    this->int_value_ptr = sensing_value;
    this->long_value_ptr = nullptr;
    this->unsigned_int_value_ptr = nullptr;
    this->unsigned_long_value_ptr = nullptr;
    this->token = "init";
    this->channel = "init";
    this->name = "init";
    this->token_empty = true;
    this->timestamp_empty = true;

    this->_element_ptr = std::unique_ptr<Element>(new Element());
    this->element_ptr = _element_ptr.get();
}

Tube::Tube(long* sensing_value) {
    this->float_value_ptr = nullptr;
    this->int_value_ptr = nullptr;
    this->long_value_ptr = sensing_value;
    this->unsigned_int_value_ptr = nullptr;
    this->unsigned_long_value_ptr = nullptr;
    this->token = "init";
    this->channel = "init";
    this->name = "init";
    this->token_empty = true;
    this->timestamp_empty = true;

    this->_element_ptr = std::unique_ptr<Element>(new Element());
    this->element_ptr = _element_ptr.get();
}

Tube::Tube(unsigned int* sensing_value) {
    this->float_value_ptr = nullptr;
    this->int_value_ptr = nullptr;
    this->long_value_ptr = nullptr;
    this->unsigned_int_value_ptr = sensing_value;
    this->unsigned_long_value_ptr = nullptr;
    this->token = "init";
    this->channel = "init";
    this->name = "init";
    this->token_empty = true;
    this->timestamp_empty = true;

    this->_element_ptr = std::unique_ptr<Element>(new Element());
    this->element_ptr = _element_ptr.get();
}

Tube::Tube(unsigned long* sensing_value) {
    this->float_value_ptr = nullptr;
    this->int_value_ptr = nullptr;
    this->long_value_ptr = nullptr;
    this->unsigned_int_value_ptr = nullptr;
    this->unsigned_long_value_ptr = sensing_value;
    this->token = "init";
    this->channel = "init";
    this->name = "init";
    this->token_empty = true;
    this->timestamp_empty = true;

    this->_element_ptr = std::unique_ptr<Element>(new Element());
    this->element_ptr = _element_ptr.get();
}


Tube::~Tube() {
    if (this->_element_ptr) {
        _element_ptr.reset(nullptr);
    }
}

bool Tube::begin(String channel, String name, String token) {
    this->channel = channel;
    this->name = name;
    this->token = token;
    this->token_empty = false;
    return true;
}

bool Tube::add(String timestamp) {
    // TODO : Test
    if (float_value_ptr != nullptr) {
        this->timestamp_empty = false;
        return element_ptr->append(float_value_ptr, timestamp);
    } else if (int_value_ptr != nullptr) {
        this->timestamp_empty = false;
        return element_ptr->append(int_value_ptr, timestamp);
    } else if (long_value_ptr != nullptr) {
        this->timestamp_empty = false;
        return element_ptr->append(long_value_ptr, timestamp);
    } else if (unsigned_int_value_ptr != nullptr) {
        this->timestamp_empty = false;
        return element_ptr->append(unsigned_int_value_ptr, timestamp);
    } else if (unsigned_long_value_ptr != nullptr) {
        this->timestamp_empty = false;
        return element_ptr->append(unsigned_long_value_ptr, timestamp);
    } else {
        // Error
        return false;
    }
}

void Tube::value(float* pick_value) { element_ptr->savedValue(pick_value); }

void Tube::value(int* pick_value) { element_ptr->savedValue(pick_value); }

void Tube::value(long* pick_value) { element_ptr->savedValue(pick_value); }

void Tube::value(unsigned int* pick_value) { element_ptr->savedValue(pick_value); }

void Tube::value(unsigned long* pick_value) { element_ptr->savedValue(pick_value); }


String Tube::timestamp() {
    if (timestamp_empty) {
        // Error
    }
    return element_ptr->savedTimestamp();
}

String Tube::toJson() {
    if (!token_empty && !timestamp_empty) {
        DynamicJsonDocument doc(256);
        doc["tube_token"] = this->token;
        doc["created_at"] = element_ptr->savedTimestamp();
        if (float_value_ptr != nullptr) {
            float value;
            element_ptr->savedValue(&value);
            doc["value"] = value; // Only 9 decimal places
        } else if (int_value_ptr != nullptr) {
            int value;
            element_ptr->savedValue(&value);
            doc["value"] = value;
        } else if (long_value_ptr != nullptr) {
            long value;
            element_ptr->savedValue(&value);
            doc["value"] = value;
        } else if (unsigned_int_value_ptr != nullptr) {
            unsigned int value;
            element_ptr->savedValue(&value);
            doc["value"] = value;
        } else if (unsigned_long_value_ptr != nullptr) {
            unsigned long value;
            element_ptr->savedValue(&value);
            doc["value"] = value;
        } else {
            // Error
        }
        String output;
        serializeJson(doc, output);
        String json = output;
        return json;
    } else {
        // Error
        return "";
    }
    return "";
}


bool Tube::parsedElementIs(String json) {
    if (!token_empty && !timestamp_empty) {
        DynamicJsonDocument doc(2048);
        DeserializationError error = deserializeJson(doc, json);
        if (error) {
            this->error = true;
            this->error_message = "Json deserialize failed";
            return false;
        }
        if (doc[0] == nullptr) {
            this->error = true;
            this->error_message = "No element found";
            return false;
        }

        String timestamp = element_ptr->savedTimestamp();
        String rep_timestamp = doc[0]["created_at"].as<String>();
        timestamp.replace(" ", "T");
        int timezone_pos = timestamp.indexOf('+');
        if (timezone_pos == -1) {
            timezone_pos = timestamp.indexOf('-');
        }
        timestamp = timestamp.substring(0, timezone_pos);

        if (float_value_ptr != nullptr) {
            float value;
            element_ptr->savedValue(&value);
            float rep_value = doc[0]["value"].as<float>();
            return value == rep_value && timestamp == rep_timestamp;
        } else if (int_value_ptr != nullptr) {
            int value;
            element_ptr->savedValue(&value);
            int rep_value = doc[0]["value"].as<int>();
            return value == rep_value && timestamp == rep_timestamp;
        } else if (long_value_ptr != nullptr) {
            long value;
            element_ptr->savedValue(&value);
            long rep_value = doc[0]["value"].as<long>();
            return value == rep_value && timestamp == rep_timestamp;
        } else if (unsigned_int_value_ptr != nullptr) {
            unsigned int value;
            element_ptr->savedValue(&value);
            unsigned int rep_value = doc[0]["value"].as<unsigned int>();
            return value == rep_value && timestamp == rep_timestamp;
        } else if (unsigned_long_value_ptr != nullptr) {
            unsigned long value;
            element_ptr->savedValue(&value);
            unsigned long rep_value = doc[0]["value"].as<unsigned long>();
            return value == rep_value && timestamp == rep_timestamp;
        }

    } else {
        // Error
        return false;
    }
    return false;
}