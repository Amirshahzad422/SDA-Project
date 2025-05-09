#ifndef BOARD_STORAGE_HANDLER_H
#define BOARD_STORAGE_HANDLER_H

#include "../domain/TrelloBoard.h"
#include "../domain/TrelloList.h"
#include "../domain/Card.h"
#include "../domain/Member.h"
#include "../domain/Label.h"
#include <cstring>
using namespace std;

class BoardStorageHandler {
private:
    char boardsFilePath[200];
    char listsFilePath[200];
    char cardsFilePath[200];
    char membersFilePath[200];
    char labelsFilePath[200];
    char activityLogsFilePath[200];
    
    // Helper methods
    bool saveToFile(const char* filePath, const char* data);
    bool readFromFile(const char* filePath, char* buffer, int bufferSize);
    char* serializeBoard(const TrelloBoard* board) const;
    char* serializeList(const TrelloList* list) const;
    char* serializeCard(const Card* card) const;
    char* serializeMember(const Member* member) const;
    TrelloBoard* deserializeBoard(const char* data);
    TrelloList* deserializeList(const char* data);
    Card* deserializeCard(const char* data);
    Member* deserializeMember(const char* data);
    
public:
    BoardStorageHandler();
    BoardStorageHandler(const char* boardsPath, const char* listsPath, const char* cardsPath,
                      const char* membersPath, const char* labelsPath, const char* logsPath);
    ~BoardStorageHandler();
    
    // Path setters
    void setBoardsFilePath(const char* path);
    void setListsFilePath(const char* path);
    void setCardsFilePath(const char* path);
    void setMembersFilePath(const char* path);
    void setLabelsFilePath(const char* path);
    void setActivityLogsFilePath(const char* path);
    
    // Board operations
    bool saveBoard(const TrelloBoard* board);
    TrelloBoard* loadBoard(const char* boardId);
    bool loadAllBoards(TrelloBoard* boards[], int& count);
    bool deleteBoard(const char* boardId);
    
    // List operations
    bool saveList(const TrelloList* list, const char* boardId);
    TrelloList* loadList(const char* listId, const char* boardId);
    bool loadListsForBoard(const char* boardId, TrelloList* lists[], int& count);
    bool deleteList(const char* listId, const char* boardId);
    
    // Card operations
    bool saveCard(const Card* card, const char* listId, const char* boardId);
    Card* loadCard(const char* cardId, const char* listId, const char* boardId);
    bool loadCardsForList(const char* listId, const char* boardId, Card* cards[], int& count);
    bool deleteCard(const char* cardId, const char* listId, const char* boardId);
    
    // Member operations
    bool saveMember(const Member* member);
    Member* loadMember(const char* memberId);
    bool loadAllMembers(Member* members[], int& count);
    bool deleteMember(const char* memberId);
    
    // Activity log operations
    bool saveActivityLogs(const TrelloBoard* board);
    bool loadActivityLogs(const char* boardId, ActivityLog* logs[], int& count);
    
    // Utility methods
    bool exportBoardToJSON(const TrelloBoard* board, const char* outputPath);
    bool importBoardFromJSON(const char* inputPath, TrelloBoard* board);
    bool backupAllData(const char* backupDirectory);
    bool restoreFromBackup(const char* backupDirectory);
};

#endif // BOARD_STORAGE_HANDLER_H 