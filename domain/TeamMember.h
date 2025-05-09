#ifndef TEAM_MEMBER_H
#define TEAM_MEMBER_H

#include "User.h"
#include <cstring>
using namespace std;

const int MAX_SKILLS = 10;
const int MAX_ASSIGNED_TASKS = 20;

class TeamMember : public User {
private:
    char skills[MAX_SKILLS][100];
    int skillCount;
    char assignedTasks[MAX_ASSIGNED_TASKS][100];
    int assignedTaskCount;
    char role[100];
    char department[100];

public:
    TeamMember();
    TeamMember(const char* name, const char* email, const char* password,
              const char* phone, const char* role, const char* department);

    // Skills management
    void addSkill(const char* skill);
    void removeSkill(const char* skill);
    bool hasSkill(const char* skill) const;
    void getSkills(char out[][100], int& count) const;

    // Task management
    void assignTask(const char* taskId);
    void removeTask(const char* taskId);
    bool hasTask(const char* taskId) const;
    void getAssignedTasks(char out[][100], int& count) const;

    // Role and department
    const char* getRole() const;
    const char* getDepartment() const;
    void setRole(const char* newRole);
    void setDepartment(const char* newDepartment);
};

#endif // TEAM_MEMBER_H 