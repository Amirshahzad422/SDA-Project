#ifndef LABEL_H
#define LABEL_H

#include <cstring>
using namespace std;

class Label {
private:
    char id[50];
    char name[100];
    char color[20]; // "red", "green", "blue", "yellow", "orange", "purple"
    bool isSystemLabel;
    
public:
    Label();
    Label(const char* id, const char* name, const char* color);
    ~Label();
    
    // Label info getters and setters
    const char* getId() const;
    const char* getName() const;
    const char* getColor() const;
    bool getIsSystemLabel() const;
    void setId(const char* id);
    void setName(const char* name);
    void setColor(const char* color);
    void setIsSystemLabel(bool isSystem);
    
    // Utility methods
    const char* getColorCode() const; // Return hex code for the color
    bool matches(const char* searchText) const;
};

#endif // LABEL_H 