#define _CRT_SECURE_NO_WARNINGS
#include "UserInterface.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Helper methods
void UserInterface::displayHeader(const char* title) {
    cout << title << endl;
    for (int i = 0; title[i] != '\0'; i++) {
        cout << "=";
    }
    cout << endl;
}

// Constructor & Destructor
UserInterface::UserInterface() {
    // Initialize members
    currentUser = nullptr;
    projectManager = nullptr;
    messageService = nullptr;
    reportManager = nullptr;
    boardManager = nullptr;
    boardUI = nullptr;
    cardAIAdapter = nullptr;
    googleMeetingAdapter = nullptr;
    zoomMeetingAdapter = nullptr;
    
    // Seed random number generator for report IDs
    srand(static_cast<unsigned int>(time(nullptr)));
}

UserInterface::~UserInterface() {
    // Clean up allocated resources
    if (currentUser) delete currentUser;
    if (projectManager) delete projectManager;
    if (messageService) delete messageService;
    if (reportManager) delete reportManager;
    if (boardManager) delete boardManager;
    if (boardUI) delete boardUI;
    if (cardAIAdapter) delete cardAIAdapter;
    if (googleMeetingAdapter) delete googleMeetingAdapter;
    if (zoomMeetingAdapter) delete zoomMeetingAdapter;
}

// Main flow
void UserInterface::run() {
    cout << "Project Management System" << endl;
    cout << "===========================" << endl;
    
    bool exitProgram = false;
    
    while (!exitProgram) {
        displayMainMenu();
        
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: // Login
                if (login()) {
                    showModulesMenu();
                }
                break;
            case 2: // Sign Up
                signup();
                break;
            case 3: // Exit
                exitProgram = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                pause();
        }
    }
    
    cout << "Thank you for using the Project Management System!" << endl;
}

// Authentication
bool UserInterface::login() {
    clearScreen();
    cout << "Login" << endl;
    cout << "=====" << endl;
    
    char username[50];
    char password[50];
    
    cout << "Username: ";
    cin >> username;
    
    cout << "Password: ";
    cin >> password;
    
    // In a real implementation, validate credentials against stored data
    // For now, just create a dummy user for demonstration
    cout << "Login successful! Welcome, " << username << "!" << endl;
    
    // Create a dummy user as current user
    if (currentUser) delete currentUser;
    
    // Create user with basic info
    currentUser = new User(username, "user@example.com", password, "555-1234");
    
    // Initialize all components
    if (!projectManager) projectManager = new ProjectManager();
    if (!boardManager) boardManager = new BoardManager();
    if (!boardUI) boardUI = new BoardUI(boardManager);
    if (!messageService) messageService = new MessageService();
    if (!reportManager) reportManager = new ReportManager();
    if (!cardAIAdapter) cardAIAdapter = new CardMLAdapter("/path/to/model", 0.75);
    if (!googleMeetingAdapter) googleMeetingAdapter = new GoogleMeetingAdapter("client-id", "client-secret", currentUser->getEmail());
    if (!zoomMeetingAdapter) zoomMeetingAdapter = new ZoomMeetingAdapter("api-key", "api-secret", currentUser->getEmail());
    
    pause();
    return true;
}

bool UserInterface::signup() {
    clearScreen();
    displayHeader("Sign Up");
    
    char username[50];
    char password[50];
    char email[100];
    char phone[50];
    
    cout << "Username: ";
    cin >> username;
    
    cout << "Password: ";
    cin >> password;
    
    cout << "Email: ";
    cin >> email;
    
    cout << "Phone: ";
    cin >> phone;
    
    // In a real implementation, store this user in database/file
    cout << "Account created successfully!" << endl;
    cout << "You can now login with your credentials." << endl;
    
    pause();
    return true;
}

void UserInterface::logout() {
    // Clean up current user
    if (currentUser) {
        delete currentUser;
        currentUser = nullptr;
    }
    cout << "Logged out successfully." << endl;
    pause();
}

// Menu displays
void UserInterface::displayMainMenu() {
    clearScreen();
    displayHeader("Main Menu");
    cout << "1. Login" << endl;
    cout << "2. Sign Up" << endl;
    cout << "3. Exit" << endl;
}

void UserInterface::displayModulesMenu(int role) {
    clearScreen();
    cout << "Modules Menu" << endl;
    cout << "============" << endl;
    cout << "1. Task Management" << endl;
    cout << "2. Messaging" << endl;
    cout << "3. Reports" << endl;
    cout << "4. Board Management" << endl;
    cout << "5. Meetings" << endl;
    cout << "6. AI Features" << endl;
    cout << "7. Log Out" << endl;
}

void UserInterface::displayTaskManagementMenu(int role) {
    clearScreen();
    displayHeader("Task Management");
    cout << "1. Create Task" << endl;
    cout << "2. Assign Task" << endl;
    cout << "3. Update Task" << endl;
    cout << "4. View Tasks" << endl;
    cout << "5. View Assigned Tasks" << endl;
    cout << "6. Back to Modules" << endl;
}

