#define _CRT_SECURE_NO_WARNINGS
#include "Task.h"

int Task::getTaskId() const {
    return taskId;
}

const char* Task::getTitle() const {
    return title;
}

TaskDescription* Task::getDescription() const {
    return description;
}

const char* Task::getStatus() const {
    return status;
}

const char* Task::getPriority() const {
    return priority;
}

const char* Task::getAssignee() const {
    return assignee;
}

const char* Task::getDueDate() const {
    return dueDate;
}

const char* Task::getAttachedFile() const {
    return attachedFile;
}

void Task::updateStatus(const char* newStatus) {
    // Implementation placeholder
}

void Task::assignTo(const char* assignee) {
    // Implementation placeholder
}

void Task::addDependency(Task* dependency) {
    // Implementation placeholder
}

void Task::removeDependency(Task* dependency) {
    // Implementation placeholder
}

void Task::setTitle(const char* title) {
    // Implementation placeholder
}

void Task::setDescription(TaskDescription* description) {
    // Implementation placeholder
}

void Task::setPriority(const char* priority) {
    // Implementation placeholder
}

void Task::setDueDate(const char* dueDate) {
    // Implementation placeholder
}

void Task::setAttachedFile(const char* file) {
    // Implementation placeholder
}

double Task::estimateEffort() const {
    // Implementation placeholder
    return 0.0;
}

void Task::setEstimationStrategy(EstimationStrategy* strategy) {
    // Implementation placeholder
}

// Constructors and destructor implementations
Task::Task() : taskId(0), description(nullptr), dependencyCount(0), estimationStrategy(nullptr) {
    title[0] = '\0';
    status[0] = '\0';
    priority[0] = '\0';
    assignee[0] = '\0';
    dueDate[0] = '\0';
    attachedFile[0] = '\0';
}

Task::Task(int id, const char* title, TaskDescription* description, const char* assignee, const char* dueDate) 
    : taskId(id), description(description), dependencyCount(0), estimationStrategy(nullptr) {
    
    strncpy(this->title, title, sizeof(this->title) - 1);
    this->title[sizeof(this->title) - 1] = '\0';
    
    strcpy(this->status, "To Do"); // Default status
    strcpy(this->priority, "Medium"); // Default priority
    
    strncpy(this->assignee, assignee, sizeof(this->assignee) - 1);
    this->assignee[sizeof(this->assignee) - 1] = '\0';
    
    strncpy(this->dueDate, dueDate, sizeof(this->dueDate) - 1);
    this->dueDate[sizeof(this->dueDate) - 1] = '\0';
    
    attachedFile[0] = '\0';
}

Task::~Task() {
    // Implementation placeholder
} 