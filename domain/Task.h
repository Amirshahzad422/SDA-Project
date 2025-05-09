#ifndef TASK_H
#define TASK_H

#include <cstring>
using namespace std;

// Forward declarations
class TaskDependency;
class TaskDescription;
class EstimationStrategy;

class Task {
protected:
    int taskId;
    char title[100];
    TaskDescription* description;
    char status[20]; // "To Do", "In Progress", "Done"
    char priority[20]; // "Low", "Medium", "High"
    char assignee[100];
    char dueDate[20];
    TaskDependency* dependencies[10]; // Fixed size array
    int dependencyCount;
    char attachedFile[200];
    EstimationStrategy* estimationStrategy;

public:
    Task();
    Task(int id, const char* title, TaskDescription* description,
         const char* assignee, const char* dueDate);
    virtual ~Task();
    
    // Task management
    void updateStatus(const char* newStatus);
    void assignTo(const char* assignee);
    void addDependency(Task* dependency);
    void removeDependency(Task* dependency);
    
    // Getters
    int getTaskId() const;
    const char* getTitle() const;
    TaskDescription* getDescription() const;
    const char* getStatus() const;
    const char* getPriority() const;
    const char* getAssignee() const;
    const char* getDueDate() const;
    const char* getAttachedFile() const;
    
    // Setters
    void setTitle(const char* title);
    void setDescription(TaskDescription* description);
    void setPriority(const char* priority);
    void setDueDate(const char* dueDate);
    void setAttachedFile(const char* file);
    
    // Estimation
    double estimateEffort() const;
    void setEstimationStrategy(EstimationStrategy* strategy);
    
    // Virtual methods for different task types
    virtual const char* getTaskType() const = 0;
};

#endif // TASK_H 