#include "Project.h"

#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Constructor
Project::Project(int projectId,
                 const string& projectName,
                 const string& description)
    : projectId(projectId),
      projectName(projectName),
      description(description)
{
    if (projectId <= 0)
    {
        throw invalid_argument("Project ID must be positive.\nProject not Created.");
    }

    if (projectName.empty())
    {
        throw invalid_argument("Project name cannot be empty.\nProject not Created.");
    }

    if (description.empty())
    {
        throw invalid_argument("Project description cannot be empty.\nProject not Created.");
    }

    cout << "\nProject created successfully!\n";
}

// Destructor
Project::~Project()
{
    // Destructor logic (if needed)
}

// Getters
int Project::getProjectId() const
{
    return projectId;
}

const string& Project::getProjectName() const
{
    return projectName;
}

const string& Project::getDescription() const
{
    return description;
}

const vector<int>& Project::getTaskIds() const
{
    return taskIds;
}

// Add task
void Project::addTask(int taskId)
{
    if (taskId <= 0)
    {
        throw invalid_argument("Invalid task ID.\nTask not added.");
    }

    if (find(taskIds.begin(), taskIds.end(), taskId)
        != taskIds.end())
    {
        throw invalid_argument("Task already exists in project.\nTask not added.");
    }

    taskIds.push_back(taskId);
}

// Display
void Project::display() const
{
    cout << "\n----- PROJECT DETAILS -----\n";

    cout << "\tProject ID: " << projectId << '\n';
    cout << "\tProject Name: " << projectName << '\n';
    cout << "\tDescription: " << description << '\n';

    cout << "\tAssociated Task IDs: ";

    if (taskIds.empty())
    {
        cout << "No tasks assigned";
    }
    else
    {
        for (int taskId : taskIds)
        {
            cout << taskId << " ";
        }
    }

    cout << '\n';
}

// Remove task
void Project::removeTask(int taskId)
{
    auto task = find(taskIds.begin(), taskIds.end(), taskId);

    if (task == taskIds.end())
    {
        throw invalid_argument("\nTask not found in project.");
    }

    taskIds.erase(task);
}