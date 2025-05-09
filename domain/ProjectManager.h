#ifndef PROJECT_MANAGER_H
#define PROJECT_MANAGER_H

#include "User.h"
#include <cstring>
using namespace std;

const int MAX_MANAGED_PROJECTS = 10;

class ProjectManager : public User {
private:
    char managedProjects[MAX_MANAGED_PROJECTS][100];
    int managedProjectCount;
    char specialization[100];
    int yearsOfExperience;

public:
    ProjectManager();
    ProjectManager(const char* name, const char* email, const char* password,
                  const char* phone, const char* specialization, int yearsOfExperience);

    // Project management
    void addManagedProject(const char* projectId);
    void removeManagedProject(const char* projectId);
    void getManagedProjects(char out[][100], int& count) const;

    // Team management
    bool assignTeamMember(const char* projectId, const char* teamMemberId);
    bool removeTeamMember(const char* projectId, const char* teamMemberId);

    // Experience and specialization
    const char* getSpecialization() const;
    int getYearsOfExperience() const;
    void setSpecialization(const char* spec);
    void setYearsOfExperience(int years);
};

#endif // PROJECT_MANAGER_H 