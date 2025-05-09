#define _CRT_SECURE_NO_WARNINGS
#include "Message.h"
#include <cstring>
#include <ctime>

Message::Message() {
    id[0] = '\0';
    sender[0] = '\0';
    recipient[0] = '\0';
    content[0] = '\0';
    timestamp = time(nullptr);
    isRead = false;
}

Message::Message(const char* id, const char* sender, const char* recipient, const char* content) {
    strncpy(this->id, id, sizeof(this->id) - 1);
    this->id[sizeof(this->id) - 1] = '\0';
    
    strncpy(this->sender, sender, sizeof(this->sender) - 1);
    this->sender[sizeof(this->sender) - 1] = '\0';
    
    strncpy(this->recipient, recipient, sizeof(this->recipient) - 1);
    this->recipient[sizeof(this->recipient) - 1] = '\0';
    
    strncpy(this->content, content, sizeof(this->content) - 1);
    this->content[sizeof(this->content) - 1] = '\0';
    
    timestamp = time(nullptr);
    isRead = false;
}

Message::~Message() {
    // Nothing to clean up
}

// Getters
const char* Message::getId() const {
    return id;
}

const char* Message::getSender() const {
    return sender;
}

const char* Message::getRecipient() const {
    return recipient;
}

const char* Message::getContent() const {
    return content;
}

time_t Message::getTimestamp() const {
    return timestamp;
}

bool Message::getIsRead() const {
    return isRead;
}

// Setters
void Message::setId(const char* id) {
    strncpy(this->id, id, sizeof(this->id) - 1);
    this->id[sizeof(this->id) - 1] = '\0';
}

void Message::setSender(const char* sender) {
    strncpy(this->sender, sender, sizeof(this->sender) - 1);
    this->sender[sizeof(this->sender) - 1] = '\0';
}

void Message::setRecipient(const char* recipient) {
    strncpy(this->recipient, recipient, sizeof(this->recipient) - 1);
    this->recipient[sizeof(this->recipient) - 1] = '\0';
}

void Message::setContent(const char* content) {
    strncpy(this->content, content, sizeof(this->content) - 1);
    this->content[sizeof(this->content) - 1] = '\0';
}

void Message::markAsRead() {
    isRead = true;
}

// Utility methods
char* Message::getFormattedTimestamp() const {
    static char dateStr[100];
    struct tm* timeinfo = localtime(&timestamp);
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d %H:%M:%S", timeinfo);
    return dateStr;
}

bool Message::isForUser(const char* userId) const {
    return strcmp(recipient, userId) == 0;
} 