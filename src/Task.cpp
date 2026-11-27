#include "Task.h"
#include "TaskManager.h"
#include "operations/TaskOperations.h"
#include "operations/ProjectOperations.h"
#include "operations/UserOperations.h"

#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

TaskManager manager;

// Constructor
Task::Task(int taskId, const string& taskName,
           const string& description,
           Priority priority,
           int assignedUserId,
           int projectId,
           const string& createdDate,
           const string& dueDate)
    : taskId(taskId),
      taskName(taskName),
      description(description),
      priority(priority),
      status(TaskStatus::TODO),
      assignedUserId(assignedUserId),
      projectId(projectId),
      createdDate(createdDate),
      dueDate(dueDate),
      completedDate("")
{
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
    return taskId;
}

string Task::getTaskName() const
{
    return taskName;
}

string Task::getDescription() const
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

string Task::getCreatedDate() const
{
    return createdDate;
}

string Task::getDueDate() const
{
    return dueDate;
}

string Task::getCompletedDate() const
{
    return completedDate;
}

const vector<int>& Task::getDependencies() const
{
    return dependencies;
}


// Setters

// Set Task Name
void Task::setTaskName()
{
    taskName = readText("\nEnter new task name: ");
}

// Set Description
void Task::setDescription()
{
    description = readDescription("\nEnter new task description: ");
}

// Set Priority
void Task::setPriority()
{
    priority = readPriority("\nEnter new task priority (Low, Medium, High, Critical): ");
}

// Set Status
void Task::setStatus()
{
    status = readTaskStatus("\nEnter new task status: ");
}

// Set Assigned User ID
void Task::setAssignedUserId()
{
    assignedUserId = readUserId("\nEnter new assigned user ID: ", manager);
}

// Set Due Date
void Task::setDueDate()
{
    dueDate = readDate("\nEnter new due date: ");
}


// Add Dependency
void Task::addDependency(int taskId)
{
    if (taskId <= 0)
    {
        throw invalid_argument("Invalid dependency task ID.");
    }

    if (taskId == this->taskId)
    {
        throw invalid_argument("A task cannot depend on itself.");
    }

    for (int dependencyId : dependencies)
    {
        if (dependencyId == taskId)
        {
            throw invalid_argument("Dependency already exists.");
        }
    }

    dependencies.push_back(taskId);
}


// Display task details

void Task::display() const
{
    cout << "\n----- TASK DETAILS -----\n";

    cout << "\tTask ID: " <<taskId << '\n';
    cout << "\tTitle: " << taskName << '\n';
    cout << "\tDescription: " << description << '\n';
    cout << "\tAssigned User ID: " << assignedUserId << '\n';
    cout << "\tProject ID: " << projectId << '\n';

    // Display Priority
    cout << "\tPriority: ";

    switch (priority)
    {
        case Priority::Low:
            cout << "Low";
            break;

        case Priority::Medium:
            cout << "Medium";
            break;

        case Priority::High:
            cout << "High";
            break;

        case Priority::Critical:
            cout << "Critical";
            break;
    }

    cout << '\n';

    cout<<"\tTask Start Date: "<<createdDate;
    cout<<"\n\tTask Due Date: "<<dueDate;

    // Display Status
    cout << "\n\tProject Status: ";

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

        case TaskStatus::ON_HOLD:
            cout << "ON_HOLD";
            break;

        case TaskStatus::CANCELLED:
            cout << "CANCELLED";
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