#ifndef CARD_AI_ADAPTER_H
#define CARD_AI_ADAPTER_H

// DESIGN ONLY - NO CODE IMPLEMENTATION
// This file represents the design for the AI module integration for card predictions

#include <cstring>
using namespace std;

// Forward declarations
class Card;
class TrelloBoard;
class TrelloList;
class Member;

// Input data structure for card predictions
class CardPredictionData {
private:
    char cardTitle[100];
    char cardDescription[1000];
    char boardId[50];
    char listId[50];
    char memberId[50];
    char labelData[500]; // Serialized label data
    char historyData[1000]; // Serialized card history
    
public:
    CardPredictionData();
    CardPredictionData(const Card* card, const TrelloBoard* board, const TrelloList* list);
    
    // Getters and setters
    const char* getCardTitle() const;
    const char* getCardDescription() const;
    const char* getBoardId() const;
    const char* getListId() const;
    const char* getMemberId() const;
    const char* getLabelData() const;
    const char* getHistoryData() const;
    
    void setCardTitle(const char* title);
    void setCardDescription(const char* description);
    void setBoardId(const char* boardId);
    void setListId(const char* listId);
    void setMemberId(const char* memberId);
    void setLabelData(const char* labelData);
    void setHistoryData(const char* historyData);
    
    // Utility methods
    char* serialize() const;
    bool deserialize(const char* data);
};

// Main AI adapter interface for card predictions
class CardAIAdapter {
public:
    virtual ~CardAIAdapter() {}
    
    // Card prediction methods
    virtual char* predictOptimalAssignee(const Card* card, const TrelloBoard* board) = 0;
    virtual int predictEstimatedHours(const Card* card) = 0;
    virtual char* suggestLabels(const Card* card) = 0;
    virtual char* predictDueDate(const Card* card) = 0;
    virtual char* suggestSimilarCards(const Card* card, const TrelloBoard* board) = 0;
    
    // Priority prediction
    virtual char* predictPriority(const Card* card) = 0;
    
    // General interface
    virtual char* predict(const CardPredictionData& input) = 0;
    virtual void train(const CardPredictionData* trainingData, int dataSize) = 0;
    virtual double getConfidenceScore() const = 0;
};

// Concrete implementation that would interface with ML model
class CardMLAdapter : public CardAIAdapter {
private:
    char modelPath[200];
    double confidenceThreshold;
    char apiEndpoint[200];
    char apiKey[100];
    
public:
    CardMLAdapter();
    CardMLAdapter(const char* modelPath, double confidenceThreshold);
    ~CardMLAdapter();
    
    // Implementation of CardAIAdapter interface
    char* predictOptimalAssignee(const Card* card, const TrelloBoard* board) override;
    int predictEstimatedHours(const Card* card) override;
    char* suggestLabels(const Card* card) override;
    char* predictDueDate(const Card* card) override;
    char* suggestSimilarCards(const Card* card, const TrelloBoard* board) override;
    char* predictPriority(const Card* card) override;
    char* predict(const CardPredictionData& input) override;
    void train(const CardPredictionData* trainingData, int dataSize) override;
    double getConfidenceScore() const override;
    
    // ML-specific methods
    bool loadModel(const char* path);
    bool callExternalAPI(const char* endpoint, const char* data, char* response, int maxLength);
    void setConfidenceThreshold(double threshold);
    void setAPICredentials(const char* endpoint, const char* key);
};

#endif // CARD_AI_ADAPTER_H 