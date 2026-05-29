#ifndef FOCUS_APP_H
#define FOCUS_APP_H

#include "Alarm.h"
#include "Community.h"
#include "Planner.h"
#include "PomodoroTimer.h"
#include "UserProfile.h"

#include <vector>

using namespace std;

class FocusApp {
private:
    UserProfile profile;
    Planner planner;
    PomodoroTimer timer;
    vector<Alarm> alarms;
    Community community;
    bool running;

    void splash() const;
    void onboarding();
    void home();
    void plannerMenu();
    void focusMenu();
    void profileMenu();
    void listTasks(const vector<Task>& tasks) const;
    void weeklyOverview() const;
    void daySchedule() const;
    void testAlarmChallenge();
    void save() const;
    void load();

public:
    FocusApp();
    ~FocusApp();

    void run();
};

#endif
