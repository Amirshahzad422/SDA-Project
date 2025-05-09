#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstring>
#include <ctime>
using namespace std;

class Message {
private:
    char id[50];
    char sender[100];
    char recipient[100];
    char content[1000];
    time_t timestamp;
    bool isRead;
    
public:
    Message();
    Message(const char* id, const char* sender, const char* recipient, 
           const char* content);
    ~Message();
    
    // Getters
    const char* getId() const;
    const char* getSender() const;
    const char* getRecipient() const;
    const char* getContent() const;
    time_t getTimestamp() const;
    bool getIsRead() const;
    
    // Setters
    void setId(const char* id);
    void setSender(const char* sender);
    void setRecipient(const char* recipient);
    void setContent(const char* content);
    void markAsRead();
    
    // Utility methods
    char* getFormattedTimestamp() const;
    bool isForUser(const char* userId) const;
};

#endif // MESSAGE_H 