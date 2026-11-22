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
            cout << "\nError: User ID cannot be empty.\n";
            continue;
        }

        try
        {
            size_t position;
            int id = stoi(input, &position);

            // Integer check
            if (position != input.length())
            {
                cout << "\nError: User ID must be a valid integer.\n";
                continue;
            }

            // Positive check
            if (id <= 0)
            {
                cout << "\nError: User ID must be greater than 0.\n";
                continue;
            }

            // Unique ID check
            if (manager.userExists(id))
            {
                cout << "\nError: User ID already exists.\n";
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
            }

            return input;
        }
        catch (const invalid_argument& e)
        {
            cout << "\nError: " << e.what() << '\n';
        }
    }
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
            // Check total email length
            if (input.length() > 254)
            {
                throw invalid_argument("Email address is too long.");
            }

            // Find @
            size_t atPosition = input.find('@');

            // Exactly one @
            if (atPosition == string::npos ||
                atPosition != input.rfind('@'))
            {
                throw invalid_argument("Email must contain exactly one '@'.");
            }

            // Separate local part and domain
            string localPart = input.substr(0, atPosition);
            string domain = input.substr(atPosition + 1);

            // Check local part and domain are not empty
            if (localPart.empty() || domain.empty())
            {
                throw invalid_argument("Invalid email format.");
            }

            // Check spaces
            if (input.find(' ') != string::npos)
            {
                throw invalid_argument("Email cannot contain spaces.");
            }

            // Check consecutive dots
            if (input.find("..") != string::npos)
            {
                throw invalid_argument("Email cannot contain consecutive dots.");
            }

            // Local part cannot start or end with '.'
            if (localPart.front() == '.' ||
                localPart.back() == '.')
            {
                throw invalid_argument(
                    "Email local part cannot start or end with '.'.");
            }

            // Domain cannot start or end with '.'
            if (domain.front() == '.' ||
                domain.back() == '.')
            {
                throw invalid_argument(
                    "Domain cannot start or end with '.'.");
            }

            // Domain must contain '.'
            size_t dotPosition = domain.find('.');

            if (dotPosition == string::npos)
            {
                throw invalid_argument(
                    "Domain must contain a valid extension.");
            }

            // Allowed characters in local part
            for (char ch : localPart)
            {
                if (!(isalnum(ch) ||
                      ch == '.' ||
                      ch == '_' ||
                      ch == '-' ||
                      ch == '+'))
                {
                    throw invalid_argument(
                        "Email contains invalid characters.");
                }
            }

            // Validate domain
            for (char ch : domain)
            {
                if (!(isalnum(ch) || ch == '.' || ch == '-'))
                {
                    throw invalid_argument(
                        "Domain contains invalid characters.");
                }
            }

            // Check each domain label
            size_t start = 0;

            while (true)
            {
                size_t dot = domain.find('.', start);

                string label;

                if (dot == string::npos)
                {
                    label = domain.substr(start);
                }
                else
                {
                    label = domain.substr(start, dot - start);
                }

                // Domain label cannot be empty
                if (label.empty())
                {
                    throw invalid_argument("Invalid domain format.");
                }

                // Label cannot start or end with '-'
                if (label.front() == '-' ||
                    label.back() == '-')
                {
                    throw invalid_argument(
                        "Domain labels cannot start or end with '-'.");
                }

                if (dot == string::npos)
                {
                    break;
                }

                start = dot + 1;
            }

            // Validate Top-Level Domain
            size_t lastDot = domain.rfind('.');
            string extension = domain.substr(lastDot + 1);

            if (extension.length() < 2)
            {
                throw invalid_argument(
                    "Email must have a valid domain extension.");
            }

            for (char ch : extension)
            {
                if (!isalpha(ch))
                {
                    throw invalid_argument(
                        "Domain extension must contain only letters.");
                }
            }

            return input;
        }
        catch (const invalid_argument& e)
        {
            cout << "\nError: " << e.what() << '\n';
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

        if (input == "Admin" || input == "admin")
        {
            return Role::Admin;
        }
        else if (input == "Manager" || input == "manager")
        {
            return Role::Manager;
        }
        else if (input == "Developer" || input == "developer")
        {
            return Role::Developer;
        }
        else if (input == "Tester" || input == "tester")
        {
            return Role::Tester;
        }

        cout << "\nError: Invalid role entered.\n";
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
        else
        {
            return false;
        }

        cout << "\nError: Invalid input. Please enter a valid input.\n";
    }
}