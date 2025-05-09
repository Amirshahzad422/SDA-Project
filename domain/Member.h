#ifndef MEMBER_H
#define MEMBER_H

#include <cstring>
using namespace std;

const int MAX_BOARDS = 20;

class Member {
private:
    char id[50];
    char username[100];
    char fullName[100];
    char email[100];
    char role[50]; // "Admin", "Member", "Observer"
    char joinedBoardIds[MAX_BOARDS][50];
    int boardCount;
    char avatarPath[200];
    
public:
    Member();
    Member(const char* id, const char* username, const char* fullName, const char* email);
    ~Member();
    
    // Member info getters and setters
    const char* getId() const;
    const char* getUsername() const;
    const char* getFullName() const;
    const char* getEmail() const;
    const char* getRole() const;
    const char* getAvatarPath() const;
    void setId(const char* id);
    void setUsername(const char* username);
    void setFullName(const char* fullName);
    void setEmail(const char* email);
    void setRole(const char* role);
    void setAvatarPath(const char* path);
    
    // Board management
    bool addBoard(const char* boardId);
    bool removeBoard(const char* boardId);
    bool isMemberOfBoard(const char* boardId) const;
    void getBoards(char outBoards[][50], int& count) const;
    int getBoardCount() const;
    
    // Utility methods
    bool isAdmin() const;
    char* getInitials() const;
    bool hasPermissionForAction(const char* actionType) const;
};

#endif // MEMBER_H 