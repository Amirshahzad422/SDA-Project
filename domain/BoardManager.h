#ifndef BOARD_MANAGER_H
#define BOARD_MANAGER_H

#include "TrelloBoard.h"
#include "TrelloList.h"
#include "Card.h"
#include "User.h"
#include "Label.h"
#include "ActivityLog.h"
#include <cstring>
using namespace std;

const int MAX_MANAGED_BOARDS = 10;
const int MAX_PREDEFINED_LABELS = 6;

class BoardManager {
private:
    TrelloBoard* boards[MAX_MANAGED_BOARDS];
    int boardCount;
    User* currentUser;
    Label* predefinedLabels[MAX_PREDEFINED_LABELS];
    int nextBoardId;
    int nextListId;
    int nextCardId;
    
    // Helper methods
    char* generateId(const char* prefix);
    void initializePredefinedLabels();
    bool validateBoardAccess(const char* boardId, const char* memberId) const;
    
public:
    BoardManager();
    BoardManager(User* user);
    ~BoardManager();
    
    // User management
    void setCurrentUser(User* user);
    User* getCurrentUser() const;
    
    // Board management
    TrelloBoard* createBoard(const char* name, const char* description = "");
    bool deleteBoard(const char* boardId);
    TrelloBoard* getBoard(const char* boardId) const;
    void getAllBoards(TrelloBoard* outBoards[], int& count) const;
    
    // List management
    TrelloList* createList(const char* boardId, const char* name);
    bool deleteList(const char* boardId, const char* listId);
    bool moveList(const char* boardId, const char* listId, int newPosition);
    
    // Card management
    Card* createCard(const char* boardId, const char* listId, const char* title, 
                    const char* description = "");
    bool deleteCard(const char* boardId, const char* listId, const char* cardId);
    bool moveCard(const char* boardId, const char* sourceListId, const char* targetListId, 
                 const char* cardId, int newPosition = -1);
    Card* getCard(const char* boardId, const char* listId, const char* cardId) const;
    
    // Label management
    Label* createLabel(const char* name, const char* color);
    Label* getPredefinedLabel(const char* color) const;
    void addLabelToCard(const char* boardId, const char* listId, const char* cardId, 
                       Label* label);
    
    // Activity logging
    void logActivity(const char* boardId, const char* type, const char* entityId, 
                   const char* description);
    void getRecentActivity(const char* boardId, ActivityLog* outLogs[], int count, 
                         int& resultCount) const;
    
    // Card search
    void searchCards(const char* boardId, const char* searchText, Card* results[], 
                    int& resultCount) const;
    void getCardsByDueDate(const char* boardId, time_t fromDate, time_t toDate, 
                          Card* results[], int& resultCount) const;
    void getCardsByMember(const char* boardId, const char* memberId, Card* results[], 
                         int& resultCount) const;
    
    // Template methods
    TrelloBoard* createBoardFromTemplate(const char* templateName);
    void applyTemplate(TrelloBoard* board, const char* templateName);
    
    // Board sharing
    bool inviteMember(const char* boardId, const char* memberId, const char* role = "Member");
    bool removeMember(const char* boardId, const char* memberId);
};

#endif // BOARD_MANAGER_H 