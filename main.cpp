#include <iostream>
#include "presentation/UserInterface.h"

using namespace std;

int main() {
    // Create and run the user interface
    UserInterface ui;
    ui.run();
    
    return 0;
}

// Data Formats for File Storage

// Task format
// id,title,description,priority,status,assignee,dueDate

// Message format
// id,sender,recipient,content,timestamp,isRead

// Board format
// id,name,description,isPrivate,memberCount,member1,member2,...

// List format
// id,boardId,name,position,isArchived

// Card format
// id,listId,title,description,position,dueDate,isComplete,isArchived,memberCount,member1,member2,...,labelCount,label1,label2,...