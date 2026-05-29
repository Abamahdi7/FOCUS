#include "FocusApp.h"

#include "InputUtils.h"
#include "MathChallenge.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>

using namespace std;

static const char* DATA_FILE = "focus_data.txt";

FocusApp::FocusApp()
    : profile(), planner(), timer(), alarms(), community(), running(true) {
    load();
}

FocusApp::~FocusApp() {
    save();
}

void FocusApp::run() {
    splash();

    if (profile.getName() == "Focus User" && profile.getCountry() == "Not set") {
        onboarding();
    }

    while (running) {
        cout << "\n========== FOCUS ==========\n";
        cout << "1. Home\n";
        cout << "2. Planner\n";
        cout << "3. Focus tools\n";
        cout << "4. Community\n";
        cout << "5. Profile\n";
        cout << "0. Exit\n";
        cout << "===========================\n";

        int choice = readInt("Choose: ", 0, 5);

        switch (choice) {
            case 1:
                home();
                break;
            case 2:
                plannerMenu();
                break;
            case 3:
                focusMenu();
                break;
            case 4:
                community.showDiscord();
                pauseScreen();
                break;
            case 5:
                profileMenu();
                break;
            case 0:
                save();
                running = false;
                break;
        }
    }
}

void FocusApp::splash() const {
    cout << "=============================\n";
    cout << "            FOCUS            \n";
    cout << "=============================\n";
}

void FocusApp::onboarding() {
    cout << "\nWelcome. Let us create your local profile.\n";
    profile.setName(readRequiredName("Name: "));

    cout << "Gender options:\n";
    cout << "1. Female\n";
    cout << "2. Male\n";

    int genderChoice = readInt("Choose gender: ", 1, 2);

    if (genderChoice == 1) {
        profile.setGender("Female");
    } else {
        profile.setGender("Male");
    }

    profile.setDateOfBirth(readDate("Date of birth (YYYY-MM-DD): "));
    profile.setCountry(readRequiredName("Country: "));
    profile.setWakeTime(readTime("Wake-up time (HH:MM): "));
    profile.setSleepTime(readTime("Sleep time (HH:MM): "));

    cout << "Profile created.\n";
    save();
}

void FocusApp::home() {
    cout << "\n========== HOME ==========\n";
    cout << "Good morning, " << profile.getName() << ".\n";
    cout << "Wake: " << profile.getWakeTime()
              << " | Sleep: " << profile.getSleepTime() << "\n";

    cout << "\nPriority tasks:\n";
    vector<Task> tasks = planner.priorityTasks();

    if (tasks.empty()) {
        cout << "No tasks yet. Create your first task in Planner.\n";
    } else {
        for (const Task& task : tasks) {
            cout << task << "\n";
        }
    }

    pauseScreen();
}

void FocusApp::plannerMenu() {
    bool back = false;

    while (!back) {
        cout << "\n========== PLANNER ==========\n";
        cout << "1. Add task\n";
        cout << "2. List all tasks\n";
        cout << "3. List tasks by date\n";
        cout << "4. Complete task\n";
        cout << "5. Delete task\n";
        cout << "6. Weekly overview\n";
        cout << "7. Day schedule\n";
        cout << "0. Back\n";

        int choice = readInt("Choose: ", 0, 7);

        if (choice == 1) {
            string title = readRequiredText("Task title: ");
            string date = readDate("Date (YYYY-MM-DD): ");
            string time = readOptionalTime("Time, optional (HH:MM): ");
            planner.addTask(title, date, time);
            save();
            cout << "Task added.\n";
        } else if (choice == 2) {
            listTasks(planner.getTasks());
        } else if (choice == 3) {
            string date = readDate("Enter date (YYYY-MM-DD): ");
            listTasks(planner.tasksForDate(date));
        } else if (choice == 4) {
            int id = readInt("Task id: ", 1, 1000000);
            cout << (planner.completeTask(id) ? "Task completed.\n" : "Task not found.\n");
            save();
        } else if (choice == 5) {
            int id = readInt("Task id: ", 1, 1000000);
            cout << (planner.deleteTask(id) ? "Task deleted.\n" : "Task not found.\n");
            save();
        } else if (choice == 6) {
            weeklyOverview();
        } else if (choice == 7) {
            daySchedule();
        } else {
            back = true;
        }
    }
}

