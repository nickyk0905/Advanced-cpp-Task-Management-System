#include "operations/ProjectOperations.h"
#include "Project.h"

#include <iostream>

using namespace std;


// Constructor
Project::Project(int projectId,
                 const string& projectName,
                 const string& description,
                 ProjectStatus projectStatus,
                 Priority priority,
                 const string& startDate,
                 const string& endDate,
                 int createdBy)
    : projectId(projectId),
      projectName(projectName),
      description(description),
      projectStatus(projectStatus),
      priority(priority),
      startDate(startDate),
      endDate(endDate),
      createdBy(createdBy)
      
{
    cout<<"\nProject created successfully!\n";
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

ProjectStatus Project::getProjectStatus() const
{
    return projectStatus;
}

Priority Project::getPriority() const
{
    return priority;
}

const string& Project::getStartDate() const
{
    return startDate;
}

const string& Project::getEndDate() const
{
    return endDate;
}

int Project::getCreatedBy() const
{
    return createdBy;
}


// Setters
void Project::setProjectName()
{
    projectName = readText("\nEnter Project Name: ");
}

void Project::setDescription()
{
    description = readDescription("\nEnter Project Description: ");
}

void Project::setProjectStatus()
{
    projectStatus = readProjectStatus_update("\nEnter Project Status (Not Started, In Progress, On Hold, Completed, Cancelled): ");
}

void Project::setPriority()
{
    priority = readPriority("\nEnter Project Priority (Low, Medium, High, Critical): ");
}

void Project::setStartDate(const string& date)
{
    startDate = date;
}

void Project::setEndDate(const string& date)
{
    endDate = date;
}


// Display project details
void Project::display() const
{
    cout<<"\n---------------------------------------------- PROJECT DETAILS --------------------------------------\n";

    cout<<"\t\t\tProject ID: " << projectId << '\n';
    cout<<"\t\t\tProject Name: " << projectName << '\n';
    cout<<"\t\t\tDescription: " << description << '\n';

    cout<<"\t\t\tProject Status: ";

    switch (projectStatus)
    {
        case ProjectStatus::NotStarted:
            cout<<"Not Started";
            break;

        case ProjectStatus::InProgress:
            cout<<"In Progress";
            break;

        case ProjectStatus::OnHold:
            cout<<"On Hold";
            break;

        case ProjectStatus::Completed:
            cout<<"Completed";
            break;

        case ProjectStatus::Cancelled:
            cout<<"Cancelled";
            break;
        case ProjectStatus::InActive:
            cout << "InActive";
            break;
    }

    cout<<'\n';

    cout<<"\t\t\tPriority: ";

    switch (priority)
    {
        case Priority::Critical:
            cout<<"Critical";
            break;

        case Priority::High:
            cout<<"High";
            break;

        case Priority::Medium:
            cout<<"Medium";
            break;
    
        case Priority::Low:
            cout<<"Low";
            break;    
    }

    cout<<'\n';

    cout<<"\t\t\tStart Date: " << startDate << '\n';
    cout<<"\t\t\tEnd Date: " << endDate << '\n';
    cout<<"\t\t\tCreated By User ID: " << createdBy << '\n';

    cout << "-----------------------------------------------------------------------------------------------------\n";
}