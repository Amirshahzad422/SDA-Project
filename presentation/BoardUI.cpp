#define _CRT_SECURE_NO_WARNINGS
#include "BoardUI.h"
#include <iostream>
using namespace std;

BoardUI::BoardUI() {
    boardManager = nullptr;
}

BoardUI::BoardUI(BoardManager* manager) {
    boardManager = manager;
}

BoardUI::~BoardUI() {
    // BoardManager is owned by UserInterface, don't delete it here
}

void BoardUI::run(User* currentUser) {
    if (!boardManager) {
        cout << "Error: BoardManager not initialized" << endl;
        return;
    }
    
    if (!currentUser) {
        cout << "Error: No user logged in" << endl;
        return;
    }
    
    boardManager->setCurrentUser(currentUser);
    
    clearScreen();
    cout << "Welcome to Board Management, " << currentUser->getName() << "!" << endl;
    cout << "===============================================" << endl;
    cout << endl;
    
    displayBoards();
}

void BoardUI::displayBoards() {
    clearScreen();
    displayHeader("Your Boards");
    
    // Display sample boards for demonstration
    cout << "1. Project Management" << endl;
    cout << "2. Personal Tasks" << endl;
    cout << "3. Team Collaboration" << endl;
    cout << "4. Create New Board" << endl;
    cout << "5. Go Back" << endl;
    
    int choice = getMenuChoice(5);
    
    switch (choice) {
        case 1:
        case 2:
        case 3:
            viewBoard(choice == 1 ? "project" : (choice == 2 ? "personal" : "team"));
            break;
        case 4:
            createNewBoard();
            break;
        case 5:
            return;
    }
}

void BoardUI::viewBoard(const char* boardId) {
    clearScreen();
    
    const char* boardName = "";
    if (strcmp(boardId, "project") == 0) {
        boardName = "Project Management";
    } else if (strcmp(boardId, "personal") == 0) {
        boardName = "Personal Tasks";
    } else if (strcmp(boardId, "team") == 0) {
        boardName = "Team Collaboration";
    } else {
        boardName = boardId;
    }
    
    displayHeader(boardName);
    
    // Display sample lists for this board
    cout << "Lists:" << endl;
    cout << "-------------------------------" << endl;
    
    if (strcmp(boardId, "project") == 0) {
        cout << "1. To Do" << endl;
        cout << "   - Design database schema" << endl;
        cout << "   - Create user interface mockups" << endl;
        cout << "   - Set up development environment" << endl;
        cout << endl;
        
        cout << "2. In Progress" << endl;
        cout << "   - Implement authentication module" << endl;
        cout << "   - Design API endpoints" << endl;
        cout << endl;
        
        cout << "3. Done" << endl;
        cout << "   - Project requirements gathering" << endl;
        cout << "   - Initial planning" << endl;
    } else if (strcmp(boardId, "personal") == 0) {
        cout << "1. Shopping List" << endl;
        cout << "   - Groceries" << endl;
        cout << "   - New laptop" << endl;
        cout << endl;
        
        cout << "2. Home Tasks" << endl;
        cout << "   - Clean garage" << endl;
        cout << "   - Fix kitchen sink" << endl;
    } else {
        cout << "1. Ideas" << endl;
        cout << "   - New product features" << endl;
        cout << "   - Process improvements" << endl;
        cout << endl;
        
        cout << "2. To Discuss" << endl;
        cout << "   - Budget allocation" << endl;
        cout << "   - Team structure" << endl;
    }
    
    cout << endl;
    cout << "Options:" << endl;
    cout << "1. Add new list" << endl;
    cout << "2. Add new card" << endl;
    cout << "3. Back to boards" << endl;
    
    int choice = getMenuChoice(3);
    
    if (choice == 1) {
        // Add new list
        createNewList(boardId);
        viewBoard(boardId); // Refresh board view
    } else if (choice == 2) {
        // Add new card
        addCardToList(boardId);
        viewBoard(boardId); // Refresh board view
    } else if (choice == 3) {
        return;
    }
}

void BoardUI::viewList(const char* boardId, const char* listId) {
    // Placeholder
}

