#pragma once
#include <Arduino.h>
inline bool validPairingPin(const String& value) {
    if (value.length() != 6) return false;
    for (unsigned int i = 0; i < value.length(); ++i)
        if (value[i] < '0' || value[i] > '9') return false;
    return true;
}
