#ifndef BUG_TASK_H
#define BUG_TASK_H

#include "Task.h"
using namespace std;

class BugTask : public Task {
private:
    char severity[20]; // "Low", "Medium", "High", "Critical"
    char reproduceSteps[500];
    char affectedVersion[50];
    bool isRegression;

public:
    BugTask();
    BugTask(int id, const char* title, TaskDescription* description,
            const char* assignee, const char* dueDate,
            const char* severity, const char* reproduceSteps,
            const char* affectedVersion, bool isRegression);
    ~BugTask();
    
    // Bug specific getters
    const char* getSeverity() const;
    const char* getReproduceSteps() const;
    const char* getAffectedVersion() const;
    bool getIsRegression() const;
    
    // Bug specific setters
    void setSeverity(const char* severity);
    void setReproduceSteps(const char* steps);
    void setAffectedVersion(const char* version);
    void setIsRegression(bool regression);
    
    // Override from Task base class
    const char* getTaskType() const override;
};

#endif // BUG_TASK_H 