void UserInterface::displayMessagingMenu() {
    clearScreen();
    displayHeader("Messaging");
    cout << "1. Send Message" << endl;
    cout << "2. View Messages" << endl;
    cout << "3. Back to Modules" << endl;
}

void UserInterface::displayReportMenu() {
    clearScreen();
    displayHeader("Reports");
    cout << "1. Generate Report" << endl;
    cout << "2. View Reports" << endl;
    cout << "3. Back to Modules" << endl;
}

void UserInterface::displayBoardManagementMenu() {
    clearScreen();
    displayHeader("Board Management");
    cout << "1. View Boards" << endl;
    cout << "2. Create New Board" << endl;
    cout << "3. Back to Modules" << endl;
}

void UserInterface::displayMeetingMenu() {
    clearScreen();
    displayHeader("Meeting Management");
    cout << "1. Create Google Meeting" << endl;
    cout << "2. Create Zoom Meeting" << endl;
    cout << "3. View All Meetings" << endl;
    cout << "4. Reschedule Meeting" << endl;
    cout << "5. Cancel Meeting" << endl;
    cout << "6. Add Participant" << endl;
    cout << "7. Export All Meetings" << endl;
    cout << "8. Back to Modules Menu" << endl;
}

void UserInterface::displayAIFeaturesMenu() {
    clearScreen();
    cout << "AI Features" << endl;
    cout << "===========" << endl;
    cout << "1. Card Prediction" << endl;
    cout << "2. Due Date Prediction" << endl;
    cout << "3. Assignee Suggestion" << endl;
    cout << "4. Priority Suggestion" << endl;
    cout << "5. Similar Cards Suggestion" << endl;
    cout << "6. Back to Modules" << endl;
}

void UserInterface::displayTaskTypesMenu() {
    clearScreen();
    cout << "Create Task" << endl;
    cout << "===========" << endl;
    cout << "1. Bug Task" << endl;
    cout << "2. Feature Task" << endl;
    cout << "3. Improvement Task" << endl;
    cout << "4. Back to Task Management" << endl;
}

// Module handlers
void UserInterface::showModulesMenu() {
    bool exitProgram = false;
    
    while (!exitProgram && currentUser) {
        displayModulesMenu(0); // 0 is a placeholder for role
        
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: // Task Management
                handleTaskManagement();
                break;
            case 2: // Messaging
                handleMessaging();
                break;
            case 3: // Reports
                handleReports();
                break;
            case 4: // Board Management
                handleBoardManagement();
                break;
            case 5: // Meetings
                handleMeetings();
                break;
            case 6: // AI Features
                handleAIFeatures();
                break;
            case 7: // Log Out
                logout();
                exitProgram = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                pause();
        }
    }
}

void UserInterface::handleTaskManagement() {
    bool exitTaskManagement = false;
    
    while (!exitTaskManagement) {
        displayTaskManagementMenu(0); // 0 is a placeholder for role
        
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: // Create Task
                createTask();
                break;
            case 2: // Assign Task
                assignTask();
                break;
            case 3: // Update Task
                updateTask();
                break;
            case 4: // View Tasks
                viewTasks();
                break;
            case 5: // View Assigned Tasks
                viewAssignedTasks();
                break;
            case 6: // Back to Modules
                exitTaskManagement = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                pause();
        }
    }
}

void UserInterface::handleMessaging() {
    bool exitMessaging = false;
    
    while (!exitMessaging) {
        displayMessagingMenu();
        
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: // Send Message
                sendMessage();
                break;
            case 2: // View Messages
                viewMessages();
                break;
            case 3: // Back to Modules
                exitMessaging = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                pause();
        }
    }
}

void UserInterface::handleReports() {
    bool exitReports = false;
    
    while (!exitReports) {
        displayReportMenu();
        
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: // Generate Report
                generateReport();
                break;
            case 2: // View Reports
                viewReports();
                break;
            case 3: // Back to Modules
                exitReports = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                pause();
        }
    }
}

void UserInterface::handleBoardManagement() {
    if (!boardManager) boardManager = new BoardManager();
    if (!boardUI) boardUI = new BoardUI(boardManager);

    if (boardUI && currentUser) {
        bool exitBoardManagement = false;
        
        while (!exitBoardManagement) {
            displayBoardManagementMenu();
            
            int choice;
            cout << "Enter your choice: ";
            cin >> choice;
            
            switch (choice) {
                case 1: // View Boards
                    if (boardUI) {
                        boardUI->run(currentUser);
                    }
                    break;
                case 2: // Create New Board
                    if (boardUI) {
                        boardUI->createNewBoard();
                    }
                    break;
                case 3: // Back to main menu
                    exitBoardManagement = true;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    pause();
            }
        }
    }
}