void FocusApp::listTasks(const vector<Task>& tasks) const {
    if (tasks.empty()) {
        cout << "No tasks found.\n";
        return;
    }

    for (const Task& task : tasks) {
        cout << task << "\n";
    }
}

void FocusApp::weeklyOverview() const {
    cout << "\n========== WEEKLY OVERVIEW ==========\n";
    vector<Task> tasks = planner.getTasks();

    if (tasks.empty()) {
        cout << "Your weekly planner is empty.\n";
        return;
    }

    for (const Task& task : tasks) {
        cout << task.getDate() << " -> "
                  << (task.isCompleted() ? "Done: " : "Open: ")
                  << task.getTitle() << "\n";
    }
}

void FocusApp::daySchedule() const {
    string date = readDate("Choose date (YYYY-MM-DD): ");
    vector<Task> tasks = planner.tasksForDate(date);

    cout << "\n========== DAY SCHEDULE ==========\n";

    if (tasks.empty()) {
        cout << "No tasks scheduled for " << date << ".\n";
        return;
    }

    for (const Task& task : tasks) {
        cout << (task.getTime().empty() ? "--:--" : task.getTime())
                  << " | " << task.getTitle()
                  << (task.isCompleted() ? " (done)" : "") << "\n";
    }
}

void FocusApp::focusMenu() {
    bool back = false;

    while (!back) {
        cout << "\n========== FOCUS TOOLS ==========\n";
        cout << "1. Pomodoro quick demo\n";
        cout << "2. Custom timer\n";
        cout << "3. Deep work demo\n";
        cout << "4. Add alarm\n";
        cout << "5. List alarms\n";
        cout << "6. Test alarm math challenge\n";
        cout << "0. Back\n";

        int choice = readInt("Choose: ", 0, 6);

        if (choice == 1) {
            timer.startQuickDemo();
        } else if (choice == 2) {
            timer.startCustomTimer();
        } else if (choice == 3) {
            cout << "\nDeep Work mode: 4 focused sessions in the mobile app.\n";
            cout << "Terminal demo: one 15-second session.\n";
            timer.runCountdown(15);
            cout << "Deep work demo finished.\n";
        } else if (choice == 4) {
            string time = readTime("Alarm time (HH:MM): ");
            alarms.push_back(Alarm(time, true));
            save();
            cout << "Alarm added.\n";
        } else if (choice == 5) {
            if (alarms.empty()) {
                cout << "No alarms yet.\n";
            } else {
                for (size_t index = 0; index < alarms.size(); ++index) {
                    cout << index + 1 << ". " << alarms[index].getTime()
                              << " | " << (alarms[index].isEnabled() ? "On" : "Off") << "\n";
                }
            }
        } else if (choice == 6) {
            testAlarmChallenge();
        } else {
            back = true;
        }
    }
}

void FocusApp::testAlarmChallenge() {
    random_device random;
    MathChallenge challenge(static_cast<int>(random()));

    cout << "\nSolve to dismiss alarm:\n";
    cout << challenge.getQuestion();

    int answer = readInt("", 0, 100);

    if (challenge.checkAnswer(answer)) {
        cout << "Correct. Alarm dismissed.\n";
    } else {
        cout << "Incorrect. Correct answer was " << challenge.getAnswer() << ".\n";
    }
}

