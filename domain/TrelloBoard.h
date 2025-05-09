#ifndef TRELLO_BOARD_H
#define TRELLO_BOARD_H

#include <cstring>
using namespace std;

const int MAX_LISTS = 10;
const int MAX_MEMBERS = 20;

// Forward declarations
class List;
class Member;
class ActivityLog;

class TrelloBoard {
private:
    char id[50];
    char name[100];
    char description[500];
    List* lists[MAX_LISTS];
    int listCount;
    char members[MAX_MEMBERS][100];
    int memberCount;
    ActivityLog* activityLogs[100];
    int activityLogCount;
    bool isPrivate;
    
public:
    TrelloBoard();
    TrelloBoard(const char* id, const char* name, const char* description);
    ~TrelloBoard();
    
    // Board info getters and setters
    const char* getId() const;
    const char* getName() const;
    const char* getDescription() const;
    bool getIsPrivate() const;
    void setId(const char* id);
    void setName(const char* name);
    void setDescription(const char* description);
    void setIsPrivate(bool isPrivate);
    
    // List management
    bool addList(List* list);
    bool removeList(const char* listId);
    List* getList(const char* listId) const;
    List* getListByIndex(int index) const;
    int getListCount() const;
    bool moveList(const char* listId, int newPosition);
    
    // Member management
    bool addMember(const char* memberId);
    bool removeMember(const char* memberId);
    bool isMember(const char* memberId) const;
    void getMembers(char outMembers[][100], int& count) const;
    
    // Activity logging
    void addActivityLog(ActivityLog* log);
    ActivityLog* getRecentActivity(int count) const;
    void clearActivityLogs();
    
    // Card operations (convenience methods)
    bool moveCardBetweenLists(const char* cardId, const char* sourceListId, const char* targetListId);
    void logCardActivity(const char* cardId, const char* activityType, const char* performedBy);
};

#endif // TRELLO_BOARD_H 