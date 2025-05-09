#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "../domain/User.h"
#include "../domain/Task.h"
#include "../domain/Report.h"
#include "../domain/Message.h"

class FileManager {
private:
    char userFilePath[200];
    char taskFilePath[200];
    char reportFilePath[200];
    char messageFilePath[200];
    char boardFilePath[200];

public:
    // Constructors
    FileManager();
    FileManager(const char* userFile, const char* taskFile, const char* reportFile, 
               const char* messageFile, const char* boardFile);
    
    // Getter methods
    const char* getUserFilePath() const;
    const char* getTaskFilePath() const;
    const char* getReportFilePath() const;
    const char* getMessageFilePath() const;
    const char* getBoardFilePath() const;
    
    // Setter methods
    void setUserFilePath(const char* path);
    void setTaskFilePath(const char* path);
    void setReportFilePath(const char* path);
    void setMessageFilePath(const char* path);
    void setBoardFilePath(const char* path);
    
    // Domain-specific file operations
    bool saveUser(const User* user);
    bool saveTask(const Task* task);
    bool saveReport(const Report* report);
    bool saveMessage(const Message* message);
    
    // Generic file operations
    bool appendToFile(const char* filePath, const char* content);
    bool readFile(const char* filePath, char* buffer, int maxSize);
    bool fileExists(const char* filePath);
    bool createEmptyFile(const char* filePath);
    bool deleteFile(const char* filePath);
    int getLineCount(const char* filePath);
};

#endif // FILE_MANAGER_H 