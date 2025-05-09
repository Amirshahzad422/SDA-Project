#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <cstring>
#include <ctime>
using namespace std;

class Feedback {
private:
    char id[50];
    char providerId[100];
    char recipientId[100];
    char content[1000];
    int rating; // 1-5 scale
    time_t timestamp;
    
public:
    Feedback();
    Feedback(const char* id, const char* providerId, const char* recipientId, 
            const char* content, int rating);
    ~Feedback();
    
    // Getters
    const char* getId() const;
    const char* getProviderId() const;
    const char* getRecipientId() const;
    const char* getContent() const;
    int getRating() const;
    time_t getTimestamp() const;
    
    // Setters
    void setId(const char* id);
    void setProviderId(const char* providerId);
    void setRecipientId(const char* recipientId);
    void setContent(const char* content);
    void setRating(int rating);
    
    // Utility methods
    char* getFormattedTimestamp() const;
    const char* getRatingDescription() const;
};

#endif // FEEDBACK_H 