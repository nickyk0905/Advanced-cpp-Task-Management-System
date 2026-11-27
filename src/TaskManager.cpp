#include "TaskManager.h"
#include "operations/UserOperations.h"
#include "operations/ProjectOperations.h"
#include "operations/TaskOperations.h"
#include "User.h"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

// Constructor
TaskManager::TaskManager()
{
    cout << "Task Manager initialized successfully!\n";
}   

// Destructor
TaskManager::~TaskManager()
{
    // Destructor logic (if needed)
}

// Create User
void TaskManager::createUser()
{
    cout << "------------------------- CREATING A USER ------------------------------\n";

    int userId = readUserId("\nEnter User ID: ", *this);
    string name = readName("\nEnter User Name: ");
    string email = readEmail("\nEnter User Email: ");
    Role role = readRole("\nEnter User Role (Admin, Manager, Developer, Tester): ");
    bool isActive = readActiveStatus("\nIs the User Active? (Yes/No): ");

    User newUser(
        userId,
        name,
        email,
        role,
        isActive
    );

    users.emplace(userId, newUser);
    cout<<"\n--------------------------------------------------------------------------\n";
    cout << "\n\t\tUser added to Task Manager successfully!\n";
    cout<<"\n--------------------------------------------------------------------------\n";
}

// Create Project
void TaskManager::createProject()
{
    cout << "------------------------- CREATING A PROJECT ------------------------------\n";

    int projectId = readProjectId("\nEnter Project ID: ", *this);

    string projectName =
        readName("\nEnter Project Name: ");

    string description =
        readDescription("\nEnter Project Description: ");

    ProjectStatus projectStatus =
        readProjectStatus("\nEnter Project Status (Not Started, In Progress): ");

    Priority priority =
        readPriority("\nEnter Project Priority (Low, Medium, High, Critical): ");

    string startDate = readDate("\nEnter Project Start Date (DD-MM-YYYY): ");

    string endDate;

    while (true)
    {
        endDate = readDate("\nEnter Project End Date (DD-MM-YYYY): ");

        if (convertDateToNumber(endDate) >
            convertDateToNumber(startDate))
        {
            break;
        }

        cout << "\nError: End date must be later than start date.\n";
    }

    int createdBy =
        readCreatedBy("\nEnter Created By User ID: ", *this);

    Project project(
        projectId,
        projectName,
        description,
        projectStatus,
        priority,
        startDate,
        endDate,
        createdBy
    );

    if (projects.find(projectId) != projects.end())
    {
        throw invalid_argument("\nProject ID already exists.");
    }

    projects.emplace(projectId, project);

    cout<<"\n--------------------------------------------------------------------------\n";
    cout << "\n\t\tProject added to Task Manager successfully!\n";
    cout<<"\n--------------------------------------------------------------------------\n";
}


// Create Task
void TaskManager::createTask()
{
    cout << "------------------------- CREATING A TASK ------------------------------\n";

    int taskId = readTaskId("\nEnter Task ID: ", *this);

    string taskName = readText("\nEnter Task Title: ");
    string description = readDescription("\nEnter Task Description: ");

    Priority priority = readPriority(
        "\nEnter Task Priority (Low, Medium, High, Critical): "
    );

    int assignedUserId = -1;

    int projectId = readProjectId_T(
        "\nEnter Project ID: ", *this
    );

    Project* project = getProject(projectId);
    string projectStartDate = project->getStartDate();
    string projectEndDate = project->getEndDate();

    cout << "\nProject Timeline";
    cout << "\nProject Start Date: " << projectStartDate;
    cout << "\nProject End Date: " << projectEndDate << "\n";

    string createdDate = readStartDate("\nEnter Created Date (DD-MM-YYYY): ", projectStartDate, projectEndDate);
    string dueDate = readEndDate("\nEnter Due Date (DD-MM-YYYY): ", createdDate, projectEndDate);

    // Create Task object
    Task task(
        taskId,
        taskName,
        description,
        priority,
        assignedUserId,
        projectId,
        createdDate,
        dueDate
    );

    // Add Task to Task Manager
    tasks.emplace(taskId, task);

    cout << "\n--------------------------------------------------------------------------\n";
    cout << "\n\t\tTask added to Task Manager successfully!\n";
    cout << "\n--------------------------------------------------------------------------\n";
}




