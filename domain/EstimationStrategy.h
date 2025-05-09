#ifndef ESTIMATION_STRATEGY_H
#define ESTIMATION_STRATEGY_H

using namespace std;

// Forward declaration
class Task;

class EstimationStrategy {
public:
    virtual ~EstimationStrategy() {}
    
    // Strategy method to estimate task effort
    virtual double estimateEffort(const Task* task) const = 0;
    
    // Factory method to get strategy name
    virtual const char* getStrategyName() const = 0;
};

#endif // ESTIMATION_STRATEGY_H 