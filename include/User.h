#ifndef USER_H
#define USER_H

#include <string>

enum class Role
{
    Admin,
    Manager,
    Developer,
    Tester
};

class User
{
private:
    int userId;
    std::string name;
    std::string email;
    Role role;
    bool isActive;

public:
    // Constructor
    User(int userId,
         const std::string& name,
         const std::string& email,
         Role role,
         bool isActive);

    // Destructor
    ~User();

    // Getters
    int getUserId() const;
    const std::string& getName() const;
    const std::string& getEmail() const;
    Role getRole() const;
    bool getIsActive() const;

    // Setters
    void setName();
    void setEmail();
    void setRole();
    void setIsActive();

    // Display
    void display() const;
};

#endif