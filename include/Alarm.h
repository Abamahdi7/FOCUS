#ifndef ALARM_H
#define ALARM_H

#include <string>

using namespace std;

class Alarm {
private:
    string time;
    bool enabled;

public:
    Alarm();
    Alarm(string alarmTime, bool isEnabled);
    ~Alarm();

    string getTime() const;
    bool isEnabled() const;

    void setTime(const string& value);
    void setEnabled(bool value);
};

#endif
