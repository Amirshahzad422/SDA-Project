#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "../domain/User.h"
#include "../domain/ProjectManager.h"
#include "../domain/TeamMember.h"
#include "../domain/Task.h"
#include "../domain/Message.h"
#include "../domain/MessageService.h"
#include "../domain/Report.h"
#include "../domain/ReportManager.h"
#include "../domain/BoardManager.h"
#include "../domain/CardAIAdapter.h"
#include "../domain/GoogleMeetingAdapter.h"
#include "../domain/ZoomMeetingAdapter.h"
#include "../domain/BugTask.h"
#include "../domain/FeatureTask.h"
#include "../domain/ImprovementTask.h"
#include "BoardUI.h"
using namespace std;

class UserInterface {
private:
    User* currentUser;
    ProjectManager* projectManager;
    MessageService* messageService;
    ReportManager* reportManager;
    BoardManager* boardManager;
    BoardUI* boardUI;
    CardAIAdapter* cardAIAdapter;
    GoogleMeetingAdapter* googleMeetingAdapter;
    ZoomMeetingAdapter* zoomMeetingAdapter;
    
    // Helper methods for UI
    void clearScreen();
    void pause();
    void displayHeader(const char* title);
    
public:
    UserInterface();
    ~UserInterface();
    
    // Main UI flow
    void run();
    
    // Menu displays
    void displayMainMenu();
    void displayModulesMenu(int role);
    void displayTaskManagementMenu(int role);
    void displayMessagingMenu();
    void displayReportMenu();
    void displayBoardManagementMenu();
    void displayMeetingMenu();
    void displayAIFeaturesMenu();
    void displayTaskTypesMenu();
    
    // User authentication
    bool login();
    bool signup();
    void logout();
    
    // Module handlers
    void showModulesMenu();
    void handleTaskManagement();
    void handleMessaging();
    void handleReports();
    void handleBoardManagement();
    void handleMeetings();
    void handleAIFeatures();
    
    // Task management operations based on user role
    void createTask();
    void assignTask();
    void updateTask();
    void viewTasks();
    void viewAssignedTasks();
    void viewAttachedFile();
    void createBugTask();
    void createFeatureTask();
    void createImprovementTask();
    
    // Messaging operations
    void sendMessage();
    void viewMessages();
    
    // Report operations
    void generateReport();
    void viewReports();
    
    // Meeting operations
    void createGoogleMeeting();
    void createZoomMeeting();
    void viewAllMeetings();
    void rescheduleMeeting();
    void cancelMeeting();
    void addParticipant();
    void exportAllMeetings();
    
    // AI Features
    void cardPrediction();
    void dueDatePrediction();
    void assigneeSuggestion();
    void prioritySuggestion();
    void similarCardsSuggestion();

    void handleLogin();
    void handleSignUp();
};

#endif // USER_INTERFACE_H 