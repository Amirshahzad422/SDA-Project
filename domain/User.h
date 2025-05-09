#ifndef USER_H
#define USER_H

using namespace std;

class User {
private:
    char name[100];
    char email[100];
    char password[100];
    char phone[100];

public:
    User();
    User(const char* name, const char* email, const char* password, const char* phone);
    
    // Getters
    const char* getName() const;
    const char* getEmail() const;
    const char* getPhone() const;
    
    // Setters
    void setName(const char* name);
    void setEmail(const char* email);
    void setPassword(const char* password);
    void setPhone(const char* phone);
    
    // Authentication
    bool authenticate(const char* password) const;
    
    // Virtual destructor for proper inheritance
    virtual ~User();
};

#endif // USER_H 