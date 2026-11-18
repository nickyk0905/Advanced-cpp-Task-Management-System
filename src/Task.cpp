#include "Task.h"

#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Constructor
Task::Task(int id, const string& title,
           const string& description,
           Priority priority,
           int assignedUserId,
           int projectId)
    : id(id),
      title(title),
      description(description),
      priority(priority),
      status(TaskStatus::TODO),
      assignedUserId(assignedUserId),
      projectId(projectId)
{
    if (id <= 0 || assignedUserId <= 0 || projectId <= 0)
    {
        throw invalid_argument("IDs must be positive.\nTask not Created.");
    }

    if (title.empty())
    {
        throw invalid_argument("Task title cannot be empty.\nTask not Created.");
    }

    cout << "\nTask created successfully!\n";
}

// Destructor
Task::~Task()
{
    // Destructor logic (if needed)
}

// Getters
int Task::getId() const
{
    return id;
}

const string& Task::getTitle() const
{
    return title;
}

const string& Task::getDescription() const
{
    return description;
}

Priority Task::getPriority() const
{
    return priority;
}

TaskStatus Task::getStatus() const
{
    return status;
}

int Task::getAssignedUserId() const
{
    return assignedUserId;
}

int Task::getProjectId() const
{
    return projectId;
}

const vector<int>& Task::getDependencies() const
{
    return dependencies;
}

// Setters
void Task::setStatus(TaskStatus newStatus)
{
    status = newStatus;
}

void Task::setPriority(Priority newPriority)
{
    priority = newPriority;
}

void Task::setAssignedUserId(int userId)
{
    if (userId <= 0)
    {
        throw invalid_argument("Invalid user ID.\nUser not assigned.");
    }

    assignedUserId = userId;
}

// Add dependency
void Task::addDependency(int taskId)
{
    if (taskId <= 0)
    {
        throw invalid_argument("Invalid dependency ID.\nDependency not added.");
    }

    if (taskId == id)
    {
        throw invalid_argument("A task cannot depend on itself.\nDependency not added.");
    }

    if (find(dependencies.begin(),
             dependencies.end(),
             taskId) != dependencies.end())
    {
        throw invalid_argument("Dependency already exists.\nDependency not added.");
    }

    dependencies.push_back(taskId);
}

// Display task details

void Task::display() const
{
    cout << "\n----- TASK DETAILS -----\n";

    cout << "\tTask ID: " << id << '\n';
    cout << "\tTitle: " << title << '\n';
    cout << "\tDescription: " << description << '\n';
    cout << "\tAssigned User ID: " << assignedUserId << '\n';
    cout << "\tProject ID: " << projectId << '\n';

    // Display Priority
    cout << "\tPriority: ";

    switch (priority)
    {
        case Priority::LOW:
            cout << "LOW";
            break;

        case Priority::MEDIUM:
            cout << "MEDIUM";
            break;

        case Priority::HIGH:
            cout << "HIGH";
            break;

        case Priority::CRITICAL:
            cout << "CRITICAL";
            break;
    }

    cout << '\n';

    // Display Status
    cout << "\tStatus: ";

    switch (status)
    {
        case TaskStatus::TODO:
            cout << "TODO";
            break;

        case TaskStatus::IN_PROGRESS:
            cout << "IN_PROGRESS";
            break;

        case TaskStatus::COMPLETED:
            cout << "COMPLETED";
            break;

        case TaskStatus::BLOCKED:
            cout << "BLOCKED";
            break;
    }

    cout << "\n\tDependencies: ";
    if (dependencies.empty())
    {
        cout << "None";
    }
    else
    {
        for (int dependencyId : dependencies)
        {
            cout << dependencyId << " ";
        }
    }

    cout << '\n';
}