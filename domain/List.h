#ifndef LIST_H
#define LIST_H

#include <cstring>
using namespace std;

const int MAX_TASKS_PER_LIST = 50;

// Forward declaration
class Task;

class List {
private:
    char id[50];
    char name[100];
    Task* tasks[MAX_TASKS_PER_LIST];
    int taskCount;
    
public:
    List();
    List(const char* id, const char* name);
    ~List();
    
    // Getters
    const char* getId() const;
    const char* getName() const;
    
    // Setters
    void setId(const char* id);
    void setName(const char* name);
    
    // Task management
    bool addTask(Task* task);
    bool removeTask(int taskIndex);
    bool moveTask(int fromIndex, int toIndex);
    Task* getTask(int index) const;
    int getTaskCount() const;
    Task* findTaskById(int taskId) const;
    Task* findTaskByTitle(const char* title) const;
};

#endif // LIST_H 