#ifndef TASK_OPERATIONS_H
#define TASK_OPERATIONS_H

#include "TaskManager.h"

using namespace std;

int readTaskId(const string& prompt, const TaskManager& manager);
int readUserId_T(const string& prompt, TaskManager& manager);
int readProjectId_T(const string& prompt, TaskManager& manager);
TaskStatus readTaskStatus(const string& prompt);
string readStartDate(const string& prompt, const string& projectStart, const string& projectEnd);
string readEndDate(const string& prompt, const string& taskStart, const string& projectEnd);

#endif