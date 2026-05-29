#ifndef PLANNER_H
#define PLANNER_H

#include "Task.h"

#include <vector>

using namespace std;

class Planner {
private:
    vector<Task> tasks;
    int nextId;

public:
    Planner();
    ~Planner();

    vector<Task> getTasks() const;
    int getNextId() const;
    void setNextId(int value);
    void setTasks(const vector<Task>& value);

    void addTask(const string& title, const string& date, const string& time);
    bool completeTask(int id);
    bool deleteTask(int id);
    vector<Task> tasksForDate(const string& date) const;
    vector<Task> priorityTasks() const;
};

#endif
