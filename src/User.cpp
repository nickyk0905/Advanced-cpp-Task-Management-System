#include "User.h"

#include <iostream>
#include <stdexcept>

using namespace std;

// Constructor
User::User(int userId, const string& name,
           const string& email)
    : userId(userId),
      name(name),
      email(email)
{
    if (userId <= 0)
    {
        throw invalid_argument("User ID must be positive.\nUser not Created.");
    }

    if (name.empty())
    {
        throw invalid_argument("User name cannot be empty.\nUser not Created.");
    }

    if (email.empty() || email.find('@') == string::npos)
    {
        throw invalid_argument("Invalid email address.");
    }

    cout << "\nUser created successfully!\n";
}

// Destructor
User::~User()
{
    // Destructor logic (if needed)
}

// Getters
int User::getUserId() const
{
    return userId;
}

const string& User::getName() const
{
    return name;
}

const string& User::getEmail() const
{
    return email;
}

// Setters
void User::setName(const string& newName)
{
    if (newName.empty())
    {
        throw invalid_argument("Name cannot be empty.\nName not updated.");
    }

    name = newName;
}

void User::setEmail(const string& newEmail)
{
    if (newEmail.empty() ||
        newEmail.find('@') == string::npos)
    {
        throw invalid_argument("Invalid email address.\nEmail not updated.");
    }

    email = newEmail;
}

// Display
void User::display() const
{
    cout << "\n----- USER DETAILS -----\n";

    cout << "\tUser ID: " << userId << '\n';
    cout << "\tName: " << name << '\n';
    cout << "\tEmail: " << email << '\n';
}