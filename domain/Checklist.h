#ifndef CHECKLIST_H
#define CHECKLIST_H

#include <cstring>
using namespace std;

const int MAX_ITEMS = 20;

class Checklist {
private:
    char id[50];
    char name[100];
    
    struct ChecklistItem {
        char text[200];
        bool isChecked;
        char assignedTo[100]; // Optional: member ID
    };
    
    ChecklistItem items[MAX_ITEMS];
    int itemCount;
    
public:
    Checklist();
    Checklist(const char* id, const char* name);
    ~Checklist();
    
    // Checklist info getters and setters
    const char* getId() const;
    const char* getName() const;
    void setId(const char* id);
    void setName(const char* name);
    
    // Item management
    bool addItem(const char* text, bool isChecked = false);
    bool removeItem(int index);
    bool updateItemText(int index, const char* newText);
    bool toggleItemStatus(int index);
    bool assignItemToMember(int index, const char* memberId);
    
    // Item retrieval
    const char* getItemText(int index) const;
    bool getItemStatus(int index) const;
    const char* getItemAssignee(int index) const;
    int getItemCount() const;
    
    // Utility methods
    int getCompletedItemCount() const;
    float getCompletionPercentage() const;
    void markAllComplete();
    void markAllIncomplete();
};

#endif // CHECKLIST_H 