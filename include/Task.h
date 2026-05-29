#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>

using namespace std;

class Task {
private:
    int id;
    string title;
    string date;
    string time;
    bool completed;

public:
    Task();
    Task(int taskId, string taskTitle, string taskDate, string taskTime);
    ~Task();

    int getId() const;
    string getTitle() const;
    string getDate() const;
    string getTime() const;
    bool isCompleted() const;

    void setTitle(const string& value);
    void setDate(const string& value);
    void setTime(const string& value);
    void setCompleted(bool value);

    friend ostream& operator<<(ostream& out, const Task& task);
};

#endif
