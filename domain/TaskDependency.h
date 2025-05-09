#ifndef TASK_DEPENDENCY_H
#define TASK_DEPENDENCY_H

using namespace std;

// Forward declaration
class Task;

class TaskDependency {
private:
    Task* sourceTask;
    Task* targetTask;
    char dependencyType[50]; // "Blocks", "Required by", "Related to", etc.
    
public:
    TaskDependency();
    TaskDependency(Task* source, Task* target, const char* type);
    ~TaskDependency();
    
    // Getters
    Task* getSourceTask() const;
    Task* getTargetTask() const;
    const char* getDependencyType() const;
    
    // Setters
    void setSourceTask(Task* source);
    void setTargetTask(Task* target);
    void setDependencyType(const char* type);
    
    // Validation
    bool isValid() const;
    bool isCyclical() const;
};

#endif // TASK_DEPENDENCY_H 