void FocusApp::profileMenu() {
    bool back = false;

    while (!back) {
        printProfileCard(profile);
        cout << "1. Edit name\n";
        cout << "2. Edit country\n";
        cout << "3. Edit date of birth\n";
        cout << "4. Edit wake/sleep time\n";
        cout << "5. Toggle dark mode\n";
        cout << "6. Toggle notifications\n";
        cout << "7. Reset app data\n";
        cout << "0. Back\n";

        int choice = readInt("Choose: ", 0, 7);

        if (choice == 1) {
            profile.setName(readRequiredName("New name: "));
        } else if (choice == 2) {
            profile.setCountry(readRequiredName("New country: "));
        } else if (choice == 3) {
            profile.setDateOfBirth(readDate("New date of birth (YYYY-MM-DD): "));
        } else if (choice == 4) {
            profile.setWakeTime(readTime("Wake-up time (HH:MM): "));
            profile.setSleepTime(readTime("Sleep time (HH:MM): "));
        } else if (choice == 5) {
            profile.setDarkMode(!profile.getDarkMode());
        } else if (choice == 6) {
            profile.setNotifications(!profile.getNotifications());
        } else if (choice == 7) {
            profile = UserProfile();
            planner = Planner();
            alarms.clear();
            cout << "App data reset.\n";
        } else {
            back = true;
        }

        save();
    }
}

void FocusApp::save() const {
    ofstream file(DATA_FILE);

    if (!file) {
        return;
    }

    file << "PROFILE\n";
    file << profile.getName() << "\n";
    file << profile.getGender() << "\n";
    file << profile.getDateOfBirth() << "\n";
    file << profile.getCountry() << "\n";
    file << profile.getWakeTime() << "\n";
    file << profile.getSleepTime() << "\n";
    file << profile.getDarkMode() << "\n";
    file << profile.getNotifications() << "\n";

    vector<Task> tasks = planner.getTasks();
    file << "TASKS " << planner.getNextId() << " " << tasks.size() << "\n";

    for (const Task& task : tasks) {
        file << task.getId() << "|"
             << task.getTitle() << "|"
             << task.getDate() << "|"
             << task.getTime() << "|"
             << task.isCompleted() << "\n";
    }

    file << "ALARMS " << alarms.size() << "\n";

    for (const Alarm& alarm : alarms) {
        file << alarm.getTime() << "|" << alarm.isEnabled() << "\n";
    }
}

void FocusApp::load() {
    ifstream file(DATA_FILE);

    if (!file) {
        return;
    }

    string marker;
    getline(file, marker);

    if (marker == "PROFILE") {
        string value;
        getline(file, value);
        profile.setName(value);
        getline(file, value);
        profile.setGender(value);
        getline(file, value);
        profile.setDateOfBirth(value);
        getline(file, value);
        profile.setCountry(value);
        getline(file, value);
        profile.setWakeTime(value);
        getline(file, value);
        profile.setSleepTime(value);
        getline(file, value);
        profile.setDarkMode(value == "1");
        getline(file, value);
        profile.setNotifications(value == "1");
    }

    string tasksMarker;
    int nextId = 1;
    size_t taskCount = 0;

    file >> tasksMarker >> nextId >> taskCount;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    if (tasksMarker == "TASKS") {
        vector<Task> loadedTasks;

        for (size_t index = 0; index < taskCount; ++index) {
            string line;
            getline(file, line);
            stringstream stream(line);

            string id;
            string title;
            string date;
            string time;
            string completed;

            getline(stream, id, '|');
            getline(stream, title, '|');
            getline(stream, date, '|');
            getline(stream, time, '|');
            getline(stream, completed, '|');

            Task task(stoi(id), title, date, time);
            task.setCompleted(completed == "1");
            loadedTasks.push_back(task);
        }

        planner.setTasks(loadedTasks);
        planner.setNextId(nextId);
    }

    string alarmMarker;
    size_t alarmCount = 0;

    if (file >> alarmMarker >> alarmCount) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        if (alarmMarker == "ALARMS") {
            alarms.clear();

            for (size_t index = 0; index < alarmCount; ++index) {
                string line;
                getline(file, line);
                stringstream stream(line);

                string time;
                string enabled;

                getline(stream, time, '|');
                getline(stream, enabled, '|');

                alarms.push_back(Alarm(time, enabled == "1"));
            }
        }
    }
}