void UserInterface::handleMeetings() {
    bool exitMenu = false;
    
    while (!exitMenu) {
        clearScreen();
        displayMeetingMenu();
        
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: // Create Google Meeting
                createGoogleMeeting();
                break;
            case 2: // Create Zoom Meeting
                createZoomMeeting();
                break;
            case 3: // View All Meetings
                viewAllMeetings();
                break;
            case 4: // Reschedule Meeting
                rescheduleMeeting();
                break;
            case 5: // Cancel Meeting
                cancelMeeting();
                break;
            case 6: // Add Participant
                addParticipant();
                break;
            case 7: // Export All Meetings
                exportAllMeetings();
                break;
            case 8: // Back to Modules Menu
                exitMenu = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                pause();
        }
    }
}

void UserInterface::handleAIFeatures() {
    bool exitAIFeatures = false;
    
    // Initialize AI adapter if not already initialized
    if (!cardAIAdapter) {
        // In a real implementation, this would initialize with proper model path
        // For demo purposes, we'll just create a dummy adapter
        cardAIAdapter = new CardMLAdapter("/path/to/model", 0.75);
    }
    
    while (!exitAIFeatures) {
        displayAIFeaturesMenu();
        
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: // Card Prediction
                cardPrediction();
                break;
            case 2: // Due Date Prediction
                dueDatePrediction();
                break;
            case 3: // Assignee Suggestion
                assigneeSuggestion();
                break;
            case 4: // Priority Suggestion
                prioritySuggestion();
                break;
            case 5: // Similar Cards Suggestion
                similarCardsSuggestion();
                break;
            case 6: // Back to Modules
                exitAIFeatures = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                pause();
        }
    }
}

// Task management
void UserInterface::createTask() {
    bool exitTaskCreation = false;
    
    while (!exitTaskCreation) {
        displayTaskTypesMenu();
        
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: // Bug Task
                createBugTask();
                break;
            case 2: // Feature Task
                createFeatureTask();
                break;
            case 3: // Improvement Task
                createImprovementTask();
                break;
            case 4: // Back
                exitTaskCreation = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                pause();
        }
    }
}

void UserInterface::assignTask() {
    clearScreen();
    displayHeader("Assign Task");
    
    // Display list of tasks
    cout << "Available Tasks:" << endl;
    cout << "1. Design database schema" << endl;
    cout << "2. Create user interface mockups" << endl;
    cout << "3. Set up development environment" << endl;
    
    int taskChoice;
    cout << "Select task to assign: ";
    cin >> taskChoice;
    
    // Display list of members
    cout << "Available Team Members:" << endl;
    cout << "1. John Doe" << endl;
    cout << "2. Jane Smith" << endl;
    cout << "3. Bob Johnson" << endl;
    
    int memberChoice;
    cout << "Select member to assign to: ";
    cin >> memberChoice;
    
    // In a real implementation, this would update the task assignment
    cout << "Task assigned successfully!" << endl;
    
    pause();
}

void UserInterface::updateTask() {
    clearScreen();
    displayHeader("Update Task");
    
    // Display list of tasks
    cout << "Your Tasks:" << endl;
    cout << "1. Design database schema (In Progress)" << endl;
    cout << "2. Create user interface mockups (Not Started)" << endl;
    cout << "3. Set up development environment (Completed)" << endl;
    
    int taskChoice;
    cout << "Select task to update: ";
    cin >> taskChoice;
    
    cout << "Update Status:" << endl;
    cout << "1. Not Started" << endl;
    cout << "2. In Progress" << endl;
    cout << "3. Completed" << endl;
    
    int statusChoice;
    cout << "Select new status: ";
    cin >> statusChoice;
    
    // In a real implementation, this would update the task status
    cout << "Task status updated successfully!" << endl;
    
    pause();
}

void UserInterface::viewTasks() {
    clearScreen();
    displayHeader("All Tasks");
    
    cout << "ID  | Title                       | Status      | Assignee     | Due Date   " << endl;
    cout << "----+-----------------------------+-------------+--------------+------------" << endl;
    cout << "001 | Design database schema      | In Progress | John Doe     | 2023-12-15 " << endl;
    cout << "002 | Create user interface       | Not Started | Jane Smith   | 2023-12-20 " << endl;
    cout << "003 | Set up development env      | Completed   | Bob Johnson  | 2023-12-10 " << endl;
    cout << "004 | Implement authentication    | In Progress | You          | 2023-12-25 " << endl;
    cout << "005 | Design API endpoints        | In Progress | You          | 2023-12-28 " << endl;
    
    pause();
}

void UserInterface::viewAssignedTasks() {
    clearScreen();
    displayHeader("Your Assigned Tasks");
    
    cout << "ID  | Title                       | Status      | Due Date   " << endl;
    cout << "----+-----------------------------+-------------+------------" << endl;
    cout << "004 | Implement authentication    | In Progress | 2023-12-25 " << endl;
    cout << "005 | Design API endpoints        | In Progress | 2023-12-28 " << endl;
    
    pause();
}

