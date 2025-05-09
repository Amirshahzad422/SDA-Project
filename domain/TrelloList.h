#ifndef TRELLO_LIST_H
#define TRELLO_LIST_H

#include <cstring>
using namespace std;

const int MAX_CARDS = 50;

// Forward declarations
class Card;

class TrelloList {
private:
    char id[50];
    char name[100];
    Card* cards[MAX_CARDS];
    int cardCount;
    int position;
    bool isArchived;
    
public:
    TrelloList();
    TrelloList(const char* id, const char* name, int position = 0);
    ~TrelloList();
    
    // List info getters and setters
    const char* getId() const;
    const char* getName() const;
    int getPosition() const;
    bool getIsArchived() const;
    void setId(const char* id);
    void setName(const char* name);
    void setPosition(int position);
    void setIsArchived(bool archived);
    
    // Card management
    bool addCard(Card* card);
    bool removeCard(const char* cardId);
    bool moveCard(const char* cardId, int newPosition);
    Card* getCard(const char* cardId) const;
    Card* getCardByIndex(int index) const;
    int getCardCount() const;
    
    // Card retrieval by criteria
    void getCardsByLabel(const char* labelId, Card* outCards[], int& count) const;
    void getCardsByMember(const char* memberId, Card* outCards[], int& count) const;
    void getCardsByDueDate(const char* date, Card* outCards[], int& count) const;
    
    // Bulk operations
    void archiveAllCards();
    void moveAllCards(TrelloList* targetList);
    void sortCardsByDueDate();
};

#endif // TRELLO_LIST_H 