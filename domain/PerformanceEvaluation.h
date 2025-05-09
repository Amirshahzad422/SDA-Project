#ifndef PERFORMANCE_EVALUATION_H
#define PERFORMANCE_EVALUATION_H

#include <cstring>
#include <ctime>
using namespace std;

const int MAX_FEEDBACK = 10;
const int MAX_METRICS = 5;

// Forward declaration
class Feedback;

class PerformanceEvaluation {
private:
    char id[50];
    char employeeId[100];
    char evaluatorId[100];
    char period[50]; // e.g., "Q1 2025"
    
    struct Metric {
        char name[100];
        int score; // 1-10 scale
        char comment[500];
    };
    
    Metric metrics[MAX_METRICS];
    int metricCount;
    Feedback* relatedFeedback[MAX_FEEDBACK];
    int feedbackCount;
    time_t creationDate;
    bool isCompleted;
    
public:
    PerformanceEvaluation();
    PerformanceEvaluation(const char* id, const char* employeeId, 
                         const char* evaluatorId, const char* period);
    ~PerformanceEvaluation();
    
    // Getters
    const char* getId() const;
    const char* getEmployeeId() const;
    const char* getEvaluatorId() const;
    const char* getPeriod() const;
    time_t getCreationDate() const;
    bool getIsCompleted() const;
    
    // Setters
    void setId(const char* id);
    void setEmployeeId(const char* employeeId);
    void setEvaluatorId(const char* evaluatorId);
    void setPeriod(const char* period);
    void setCompleted(bool completed);
    
    // Metrics management
    bool addMetric(const char* name, int score, const char* comment);
    bool updateMetric(int index, int score, const char* comment);
    Metric getMetric(int index) const;
    int getMetricCount() const;
    
    // Feedback management
    bool addFeedback(Feedback* feedback);
    Feedback* getFeedback(int index) const;
    int getFeedbackCount() const;
    
    // Summary methods
    double getAverageScore() const;
    const char* getOverallRating() const;
    char* getSummary() const;
};

#endif // PERFORMANCE_EVALUATION_H 