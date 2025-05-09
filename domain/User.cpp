#define _CRT_SECURE_NO_WARNINGS
#include "User.h"
#include <cstring>

User::User() {
    name[0] = '\0';
    email[0] = '\0';
    password[0] = '\0';
    phone[0] = '\0';
}

User::User(const char* name, const char* email, const char* password, const char* phone) {
    strncpy(this->name, name, sizeof(this->name) - 1);
    this->name[sizeof(this->name) - 1] = '\0';
    
    strncpy(this->email, email, sizeof(this->email) - 1);
    this->email[sizeof(this->email) - 1] = '\0';
    
    strncpy(this->password, password, sizeof(this->password) - 1);
    this->password[sizeof(this->password) - 1] = '\0';
    
    strncpy(this->phone, phone, sizeof(this->phone) - 1);
    this->phone[sizeof(this->phone) - 1] = '\0';
}

User::~User() {
    // Nothing to clean up
}

const char* User::getName() const {
    return name;
}

const char* User::getEmail() const {
    return email;
}

const char* User::getPhone() const {
    return phone;
}

void User::setName(const char* name) {
    strncpy(this->name, name, sizeof(this->name) - 1);
    this->name[sizeof(this->name) - 1] = '\0';
}

void User::setEmail(const char* email) {
    strncpy(this->email, email, sizeof(this->email) - 1);
    this->email[sizeof(this->email) - 1] = '\0';
}

void User::setPassword(const char* password) {
    strncpy(this->password, password, sizeof(this->password) - 1);
    this->password[sizeof(this->password) - 1] = '\0';
}

void User::setPhone(const char* phone) {
    strncpy(this->phone, phone, sizeof(this->phone) - 1);
    this->phone[sizeof(this->phone) - 1] = '\0';
}

bool User::authenticate(const char* password) const {
    return strcmp(this->password, password) == 0;
} 