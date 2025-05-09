#ifndef TASK_DESCRIPTION_H
#define TASK_DESCRIPTION_H

#include <cstring>
using namespace std;

const int MAX_COMMENTS = 20;
const int MAX_ATTACHMENTS = 10;

// Forward declarations
class Comment;
class FileAttachment;

class TaskDescription {
private:
    char text[1000];
    Comment* comments[MAX_COMMENTS];
    int commentCount;
    FileAttachment* attachments[MAX_ATTACHMENTS];
    int attachmentCount;

public:
    TaskDescription();
    TaskDescription(const char* text);
    ~TaskDescription();
    
    // Basic text description
    const char* getText() const;
    void setText(const char* text);
    
    // Comments management
    void addComment(Comment* comment);
    void removeComment(int commentIndex);
    Comment* getComment(int index) const;
    int getCommentCount() const;
    
    // Attachments management
    void addAttachment(FileAttachment* attachment);
    void removeAttachment(int attachmentIndex);
    FileAttachment* getAttachment(int index) const;
    int getAttachmentCount() const;
};

#endif // TASK_DESCRIPTION_H 