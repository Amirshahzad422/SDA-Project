#ifndef IMPROVEMENT_TASK_H
#define IMPROVEMENT_TASK_H

#include "Task.h"
using namespace std;

class ImprovementTask : public Task {
private:
    char impactArea[100]; // "Performance", "UI/UX", "Code Quality", etc.
    char justification[500];
    int benefitRating; // 1-5 scale
    bool isRefactoring;

public:
    ImprovementTask();
    ImprovementTask(int id, const char* title, TaskDescription* description,
                   const char* assignee, const char* dueDate,
                   const char* impactArea, const char* justification,
                   int benefitRating, bool isRefactoring);
    ~ImprovementTask();
    
    // Improvement specific getters
    const char* getImpactArea() const;
    const char* getJustification() const;
    int getBenefitRating() const;
    bool getIsRefactoring() const;
    
    // Improvement specific setters
    void setImpactArea(const char* area);
    void setJustification(const char* reason);
    void setBenefitRating(int rating);
    void setIsRefactoring(bool refactoring);
    
    // Override from Task base class
    const char* getTaskType() const override;
};

#endif // IMPROVEMENT_TASK_H 