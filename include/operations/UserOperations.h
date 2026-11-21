#ifndef USER_OPERATIONS_H
#define USER_OPERATIONS_H

#include "TaskManager.h"

using namespace std;

int readUserId(const string& prompt, TaskManager& manager);
string readText(const string& prompt);
string readEmail(const string& prompt);
Role readRole(const string& prompt);
bool readActiveStatus(const string& prompt);

#endif