#ifndef HOURS_BASED_ESTIMATION_H
#define HOURS_BASED_ESTIMATION_H

#include "EstimationStrategy.h"
#include "Task.h"
#include <cstring>
using namespace std;

class HoursBasedEstimation : public EstimationStrategy {
private:
    double hourlyRate;
    int complexityFactor; // 1-5 scale
    
public:
    HoursBasedEstimation();
    HoursBasedEstimation(double rate, int complexity);
    ~HoursBasedEstimation();
    
    // Implementation of EstimationStrategy interface
    double estimateEffort(const Task* task) const override;
    const char* getStrategyName() const override;
    
    // Specific getters and setters
    double getHourlyRate() const;
    int getComplexityFactor() const;
    void setHourlyRate(double rate);
    void setComplexityFactor(int factor);
};

#endif // HOURS_BASED_ESTIMATION_H 