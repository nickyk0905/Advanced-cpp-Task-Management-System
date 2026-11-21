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
                cout << "\nUser ID must be a valid integer.\n";
                continue;
            }

            // Positive check
            if (id <= 0)
            {
                cout << "\nUser ID must be greater than 0.\n";
                continue;
            }

            // Unique ID check
            if (manager.userExists(id))
            {
                cout << "\nUser ID already exists.\n";
                continue;
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