void UserInterface::viewAttachedFile() {
    clearScreen();
    displayHeader("View Attached File");
    
    cout << "Select a task to view attachments:" << endl;
    cout << "1. Design database schema" << endl;
    cout << "2. Create user interface mockups" << endl;
    
    int taskChoice;
    cout << "Enter your choice: ";
    cin >> taskChoice;
    
    if (taskChoice == 1) {
        cout << "Attached files for 'Design database schema':" << endl;
        cout << "1. database_schema_v1.pdf" << endl;
        cout << "2. requirements.docx" << endl;
    } else {
        cout << "Attached files for 'Create user interface mockups':" << endl;
        cout << "1. ui_wireframes.pdf" << endl;
        cout << "2. style_guide.pdf" << endl;
    }
    
    pause();
}

// Messaging
void UserInterface::sendMessage() {
    clearScreen();
    displayHeader("Send New Message");
    
    // Display list of recipients
    cout << "Select recipient:" << endl;
    cout << "1. John Doe" << endl;
    cout << "2. Jane Smith" << endl;
    cout << "3. Bob Johnson" << endl;
    cout << "4. Team Channel" << endl;
    
    int recipientChoice;
    cout << "Enter your choice: ";
    cin >> recipientChoice;
    
    // Get message content
    char subject[100];
    char message[1000];
    
    cout << "Subject: ";
    cin.ignore();
    cin.getline(subject, 100);
    
    cout << "Message: ";
    cin.getline(message, 1000);
    
    // In a real implementation, this would send the message
    cout << "Message sent successfully!" << endl;
    
    pause();
}

void UserInterface::viewMessages() {
    clearScreen();
    displayHeader("Your Messages");
    
    cout << "Inbox:" << endl;
    cout << "1. John Doe - Project Update - 2023-12-10" << endl;
    cout << "2. Jane Smith - Meeting Schedule - 2023-12-09" << endl;
    cout << "3. Team Channel - Weekly Update - 2023-12-08" << endl;
    
    int messageChoice;
    cout << "Select message to view (0 to go back): ";
    cin >> messageChoice;
    
    if (messageChoice > 0 && messageChoice <= 3) {
        clearScreen();
        
        if (messageChoice == 1) {
            displayHeader("Message: Project Update");
            cout << "From: John Doe" << endl;
            cout << "Date: 2023-12-10" << endl;
            cout << "----------------------" << endl;
            cout << "Hi there," << endl;
            cout << "I've completed the database schema design. Please review when you get a chance." << endl;
            cout << "Best regards," << endl;
            cout << "John" << endl;
        } else if (messageChoice == 2) {
            displayHeader("Message: Meeting Schedule");
            cout << "From: Jane Smith" << endl;
            cout << "Date: 2023-12-09" << endl;
            cout << "----------------------" << endl;
            cout << "Hello," << endl;
            cout << "Let's schedule a meeting to discuss the API endpoints." << endl;
            cout << "How about tomorrow at 2pm?" << endl;
            cout << "Jane" << endl;
        } else {
            displayHeader("Message: Weekly Update");
            cout << "From: Team Channel" << endl;
            cout << "Date: 2023-12-08" << endl;
            cout << "----------------------" << endl;
            cout << "Team," << endl;
            cout << "We've made great progress this week. Here's a summary:" << endl;
            cout << "- Database schema design: 100%" << endl;
            cout << "- UI mockups: 80%" << endl;
            cout << "- API endpoints: 50%" << endl;
            cout << "Great job everyone!" << endl;
        }
        
        pause();
    }
}

// Reports
void UserInterface::generateReport() {
    clearScreen();
    displayHeader("Generate Report");
    
    cout << "Select report type:" << endl;
    cout << "1. Project Status Report" << endl;
    cout << "2. Task Completion Report" << endl;
    cout << "3. User Activity Report" << endl;
    
    int reportType;
    cout << "Enter your choice: ";
    cin >> reportType;
    
    char startDate[20];
    char endDate[20];
    
    cout << "Start Date (YYYY-MM-DD): ";
    cin.ignore();
    cin.getline(startDate, 20);
    
    cout << "End Date (YYYY-MM-DD): ";
    cin.getline(endDate, 20);
    
    // In a real implementation, this would generate the report
    cout << "Report generated successfully!" << endl;
    cout << "Report ID: RPT-" << (100 + rand() % 900) << endl;
    
    pause();
}

