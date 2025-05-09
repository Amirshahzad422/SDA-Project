#define _CRT_SECURE_NO_WARNINGS
#include "CardAIAdapter.h"
#include <cstring>
#include <cstdio>

// Forward declarations
class Card;
class TrelloBoard;
class TrelloList;

// CardPredictionData implementation
CardPredictionData::CardPredictionData() {
    cardTitle[0] = '\0';
    cardDescription[0] = '\0';
    boardId[0] = '\0';
    listId[0] = '\0';
    memberId[0] = '\0';
    labelData[0] = '\0';
    historyData[0] = '\0';
}

CardPredictionData::CardPredictionData(const Card* card, const TrelloBoard* board, const TrelloList* list) {
    // In a real implementation, this would extract data from the actual objects
    // For now, just set placeholder values
    
    strcpy(cardTitle, "Sample Card");
    strcpy(cardDescription, "This is a sample card description");
    strcpy(boardId, "board-123");
    strcpy(listId, "list-456");
    strcpy(memberId, "member-789");
    strcpy(labelData, "bug,high,frontend");
    strcpy(historyData, "created:2023-05-01,updated:2023-05-10");
}

// Getters
const char* CardPredictionData::getCardTitle() const {
    return cardTitle;
}

const char* CardPredictionData::getCardDescription() const {
    return cardDescription;
}

const char* CardPredictionData::getBoardId() const {
    return boardId;
}

const char* CardPredictionData::getListId() const {
    return listId;
}

const char* CardPredictionData::getMemberId() const {
    return memberId;
}

const char* CardPredictionData::getLabelData() const {
    return labelData;
}

const char* CardPredictionData::getHistoryData() const {
    return historyData;
}

// Setters
void CardPredictionData::setCardTitle(const char* title) {
    strncpy(cardTitle, title, sizeof(cardTitle) - 1);
    cardTitle[sizeof(cardTitle) - 1] = '\0';
}

void CardPredictionData::setCardDescription(const char* description) {
    strncpy(cardDescription, description, sizeof(cardDescription) - 1);
    cardDescription[sizeof(cardDescription) - 1] = '\0';
}

void CardPredictionData::setBoardId(const char* boardId) {
    strncpy(this->boardId, boardId, sizeof(this->boardId) - 1);
    this->boardId[sizeof(this->boardId) - 1] = '\0';
}

void CardPredictionData::setListId(const char* listId) {
    strncpy(this->listId, listId, sizeof(this->listId) - 1);
    this->listId[sizeof(this->listId) - 1] = '\0';
}

void CardPredictionData::setMemberId(const char* memberId) {
    strncpy(this->memberId, memberId, sizeof(this->memberId) - 1);
    this->memberId[sizeof(this->memberId) - 1] = '\0';
}

void CardPredictionData::setLabelData(const char* labelData) {
    strncpy(this->labelData, labelData, sizeof(this->labelData) - 1);
    this->labelData[sizeof(this->labelData) - 1] = '\0';
}

void CardPredictionData::setHistoryData(const char* historyData) {
    strncpy(this->historyData, historyData, sizeof(this->historyData) - 1);
    this->historyData[sizeof(this->historyData) - 1] = '\0';
}

// Utility methods
char* CardPredictionData::serialize() const {
    // Allocate memory for the serialized string (must be freed by caller)
    char* result = new char[2000];
    
    // Format: title|description|boardId|listId|memberId|labelData|historyData
    sprintf(result, "%s|%s|%s|%s|%s|%s|%s",
            cardTitle, cardDescription, boardId, listId, memberId, labelData, historyData);
    
    return result;
}

bool CardPredictionData::deserialize(const char* data) {
    if (!data) return false;
    
    // Parse the serialized string
    char buffer[2000];
    strncpy(buffer, data, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    
    // Format: title|description|boardId|listId|memberId|labelData|historyData
    char* token = strtok(buffer, "|");
    if (token) {
        setCardTitle(token);
        
        token = strtok(nullptr, "|");
        if (token) setCardDescription(token);
        else return false;
        
        token = strtok(nullptr, "|");
        if (token) setBoardId(token);
        else return false;
        
        token = strtok(nullptr, "|");
        if (token) setListId(token);
        else return false;
        
        token = strtok(nullptr, "|");
        if (token) setMemberId(token);
        else return false;
        
        token = strtok(nullptr, "|");
        if (token) setLabelData(token);
        else return false;
        
        token = strtok(nullptr, "|");
        if (token) setHistoryData(token);
        else return false;
        
        return true;
    }
    
    return false;
} 