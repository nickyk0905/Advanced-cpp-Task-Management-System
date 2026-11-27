#include "operations/TaskOperations.h"
#include "operations/UserOperations.h"
#include "operations/ProjectOperations.h"
#include "TaskManager.h"

#include "Task.h"
#include "Priority.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

using namespace std;


int readTaskId(const string& prompt, const TaskManager& manager)
{
    string input;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (input.empty())
        {
            cout << "\nError: Task ID cannot be empty.\n";
            continue;
        }

        try
        {
            size_t position;
            int taskId = stoi(input, &position);

            // Integer check
            if (position != input.length())
            {
                cout << "\nError: Task ID must be a valid integer.\n";
                continue;
            }

            // Positive check
            if (taskId <= 0)
            {
                cout << "\nError: Task ID must be greater than 0.\n";
                continue;
            }

            // Unique ID check
            if (manager.taskExists(taskId))
            {
                cout << "\nError: Task ID already exists.\n";
                continue;
            }

            return taskId;
        }
        catch (const invalid_argument&)
        {
            cout << "\nTask ID must be a valid integer.\n";
        }
        catch (const out_of_range&)
        {
            cout << "\nTask ID is out of range.\n";
        }
    }
}



int readUserId_T(const string& prompt, TaskManager& manager)
{
    string input;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (input.empty())
        {
            cout << "\nError: User ID cannot be empty.\n";
            continue;
        }

        try
        {
            size_t position;
            int id = stoi(input, &position);

            if (position != input.length())
            {
                cout << "\nError: User ID must be a valid integer.\n";
                continue;
            }

            if (id <= 0)
            {
                cout << "\nError: User ID must be greater than 0.\n";
                continue;
            }

            // Existence check
            if (!manager.userExists(id))
            {
                cout << "\nUser ID does not exist.\n";
                cout << "\nWould you like to create a new user? (Yes/No): ";

                string choice;
                getline(cin, choice);

                if (choice == "Yes" || choice == "yes" ||
                    choice == "Y" || choice == "y")
                {
                    cout<<"\n";
                    manager.createUser();

                    // Check the originally entered ID again
                    if (!manager.userExists(id))
                    {
                        cout << "\nThe entered User ID still does not exist."
                             << "\nPlease enter an existing User ID.\n";
                        continue;
                    }
                }
                else
                {
                    cout << "\nPlease enter an existing User ID.\n";
                    continue;
                }
            }

            return id;
        }
        catch (const invalid_argument&)
        {
            cout << "\nUser ID must be a valid integer.\n";
        }
        catch (const out_of_range&)
        {
            cout << "\nUser ID is out of range.\n";
        }
    }
}



int readProjectId_T(const string& prompt, TaskManager& manager)
{
    string input;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (input.empty())
        {
            cout << "\nError: Project ID cannot be empty.\n";
            continue;
        }

        try
        {
            size_t position;

            int id = stoi(input, &position);

            if (position != input.length())
            {
                cout << "\nError:Project ID must be a valid integer.\n";
                continue;
            }

            if (id <= 0)
            {
                cout << "\nError:Project ID must be greater than 0.\n";
                continue;
            }

            // Existence check
            if (!manager.projectExists(id))
            {
                cout << "\nProject ID does not exist.\n";
                cout << "\nWould you like to create a new Project? (Yes/No): ";

                string choice;
                getline(cin, choice);

                if (choice == "Yes" || choice == "yes" ||
                    choice == "Y" || choice == "y")
                {
                    cout<<"\n";
                    manager.createProject();

                    // Check the originally entered ID again
                    if (!manager.projectExists(id))
                    {
                        cout << "\nThe entered Project ID still does not exist."
                             << "\nPlease enter an existing Project ID.\n";
                        continue;
                    }
                }
                else
                {
                    cout << "\nPlease enter an existing Project ID.\n";
                    continue;
                }
            }

            return id;
        }
        catch (const invalid_argument& e)
        {
            cout << "\nError: Project ID must be a valid integer.\n";
        }
        catch (const out_of_range& e)
        {
            cout << "\nError: Project ID is out of range.\n";
        }
    }
}



// Read Task Status
TaskStatus readTaskStatus(const string& prompt)
{
    string input;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (input == "TODO" || input == "Todo" || input == "todo")
            return TaskStatus::TODO;

        if (input == "IN_PROGRESS" || input == "In_Progress" || input == "in_progress")
            return TaskStatus::IN_PROGRESS;

        if (input == "BLOCKED" || input == "Blocked" || input == "blocked")
            return TaskStatus::BLOCKED;

        if (input == "ON_HOLD" || input == "On_Hold" || input == "on_hold")
            return TaskStatus::ON_HOLD;

        if (input == "COMPLETED" || input == "Completed" || input == "completed")
            return TaskStatus::COMPLETED;

        if (input == "CANCELLED" || input == "Cancelled" || input == "cancelled")
            return TaskStatus::CANCELLED;

        cout << "\nError: Invalid task status.\n";
        cout << "Choose: TODO, IN_PROGRESS, BLOCKED, ON_HOLD, COMPLETED, CANCELLED.\n";
    }
}

