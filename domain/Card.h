#ifndef CARD_H
#define CARD_H

#include <cstring>
#include <ctime>
using namespace std;

const int MAX_LABELS = 10;
const int CARD_MAX_MEMBERS = 10;
const int MAX_COMMENTS = 50;
const int MAX_ATTACHMENTS = 10;
const int MAX_CHECKLISTS = 5;

// Forward declarations
class Label;
class Member;
class Comment;
class Attachment;
class Checklist;

class Card {
private:
    char id[50];
    char title[100];
    char description[1000];
    Label* labels[MAX_LABELS];
    int labelCount;
    char assignedMembers[CARD_MAX_MEMBERS][100];
    int memberCount;
    Comment* comments[MAX_COMMENTS];
    int commentCount;
    char attachmentPaths[MAX_ATTACHMENTS][200];
    int attachmentCount;
    Checklist* checklists[MAX_CHECKLISTS];
    int checklistCount;
    time_t dueDate;
    bool isComplete;
    bool isArchived;
    int position;
    
public:
    Card();
    Card(const char* id, const char* title, const char* description = "");
    ~Card();
    
    // Card info getters and setters
    const char* getId() const;
    const char* getTitle() const;
    const char* getDescription() const;
    time_t getDueDate() const;
    bool getIsComplete() const;
    bool getIsArchived() const;
    int getPosition() const;
    void setId(const char* id);
    void setTitle(const char* title);
    void setDescription(const char* description);
    void setDueDate(time_t dueDate);
    void setIsComplete(bool complete);
    void setIsArchived(bool archived);
    void setPosition(int position);
    
    // Label management
    bool addLabel(Label* label);
    bool removeLabel(const char* labelId);
    bool hasLabel(const char* labelId) const;
    void getLabels(Label* outLabels[], int& count) const;
    
    // Member management
    bool addMember(const char* memberId);
    bool removeMember(const char* memberId);
    bool hasMember(const char* memberId) const;
    void getMembers(char outMembers[][100], int& count) const;
    
    // Comment management
    bool addComment(Comment* comment);
    bool removeComment(int commentIndex);
    Comment* getComment(int index) const;
    int getCommentCount() const;
    
    // Attachment management
    bool addAttachment(const char* filePath);
    bool removeAttachment(int attachmentIndex);
    const char* getAttachment(int index) const;
    int getAttachmentCount() const;
    
    // Checklist management
    bool addChecklist(Checklist* checklist);
    bool removeChecklist(int checklistIndex);
    Checklist* getChecklist(int index) const;
    int getChecklistCount() const;
    
    // Utility methods
    char* getFormattedDueDate() const;
    bool isDueSoon(int daysThreshold = 3) const;
    bool isOverdue() const;
    float getChecklistCompletionPercentage() const;
};

#endif // CARD_H 