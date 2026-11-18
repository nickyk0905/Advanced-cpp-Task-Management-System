
#ifndef USER_H
#define USER_H

#include <string>

class User
{
private:
    int userId;
    std::string name;
    std::string email;

public:

    // Constructor
    User(int userId, const std::string& name,
         const std::string& email);

    // Destructor
    ~User();

    // Getters
    int getUserId() const;
    const std::string& getName() const;
    const std::string& getEmail() const;

    // Setters
    void setName(const std::string& newName);
    void setEmail(const std::string& newEmail);

    // Display
    void display() const;
};

#endif
