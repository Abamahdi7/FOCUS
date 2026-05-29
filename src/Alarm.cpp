#include "Alarm.h"

using namespace std;

Alarm::Alarm() : time("06:30"), enabled(true) {
}

Alarm::Alarm(string alarmTime, bool isEnabled)
    : time(alarmTime.empty() ? "06:30" : alarmTime), enabled(isEnabled) {
}

Alarm::~Alarm() {
}

string Alarm::getTime() const {
    return time;
}

bool Alarm::isEnabled() const {
    return enabled;
}

void Alarm::setTime(const string& value) {
    time = value.empty() ? "06:30" : value;
}

void Alarm::setEnabled(bool value) {
    enabled = value;
}
