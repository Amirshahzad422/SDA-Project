#ifndef PROJECT_H
#define PROJECT_H

#include <cstring>
using namespace std;

const int MAX_TEAM_MEMBERS = 20;
const int MAX_BOARDS = 5;

// Forward declarations
class Board;
class User;

class Project {
private:
    char id[50];
    char name[100];
    char description[500];
    char manager[100];
    char teamMembers[MAX_TEAM_MEMBERS][100];
    int teamMemberCount;
    Board* boards[MAX_BOARDS];
    int boardCount;
    char startDate[20];
    char endDate[20];
    
public:
    Project();
    Project(const char* id, const char* name, const char* description, 
           const char* manager, const char* startDate, const char* endDate);
    ~Project();
    
    // Getters
    const char* getId() const;
    const char* getName() const;
    const char* getDescription() const;
    const char* getManager() const;
    const char* getStartDate() const;
    const char* getEndDate() const;
    
    // Setters
    void setId(const char* id);
    void setName(const char* name);
    void setDescription(const char* description);
    void setManager(const char* manager);
    void setStartDate(const char* date);
    void setEndDate(const char* date);
    
    // Team management
    bool addTeamMember(const char* memberId);
    bool removeTeamMember(const char* memberId);
    void getTeamMembers(char out[][100], int& count) const;
    bool isTeamMember(const char* memberId) const;
    
    // Board management
    bool addBoard(Board* board);
    bool removeBoard(int boardIndex);
    Board* getBoard(int index) const;
    int getBoardCount() const;
};

#endif // PROJECT_H 