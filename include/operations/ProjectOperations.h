#ifndef PROJECT_OPERATIONS_H
#define PROJECT_OPERATIONS_H

#include "Project.h"
#include "TaskManager.h"
#include <string>

using namespace std;

int readProjectId(const string& prompt, TaskManager& manager);
int readCreatedBy(const string& prompt, TaskManager& manager);
string readText(const string& prompt);
string readDescription(const string& prompt);
ProjectStatus readProjectStatus(const string& prompt);
ProjectStatus readProjectStatus_update(const string& prompt);
Priority readPriority(const string& prompt);
string readDate(const string& prompt);


// Function to convert date string to a comparable integer format (YYYYMMDD)
int convertDateToNumber(const string& date);

#endif