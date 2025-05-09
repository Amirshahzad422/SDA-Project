#ifndef FEATURE_TASK_H
#define FEATURE_TASK_H

#include "Task.h"
using namespace std;

class FeatureTask : public Task {
private:
    char userStory[500];
    char acceptanceCriteria[500];
    bool hasMockups;
    char targetRelease[50];

public:
    FeatureTask();
    FeatureTask(int id, const char* title, TaskDescription* description,
               const char* assignee, const char* dueDate,
               const char* userStory, const char* acceptanceCriteria,
               bool hasMockups, const char* targetRelease);
    ~FeatureTask();
    
    // Feature specific getters
    const char* getUserStory() const;
    const char* getAcceptanceCriteria() const;
    bool getHasMockups() const;
    const char* getTargetRelease() const;
    
    // Feature specific setters
    void setUserStory(const char* story);
    void setAcceptanceCriteria(const char* criteria);
    void setHasMockups(bool mockups);
    void setTargetRelease(const char* release);
    
    // Override from Task base class
    const char* getTaskType() const override;
};

#endif // FEATURE_TASK_H 