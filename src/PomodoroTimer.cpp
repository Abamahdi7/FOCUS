#include "PomodoroTimer.h"

#include "InputUtils.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>

using namespace std;

PomodoroTimer::PomodoroTimer() : focusMinutes(25), breakMinutes(5), session(1) {
}

PomodoroTimer::PomodoroTimer(int focus, int rest)
    : focusMinutes(max(1, focus)), breakMinutes(max(1, rest)), session(1) {
}

PomodoroTimer::~PomodoroTimer() {
}

int PomodoroTimer::getFocusMinutes() const {
    return focusMinutes;
}

int PomodoroTimer::getBreakMinutes() const {
    return breakMinutes;
}

int PomodoroTimer::getSession() const {
    return session;
}

void PomodoroTimer::setFocusMinutes(int value) {
    focusMinutes = max(1, value);
}

void PomodoroTimer::setBreakMinutes(int value) {
    breakMinutes = max(1, value);
}

void PomodoroTimer::resetSession() {
    session = 1;
}

void PomodoroTimer::runCountdown(int seconds) {
    for (int remaining = seconds; remaining >= 0; --remaining) {
        int minutes = remaining / 60;
        int secs = remaining % 60;

        cout << "\rRemaining: "
                  << setw(2) << setfill('0') << minutes
                  << ":"
                  << setw(2) << setfill('0') << secs
                  << flush;

        this_thread::sleep_for(chrono::seconds(1));
    }

    cout << setfill(' ') << "\n";
}

void PomodoroTimer::startQuickDemo() {
    cout << "\nPomodoro 25/5 mode.\n";
    cout << "For terminal testing, this demo runs for 10 seconds only.\n";
    runCountdown(10);
    cout << "Session " << session << " finished.\n";
    session++;
}

void PomodoroTimer::startCustomTimer() {
    int seconds = readInt("Enter timer duration in seconds (1-3600): ", 1, 3600);
    runCountdown(seconds);
    cout << "Custom timer finished.\n";
}
