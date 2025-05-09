#ifndef COMMENT_H
#define COMMENT_H

#include <cstring>
#include <ctime>
using namespace std;

class Comment {
private:
    char author[100];
    char text[1000];
    time_t timestamp;
    bool isEdited;
    
public:
    Comment();
    Comment(const char* author, const char* text);
    ~Comment();
    
    // Getters
    const char* getAuthor() const;
    const char* getText() const;
    time_t getTimestamp() const;
    bool getIsEdited() const;
    
    // Setters
    void setAuthor(const char* author);
    void setText(const char* text);
    
    // Comment operations
    void edit(const char* newText);
    char* getFormattedDate() const;
    char* getFormattedComment() const;
};

#endif // COMMENT_H 