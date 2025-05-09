#define _CRT_SECURE_NO_WARNINGS
#include "FileManager.h"
#include <cstdio>
#include <cstring>
#include <cstdlib> // For atoi function

FileManager::FileManager() {
    // Set default file paths
    strcpy(userFilePath, "users.txt");
    strcpy(taskFilePath, "tasks.txt");
    strcpy(reportFilePath, "reports.txt");
    strcpy(messageFilePath, "messages.txt");
    strcpy(boardFilePath, "boards.txt");
}

FileManager::FileManager(const char* userFile, const char* taskFile, const char* reportFile, 
                     const char* messageFile, const char* boardFile) {
    setUserFilePath(userFile);
    setTaskFilePath(taskFile);
    setReportFilePath(reportFile);
    setMessageFilePath(messageFile);
    setBoardFilePath(boardFile);
}

// Getter methods
const char* FileManager::getUserFilePath() const {
    return userFilePath;
}

const char* FileManager::getTaskFilePath() const {
    return taskFilePath;
}

const char* FileManager::getReportFilePath() const {
    return reportFilePath;
}

const char* FileManager::getMessageFilePath() const {
    return messageFilePath;
}

const char* FileManager::getBoardFilePath() const {
    return boardFilePath;
}

// Setter methods
void FileManager::setUserFilePath(const char* path) {
    strncpy(userFilePath, path, sizeof(userFilePath) - 1);
    userFilePath[sizeof(userFilePath) - 1] = '\0';
}

void FileManager::setTaskFilePath(const char* path) {
    strncpy(taskFilePath, path, sizeof(taskFilePath) - 1);
    taskFilePath[sizeof(taskFilePath) - 1] = '\0';
}

void FileManager::setReportFilePath(const char* path) {
    strncpy(reportFilePath, path, sizeof(reportFilePath) - 1);
    reportFilePath[sizeof(reportFilePath) - 1] = '\0';
}

void FileManager::setMessageFilePath(const char* path) {
    strncpy(messageFilePath, path, sizeof(messageFilePath) - 1);
    messageFilePath[sizeof(messageFilePath) - 1] = '\0';
}

void FileManager::setBoardFilePath(const char* path) {
    strncpy(boardFilePath, path, sizeof(boardFilePath) - 1);
    boardFilePath[sizeof(boardFilePath) - 1] = '\0';
}

// User data storage
bool FileManager::saveUser(const User* user) {
    if (!user) return false;
    
    // Open the file in append mode
    FILE* file = fopen(userFilePath, "a");
    if (!file) return false;
    
    // Write user data in CSV format: name,email,phone
    fprintf(file, "%s,%s,%s\n", 
            user->getName(),
            user->getEmail(),
            user->getPhone());
    
    fclose(file);
    return true;
}

bool FileManager::saveTask(const Task* task) {
    if (!task) return false;
    
    // Open the file in append mode
    FILE* file = fopen(taskFilePath, "a");
    if (!file) return false;
    
    // Write task data in CSV format: id,title,status,priority,assignee,dueDate
    fprintf(file, "%d,%s,%s,%s,%s,%s\n",
            task->getTaskId(),
            task->getTitle(),
            task->getStatus(),
            task->getPriority(),
            task->getAssignee(),
            task->getDueDate());
    
    fclose(file);
    return true;
}

bool FileManager::saveReport(const Report* report) {
    if (!report) return false;
    
    // Open the file in append mode
    FILE* file = fopen(reportFilePath, "a");
    if (!file) return false;
    
    // Write report data in CSV format: id,title,description,type,generatedBy
    fprintf(file, "%s,%s,%s,%s,%s\n",
            report->getId(),
            report->getTitle(),
            report->getDescription(),
            report->getType(),
            report->getGeneratedBy());
    
    fclose(file);
    return true;
}

bool FileManager::saveMessage(const Message* message) {
    if (!message) return false;
    
    // Open the file in append mode
    FILE* file = fopen(messageFilePath, "a");
    if (!file) return false;
    
    // Format timestamp into a string
    char timestampStr[20];
    sprintf(timestampStr, "%lld", (long long)message->getTimestamp());
    
    // Write message data in CSV format: id,sender,recipient,content,timestamp,isRead
    fprintf(file, "%s,%s,%s,%s,%s,%d\n",
            message->getId(),
            message->getSender(),
            message->getRecipient(),
            message->getContent(),
            timestampStr,
            message->getIsRead() ? 1 : 0);
    
    fclose(file);
    return true;
}

// Generic file operations
bool FileManager::appendToFile(const char* filePath, const char* content) {
    FILE* file = fopen(filePath, "a");
    if (!file) return false;
    
    fprintf(file, "%s\n", content);
    
    fclose(file);
    return true;
}

bool FileManager::readFile(const char* filePath, char* buffer, int maxSize) {
    FILE* file = fopen(filePath, "r");
    if (!file) return false;
    
    size_t bytesRead = fread(buffer, 1, maxSize - 1, file);
    buffer[bytesRead] = '\0';
    
    fclose(file);
    return true;
}

bool FileManager::fileExists(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

bool FileManager::createEmptyFile(const char* filePath) {
    FILE* file = fopen(filePath, "w");
    if (!file) return false;
    
    fclose(file);
    return true;
}

bool FileManager::deleteFile(const char* filePath) {
    return remove(filePath) == 0;
}

int FileManager::getLineCount(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (!file) return 0;
    
    int lineCount = 0;
    char buffer[1024];
    
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        lineCount++;
    }
    
    fclose(file);
    return lineCount;
} 