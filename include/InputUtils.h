#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <string>

using namespace std;

string readLine(const string& prompt);
int readInt(const string& prompt, int minValue, int maxValue);
string readRequiredName(const string& prompt);
string readRequiredText(const string& prompt);
string readDate(const string& prompt);
string readTime(const string& prompt);
string readOptionalTime(const string& prompt);
void pauseScreen();

#endif
