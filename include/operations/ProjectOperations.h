#ifndef PROJECT_OPERATIONS_H
#define PROJECT_OPERATIONS_H

#include "Project.h"
#include "TaskManager.h"
#include <string>

using namespace std;

int readProjectId(const string& prompt, TaskManager& manager);
int readCreatedBy(const string& prompt, TaskManager& manager);
string readProjectName(const string& prompt);
string readProjectDescription(const string& prompt);
ProjectStatus readProjectStatus(const string& prompt);
Priority readPriority(const string& prompt);
string readDate(const string& prompt);

#endif