// Assign Task
void TaskManager::assignTask(int taskId)
{
    auto task = tasks.find(taskId);

    if (task == tasks.end())
    {
        throw invalid_argument("Task not found.");
    }

    task->second.setAssignedUserId();

    cout << "\nTask assigned successfully!\n";
}

// Update Task Status
void TaskManager::updateTaskStatus(int taskId)
{
    auto task = tasks.find(taskId);

    if (task == tasks.end())
    {
        throw invalid_argument("Task not found.");
    }

    cout << "\nTask status updated successfully!\n";
}

// Delete Task
void TaskManager::deleteTask(int taskId)
{
    auto task = tasks.find(taskId);

    if (task == tasks.end())
    {
        throw invalid_argument("Task not found.");
    }

    // Find the project associated with this task
    auto project = projects.find(task->second.getProjectId());

    if (project == projects.end())
    {
        throw logic_error("Associated project does not exist.");
    }

    tasks.erase(task);

    cout << "Task deleted successfully!\n";
}

// View All Users
void TaskManager::viewUsers() const
{
    if (users.empty())
    {
        cout << "\nNo users available.\n";
        return;
    }

    cout << "\n===== ALL USERS =====\n";

    for (const auto& entry : users)
    {
        entry.second.display();
    }
}

// View All Projects
void TaskManager::viewProjects() const
{
    if (projects.empty())
    {
        cout << "\nNo projects available.\n";
        return;
    }

    cout << "\n===== ALL PROJECTS =====\n";

    for (const auto& entry : projects)
    {
        entry.second.display();
    }
}

// View Tasks
void TaskManager::viewTasks() const
{
    if (tasks.empty())
    {
        cout << "No tasks available.\n";
        return;
    }

    cout << "\n===== ALL TASKS =====\n";

    for (const auto& entry : tasks)
    {
        entry.second.display();
    }
}

// Search Task
void TaskManager::searchTask(int taskId) const
{
    auto task = tasks.find(taskId);

    if (task == tasks.end())
    {
        cout << "Task not found.\n";
        return;
    }

    task->second.display();
}

// Sort Tasks by ID
void TaskManager::sortTasksById()
{
    if (tasks.empty())
    {
        cout << "No tasks available to sort.\n";
        return;
    }

    // Store pointers instead of copying Task objects
    vector<const Task*> sortedTasks;

    for (const auto& entry : tasks)
    {
        sortedTasks.push_back(&entry.second);
    }

    sort(
        sortedTasks.begin(),
        sortedTasks.end(),
        [](const Task* a, const Task* b)
        {
            return a->getId() < b->getId();
        }
    );

    cout << "\n===== TASKS SORTED BY ID =====\n";

    for (const Task* task : sortedTasks)
    {
        task->display();
    }
}

// Show High Priority Tasks
void TaskManager::showHighPriorityTasks() const
{
    // Store pointers instead of copying Task objects
    vector<const Task*> highPriorityTasks;

    // Filter HIGH and CRITICAL priority tasks
    for (const auto& entry : tasks)
    {
        if (entry.second.getPriority() == Priority::High ||
            entry.second.getPriority() == Priority::Critical)
        {
            highPriorityTasks.push_back(&entry.second);
        }
    }

    if (highPriorityTasks.empty())
    {
        cout << "\nNo high-priority tasks available.\n";
        return;
    }

    cout << "\n===== HIGH PRIORITY TASKS =====\n";

    for (const Task* task : highPriorityTasks)
    {
        task->display();
    }
}

// Add Task Dependency
void TaskManager::addTaskDependency(int taskId, int dependencyTaskId)
{
    auto task = tasks.find(taskId);

    if (task == tasks.end())
    {
        throw invalid_argument("Task not found.");
    }

    if (tasks.find(dependencyTaskId) == tasks.end())
    {
        throw invalid_argument("Dependency task not found.");
    }

    task->second.addDependency(dependencyTaskId);

    cout << "Task dependency added successfully!\n";
}

// View Task Dependencies
void TaskManager::viewTaskDependencies(int taskId) const
{
    auto task = tasks.find(taskId);

    if (task == tasks.end())
    {
        throw invalid_argument("Task not found.");
    }

    const vector<int>& dependencies = task->second.getDependencies();

    cout << "\n===== TASK DEPENDENCIES =====\n";
    cout << "Task ID: " << taskId << '\n';

    if (dependencies.empty())
    {
        cout << "No dependencies found.\n";
        return;
    }

    cout << "Depends on Task IDs: ";

    for (int dependencyId : dependencies)
    {
        cout << dependencyId << " ";
    }

    cout << '\n';
}

