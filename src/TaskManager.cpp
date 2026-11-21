#include "TaskManager.h"
#include "operations/UserOperations.h"
#include "User.h"

#include <iostream>
#include <stdexcept>
#include <vector>
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
    cout << "-------- CREATING A USER --------\n";

    int userId = readUserId("\nEnter User ID: ", *this);
    string name = readText("\nEnter User Name: ");
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
    cout<<"\n--------------------------------------------------------------------------";
    cout << "\n\tUser added to Task Manager successfully!\n";
    cout<<"\n--------------------------------------------------------------------------";
}

// Create Project
void TaskManager::createProject(const Project& project)
{
    int id = project.getProjectId();

    if (projects.find(id) != projects.end())
    {
        throw invalid_argument("\nProject ID already exists.");
    }

    projects.emplace(id, project);

    cout << "\nProject added to Task Manager successfully!\n";
}

// Create Task
void TaskManager::createTask(
    int id,
    const string& title,
    const string& description,
    Priority priority,
    int assignedUserId,
    int projectId)
{
    if (tasks.find(id) != tasks.end())
    {
        throw invalid_argument("\nTask ID already exists.");
    }

    if (users.find(assignedUserId) == users.end())
    {
        throw invalid_argument("\nAssigned user does not exist.");
    }

    auto project = projects.find(projectId);

    if (project == projects.end())
    {
        throw invalid_argument("\nProject does not exist.");
    }

    // Add task ID to the associated project
    project->second.addTask(id);

    try
    {
        // Create Task and store it in the unordered_map
        Task task(
            id,
            title,
            description,
            priority,
            assignedUserId,
            projectId
        );

        tasks.emplace(id, task);
    }
    catch (...)
    {
        // Roll back project association if task creation fails
        project->second.removeTask(id);
        throw;
    }

    cout << "\nTask added to Task Manager successfully!\n";
}

// Assign Task
void TaskManager::assignTask(int taskId, int userId)
{
    auto task = tasks.find(taskId);

    if (task == tasks.end())
    {
        throw invalid_argument("Task not found.");
    }

    if (users.find(userId) == users.end())
    {
        throw invalid_argument("User not found.");
    }

    task->second.setAssignedUserId(userId);

    cout << "\nTask assigned successfully!\n";
}

// Update Task Status
void TaskManager::updateTaskStatus(int taskId, TaskStatus status)
{
    auto task = tasks.find(taskId);

    if (task == tasks.end())
    {
        throw invalid_argument("Task not found.");
    }

    task->second.setStatus(status);

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

    // Remove task ID from project before deleting the task
    project->second.removeTask(taskId);

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
        if (entry.second.getPriority() == Priority::HIGH ||
            entry.second.getPriority() == Priority::CRITICAL)
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

bool TaskManager::userExists(int userId) const
{
    return users.find(userId) != users.end();
}