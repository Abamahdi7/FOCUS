#ifndef POMODORO_TIMER_H
#define POMODORO_TIMER_H

class PomodoroTimer {
private:
    int focusMinutes;
    int breakMinutes;
    int session;

public:
    PomodoroTimer();
    PomodoroTimer(int focus, int rest);
    ~PomodoroTimer();

    int getFocusMinutes() const;
    int getBreakMinutes() const;
    int getSession() const;

    void setFocusMinutes(int value);
    void setBreakMinutes(int value);
    void resetSession();
    void runCountdown(int seconds);
    void startQuickDemo();
    void startCustomTimer();
};

#endif
