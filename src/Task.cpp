#include "Task.h"

using namespace std;

Task::Task()
    : id(0), title("Untitled task"), date("Today"), time(""), completed(false) {
}

Task::Task(int taskId, string taskTitle, string taskDate, string taskTime)
    : id(taskId), title(taskTitle), date(taskDate), time(taskTime), completed(false) {
}

Task::~Task() {
}

int Task::getId() const {
    return id;
}

string Task::getTitle() const {
    return title;
}

string Task::getDate() const {
    return date;
}

string Task::getTime() const {
    return time;
}

bool Task::isCompleted() const {
    return completed;
}

void Task::setTitle(const string& value) {
    title = value.empty() ? "Untitled task" : value;
}

void Task::setDate(const string& value) {
    date = value.empty() ? "Today" : value;
}

void Task::setTime(const string& value) {
    time = value;
}

void Task::setCompleted(bool value) {
    completed = value;
}

ostream& operator<<(ostream& out, const Task& task) {
    out << "[" << task.id << "] "
        << (task.completed ? "(done) " : "(open) ")
        << task.title << " | " << task.date;

    if (!task.time.empty()) {
        out << " at " << task.time;
    }

    return out;
}
