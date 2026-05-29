#include "UserProfile.h"

using namespace std;

UserProfile::UserProfile()
    : name("Focus User"),
      gender("Male"),
      dateOfBirth("Not set"),
      country("Not set"),
      wakeTime("06:00"),
      sleepTime("22:30"),
      darkMode(false),
      notifications(true) {
}

UserProfile::UserProfile(string userName, string userCountry)
    : name(userName),
      gender("Male"),
      dateOfBirth("Not set"),
      country(userCountry),
      wakeTime("06:00"),
      sleepTime("22:30"),
      darkMode(false),
      notifications(true) {
}

UserProfile::~UserProfile() {
}

string UserProfile::getName() const {
    return name;
}

string UserProfile::getGender() const {
    return gender;
}

string UserProfile::getDateOfBirth() const {
    return dateOfBirth;
}

string UserProfile::getCountry() const {
    return country;
}

string UserProfile::getWakeTime() const {
    return wakeTime;
}

string UserProfile::getSleepTime() const {
    return sleepTime;
}

bool UserProfile::getDarkMode() const {
    return darkMode;
}

bool UserProfile::getNotifications() const {
    return notifications;
}

void UserProfile::setName(const string& value) {
    name = value.empty() ? "Focus User" : value;
}

void UserProfile::setGender(const string& value) {
    gender = value == "Female" ? "Female" : "Male";
}

void UserProfile::setDateOfBirth(const string& value) {
    dateOfBirth = value.empty() ? "Not set" : value;
}

void UserProfile::setCountry(const string& value) {
    country = value.empty() ? "Not set" : value;
}

void UserProfile::setWakeTime(const string& value) {
    wakeTime = value.empty() ? "06:00" : value;
}

void UserProfile::setSleepTime(const string& value) {
    sleepTime = value.empty() ? "22:30" : value;
}

void UserProfile::setDarkMode(bool value) {
    darkMode = value;
}

void UserProfile::setNotifications(bool value) {
    notifications = value;
}

ostream& operator<<(ostream& out, const UserProfile& profile) {
    out << "Name: " << profile.name << "\n"
        << "Gender: " << profile.gender << "\n"
        << "Date of birth: " << profile.dateOfBirth << "\n"
        << "Country: " << profile.country << "\n"
        << "Wake-up time: " << profile.wakeTime << "\n"
        << "Sleep time: " << profile.sleepTime << "\n"
        << "Theme: " << (profile.darkMode ? "Dark" : "Light") << "\n"
        << "Notifications: " << (profile.notifications ? "On" : "Off");
    return out;
}

void printProfileCard(const UserProfile& profile) {
    cout << "\n========== PROFILE ==========\n";
    cout << profile << "\n";
    cout << "App version: Focus Beta\n";
    cout << "=============================\n";
}
