
#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <vector>

class Project
{
private:
    int projectId;
    std::string projectName;
    std::string description;

    std::vector<int> taskIds;

public:

    // Constructor
    Project(int projectId,
            const std::string& projectName,
            const std::string& description);

    // Destructor
    ~Project();

    // Getters
    int getProjectId() const;
    const std::string& getProjectName() const;
    const std::string& getDescription() const;
    const std::vector<int>& getTaskIds() const;

    // Task management
    void addTask(int taskId);

    // Remove a task
    void removeTask(int taskId);

    // Display
    void display() const;
};

#endif