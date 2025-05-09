#ifndef AI_ADAPTER_H
#define AI_ADAPTER_H

// DESIGN ONLY - NO CODE IMPLEMENTATION
// This file represents the design for the AI module integration

#include <cstring>
using namespace std;

// Forward declarations for domain objects this adapter would interact with
class Task;
class User;
class Project;

// Represents the input data for AI predictions
class DomainData {
private:
    char dataType[100]; // Type of data being passed (e.g., "Task", "User", "TaskList")
    char dataContent[5000]; // JSON or serialized version of the domain data
    
public:
    DomainData();
    DomainData(const char* type, const char* content);
    
    const char* getDataType() const;
    const char* getDataContent() const;
    void setDataType(const char* type);
    void setDataContent(const char* content);
};

// Main AI adapter interface
class AIAdapter {
public:
    // Predictive task management
    virtual char* predictOptimalAssignee(Task* task) = 0;
    virtual double predictCompletionTime(Task* task) = 0;
    virtual char* suggestTaskDependencies(Task* task) = 0;
    
    // Team optimization
    virtual char* recommendTeamFormation(Project* project) = 0;
    virtual char* identifySkillGaps(User* team[], int teamSize) = 0;
    
    // General AI interface
    virtual char* predict(const DomainData& input) = 0;
    virtual void train(const DomainData* trainingData, int dataSize) = 0;
    virtual double getConfidenceScore() const = 0;
    
    virtual ~AIAdapter() {}
};

// Implementation would be provided by a concrete adapter
class MLModelAdapter : public AIAdapter {
private:
    char modelPath[200];
    char modelVersion[50];
    double confidenceThreshold;
    
public:
    MLModelAdapter();
    MLModelAdapter(const char* modelPath, const char* version, double threshold);
    ~MLModelAdapter();
    
    // Implementation of AIAdapter interface
    char* predictOptimalAssignee(Task* task) override;
    double predictCompletionTime(Task* task) override;
    char* suggestTaskDependencies(Task* task) override;
    char* recommendTeamFormation(Project* project) override;
    char* identifySkillGaps(User* team[], int teamSize) override;
    char* predict(const DomainData& input) override;
    void train(const DomainData* trainingData, int dataSize) override;
    double getConfidenceScore() const override;
    
    // ML model specific methods
    bool loadModel(const char* modelPath);
    bool updateModel(const char* newModelPath);
    void setConfidenceThreshold(double threshold);
};

#endif // AI_ADAPTER_H 