void TaskManager::updateUser(int userId)
{
    cout << "------------------------- UPDATE USER INFO ------------------------------\n";
    cout<< "\nUser ID: " << userId << '\n';
    cout << "-----------------------------------------------------------------------\n";
    while(true)
    {
        cout << "1. Update Name\n";
        cout << "2. Update Email\n";
        cout << "3. Update Role\n";
        cout << "4. Update Active Status\n";
        cout << "0. Exit Update\n";
        
        int choice;
        cout<<"\nEnter your choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                users.at(userId).setName();
                cout << "\nUser name updated successfully!\n";
                break;
            case 2:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                users.at(userId).setEmail();
                cout << "\nUser email updated successfully!\n";
                break;
            case 3:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                users.at(userId).setRole();
                cout << "\nUser role updated successfully!\n";
                break;
            case 4:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                users.at(userId).setIsActive();
                cout << "\nUser active status updated successfully!\n";
                break;
            case 0:
                cout << "\nExiting user update...\n";
                return;
            default:
                cout << "\nError: Invalid choice. Please try again.\n";
        }
        cout<<"\nDo you want to make another update? (Y/N): ";
        char cont;
        cin >> cont;
        if (cont == 'N' || cont == 'n')
        {
            break;
        }
    }
    cout << "-----------------------------------------------------------------------\n";
}


bool TaskManager::userExists(int userId) const
{
    return users.find(userId) != users.end();
}


bool TaskManager::projectExists(int projectId) const
{
    return projects.find(projectId) != projects.end();
}


// Check whether Task ID exists
bool TaskManager::taskExists(int taskId) const
{
    return tasks.find(taskId) != tasks.end();
}


void TaskManager::updateProject(int projectId)
{
    cout << "------------------------- UPDATE PROJECT INFO ------------------------------\n";
    cout << "\nProject ID: " << projectId << '\n';
    cout << "-----------------------------------------------------------------------\n";

    while (true)
    {
        cout << "1. Update Project Name\n";
        cout << "2. Update Description\n";
        cout << "3. Update Project Status\n";
        cout << "4. Update Priority\n";
        cout << "5. Update Start Date\n";
        cout << "6. Update End Date\n";
        cout << "0. Exit Update\n";

        int choice;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                projects.at(projectId).setProjectName();
                cout << "\nProject name updated successfully!\n";
                break;

            case 2:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                projects.at(projectId).setDescription();
                cout << "\nProject description updated successfully!\n";
                break;

            case 3:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                projects.at(projectId).setProjectStatus();
                cout << "\nProject status updated successfully!\n";
                break;

            case 4:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                projects.at(projectId).setPriority();
                cout << "\nProject priority updated successfully!\n";
                break;

            case 5:
            {
                while(true)
                {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    string newStartDate = readDate("\nEnter New Start Date (DD-MM-YYYY): ");

                    if (convertDateToNumber(newStartDate) >=
                        convertDateToNumber(projects.at(projectId).getEndDate()))
                    {
                        cout << "\nError: Start date must be earlier than end date.\n";
                        continue;
                    }

                    // Assign the validated date
                projects.at(projectId).setStartDate(newStartDate);
                }

                cout << "\nProject start date updated successfully!\n";
                break;
            }

            case 6:                
            {
                while(true)
                {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    string newEndDate = readDate("\nEnter New End Date (DD-MM-YYYY): ");

                    if (convertDateToNumber(newEndDate) <=
                        convertDateToNumber(projects.at(projectId).getStartDate()))
                    {
                        cout << "\nError: End date must be later than start date.\n";
                        break;
                    }

                    projects.at(projectId).setEndDate(newEndDate);
                }
                
                cout << "\nProject end date updated successfully!\n";
                break;
            }

            case 0:
                cout << "\nExiting project update...\n";
                return;

            default:
                cout << "\nError: Invalid choice. Please try again.\n";
        }

        cout << "\nDo you want to make another update? (Y/N): ";

        char cont;
        cin >> cont;

        if (cont != 'Y' && cont != 'y')
        {
            break;
        }
    }

    cout << "-----------------------------------------------------------------------\n";
}


Project* TaskManager::getProject(int projectId)
{
    auto it = projects.find(projectId);

    if (it == projects.end())
        return nullptr;

    return &(it->second);
}