void UserInterface::viewReports() {
    clearScreen();
    displayHeader("View Reports");
    
    cout << "Available Reports:" << endl;
    cout << "1. RPT-123: Project Status Report (2023-11-01 to 2023-11-30)" << endl;
    cout << "2. RPT-456: Task Completion Report (2023-10-01 to 2023-10-31)" << endl;
    cout << "3. RPT-789: User Activity Report (2023-09-01 to 2023-09-30)" << endl;
    
    int reportChoice;
    cout << "Select report to view (0 to go back): ";
    cin >> reportChoice;
    
    if (reportChoice > 0 && reportChoice <= 3) {
        clearScreen();
        
        if (reportChoice == 1) {
            displayHeader("Project Status Report");
            cout << "Period: 2023-11-01 to 2023-11-30" << endl;
            cout << "Generated: 2023-12-01" << endl;
            cout << "----------------------" << endl;
            cout << "Project Status Summary:" << endl;
            cout << "- Total Tasks: 25" << endl;
            cout << "- Completed: 15 (60%)" << endl;
            cout << "- In Progress: 8 (32%)" << endl;
            cout << "- Not Started: 2 (8%)" << endl;
            cout << endl;
            cout << "Key Milestones:" << endl;
            cout << "- Database Design: Completed" << endl;
            cout << "- UI Development: In Progress (75%)" << endl;
            cout << "- API Development: In Progress (50%)" << endl;
            cout << "- Testing: Not Started" << endl;
        } else if (reportChoice == 2) {
            displayHeader("Task Completion Report");
            cout << "Period: 2023-10-01 to 2023-10-31" << endl;
            cout << "Generated: 2023-11-01" << endl;
            cout << "----------------------" << endl;
            cout << "Task Completion by User:" << endl;
            cout << "- John Doe: 5 tasks" << endl;
            cout << "- Jane Smith: 7 tasks" << endl;
            cout << "- Bob Johnson: 3 tasks" << endl;
            cout << "- You: 4 tasks" << endl;
        } else {
            displayHeader("User Activity Report");
            cout << "Period: 2023-09-01 to 2023-09-30" << endl;
            cout << "Generated: 2023-10-01" << endl;
            cout << "----------------------" << endl;
            cout << "User Activity Summary:" << endl;
            cout << "- John Doe: 45 actions, 20 comments" << endl;
            cout << "- Jane Smith: 62 actions, 15 comments" << endl;
            cout << "- Bob Johnson: 30 actions, 10 comments" << endl;
            cout << "- You: 50 actions, 25 comments" << endl;
        }
        
        pause();
    }
}

// Meeting operations
void UserInterface::createGoogleMeeting() {
    clearScreen();
    displayHeader("Create Google Meeting");
    
    char title[100];
    char date[20];
    char time[20];
    char duration[20];
    
    cout << "Meeting Title: ";
    cin.ignore();
    cin.getline(title, sizeof(title));
    
    cout << "Date (YYYY-MM-DD): ";
    cin.getline(date, sizeof(date));
    
    cout << "Time (HH:MM): ";
    cin.getline(time, sizeof(time));
    
    cout << "Duration (e.g., '1 hour'): ";
    cin.getline(duration, sizeof(duration));
    
    // Create meeting
    googleMeetingAdapter->createMeeting(title, date, time, duration, currentUser->getName());
    
    cout << "Google Meeting created successfully!" << endl;
    pause();
}

void UserInterface::createZoomMeeting() {
    clearScreen();
    displayHeader("Create Zoom Meeting");
    
    char title[100];
    char description[500];
    char date[20];
    char time[20];
    char duration[20];
    
    cout << "Meeting Title: ";
    cin.ignore();
    cin.getline(title, sizeof(title));
    
    cout << "Meeting Description: ";
    cin.getline(description, sizeof(description));
    
    cout << "Date (YYYY-MM-DD): ";
    cin.getline(date, sizeof(date));
    
    cout << "Time (HH:MM): ";
    cin.getline(time, sizeof(time));
    
    cout << "Duration (e.g., '1 hour'): ";
    cin.getline(duration, sizeof(duration));
    
    // Create the meeting with description
    zoomMeetingAdapter->createMeetingWithDescription(title, description, date, time, duration, currentUser->getName());
    
    // Export meeting details to a file
    char exportFilename[100];
    sprintf(exportFilename, "zoom_meeting_%s.txt", title);
    
    // Get the ID of the meeting we just created (assuming it's the most recent one)
    char meetingId[50];
    sprintf(meetingId, "zoom-%d", 1000); // This is a simplification, in real code you'd get the actual ID
    
    // Export the details
    zoomMeetingAdapter->exportMeetingDetails(meetingId, exportFilename);
    
    cout << "Meeting created successfully!" << endl;
    cout << "Meeting details exported to: " << exportFilename << endl;
    pause();
}

void UserInterface::viewAllMeetings() {
    clearScreen();
    cout << "All Meetings" << endl;
    cout << "===========" << endl;
    
    cout << "Google Meetings:" << endl;
    cout << "------------------" << endl;
    cout << "1. Team Standup - 2023-12-15 09:00 - 30min" << endl;
    cout << "2. Project Review - 2023-12-16 14:00 - 60min" << endl;
    cout << endl;
    
    cout << "Zoom Meetings:" << endl;
    cout << "------------------" << endl;
    cout << "3. Client Demo - 2023-12-17 11:00 - 45min" << endl;
    cout << "4. Sprint Planning - 2023-12-18 10:00 - 90min" << endl;
    
    pause();
}

