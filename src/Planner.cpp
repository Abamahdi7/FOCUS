#include "Planner.h"

#include <algorithm>

using namespace std;

Planner::Planner() : nextId(1) {
}

Planner::~Planner() {
}

vector<Task> Planner::getTasks() const {
    return tasks;
}

int Planner::getNextId() const {
    return nextId;
}

void Planner::setNextId(int value) {
    nextId = max(1, value);
}

void Planner::setTasks(const vector<Task>& value) {
    tasks = value;
}

void Planner::addTask(const string& title, const string& date, const string& time) {
    Task task(nextId++, title.empty() ? "Untitled task" : title, date.empty() ? "Today" : date, time);
    tasks.push_back(task);
}

bool Planner::completeTask(int id) {
    for (Task& task : tasks) {
        if (task.getId() == id) {
            task.setCompleted(true);
            return true;
        }
    }

    return false;
}

bool Planner::deleteTask(int id) {
    size_t oldSize = tasks.size();
    tasks.erase(remove_if(tasks.begin(), tasks.end(), [id](const Task& task) {
        return task.getId() == id;
    }), tasks.end());

    return tasks.size() != oldSize;
}

vector<Task> Planner::tasksForDate(const string& date) const {
    vector<Task> result;

    for (const Task& task : tasks) {
        if (task.getDate() == date) {
            result.push_back(task);
        }
    }

    return result;
}

vector<Task> Planner::priorityTasks() const {
    vector<Task> result;

    for (const Task& task : tasks) {
        if (!task.isCompleted()) {
            result.push_back(task);
        }
    }

    return result;
}
