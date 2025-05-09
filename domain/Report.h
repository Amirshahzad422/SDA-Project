#ifndef REPORT_H
#define REPORT_H

#include <cstring>
#include <ctime>
using namespace std;

class Report {
private:
    char id[50];
    char title[100];
    char description[500];
    char type[50]; // "Task Summary", "User Performance", etc.
    char generatedBy[100];
    time_t generationDate;
    char content[5000];
    
public:
    Report();
    Report(const char* id, const char* title, const char* description, 
          const char* type, const char* generatedBy);
    ~Report();
    
    // Getters
    const char* getId() const;
    const char* getTitle() const;
    const char* getDescription() const;
    const char* getType() const;
    const char* getGeneratedBy() const;
    time_t getGenerationDate() const;
    const char* getContent() const;
    
    // Setters
    void setId(const char* id);
    void setTitle(const char* title);
    void setDescription(const char* description);
    void setType(const char* type);
    void setGeneratedBy(const char* generatedBy);
    void setContent(const char* content);
    
    // Report operations
    bool exportToFile(const char* filePath) const;
    char* getFormattedGenerationDate() const;
    void generateSummary(char* summary, int maxLength) const;
};

#endif // REPORT_H 