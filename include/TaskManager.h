
#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <unordered_map>
#include <string>

#include "User.h"
#include "Project.h"
#include "Task.h"

class TaskManager
{
private:

    // Storage for application objects
    std::unordered_map<int, User> users;
    std::unordered_map<int, Project> projects;
    std::unordered_map<int, Task> tasks;

public:

    // Constructor
    TaskManager();

    // Destructor
    ~TaskManager();

    // User management
    void createUser(const User& user);

    // Project management
    void createProject(const Project& project);

    // Task management
    void createTask(
        int id,
        const std::string& title,
        const std::string& description,
        Priority priority,
        int assignedUserId,
        int projectId
    );

    // Assignment
    void assignTask(int taskId, int userId);

    // Adding Task Dependency
    void addTaskDependency(int taskId, int dependencyTaskId);

    // Task operations
    void updateTaskStatus(int taskId, TaskStatus status);
    void deleteTask(int taskId);

    // Retrieval
    void viewTasks() const;
    void searchTask(int taskId) const;

    // Sorting
    void sortTasksById();

    // Priority filtering
    void showHighPriorityTasks() const;

    // User retrieval
    void viewUsers() const;

    // Project retrieval
    void viewProjects() const;

    // View Task Dependencies
    void viewTaskDependencies(int taskId) const;
    
};

#endif