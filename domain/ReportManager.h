#ifndef REPORT_MANAGER_H
#define REPORT_MANAGER_H

#include "Report.h"
using namespace std;

const int MAX_REPORTS = 50;

class ReportManager {
private:
    Report* reports[MAX_REPORTS];
    int reportCount;
    
public:
    ReportManager();
    ~ReportManager();
    
    // Report management
    bool addReport(Report* report);
    bool deleteReport(const char* reportId);
    
    // Report retrieval
    Report* findReportById(const char* reportId) const;
    void getReportsByType(const char* type, Report* outReports[], int& count) const;
    void getReportsByUser(const char* userId, Report* outReports[], int& count) const;
    
    // Report generation methods
    Report* generateTaskSummaryReport(const char* projectId, const char* generatedBy);
    Report* generateUserPerformanceReport(const char* userId, const char* generatedBy);
    Report* generateProjectStatusReport(const char* projectId, const char* generatedBy);
    
    // File operations
    bool exportAllReports(const char* directoryPath) const;
    bool importReports(const char* directoryPath);
};

#endif // REPORT_MANAGER_H 