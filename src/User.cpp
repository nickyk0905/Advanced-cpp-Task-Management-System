#include "operations/UserOperations.h"
#include "User.h"

#include <iostream>

using namespace std;

// Constructor
User::User(int userId,
           const string& name,
           const string& email,
           Role role,
           bool isActive)
    : userId(userId),
      name(name),
      email(email),
      role(role),
      isActive(isActive)
{
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

Role User::getRole() const
{
    return role;
}

bool User::getIsActive() const
{
    return isActive;
}

// Setters
void User::setName()
{
    name = readName("\nEnter User Name: ");
}

void User::setEmail()
{
    email = readEmail("\nEnter User Email: ");
}

void User::setRole()
{
    role = readRole("\nEnter User Role (Admin, Manager, Developer, Tester): ");
}

void User::setIsActive()
{
    isActive = readActiveStatus("\nIs the User Active? (Yes/No): ");
}

// Display
void User::display() const
{
    cout << "\n---------------------------------------------- USER DETAILS -----------------------------------------\n";

    cout << "\t\t\tUser ID: " << userId << '\n';
    cout << "\t\t\tName: " << name << '\n';
    cout << "\t\t\tEmail: " << email << '\n';

    cout << "\t\t\tRole: ";

    switch (role)
    {
        case Role::Admin:
            cout << "Admin";
            break;

        case Role::Manager:
            cout << "Manager";
            break;

        case Role::Developer:
            cout << "Developer";
            break;

        case Role::Tester:
            cout << "Tester";
            break;
    }

    cout << '\n';
    cout << "\t\t\tStatus: " << (isActive ? "Active" : "Inactive") << '\n';
    cout << "-----------------------------------------------------------------------------------------------------\n";
}