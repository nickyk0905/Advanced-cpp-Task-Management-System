#include "operations/ProjectOperations.h"
#include "Project.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>

using namespace std;

int readProjectId(const string& prompt, TaskManager& manager)
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

            if (manager.projectExists(id))
            {
                cout << "\nError: Project ID already exists.\n";
                continue;
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

string readProjectName(const string& prompt)
{
    string input;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        // Check empty input
        if (input.empty())
        {
            cout << "\nError: Project name cannot be empty.\n";
            continue;
        }

        // Check length
        if (input.length() < 3 || input.length() > 100)
        {
            cout << "\nError: Project name's length must be between "
                 << "3 and 100 characters.\n";
            continue;
        }

        // Validate characters
        try
        {
            if (input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 -_&()."
                ) != string::npos)
            {
                throw invalid_argument(
                    "Project name contains invalid characters."
                );
            }

            return input;
        }
        catch (const invalid_argument& e)
        {
            cout << "\nError: " << e.what() << '\n';
        }
    }
}

string readProjectDescription(const string& prompt)
{
    string input;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        // Check empty input
        if (input.empty())
        {
            cout << "\nError: Project description cannot be empty.\n";
            continue;
        }

        // Check length
        if (input.length() < 10 || input.length() > 500)
        {
            cout << "\nError: Project description must be between "
                 << "10 and 500 characters.\n";
            continue;
        }

        // Description can contain letters, numbers and punctuation.
        return input;
    }
}


ProjectStatus readProjectStatus(const string& prompt)
{
    while (true)
    {
        cout << prompt;

        string input;
        getline(cin, input);

        if(input.empty())
        {
          cout<<"\nError: Project Status cannot be empty.\n";
          continue;
        }

        if (input == "Not Started" || input == "not started")
        {
            return ProjectStatus::NotStarted;
        }
        else if (input == "In Progress" || input == "in progress")
        {
            return ProjectStatus::InProgress;
        }
        else if (input == "On Hold" || input == "on hold")
        {
            return ProjectStatus::OnHold;
        }
        else if (input == "Completed" || input == "completed")
        {
            return ProjectStatus::Completed;
        }
        else if (input == "Cancelled" || input == "cancelled")
        {
            return ProjectStatus::Cancelled;
        }

        cout << "\nError: Invalid project status.\n";
    }
}


Priority readPriority(const string& prompt)
{
    while (true)
    {
        cout << prompt;

        string input;
        getline(cin, input);

        if(input.empty())
        {
          cout<<"\nError: Priority cannot be empty.\n";
          continue;
        }

        if (input == "Critical" || input == "critical")
        {
            return Priority::Critical;
        }
        else if (input == "High" || input == "high")
        {
            return Priority::High;
        }
        else if (input == "Medium" || input == "medium")
        {
            return Priority::Medium;
        }
        else if (input == "Low" || input == "low")
        {
            return Priority::Low;
        }
        
        cout << "\nError: Invalid priority.\n";
    }
}


string readDate(const string& prompt)
{
    string input;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (input.empty())
        {
            cout << "\nError: Date cannot be empty.\n";
            continue;
        }

        // Expected format: DD-MM-YYYY
        if (input.length() != 10 ||
            input[2] != '-' ||
            input[5] != '-')
        {
            cout << "\nError: Date must be in DD-MM-YYYY format.\n";
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

int readCreatedBy(const string& prompt, TaskManager& manager)
{
    string input;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (input.empty())
        {
            cout << "\nError: Created By User ID cannot be empty.\n";
            continue;
        }

        try
        {
            size_t position;

            int userId = stoi(input, &position);

            if (position != input.length())
            {
                cout << "\nError: Created By User ID must be a valid integer.\n";
                continue;
            }

            if (userId <= 0)
            {
                cout << "\nError: Created By User ID must be greater than 0.\n";
                continue;
            }

            if (!manager.userExists(userId))
            {
                cout << "\nError: User ID does not exist.\n";
                string choice;

                cout << "Would you like to create a new user? (Yes/No): ";
                getline(cin, choice);

                if (choice == "Yes" || choice == "yes" ||
                    choice == "Y" || choice == "y")
                {
                    manager.createUser();
                    cout<<"\n";
                }
                else
                {
                    continue;
                }
            }

            return userId;
        }
        catch (const invalid_argument&)
        {
            cout << "\nError: Created By User ID must be a valid integer.\n";
        }
        catch (const out_of_range&)
        {
            cout << "\nError: Created By User ID is out of range.\n";
        }
    }
}