
#ifndef TASK_H
#define TASK_H

#include "Priority.h"

#include <string>
#include <vector>

enum class TaskStatus
{
    TODO,
    IN_PROGRESS,
    COMPLETED,
    BLOCKED
};

class Task
{
private:
    int id;
    std::string title;
    std::string description;

    Priority priority;
    TaskStatus status;

    int assignedUserId;
    int projectId;

    std::vector<int> dependencies;

public:

    // Constructor
    Task(int id, const std::string& title,
         const std::string& description,
         Priority priority,
         int assignedUserId,
         int projectId);

    // Destructor
    ~Task();

    // Getters
    int getId() const;
    const std::string& getTitle() const;
    const std::string& getDescription() const;

    Priority getPriority() const;
    TaskStatus getStatus() const;

    int getAssignedUserId() const;
    int getProjectId() const;

    const std::vector<int>& getDependencies() const;

    // Setters
    void setStatus(TaskStatus newStatus);
    void setPriority(Priority newPriority);
    void setAssignedUserId(int userId);

    // Dependency management
    void addDependency(int taskId);

    // Display
    void display() const;
};

#endif