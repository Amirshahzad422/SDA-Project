#ifndef AGILE_POINT_ESTIMATION_H
#define AGILE_POINT_ESTIMATION_H

#include "EstimationStrategy.h"
#include "Task.h"
#include <cstring>
using namespace std;

class AgilePointEstimation : public EstimationStrategy {
private:
    int fibonacciPoints; // Typically 1, 2, 3, 5, 8, 13, 21
    double pointValue;
    char velocityFactor[20]; // "High", "Medium", "Low"
    
public:
    AgilePointEstimation();
    AgilePointEstimation(int points, double value, const char* velocity);
    ~AgilePointEstimation();
    
    // Implementation of EstimationStrategy interface
    double estimateEffort(const Task* task) const override;
    const char* getStrategyName() const override;
    
    // Specific getters and setters
    int getFibonacciPoints() const;
    double getPointValue() const;
    const char* getVelocityFactor() const;
    void setFibonacciPoints(int points);
    void setPointValue(double value);
    void setVelocityFactor(const char* velocity);
    
    // Helper methods
    static bool isValidFibonacciPoint(int point);
    double calculateEffort() const;
};

#endif // AGILE_POINT_ESTIMATION_H 