void UserInterface::rescheduleMeeting() {
    clearScreen();
    cout << "Reschedule Meeting" << endl;
    cout << "================" << endl;
    
    cout << "Select a meeting to reschedule:" << endl;
    cout << "1. Team Standup (Google) - 2023-12-15 09:00" << endl;
    cout << "2. Project Review (Google) - 2023-12-16 14:00" << endl;
    cout << "3. Client Demo (Zoom) - 2023-12-17 11:00" << endl;
    cout << "4. Sprint Planning (Zoom) - 2023-12-18 10:00" << endl;
    
    int meetingChoice;
    cout << "Enter your choice: ";
    cin >> meetingChoice;
    
    char newDate[20];
    char newTime[20];
    
    cout << "New Date (YYYY-MM-DD): ";
    cin.ignore();
    cin.getline(newDate, 20);
    
    cout << "New Time (HH:MM): ";
    cin.getline(newTime, 20);
    
    // In a real implementation, this would reschedule the meeting via the appropriate adapter
    cout << "Meeting rescheduled successfully to " << newDate << " at " << newTime << "!" << endl;
    
    pause();
}

void UserInterface::cancelMeeting() {
    clearScreen();
    cout << "Cancel Meeting" << endl;
    cout << "=============" << endl;
    
    cout << "Select a meeting to cancel:" << endl;
    cout << "1. Team Standup (Google) - 2023-12-15 09:00" << endl;
    cout << "2. Project Review (Google) - 2023-12-16 14:00" << endl;
    cout << "3. Client Demo (Zoom) - 2023-12-17 11:00" << endl;
    cout << "4. Sprint Planning (Zoom) - 2023-12-18 10:00" << endl;
    
    int meetingChoice;
    cout << "Enter your choice: ";
    cin >> meetingChoice;
    
    char confirmCancel[10];
    cout << "Are you sure you want to cancel this meeting? (yes/no): ";
    cin.ignore();
    cin.getline(confirmCancel, 10);
    
    if (strcmp(confirmCancel, "yes") == 0) {
        // In a real implementation, this would cancel the meeting via the appropriate adapter
        cout << "Meeting cancelled successfully!" << endl;
    } else {
        cout << "Cancellation aborted." << endl;
    }
    
    pause();
}

void UserInterface::addParticipant() {
    clearScreen();
    cout << "Add Participant" << endl;
    cout << "==============" << endl;
    
    cout << "Select a meeting:" << endl;
    cout << "1. Team Standup (Google) - 2023-12-15 09:00" << endl;
    cout << "2. Project Review (Google) - 2023-12-16 14:00" << endl;
    cout << "3. Client Demo (Zoom) - 2023-12-17 11:00" << endl;
    cout << "4. Sprint Planning (Zoom) - 2023-12-18 10:00" << endl;
    
    int meetingChoice;
    cout << "Enter your choice: ";
    cin >> meetingChoice;
    
    cout << "Available team members:" << endl;
    cout << "1. John Doe (john@example.com)" << endl;
    cout << "2. Jane Smith (jane@example.com)" << endl;
    cout << "3. Bob Johnson (bob@example.com)" << endl;
    cout << "4. Custom email" << endl;
    
    int participantChoice;
    cout << "Select participant to add: ";
    cin >> participantChoice;
    
    char participantEmail[100] = "";
    
    if (participantChoice == 4) {
        cout << "Enter participant email: ";
        cin.ignore();
        cin.getline(participantEmail, 100);
    } else {
        // Set email based on choice
        const char* emails[] = {"john@example.com", "jane@example.com", "bob@example.com"};
        strcpy(participantEmail, emails[participantChoice - 1]);
    }
    
    // In a real implementation, this would add the participant via the appropriate adapter
    cout << "Participant " << participantEmail << " added to the meeting successfully!" << endl;
    
    pause();
}

// AI Features
void UserInterface::cardPrediction() {
    clearScreen();
    cout << "Card Prediction" << endl;
    cout << "==============" << endl;
    
    cout << "Enter card details for prediction:" << endl;
    
    char title[100];
    char description[500];
    
    cout << "Card Title: ";
    cin.ignore();
    cin.getline(title, 100);
    
    cout << "Description: ";
    cin.getline(description, 500);
    
    // In a real implementation, this would use the CardAIAdapter to make predictions
    cout << "AI Analysis Results:" << endl;
    cout << "-------------------" << endl;
    cout << "Recommended List: 'To Do'" << endl;
    cout << "Suggested Labels: 'Backend', 'API'" << endl;
    cout << "Estimated Time: 4.5 hours" << endl;
    cout << "Suggested Due Date: 2023-12-20" << endl;
    cout << "Recommended Assignee: Jane Smith" << endl;
    cout << "Predicted Priority: Medium" << endl;
    cout << "Confidence Score: 85%" << endl;
    
    pause();
}

