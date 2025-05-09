#ifndef FILE_ATTACHMENT_H
#define FILE_ATTACHMENT_H

#include <cstring>
#include <ctime>
using namespace std;

class FileAttachment {
private:
    char fileName[200];
    char filePath[500];
    char fileType[50];
    long fileSize;
    time_t uploadTimestamp;
    char uploadedBy[100];
    
public:
    FileAttachment();
    FileAttachment(const char* name, const char* path, const char* type, 
                  long size, const char* uploader);
    ~FileAttachment();
    
    // Getters
    const char* getFileName() const;
    const char* getFilePath() const;
    const char* getFileType() const;
    long getFileSize() const;
    time_t getUploadTimestamp() const;
    const char* getUploadedBy() const;
    
    // Setters
    void setFileName(const char* name);
    void setFilePath(const char* path);
    void setFileType(const char* type);
    void setFileSize(long size);
    void setUploadedBy(const char* uploader);
    
    // File operations
    bool copyToLocalPath(const char* destinationPath) const;
    char* getFormattedUploadDate() const;
    char* getFormattedFileSize() const;
    bool exists() const;
};

#endif // FILE_ATTACHMENT_H 