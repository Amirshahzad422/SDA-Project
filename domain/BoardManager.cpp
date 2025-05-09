#define _CRT_SECURE_NO_WARNINGS
#include "BoardManager.h"

BoardManager::BoardManager() {
    // Initialize members
    currentUser = nullptr;
    boardCount = 0;
    nextBoardId = 1;
    nextListId = 1;
    nextCardId = 1;
}

BoardManager::BoardManager(User* user) {
    // Initialize members
    currentUser = user;
    boardCount = 0;
    nextBoardId = 1;
    nextListId = 1;
    nextCardId = 1;
}

BoardManager::~BoardManager() {
    // Cleanup as needed
}

void BoardManager::setCurrentUser(User* user) {
    currentUser = user;
}

User* BoardManager::getCurrentUser() const {
    return currentUser;
} 