void UserInterface::dueDatePrediction() {
    clearScreen();
    cout << "Due Date Prediction" << endl;
    cout << "=================" << endl;
    
    cout << "Select a card for due date prediction:" << endl;
    cout << "1. Design database schema" << endl;
    cout << "2. Create user interface mockups" << endl;
    cout << "3. Implement authentication module" << endl;
    cout << "4. New card" << endl;
    
    int cardChoice;
    cout << "Enter your choice: ";
    cin >> cardChoice;
    
    if (cardChoice == 4) {
        char title[100];
        char description[500];
        
        cout << "Card Title: ";
        cin.ignore();
        cin.getline(title, 100);
        
        cout << "Description: ";
        cin.getline(description, 500);
    }
    
    // In a real implementation, this would use the CardAIAdapter for predictions
    cout << "AI Due Date Prediction:" << endl;
    cout << "---------------------" << endl;
    cout << "Predicted Due Date: 2023-12-22" << endl;
    cout << "Estimated Hours: 8.5" << endl;
    cout << "Confidence: 82%" << endl;
    cout << "Based on: 15 similar historical cards" << endl;
    
    pause();
}

void UserInterface::assigneeSuggestion() {
    clearScreen();
    cout << "Assignee Suggestion" << endl;
    cout << "=================" << endl;
    
    cout << "Select a card for assignee suggestion:" << endl;
    cout << "1. Design database schema" << endl;
    cout << "2. Create user interface mockups" << endl;
    cout << "3. Implement authentication module" << endl;
    cout << "4. New card" << endl;
    
    int cardChoice;
    cout << "Enter your choice: ";
    cin >> cardChoice;
    
    if (cardChoice == 4) {
        char title[100];
        char description[500];
        
        cout << "Card Title: ";
        cin.ignore();
        cin.getline(title, 100);
        
        cout << "Description: ";
        cin.getline(description, 500);
    }
    
    // In a real implementation, this would use the CardAIAdapter for suggestions
    cout << "AI Assignee Suggestions:" << endl;
    cout << "---------------------" << endl;
    cout << "1. John Doe (95% match)" << endl;
    cout << "   Expertise: Database design, Backend development" << endl;
    cout << "   Current workload: 3 tasks (Low)" << endl;
    cout << endl;
    cout << "2. Jane Smith (82% match)" << endl;
    cout << "   Expertise: API development, Authentication" << endl;
    cout << "   Current workload: 5 tasks (Medium)" << endl;
    cout << endl;
    cout << "3. Bob Johnson (65% match)" << endl;
    cout << "   Expertise: DevOps, Testing" << endl;
    cout << "   Current workload: 2 tasks (Low)" << endl;
    
    pause();
}

void UserInterface::prioritySuggestion() {
    clearScreen();
    cout << "Priority Suggestion" << endl;
    cout << "=================" << endl;
    
    cout << "Select a card for priority suggestion:" << endl;
    cout << "1. Design database schema" << endl;
    cout << "2. Create user interface mockups" << endl;
    cout << "3. Implement authentication module" << endl;
    cout << "4. New card" << endl;
    
    int cardChoice;
    cout << "Enter your choice: ";
    cin >> cardChoice;
    
    if (cardChoice == 4) {
        char title[100];
        char description[500];
        
        cout << "Card Title: ";
        cin.ignore();
        cin.getline(title, 100);
        
        cout << "Description: ";
        cin.getline(description, 500);
    }
    
    // In a real implementation, this would use the CardAIAdapter for suggestions
    cout << "AI Priority Suggestion:" << endl;
    cout << "---------------------" << endl;
    cout << "Suggested Priority: High" << endl;
    cout << "Confidence: 89%" << endl;
    cout << "Reasons:" << endl;
    cout << "1. Dependency for other high-priority tasks" << endl;
    cout << "2. Approaching deadline" << endl;
    cout << "3. Similar to other high-priority tasks in the project" << endl;
    
    pause();
}

void UserInterface::similarCardsSuggestion() {
    clearScreen();
    cout << "Similar Cards Suggestion" << endl;
    cout << "=====================" << endl;
    
    cout << "Select a card to find similar items:" << endl;
    cout << "1. Design database schema" << endl;
    cout << "2. Create user interface mockups" << endl;
    cout << "3. Implement authentication module" << endl;
    cout << "4. New card" << endl;
    
    int cardChoice;
    cout << "Enter your choice: ";
    cin >> cardChoice;
    
    if (cardChoice == 4) {
        char title[100];
        char description[500];
        
        cout << "Card Title: ";
        cin.ignore();
        cin.getline(title, 100);
        
        cout << "Description: ";
        cin.getline(description, 500);
    }
    
    // In a real implementation, this would use the CardAIAdapter for suggestions
    cout << "Similar Cards Found:" << endl;
    cout << "-------------------" << endl;
    cout << "1. Database Schema for User Module (90% similarity)" << endl;
    cout << "   Completed on: 2023-10-15" << endl;
    cout << "   Assignee: John Doe" << endl;
    cout << "   Time taken: 6.5 hours" << endl;
    cout << endl;
    cout << "2. Product Database Design (85% similarity)" << endl;
    cout << "   Completed on: 2023-09-20" << endl;
    cout << "   Assignee: Jane Smith" << endl;
    cout << "   Time taken: 8 hours" << endl;
    cout << endl;
    cout << "3. Order System Data Model (75% similarity)" << endl;
    cout << "   Completed on: 2023-11-05" << endl;
    cout << "   Assignee: John Doe" << endl;
    cout << "   Time taken: 10 hours" << endl;
    
    pause();
}

