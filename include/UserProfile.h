#ifndef USER_PROFILE_H
#define USER_PROFILE_H

#include <iostream>
#include <string>

using namespace std;

class UserProfile {
private:
    string name;
    string gender;
    string dateOfBirth;
    string country;
    string wakeTime;
    string sleepTime;
    bool darkMode;
    bool notifications;

public:
    UserProfile();
    UserProfile(string userName, string userCountry);
    ~UserProfile();

    string getName() const;
    string getGender() const;
    string getDateOfBirth() const;
    string getCountry() const;
    string getWakeTime() const;
    string getSleepTime() const;
    bool getDarkMode() const;
    bool getNotifications() const;

    void setName(const string& value);
    void setGender(const string& value);
    void setDateOfBirth(const string& value);
    void setCountry(const string& value);
    void setWakeTime(const string& value);
    void setSleepTime(const string& value);
    void setDarkMode(bool value);
    void setNotifications(bool value);

    friend ostream& operator<<(ostream& out, const UserProfile& profile);
    friend void printProfileCard(const UserProfile& profile);
};

#endif
