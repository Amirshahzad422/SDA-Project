#define _CRT_SECURE_NO_WARNINGS
#include "Member.h"
#include <cstring>

Member::Member() {
    id[0] = '\0';
    username[0] = '\0';
    fullName[0] = '\0';
    email[0] = '\0';
    role[0] = '\0';
    avatarPath[0] = '\0';
    boardCount = 0;
}

Member::Member(const char* id, const char* username, const char* fullName, const char* email) {
    strncpy(this->id, id, sizeof(this->id) - 1);
    this->id[sizeof(this->id) - 1] = '\0';
    
    strncpy(this->username, username, sizeof(this->username) - 1);
    this->username[sizeof(this->username) - 1] = '\0';
    
    strncpy(this->fullName, fullName, sizeof(this->fullName) - 1);
    this->fullName[sizeof(this->fullName) - 1] = '\0';
    
    strncpy(this->email, email, sizeof(this->email) - 1);
    this->email[sizeof(this->email) - 1] = '\0';
    
    strcpy(this->role, "Member");
    avatarPath[0] = '\0';
    boardCount = 0;
}

Member::~Member() {
    // Nothing to clean up
}

const char* Member::getId() const {
    return id;
}

const char* Member::getUsername() const {
    return username;
}

const char* Member::getFullName() const {
    return fullName;
}

const char* Member::getEmail() const {
    return email;
}

const char* Member::getRole() const {
    return role;
}

const char* Member::getAvatarPath() const {
    return avatarPath;
}

void Member::setId(const char* id) {
    strncpy(this->id, id, sizeof(this->id) - 1);
    this->id[sizeof(this->id) - 1] = '\0';
}

void Member::setUsername(const char* username) {
    strncpy(this->username, username, sizeof(this->username) - 1);
    this->username[sizeof(this->username) - 1] = '\0';
}

void Member::setFullName(const char* fullName) {
    strncpy(this->fullName, fullName, sizeof(this->fullName) - 1);
    this->fullName[sizeof(this->fullName) - 1] = '\0';
}

void Member::setEmail(const char* email) {
    strncpy(this->email, email, sizeof(this->email) - 1);
    this->email[sizeof(this->email) - 1] = '\0';
}

void Member::setRole(const char* role) {
    strncpy(this->role, role, sizeof(this->role) - 1);
    this->role[sizeof(this->role) - 1] = '\0';
}

void Member::setAvatarPath(const char* path) {
    strncpy(this->avatarPath, path, sizeof(this->avatarPath) - 1);
    this->avatarPath[sizeof(this->avatarPath) - 1] = '\0';
}

bool Member::addBoard(const char* boardId) {
    if (boardCount >= MAX_BOARDS) {
        return false;
    }
    
    strncpy(joinedBoardIds[boardCount], boardId, 49);
    joinedBoardIds[boardCount][49] = '\0';
    boardCount++;
    return true;
}

bool Member::removeBoard(const char* boardId) {
    for (int i = 0; i < boardCount; i++) {
        if (strcmp(joinedBoardIds[i], boardId) == 0) {
            // Move the last board to this position
            if (i < boardCount - 1) {
                strcpy(joinedBoardIds[i], joinedBoardIds[boardCount - 1]);
            }
            boardCount--;
            return true;
        }
    }
    return false;
}

bool Member::isMemberOfBoard(const char* boardId) const {
    for (int i = 0; i < boardCount; i++) {
        if (strcmp(joinedBoardIds[i], boardId) == 0) {
            return true;
        }
    }
    return false;
}

void Member::getBoards(char outBoards[][50], int& count) const {
    count = boardCount;
    for (int i = 0; i < boardCount; i++) {
        strcpy(outBoards[i], joinedBoardIds[i]);
    }
}

int Member::getBoardCount() const {
    return boardCount;
}

bool Member::isAdmin() const {
    return strcmp(role, "Admin") == 0;
}

char* Member::getInitials() const {
    static char initials[3] = {0};
    
    if (fullName[0] != '\0') {
        initials[0] = fullName[0];
        
        // Find the space for the last name
        const char* space = strchr(fullName, ' ');
        if (space != nullptr && *(space + 1) != '\0') {
            initials[1] = *(space + 1);
        } else {
            initials[1] = '\0';
        }
        
        initials[2] = '\0';
    } else if (username[0] != '\0') {
        initials[0] = username[0];
        initials[1] = '\0';
    } else {
        initials[0] = '\0';
    }
    
    return initials;
}

bool Member::hasPermissionForAction(const char* actionType) const {
    // Simple permission system:
    // Admin can do anything
    if (isAdmin()) {
        return true;
    }
    
    // Regular members can do most operations except admin operations
    if (strcmp(actionType, "DeleteBoard") == 0 ||
        strcmp(actionType, "ManageMembers") == 0 ||
        strcmp(actionType, "ManageSettings") == 0) {
        return false;
    }
    
    return true;
} 