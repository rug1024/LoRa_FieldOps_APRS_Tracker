#pragma once
#include <Arduino.h>
inline bool validPairingPin(const String& value) {
    if (value.length() != 6) return false;
    for (unsigned int i = 0; i < value.length(); ++i)
        if (value[i] < '0' || value[i] > '9') return false;
    return true;
}
inline bool parseOledBrightness(const String& value, int& result) {
    if (value.length() == 0 || value.length() > 3) return false;
    int parsed = 0;
    for (unsigned int i = 0; i < value.length(); ++i) {
        if (value[i] < '0' || value[i] > '9') return false;
        parsed = parsed * 10 + value[i] - '0';
    }
    if (parsed < 1 || parsed > 100) return false;
    result = parsed;
    return true;
}
