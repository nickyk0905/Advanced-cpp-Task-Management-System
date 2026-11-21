#include <iostream>
#include <cctype>
#include <string>
#include <stdexcept>

#include "Task.h"
#include "User.h"
#include "Project.h"
#include "TaskManager.h"

#include "operations/UserOperations.h"

using namespace std;


// Read integer input
int readInt(const string& prompt)
{
    string input;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        try
        {
            size_t position;
            int value = stoi(input, &position);

            if (position != input.length())
            {
                throw invalid_argument("Invalid input");
            }

            return value;
        }
        catch (const exception&)
        {
            cout << "Invalid input. Please enter a valid number.\n";
        }
    }
}


// Read text input
string readText1(const string& prompt)
{
    string input;

    cout << prompt;
    getline(cin, input);

    return input;
}


// Wait for Enter before showing the menu
void waitForKey()
{
    cout << "\nPress Enter to continue...";
    cin.get();
}


int main()
{
    cout << "\n===== ADVANCED C++ TASK MANAGEMENT SYSTEM =====\n";

    TaskManager manager;

    int choice = -1;

    do
    {
        // Menu appears only after pressing Enter
        waitForKey();

        cout << "\n========== MAIN MENU ==========\n";
        cout << "1. Create User\n";
        cout << "2. Create Project\n";
        cout << "3. Create Task\n";
        cout << "4. Assign Task\n";
        cout << "5. Update Task Status\n";
        cout << "6. View All Tasks\n";
        cout << "7. Search Task\n";
        cout << "8. Sort Tasks By ID\n";
        cout << "9. Show High Priority Tasks\n";
        cout << "10. Delete Task\n";
        cout << "11. Update User Info\n";
        cout << "12. View All Users\n";
        cout << "13. View All Projects\n";
        cout << "14. Add Task Dependency\n";
        cout << "15. View Task Dependencies\n";
        cout << "0. Exit\n";

        choice = readInt("\nEnter your choice: ");

        cout << "\n";

        try
        {
            switch (choice)
            {
                // =================================
                // CREATE USER
                // =================================

                case 1:
                {
                    manager.createUser();
                    break;
                }


                // =================================
                // CREATE PROJECT
                // =================================

                case 2:
                {
                    int id = readInt("Enter Project ID: ");

                    string name = readText1("Enter Project Name: ");
                    string description = readText1("Enter Description: ");

                    Project project(id, name, description);

                    manager.createProject(project);

                    break;
                }


                // =================================
                // CREATE TASK
                // =================================

                case 3:
                {
                    int id = readInt("Enter Task ID: ");

                    string title = readText1("Enter Task Title: ");
                    string description = readText1("Enter Description: ");

                    cout << "\nPriority:\n";
                    cout << "1. LOW\n";
                    cout << "2. MEDIUM\n";
                    cout << "3. HIGH\n";
                    cout << "4. CRITICAL\n";

                    int priorityChoice = readInt("Choose Priority: ");

                    Priority priority;

                    switch (priorityChoice)
                    {
                        case 1:
                            priority = Priority::LOW;
                            break;

                        case 2:
                            priority = Priority::MEDIUM;
                            break;

                        case 3:
                            priority = Priority::HIGH;
                            break;

                        case 4:
                            priority = Priority::CRITICAL;
                            break;

                        default:
                            throw invalid_argument(
                                "Invalid priority choice."
                            );
                    }

                    int userId =
                        readInt("Enter Assigned User ID: ");

                    int projectId =
                        readInt("Enter Project ID: ");

                    manager.createTask(
                        id,
                        title,
                        description,
                        priority,
                        userId,
                        projectId
                    );

                    break;
                }


                // =================================
                // ASSIGN TASK
                // =================================

                case 4:
                {
                    int taskId =
                        readInt("Enter Task ID: ");

                    int userId =
                        readInt("Enter User ID: ");

                    manager.assignTask(taskId, userId);

                    break;
                }


                // =================================
                // UPDATE TASK STATUS
                // =================================

                case 5:
                {
                    int taskId =
                        readInt("Enter Task ID: ");

                    cout << "\nStatus:\n";
                    cout << "1. TODO\n";
                    cout << "2. IN_PROGRESS\n";
                    cout << "3. COMPLETED\n";
                    cout << "4. BLOCKED\n";

                    int statusChoice =
                        readInt("Choose Status: ");

                    TaskStatus status;

                    switch (statusChoice)
                    {
                        case 1:
                            status = TaskStatus::TODO;
                            break;

                        case 2:
                            status = TaskStatus::IN_PROGRESS;
                            break;

                        case 3:
                            status = TaskStatus::COMPLETED;
                            break;

                        case 4:
                            status = TaskStatus::BLOCKED;
                            break;

                        default:
                            throw invalid_argument(
                                "Invalid status choice."
                            );
                    }

                    manager.updateTaskStatus(
                        taskId,
                        status
                    );

                    break;
                }


                // =================================
                // VIEW ALL TASKS
                // =================================

                case 6:
                    manager.viewTasks();
                    break;


                // =================================
                // SEARCH TASK
                // =================================

                case 7:
                {
                    int taskId =
                        readInt("Enter Task ID: ");

                    manager.searchTask(taskId);

                    break;
                }


                // =================================
                // SORT TASKS BY ID
                // =================================

                case 8:
                    manager.sortTasksById();
                    break;


                // =================================
                // SHOW HIGH PRIORITY TASKS
                // =================================

                case 9:
                    manager.showHighPriorityTasks();
                    break;


                // =================================
                // DELETE TASK
                // =================================

                case 10:
                {
                    int taskId =
                        readInt("Enter Task ID: ");

                    manager.deleteTask(taskId);

                    break;
                }


                // =================================
                // VIEW ALL USERS
                // =================================

                case 11:
                {
                    int userId;
                    while(true)                    
                    {                        
                        cout<<"Enter User ID to update: ";
                        cin>>userId;

                        if (!manager.userExists(userId))
                        {
                            cout << "\nError: User not found.\n\n";
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }

                    manager.updateUser(userId);
                    break;
                }


                case 12:
                    manager.viewUsers();
                    break;


                // =================================
                // VIEW ALL PROJECTS
                // =================================

                case 13:
                    manager.viewProjects();
                    break;


                // =================================
                // ADD TASK DEPENDENCY
                // =================================

                case 14:
                {
                    int taskId =
                        readInt("Enter Dependant Task ID: ");

                    int dependencyTaskId =
                        readInt("Enter Task ID: ");

                    manager.addTaskDependency(
                        taskId,
                        dependencyTaskId
                    );

                    break;
                }


                // =================================
                // VIEW TASK DEPENDENCIES
                // =================================

                case 15:
                {
                    int taskId =
                        readInt("Enter Task ID: ");

                    manager.viewTaskDependencies(taskId);

                    break;
                }


                // =================================
                // EXIT
                // =================================

                case 0:
                    cout<<"\n------------------------------------------------------------------------------------\n";
                    cout << "\n\t\t\tExiting Task Management System...\n";
                    cout<<"\n------------------------------------------------------------------------------------\n";
                    break;


                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }

        catch (const exception& e)
        {
            cout << "\nError: " << e.what() << '\n';
        }

    } while (choice != 0);

    return 0;
}