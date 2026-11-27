#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "Priority.h"

using namespace std;

class TaskManager;

enum class TaskStatus
{
    TODO,
    IN_PROGRESS,
    BLOCKED,
    ON_HOLD,
    COMPLETED,
    CANCELLED
};

class Task
{
private:
    int taskId;

    string taskName;
    string description;

    Priority priority;
    TaskStatus status;

    int assignedUserId;
    int projectId;

    string createdDate;
    string dueDate;
    string completedDate;

    vector<int> dependencies;

public:

    // Constructor
    Task(int taskId,
         const string& taskName,
         const string& description,
         Priority priority,
         int assignedUserId,
         int projectId,
         const string& createdDate,
         const string& dueDate);

    // Destructor
    ~Task();

    // Getters
    int getId() const;
    string getTaskName() const;
    string getDescription() const;

    Priority getPriority() const;
    TaskStatus getStatus() const;

    int getAssignedUserId() const;
    int getProjectId() const;

    string getCreatedDate() const;
    string getDueDate() const;
    string getCompletedDate() const;

    const vector<int>& getDependencies() const;

    // Setters
    void setTaskName();
    void setDescription();
    void setPriority();
    void setStatus();
    void setAssignedUserId();
    void setDueDate();

    // Dependency Management
    void addDependency(int taskId);
    // Display
    void display() const;
};

#endif