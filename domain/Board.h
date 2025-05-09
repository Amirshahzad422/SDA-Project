#ifndef BOARD_H
#define BOARD_H

#include <cstring>
using namespace std;

const int MAX_LISTS = 10;

// Forward declaration
class List;

class Board {
private:
    char id[50];
    char name[100];
    char description[500];
    List* lists[MAX_LISTS];
    int listCount;
    
public:
    Board();
    Board(const char* id, const char* name, const char* description);
    ~Board();
    
    // Getters
    const char* getId() const;
    const char* getName() const;
    const char* getDescription() const;
    
    // Setters
    void setId(const char* id);
    void setName(const char* name);
    void setDescription(const char* description);
    
    // List management
    bool addList(List* list);
    bool removeList(int listIndex);
    bool moveList(int fromIndex, int toIndex);
    List* getList(int index) const;
    int getListCount() const;
    List* findListById(const char* id) const;
    List* findListByName(const char* name) const;
};

#endif // BOARD_H 