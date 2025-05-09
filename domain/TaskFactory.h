#ifndef TASK_FACTORY_H
#define TASK_FACTORY_H

#include "Task.h"
#include "BugTask.h"
#include "FeatureTask.h"
#include "ImprovementTask.h"
#include "TaskDescription.h"
using namespace std;

class TaskFactory {
public:
    // Create a task of the specified type
    static Task* createTask(const char* taskType, int id, const char* title, 
                           const char* descriptionText, const char* assignee, 
                           const char* dueDate);
    
    // Create a bug task with specific bug details
    static BugTask* createBugTask(int id, const char* title, const char* descriptionText,
                                 const char* assignee, const char* dueDate,
                                 const char* severity, const char* reproduceSteps,
                                 const char* affectedVersion, bool isRegression);
    
    // Create a feature task with specific feature details
    static FeatureTask* createFeatureTask(int id, const char* title, const char* descriptionText,
                                         const char* assignee, const char* dueDate,
                                         const char* userStory, const char* acceptanceCriteria,
                                         bool hasMockups, const char* targetRelease);
    
    // Create an improvement task with specific improvement details
    static ImprovementTask* createImprovementTask(int id, const char* title, const char* descriptionText,
                                                const char* assignee, const char* dueDate,
                                                const char* impactArea, const char* justification,
                                                int benefitRating, bool isRefactoring);
};

#endif // TASK_FACTORY_H 