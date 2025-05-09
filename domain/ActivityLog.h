#ifndef ACTIVITY_LOG_H
#define ACTIVITY_LOG_H

#include <cstring>
#include <ctime>
using namespace std;

class ActivityLog {
private:
    char id[50];
    char type[50]; // "create_card", "move_card", "add_comment", etc.
    char entityId[50]; // Card ID, List ID, etc.
    char performedBy[100]; // Member ID who performed the action
    char description[500];
    time_t timestamp;
    char data[1000]; // JSON-like string with additional data 
    
public:
    ActivityLog();
    ActivityLog(const char* id, const char* type, const char* entityId, 
              const char* performedBy, const char* description);
    ~ActivityLog();
    
    // Log info getters and setters
    const char* getId() const;
    const char* getType() const;
    const char* getEntityId() const;
    const char* getPerformedBy() const;
    const char* getDescription() const;
    time_t getTimestamp() const;
    const char* getData() const;
    void setId(const char* id);
    void setType(const char* type);
    void setEntityId(const char* entityId);
    void setPerformedBy(const char* performedBy);
    void setDescription(const char* description);
    void setData(const char* data);
    
    // Utility methods
    char* getFormattedTimestamp() const;
    char* getFormattedDescription() const;
    bool involvesEntity(const char* entityId) const;
    bool involvesUser(const char* userId) const;
};

#endif // ACTIVITY_LOG_H 