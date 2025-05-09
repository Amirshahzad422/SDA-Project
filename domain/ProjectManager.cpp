#define _CRT_SECURE_NO_WARNINGS
#include "ProjectManager.h"
#include <cstring>

ProjectManager::ProjectManager() : User() {
    // Initialize default values
    managedProjectCount = 0;
    specialization[0] = '\0';
    yearsOfExperience = 0;
}

ProjectManager::ProjectManager(const char* name, const char* email, const char* password,
                            const char* phone, const char* specialization, int yearsOfExperience)
    : User(name, email, password, phone) {
    
    // Initialize project manager specific data
    managedProjectCount = 0;
    
    strncpy(this->specialization, specialization, sizeof(this->specialization) - 1);
    this->specialization[sizeof(this->specialization) - 1] = '\0';
    
    this->yearsOfExperience = yearsOfExperience;
}

void ProjectManager::addManagedProject(const char* projectId) {
    if (managedProjectCount < MAX_MANAGED_PROJECTS) {
        strncpy(managedProjects[managedProjectCount], projectId, 99);
        managedProjects[managedProjectCount][99] = '\0';
        managedProjectCount++;
    }
}

void ProjectManager::removeManagedProject(const char* projectId) {
    for (int i = 0; i < managedProjectCount; i++) {
        if (strcmp(managedProjects[i], projectId) == 0) {
            // Move the last project to this position
            if (i < managedProjectCount - 1) {
                strcpy(managedProjects[i], managedProjects[managedProjectCount - 1]);
            }
            managedProjectCount--;
            break;
        }
    }
}

void ProjectManager::getManagedProjects(char out[][100], int& count) const {
    count = managedProjectCount;
    for (int i = 0; i < managedProjectCount; i++) {
        strcpy(out[i], managedProjects[i]);
    }
}

bool ProjectManager::assignTeamMember(const char* projectId, const char* teamMemberId) {
    // In a real implementation, this would update a database or file
    // For now, just return success
    return true;
}

bool ProjectManager::removeTeamMember(const char* projectId, const char* teamMemberId) {
    // In a real implementation, this would update a database or file
    // For now, just return success
    return true;
}

const char* ProjectManager::getSpecialization() const {
    return specialization;
}

int ProjectManager::getYearsOfExperience() const {
    return yearsOfExperience;
}

void ProjectManager::setSpecialization(const char* spec) {
    strncpy(specialization, spec, sizeof(specialization) - 1);
    specialization[sizeof(specialization) - 1] = '\0';
}

void ProjectManager::setYearsOfExperience(int years) {
    yearsOfExperience = years;
} 