#ifndef PROJECT_H
#define PROJECT_H

#include "Priority.h"

#include <string>

using namespace std;

enum class ProjectStatus
{
    NotStarted,
    InProgress,
    OnHold,
    Completed,
    Cancelled
};

class Project
{
private:
    int projectId;
    string projectName;
    string description;

    ProjectStatus projectStatus;
    Priority priority;

    string startDate;
    string endDate;

    // User ID of the user who created the project
    int createdBy;

public:
    Project(int projectId,
            const string& projectName,
            const string& description,
            ProjectStatus projectStatus,
            Priority priority,
            const string& startDate,
            const string& endDate,
            int createdBy);

    ~Project();

    // Getters
    int getProjectId() const;
    const string& getProjectName() const;
    const string& getDescription() const;
    ProjectStatus getProjectStatus() const;
    Priority getPriority() const;
    const string& getStartDate() const;
    const string& getEndDate() const;
    int getCreatedBy() const;

    // Setters
    void setProjectName();
    void setDescription();
    void setProjectStatus();
    void setPriority();
    void setStartDate();
    void setEndDate();

    // Display project details
    void display() const;
};

#endif