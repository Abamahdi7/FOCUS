#include "InputUtils.h"

#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace {
    string trim(const string& value) {
        size_t start = 0;
        while (start < value.size() && isspace(static_cast<unsigned char>(value[start]))) {
            start++;
        }

        size_t end = value.size();
        while (end > start && isspace(static_cast<unsigned char>(value[end - 1]))) {
            end--;
        }

        return value.substr(start, end - start);
    }

    bool isDigitsOnly(const string& value) {
        if (value.empty()) {
            return false;
        }

        for (char ch : value) {
            if (!isdigit(static_cast<unsigned char>(ch))) {
                return false;
            }
        }

        return true;
    }

    bool hasAtLeastTwoUsefulCharacters(const string& value) {
        int count = 0;

        for (char ch : value) {
            if (!isspace(static_cast<unsigned char>(ch))) {
                count++;
            }
        }

        return count >= 2;
    }

    bool isNameLikeText(const string& value) {
        string cleaned = trim(value);

        if (!hasAtLeastTwoUsefulCharacters(cleaned)) {
            return false;
        }

        for (unsigned char ch : cleaned) {
            if (isdigit(ch)) {
                return false;
            }

            if (isalpha(ch) || isspace(ch) || ch == '-' || ch == '\'' || ch >= 128) {
                continue;
            }

            return false;
        }

        return true;
    }

    bool isRequiredText(const string& value) {
        string cleaned = trim(value);

        if (!hasAtLeastTwoUsefulCharacters(cleaned)) {
            return false;
        }

        return !isDigitsOnly(cleaned);
    }

    bool isLeapYear(int year) {
        return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    }

    bool isValidDate(const string& value) {
        if (value.size() != 10 || value[4] != '-' || value[7] != '-') {
            return false;
        }

        string yearText = value.substr(0, 4);
        string monthText = value.substr(5, 2);
        string dayText = value.substr(8, 2);

        if (!isDigitsOnly(yearText) || !isDigitsOnly(monthText) || !isDigitsOnly(dayText)) {
            return false;
        }

        int year = stoi(yearText);
        int month = stoi(monthText);
        int day = stoi(dayText);

        if (year < 1900 || year > 2100 || month < 1 || month > 12) {
            return false;
        }

        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (month == 2 && isLeapYear(year)) {
            return day >= 1 && day <= 29;
        }

        return day >= 1 && day <= daysInMonth[month - 1];
    }

    bool isValidTime(const string& value) {
        if (value.size() != 5 || value[2] != ':') {
            return false;
        }

        string hourText = value.substr(0, 2);
        string minuteText = value.substr(3, 2);

        if (!isDigitsOnly(hourText) || !isDigitsOnly(minuteText)) {
            return false;
        }

        int hour = stoi(hourText);
        int minute = stoi(minuteText);

        return hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59;
    }

    string randomDateExample() {
        static bool seeded = false;

        if (!seeded) {
            srand(static_cast<unsigned int>(time(nullptr)));
            seeded = true;
        }

        int year = 1990 + rand() % 15;
        int month = 1 + rand() % 12;
        int day = 1 + rand() % 28;

        stringstream example;
        example << year << "-"
                << setw(2) << setfill('0') << month << "-"
                << setw(2) << setfill('0') << day;

        return example.str();
    }
}

string readLine(const string& prompt) {
    cout << prompt;
    string value;
    getline(cin, value);
    return value;
}

int readInt(const string& prompt, int minValue, int maxValue) {
    while (true) {
        cout << prompt;
        string text;
        getline(cin, text);
        text = trim(text);

        if (isDigitsOnly(text)) {
            try {
                int value = stoi(text);

                if (value >= minValue && value <= maxValue) {
                    return value;
                }
            } catch (const out_of_range&) {
            }
        }

        cout << "Invalid number. Enter a valid number from "
                  << minValue << " to " << maxValue << ".\n";
    }
}

string readRequiredName(const string& prompt) {
    while (true) {
        string value = trim(readLine(prompt));

        if (isNameLikeText(value)) {
            return value;
        }

        cout << "Invalid text. Use letters only, at least 2 characters, no numbers.\n";
    }
}

string readRequiredText(const string& prompt) {
    while (true) {
        string value = trim(readLine(prompt));

        if (isRequiredText(value)) {
            return value;
        }

        cout << "Invalid text. Enter meaningful text, not only numbers.\n";
    }
}

string readDate(const string& prompt) {
    while (true) {
        string value = trim(readLine(prompt));

        if (isValidDate(value)) {
            return value;
        }

        cout << "Invalid date. Use YYYY-MM-DD, for example "
             << randomDateExample() << ".\n";
    }
}

string readTime(const string& prompt) {
    while (true) {
        string value = trim(readLine(prompt));

        if (isValidTime(value)) {
            return value;
        }

        cout << "Invalid time. Use HH:MM with two digits, for example 06:00 or 22:30.\n";
    }
}

string readOptionalTime(const string& prompt) {
    while (true) {
        string value = trim(readLine(prompt));

        if (value.empty() || isValidTime(value)) {
            return value;
        }

        cout << "Invalid time. Use HH:MM with two digits, or leave it empty.\n";
    }
}

void pauseScreen() {
    cout << "\nPress ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