void BoardUI::viewCard(const char* boardId, const char* listId, const char* cardId) {
    // Placeholder
}

void BoardUI::createNewBoard() {
    clearScreen();
    displayHeader("Create New Board");
    
    char name[100];
    char description[200];
    
    cout << "Enter board name: ";
    cin.ignore();
    cin.getline(name, 100);
    
    cout << "Enter board description (optional): ";
    cin.getline(description, 200);
    
    char visibility[10] = "";
    cout << "Board visibility (public/private): ";
    cin.getline(visibility, 10);
    
    bool isPrivate = (strcmp(visibility, "private") == 0);
    
    // Here you would actually create a board in the BoardManager in a real implementation
    cout << "Board '" << name << "' created successfully!" << endl;
    cout << "Privacy setting: " << (isPrivate ? "Private" : "Public") << endl;
    
    // Ask if user wants to add initial lists
    if (confirmAction("Do you want to add initial lists to this board?")) {
        char listName[100];
        
        cout << "Enter name for list 1 (e.g., 'To Do'): ";
        cin.getline(listName, 100);
        cout << "List '" << listName << "' added." << endl;
        
        cout << "Enter name for list 2 (e.g., 'In Progress') or leave empty to skip: ";
        cin.getline(listName, 100);
        if (listName[0] != '\0') {
            cout << "List '" << listName << "' added." << endl;
            
            cout << "Enter name for list 3 (e.g., 'Done') or leave empty to skip: ";
            cin.getline(listName, 100);
            if (listName[0] != '\0') {
                cout << "List '" << listName << "' added." << endl;
            }
        }
    }
    
    pause();
}

void BoardUI::clearScreen() {
    // Simple cross-platform clear screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void BoardUI::pause() {
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void BoardUI::displayHeader(const char* title) {
    cout << title << endl;
    for (int i = 0; i < strlen(title); i++) {
        cout << "=";
    }
    cout << endl;
}

int BoardUI::getMenuChoice(int maxOption) {
    int choice;
    do {
        cout << "Enter your choice (1-" << maxOption << "): ";
        cin >> choice;
        
        if (cin.fail() || choice < 1 || choice > maxOption) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice. Please try again." << endl;
        }
        else {
            break;
        }
    } while (true);
    
    return choice;
}

char* BoardUI::getInput(const char* prompt, char* buffer, int maxLength) {
    cout << prompt;
    cin.ignore();
    cin.getline(buffer, maxLength);
    return buffer;
}

bool BoardUI::confirmAction(const char* message) {
    cout << message << " (y/n): ";
    char choice;
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

void BoardUI::createNewList(const char* boardId) {
    clearScreen();
    displayHeader("Add New List");
    
    char listName[100];
    cout << "Enter list name: ";
    cin.ignore();
    cin.getline(listName, 100);
    
    // Here you would actually add the list to the board in a real implementation
    cout << "List '" << listName << "' added successfully!" << endl;
    
    pause();
}

void BoardUI::addCardToList(const char* boardId) {
    clearScreen();
    displayHeader("Add New Card");
    
    // Show available lists
    cout << "Choose a list to add the card to:" << endl;
    if (strcmp(boardId, "project") == 0) {
        cout << "1. To Do" << endl;
        cout << "2. In Progress" << endl;
        cout << "3. Done" << endl;
    } else if (strcmp(boardId, "personal") == 0) {
        cout << "1. Shopping List" << endl;
        cout << "2. Home Tasks" << endl;
    } else {
        cout << "1. Ideas" << endl;
        cout << "2. To Discuss" << endl;
    }
    
    int listChoice;
    cout << "Enter list number: ";
    cin >> listChoice;
    
    // Get card details
    char cardTitle[100];
    char cardDescription[500];
    
    cout << "Enter card title: ";
    cin.ignore();
    cin.getline(cardTitle, 100);
    
    cout << "Enter card description (optional): ";
    cin.getline(cardDescription, 500);
    
    // Here you would actually add the card to the list in a real implementation
    cout << "Card '" << cardTitle << "' added successfully!" << endl;
    
    pause();
} 