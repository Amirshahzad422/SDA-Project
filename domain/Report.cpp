#define _CRT_SECURE_NO_WARNINGS
#include "Report.h"
#include <cstring>
#include <ctime>
#include <cstdio>

Report::Report() {
    id[0] = '\0';
    title[0] = '\0';
    description[0] = '\0';
    type[0] = '\0';
    generatedBy[0] = '\0';
    generationDate = time(nullptr);
    content[0] = '\0';
}

Report::Report(const char* id, const char* title, const char* description, 
              const char* type, const char* generatedBy) {
    strncpy(this->id, id, sizeof(this->id) - 1);
    this->id[sizeof(this->id) - 1] = '\0';
    
    strncpy(this->title, title, sizeof(this->title) - 1);
    this->title[sizeof(this->title) - 1] = '\0';
    
    strncpy(this->description, description, sizeof(this->description) - 1);
    this->description[sizeof(this->description) - 1] = '\0';
    
    strncpy(this->type, type, sizeof(this->type) - 1);
    this->type[sizeof(this->type) - 1] = '\0';
    
    strncpy(this->generatedBy, generatedBy, sizeof(this->generatedBy) - 1);
    this->generatedBy[sizeof(this->generatedBy) - 1] = '\0';
    
    generationDate = time(nullptr);
    content[0] = '\0';
}

Report::~Report() {
    // Nothing to clean up
}

// Getters
const char* Report::getId() const {
    return id;
}

const char* Report::getTitle() const {
    return title;
}

const char* Report::getDescription() const {
    return description;
}

const char* Report::getType() const {
    return type;
}

const char* Report::getGeneratedBy() const {
    return generatedBy;
}

time_t Report::getGenerationDate() const {
    return generationDate;
}

const char* Report::getContent() const {
    return content;
}

// Setters
void Report::setId(const char* id) {
    strncpy(this->id, id, sizeof(this->id) - 1);
    this->id[sizeof(this->id) - 1] = '\0';
}

void Report::setTitle(const char* title) {
    strncpy(this->title, title, sizeof(this->title) - 1);
    this->title[sizeof(this->title) - 1] = '\0';
}

void Report::setDescription(const char* description) {
    strncpy(this->description, description, sizeof(this->description) - 1);
    this->description[sizeof(this->description) - 1] = '\0';
}

void Report::setType(const char* type) {
    strncpy(this->type, type, sizeof(this->type) - 1);
    this->type[sizeof(this->type) - 1] = '\0';
}

void Report::setGeneratedBy(const char* generatedBy) {
    strncpy(this->generatedBy, generatedBy, sizeof(this->generatedBy) - 1);
    this->generatedBy[sizeof(this->generatedBy) - 1] = '\0';
}

void Report::setContent(const char* content) {
    strncpy(this->content, content, sizeof(this->content) - 1);
    this->content[sizeof(this->content) - 1] = '\0';
}

// Report operations
bool Report::exportToFile(const char* filePath) const {
    FILE* file = fopen(filePath, "w");
    if (!file) return false;
    
    fprintf(file, "Report ID: %s\n", id);
    fprintf(file, "Title: %s\n", title);
    fprintf(file, "Type: %s\n", type);
    fprintf(file, "Generated By: %s\n", generatedBy);
    
    // Format the date
    char dateStr[100];
    struct tm* timeinfo = localtime(&generationDate);
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    fprintf(file, "Generation Date: %s\n\n", dateStr);
    fprintf(file, "Description:\n%s\n\n", description);
    fprintf(file, "Content:\n%s\n", content);
    
    fclose(file);
    return true;
}

char* Report::getFormattedGenerationDate() const {
    static char dateStr[100];
    struct tm* timeinfo = localtime(&generationDate);
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d %H:%M:%S", timeinfo);
    return dateStr;
}

void Report::generateSummary(char* summary, int maxLength) const {
    // Create a brief summary of the report
    snprintf(summary, maxLength, "Report: %s - %s (%s)", title, type, getFormattedGenerationDate());
} 