string readStartDate(const string& prompt, const string& projectStart, const string& projectEnd)
{
    string input;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (input.empty())
        {
            cout << "\nError: Task Start Date cannot be empty.\n";
            continue;
        }

        // Expected format: DD-MM-YYYY
        if (input.length() != 10 ||
            input[2] != '-' ||
            input[5] != '-')
        {
            cout << "\nError: Task Start Date must be in DD-MM-YYYY format.\n";
            continue;
        }

        try
        {
            // Check that all other characters are digits
            for (int i = 0; i < 10; i++)
            {
                if (i == 2 || i == 5)
                    continue;

                if (!isdigit(static_cast<unsigned char>(input[i])))
                {
                    throw invalid_argument("Invalid date");
                }
            }

            int day = stoi(input.substr(0, 2));
            int month = stoi(input.substr(3, 2));
            int year = stoi(input.substr(6, 4));

            if (year < 2000 || year > 2100)
            {
                throw invalid_argument("Invalid year");
            }

            if (month < 1 || month > 12)
            {
                throw invalid_argument("Invalid month");
            }

            // Validate number of days in the month
            int daysInMonth[] = {
                31, 28, 31, 30, 31, 30,
                31, 31, 30, 31, 30, 31
            };

            // Leap year validation
            bool isLeapYear =
                (year % 400 == 0) ||
                (year % 4 == 0 && year % 100 != 0);

            if (isLeapYear)
            {
                daysInMonth[1] = 29;
            }

            if (day < 1 || day > daysInMonth[month - 1])
            {
                throw invalid_argument("Invalid day");
            }

            int taskStartDate = convertDateToNumber(input);
            int projectStartDate = convertDateToNumber(projectStart);
            int projectEndDate = convertDateToNumber(projectEnd);

            if (taskStartDate < projectStartDate)
            {
                cout << "\nError: Task Start Date cannot be earlier than "<< "Project Start Date (" << projectStart << ").\n";
                continue;
            }
            else if(taskStartDate > projectEndDate)
            {
                cout << "\nError: Task Start Date cannot be later than "<< "Project End Date (" << projectEnd << ").\n";
                continue;
            }

            return input;
        }
        catch (const invalid_argument&)
        {
            cout << "\nError: Invalid date. "
                 << "Please enter a valid date in DD-MM-YYYY format.\n";
        }
        catch (const out_of_range&)
        {
            cout << "\nError: Date value is out of range.\n";
        }
    }
}

string readEndDate(const string& prompt, const string& taskStart, const string& projectEnd)
{
    string input;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (input.empty())
        {
            cout << "\nError: Task Due Date cannot be empty.\n";
            continue;
        }

        // Expected format: DD-MM-YYYY
        if (input.length() != 10 ||
            input[2] != '-' ||
            input[5] != '-')
        {
            cout << "\nError: Task Due Date must be in DD-MM-YYYY format.\n";
            continue;
        }

        try
        {
            // Check that all other characters are digits
            for (int i = 0; i < 10; i++)
            {
                if (i == 2 || i == 5)
                    continue;

                if (!isdigit(static_cast<unsigned char>(input[i])))
                {
                    throw invalid_argument("Invalid date");
                }
            }

            int day = stoi(input.substr(0, 2));
            int month = stoi(input.substr(3, 2));
            int year = stoi(input.substr(6, 4));

            if (year < 2000 || year > 2100)
            {
                throw invalid_argument("Invalid year");
            }

            if (month < 1 || month > 12)
            {
                throw invalid_argument("Invalid month");
            }

            // Validate number of days in the month
            int daysInMonth[] = {
                31, 28, 31, 30, 31, 30,
                31, 31, 30, 31, 30, 31
            };

            // Leap year validation
            bool isLeapYear =
                (year % 400 == 0) ||
                (year % 4 == 0 && year % 100 != 0);

            if (isLeapYear)
            {
                daysInMonth[1] = 29;
            }

            if (day < 1 || day > daysInMonth[month - 1])
            {
                throw invalid_argument("Invalid day");
            }

            int taskStartDate = convertDateToNumber(taskStart);
            int taskDueDate = convertDateToNumber(input);
            int projectEndDate = convertDateToNumber(projectEnd);

            if (taskDueDate < taskStartDate)
            {
                cout << "\nError: Task Due Date cannot be earlier than "
                    << "Task Start Date (" << taskStart << ").\n";
                continue;
            }
            else if (taskDueDate > projectEndDate)
            {
                cout << "\nError: Task Due Date cannot be later than "
                    << "Project End Date (" << projectEnd << ").\n";
                continue;
            }


            return input;
        }
        catch (const invalid_argument&)
        {
            cout << "\nError: Invalid date. "
                 << "Please enter a valid date in DD-MM-YYYY format.\n";
        }
        catch (const out_of_range&)
        {
            cout << "\nError: Date value is out of range.\n";
        }
    }
}