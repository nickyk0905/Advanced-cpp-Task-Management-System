#include "operations/UserOperations.h"
#include "User.h"

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;


int readUserId(const string& prompt, TaskManager& manager)
{
    string input;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        // Empty check
        if (input.empty())
        {
            cout << "\nUser ID cannot be empty.\n";
            continue;
        }

        try
        {
            size_t position;
            int id = stoi(input, &position);

            // Integer check
            if (position != input.length())
            {
                throw invalid_argument(
                    "User ID must be a valid integer.\n"
                );
            }

            // Positive check
            if (id <= 0)
            {
                throw invalid_argument(
                    "User ID must be greater than 0.\n"
                );
            }

            // Unique ID check
            if (manager.userExists(id))
            {
                throw invalid_argument(
                    "User ID already exists.\n"
                );
            }

            return id;
        }
        catch (invalid_argument& e)
        {
            cout << "\nError: " << e.what() << '\n';
            continue;
        }
        catch (exception& e)
        {
            cout << "\nError: " << e.what() << '\n';
            continue;
        }
    }
}


// Read text input
string readText(const string& prompt)
{
    string input;

    while(true)
    {
        cout << prompt;
        getline(cin, input);
        
        if (input.empty())
        {
            cout<<"\nError: Input cannot be empty.\n";
            continue;
        }
        try
        {            
            if(input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos) {
                throw invalid_argument("Input contains invalid characters.");
                continue;    
            }

            return input;
        }
        catch (const invalid_argument& e)
        {
            cout << "Error: " << e.what() << '\n';
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << '\n';
        } 
    }

    return input;
}


// Read email input
string readEmail(const string& prompt)  
{
    string input;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        // Check empty input
        if (input.empty())
        {
            cout << "\nError: Email cannot be empty.\n";
            continue;
        }

        try
        {
            // Find @
            size_t atPosition = input.find('@');

            // Basic email validation
            if (atPosition == string::npos ||
                atPosition == 0 ||
                atPosition == input.length() - 1 ||
                atPosition != input.rfind('@') ||
                input.find('.', atPosition) == string::npos)
            {
                throw invalid_argument("Invalid email");
            }

            // Check for spaces
            if (input.find(' ') != string::npos)
            {
                throw invalid_argument("Invalid email");
            }

            return input;
        }
        catch (const exception&)
        {
            cout << "\nError: Invalid email address. Please enter a valid email.\n";
        }
    }
}


Role readRole(const string& prompt)
{
    while (true)
    {
        cout << prompt;

        string input;
        getline(cin, input);

        if (input == "Admin")
        {
            return Role::Admin;
        }
        else if (input == "Manager")
        {
            return Role::Manager;
        }
        else if (input == "Developer")
        {
            return Role::Developer;
        }
        else if (input == "Tester")
        {
            return Role::Tester;
        }

        cout << "Error: Invalid role entered.\n";
    }
}


// Read Active Status
bool readActiveStatus(const string& prompt)
{
    while (true)
    {
        cout << prompt;
        string status;

        getline(cin, status);

        if (status == "Yes" || status == "yes" || status == "Y" || status == "y")
        {
            return true;
        }

        if (status == "No" || status == "no" || status == "N" || status == "n")
        {
            return false;
        }

        cout << "Invalid input. Please enter a valid input.\n";
    }
}