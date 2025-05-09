#ifndef BOARD_UI_H
#define BOARD_UI_H

#include "../domain/BoardManager.h"
#include "../domain/User.h"
using namespace std;

class BoardUI {
private:
    BoardManager* boardManager;
    
    // Helper methods for UI
    void clearScreen();
    void pause();
    void displayHeader(const char* title);
    int getMenuChoice(int maxOption);
    char* getInput(const char* prompt, char* buffer, int maxLength);
    bool confirmAction(const char* message);
    
    // Menu display methods
    void displayMainMenu();
    void displayBoardMenu(const char* boardId);
    void displayListMenu(const char* boardId, const char* listId);
    void displayCardMenu(const char* boardId, const char* listId, const char* cardId);
    void displayLabelMenu(const char* boardId, const char* listId, const char* cardId);
    void displayMemberMenu(const char* boardId);
    
    // Card operation methods
    void createNewCard(const char* boardId, const char* listId);
    void editCardDetails(const char* boardId, const char* listId, const char* cardId);
    void moveCardUI(const char* boardId, const char* sourceListId, const char* cardId);
    void assignMemberToCard(const char* boardId, const char* listId, const char* cardId);
    void addLabelToCardUI(const char* boardId, const char* listId, const char* cardId);
    void addCommentToCard(const char* boardId, const char* listId, const char* cardId);
    void addChecklistToCard(const char* boardId, const char* listId, const char* cardId);
    
    // List operation methods
    void editListName(const char* boardId, const char* listId);
    void moveListUI(const char* boardId, const char* listId);
    void archiveList(const char* boardId, const char* listId);
    
    // Board operation methods
    void editBoardDetails(const char* boardId);
    void inviteMemberUI(const char* boardId);
    void viewBoardActivity(const char* boardId);
    
    // Search and filter methods
    void searchBoardCards(const char* boardId);
    void filterCardsByDueDate(const char* boardId);
    void filterCardsByMember(const char* boardId);
    void filterCardsByLabel(const char* boardId);
    
public:
    BoardUI();
    BoardUI(BoardManager* manager);
    ~BoardUI();
    
    // Main UI flow
    void run(User* currentUser);
    void displayBoards();
    void viewBoard(const char* boardId);
    void viewList(const char* boardId, const char* listId);
    void viewCard(const char* boardId, const char* listId, const char* cardId);
    void createNewBoard();
    
    // New functionality
    void createNewList(const char* boardId);
    void addCardToList(const char* boardId);
};

#endif // BOARD_UI_H 