void UserInterface::createBugTask() {
    clearScreen();
    cout << "Create Bug Task" << endl;
    cout << "==============" << endl;
    
    char title[100];
    char description[500];
    char priority[20];
    char dueDate[20];
    char severity[20];
    char reproduceSteps[500];
    char affectedVersion[50];
    char isRegressionStr[10];
    
    cout << "Bug Title: ";
    cin.ignore();
    cin.getline(title, 100);
    
    cout << "Description: ";
    cin.getline(description, 500);
    
    cout << "Priority (Low/Medium/High): ";
    cin.getline(priority, 20);
    
    cout << "Due Date (YYYY-MM-DD): ";
    cin.getline(dueDate, 20);
    
    cout << "Severity (Low/Medium/High/Critical): ";
    cin.getline(severity, 20);
    
    cout << "Steps to Reproduce: ";
    cin.getline(reproduceSteps, 500);
    
    cout << "Affected Version: ";
    cin.getline(affectedVersion, 50);
    
    cout << "Is Regression (yes/no): ";
    cin.getline(isRegressionStr, 10);
    
    bool isRegression = (strcmp(isRegressionStr, "yes") == 0);
    
    // In a real implementation, this would create a bug task in the system
    cout << "Bug Task '" << title << "' created successfully!" << endl;
    cout << "Severity: " << severity << endl;
    cout << "Priority: " << priority << endl;
    cout << "Due Date: " << dueDate << endl;
    
    pause();
}

void UserInterface::createFeatureTask() {
    clearScreen();
    cout << "Create Feature Task" << endl;
    cout << "=================" << endl;
    
    char title[100];
    char description[500];
    char priority[20];
    char dueDate[20];
    char businessValue[100];
    char acceptanceCriteria[500];
    char complexityStr[20];
    
    cout << "Feature Title: ";
    cin.ignore();
    cin.getline(title, 100);
    
    cout << "Description: ";
    cin.getline(description, 500);
    
    cout << "Priority (Low/Medium/High): ";
    cin.getline(priority, 20);
    
    cout << "Due Date (YYYY-MM-DD): ";
    cin.getline(dueDate, 20);
    
    cout << "Business Value: ";
    cin.getline(businessValue, 100);
    
    cout << "Acceptance Criteria: ";
    cin.getline(acceptanceCriteria, 500);
    
    cout << "Complexity (Easy/Medium/Hard): ";
    cin.getline(complexityStr, 20);
    
    // In a real implementation, this would create a feature task in the system
    cout << "Feature Task '" << title << "' created successfully!" << endl;
    cout << "Business Value: " << businessValue << endl;
    cout << "Priority: " << priority << endl;
    cout << "Due Date: " << dueDate << endl;
    
    pause();
}

void UserInterface::createImprovementTask() {
    clearScreen();
    cout << "Create Improvement Task" << endl;
    cout << "=====================" << endl;
    
    char title[100];
    char description[500];
    char priority[20];
    char dueDate[20];
    char impactArea[100];
    char currentState[300];
    char desiredState[300];
    
    cout << "Improvement Title: ";
    cin.ignore();
    cin.getline(title, 100);
    
    cout << "Description: ";
    cin.getline(description, 500);
    
    cout << "Priority (Low/Medium/High): ";
    cin.getline(priority, 20);
    
    cout << "Due Date (YYYY-MM-DD): ";
    cin.getline(dueDate, 20);
    
    cout << "Impact Area: ";
    cin.getline(impactArea, 100);
    
    cout << "Current State: ";
    cin.getline(currentState, 300);
    
    cout << "Desired State: ";
    cin.getline(desiredState, 300);
    
    // In a real implementation, this would create an improvement task in the system
    cout << "Improvement Task '" << title << "' created successfully!" << endl;
    cout << "Impact Area: " << impactArea << endl;
    cout << "Priority: " << priority << endl;
    cout << "Due Date: " << dueDate << endl;
    
    pause();
}

// UI utility methods
void UserInterface::clearScreen() {
    // Simple cross-platform clear screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void UserInterface::pause() {
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

// Add a new method to export all meetings to files
void UserInterface::exportAllMeetings() {
    clearScreen();
    displayHeader("Export All Meetings");
    
    // Export Zoom meetings
    if (zoomMeetingAdapter) {
        zoomMeetingAdapter->saveMeetingsToFile();
        cout << "All Zoom meetings have been saved to: zoom_meetings.txt" << endl;
    }
    
    // Export Google meetings
    if (googleMeetingAdapter) {
        // If GoogleMeetingAdapter had same methods, we'd call them here
        cout << "Google meetings functionality not yet implemented." << endl;
    }
    
    pause();
} 