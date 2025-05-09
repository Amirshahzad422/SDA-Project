#ifndef MESSAGE_SERVICE_H
#define MESSAGE_SERVICE_H

#include "Message.h"
#include <cstring>
using namespace std;

const int MAX_MESSAGES = 100;

class MessageService {
private:
    Message* messages[MAX_MESSAGES];
    int messageCount;
    
public:
    MessageService();
    ~MessageService();
    
    // Message operations
    bool sendMessage(const char* sender, const char* recipient, const char* content);
    bool deleteMessage(const char* messageId);
    
    // Message retrieval
    Message* findMessageById(const char* messageId) const;
    void getMessagesForUser(const char* userId, Message* outMessages[], int& count) const;
    void getUnreadMessagesForUser(const char* userId, Message* outMessages[], int& count) const;
    int getUnreadMessageCountForUser(const char* userId) const;
    
    // Message management
    bool markMessageAsRead(const char* messageId);
    bool markAllMessagesAsReadForUser(const char* userId);
    void purgeOldMessages(int daysOld);
};

#endif // MESSAGE_SERVICE_H 