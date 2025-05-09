#define _CRT_SECURE_NO_WARNINGS
#include "ZoomMeetingAdapter.h"
#include <cstring>
#include <cstdio>
#include <cstdlib> // For atoi function

ZoomMeetingAdapter::ZoomMeetingAdapter() {
    apiKey[0] = '\0';
    apiSecret[0] = '\0';
    zoomAccount[0] = '\0';
    meetingCount = 0;
    strcpy(filePath, "zoom_meetings.txt"); // Default storage path
}

ZoomMeetingAdapter::ZoomMeetingAdapter(const char* apiKey, const char* apiSecret, const char* account) {
    strncpy(this->apiKey, apiKey, sizeof(this->apiKey) - 1);
    this->apiKey[sizeof(this->apiKey) - 1] = '\0';
    
    strncpy(this->apiSecret, apiSecret, sizeof(this->apiSecret) - 1);
    this->apiSecret[sizeof(this->apiSecret) - 1] = '\0';
    
    strncpy(this->zoomAccount, account, sizeof(this->zoomAccount) - 1);
    this->zoomAccount[sizeof(this->zoomAccount) - 1] = '\0';
    
    meetingCount = 0;
    strcpy(filePath, "zoom_meetings.txt"); // Default storage path
    
    // Load any existing meetings from file
    loadMeetingsFromFile();
}

ZoomMeetingAdapter::~ZoomMeetingAdapter() {
    // Save meetings to file before destroying object
    saveMeetingsToFile();
}

bool ZoomMeetingAdapter::createMeeting(const char* title, const char* date, const char* time, 
                                     const char* duration, const char* host) {
    if (meetingCount >= 10) {
        return false; // Maximum meetings reached
    }
    
    // In a real implementation, this would make API calls to Zoom
    
    // For demonstration, just store the meeting locally
    ZoomMeeting& meeting = meetings[meetingCount];
    
    sprintf(meeting.id, "zoom-%d", meetingCount + 1000);
    strncpy(meeting.title, title, sizeof(meeting.title) - 1);
    meeting.title[sizeof(meeting.title) - 1] = '\0';
    
    // Initialize description
    meeting.description[0] = '\0';
    
    strncpy(meeting.date, date, sizeof(meeting.date) - 1);
    meeting.date[sizeof(meeting.date) - 1] = '\0';
    
    strncpy(meeting.time, time, sizeof(meeting.time) - 1);
    meeting.time[sizeof(meeting.time) - 1] = '\0';
    
    strncpy(meeting.duration, duration, sizeof(meeting.duration) - 1);
    meeting.duration[sizeof(meeting.duration) - 1] = '\0';
    
    strncpy(meeting.host, host, sizeof(meeting.host) - 1);
    meeting.host[sizeof(meeting.host) - 1] = '\0';
    
    sprintf(meeting.meetingLink, "https://zoom.us/j/%d", meetingCount + 1000);
    meeting.participantCount = 0;
    meeting.isActive = true;
    
    meetingCount++;
    
    // Generate a password for the meeting
    char password[50];
    generateMeetingPassword(password, sizeof(password));
    strncpy(meeting.password, password, sizeof(meeting.password) - 1);
    meeting.password[sizeof(meeting.password) - 1] = '\0';
    
    // Simulate sending invitations
    sendZoomInvitations(meeting.id);
    
    // Save all meetings to file for persistence
    saveMeetingsToFile();
    
    return true;
}

void ZoomMeetingAdapter::createMeetingWithDescription(const char* title, const char* description,
                                                  const char* date, const char* time,
                                                  const char* duration, const char* host) {
    if (createMeeting(title, date, time, duration, host)) {
        // Meeting created successfully, now add description
        strncpy(meetings[meetingCount-1].description, description, sizeof(meetings[meetingCount-1].description) - 1);
        meetings[meetingCount-1].description[sizeof(meetings[meetingCount-1].description) - 1] = '\0';
        
        // Save to file after updating
        saveMeetingsToFile();
    }
}

bool ZoomMeetingAdapter::cancelMeeting(const char* meetingId) {
    // Find the meeting
    for (int i = 0; i < meetingCount; i++) {
        if (strcmp(meetings[i].id, meetingId) == 0) {
            meetings[i].isActive = false;
            
            // Save changes to file
            saveMeetingsToFile();
            
            return true;
        }
    }
    
    return false;
}

bool ZoomMeetingAdapter::rescheduleMeeting(const char* meetingId, const char* newDate, const char* newTime) {
    // Find the meeting
    for (int i = 0; i < meetingCount; i++) {
        if (strcmp(meetings[i].id, meetingId) == 0) {
            strncpy(meetings[i].date, newDate, sizeof(meetings[i].date) - 1);
            meetings[i].date[sizeof(meetings[i].date) - 1] = '\0';
            
            strncpy(meetings[i].time, newTime, sizeof(meetings[i].time) - 1);
            meetings[i].time[sizeof(meetings[i].time) - 1] = '\0';
            
            // Save changes to file
            saveMeetingsToFile();
            
            return true;
        }
    }
    
    return false;
}

bool ZoomMeetingAdapter::addParticipant(const char* meetingId, const char* participantId) {
    // Find the meeting
    for (int i = 0; i < meetingCount; i++) {
        if (strcmp(meetings[i].id, meetingId) == 0) {
            if (meetings[i].participantCount >= MAX_PARTICIPANTS) {
                return false; // Maximum participants reached
            }
            
            strncpy(meetings[i].participants[meetings[i].participantCount], participantId, 99);
            meetings[i].participants[meetings[i].participantCount][99] = '\0';
            meetings[i].participantCount++;
            
            // Save changes to file
            saveMeetingsToFile();
            
            return true;
        }
    }
    
    return false;
}

bool ZoomMeetingAdapter::removeParticipant(const char* meetingId, const char* participantId) {
    // Find the meeting
    for (int i = 0; i < meetingCount; i++) {
        if (strcmp(meetings[i].id, meetingId) == 0) {
            // Find the participant
            for (int j = 0; j < meetings[i].participantCount; j++) {
                if (strcmp(meetings[i].participants[j], participantId) == 0) {
                    // Move the last participant to this position
                    if (j < meetings[i].participantCount - 1) {
                        strcpy(meetings[i].participants[j], meetings[i].participants[meetings[i].participantCount - 1]);
                    }
                    
                    meetings[i].participantCount--;
                    
                    // Save changes to file
                    saveMeetingsToFile();
                    
                    return true;
                }
            }
        }
    }
    
    return false;
}

void ZoomMeetingAdapter::getParticipants(const char* meetingId, char participants[][100], int& count) const {
    count = 0;
    
    // Find the meeting
    for (int i = 0; i < meetingCount; i++) {
        if (strcmp(meetings[i].id, meetingId) == 0) {
            count = meetings[i].participantCount;
            
            // Copy participants
            for (int j = 0; j < count; j++) {
                strcpy(participants[j], meetings[i].participants[j]);
            }
            
            return;
        }
    }
}

const char* ZoomMeetingAdapter::getMeetingPlatform() const {
    return "Zoom";
}

const char* ZoomMeetingAdapter::getMeetingLink(const char* meetingId) const {
    // Find the meeting
    for (int i = 0; i < meetingCount; i++) {
        if (strcmp(meetings[i].id, meetingId) == 0) {
            return meetings[i].meetingLink;
        }
    }
    
    return "";
}

bool ZoomMeetingAdapter::isMeetingValid(const char* meetingId) const {
    // Find the meeting
    for (int i = 0; i < meetingCount; i++) {
        if (strcmp(meetings[i].id, meetingId) == 0) {
            return meetings[i].isActive;
        }
    }
    
    return false;
}

void ZoomMeetingAdapter::setZoomCredentials(const char* apiKey, const char* apiSecret, const char* account) {
    strncpy(this->apiKey, apiKey, sizeof(this->apiKey) - 1);
    this->apiKey[sizeof(this->apiKey) - 1] = '\0';
    
    strncpy(this->apiSecret, apiSecret, sizeof(this->apiSecret) - 1);
    this->apiSecret[sizeof(this->apiSecret) - 1] = '\0';
    
    strncpy(this->zoomAccount, account, sizeof(this->zoomAccount) - 1);
    this->zoomAccount[sizeof(this->zoomAccount) - 1] = '\0';
}

bool ZoomMeetingAdapter::generateMeetingPassword(char* password, int length) const {
    // In a real implementation, this would generate a secure password
    // For demonstration, just set a fixed password
    if (length < 8) return false;
    
    strncpy(password, "zoom123", length - 1);
    password[length - 1] = '\0';
    return true;
}

bool ZoomMeetingAdapter::sendZoomInvitations(const char* meetingId) const {
    // In a real implementation, this would send invitations to participants
    // For demonstration, just pretend it was successful
    return true;
}

// New file storage methods

void ZoomMeetingAdapter::setStorageFilePath(const char* path) {
    strncpy(filePath, path, sizeof(filePath) - 1);
    filePath[sizeof(filePath) - 1] = '\0';
}

bool ZoomMeetingAdapter::saveMeetingsToFile() {
    FILE* file = fopen(filePath, "w");
    if (!file) {
        return false;
    }
    
    // Write the number of meetings
    fprintf(file, "%d\n", meetingCount);
    
    // Write each meeting
    for (int i = 0; i < meetingCount; i++) {
        ZoomMeeting& meeting = meetings[i];
        
        // Format: id,title,description,date,time,duration,host,meetingLink,password,isActive,participantCount,[participants]
        fprintf(file, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%d|%d",
                meeting.id, meeting.title, meeting.description, meeting.date, meeting.time,
                meeting.duration, meeting.host, meeting.meetingLink, meeting.password,
                meeting.isActive ? 1 : 0, meeting.participantCount);
        
        // Write participants
        for (int j = 0; j < meeting.participantCount; j++) {
            fprintf(file, "|%s", meeting.participants[j]);
        }
        
        fprintf(file, "\n");
    }
    
    fclose(file);
    return true;
}

bool ZoomMeetingAdapter::loadMeetingsFromFile() {
    FILE* file = fopen(filePath, "r");
    if (!file) {
        return false; // File does not exist or cannot be opened
    }
    
    // Read number of meetings
    if (fscanf(file, "%d\n", &meetingCount) != 1) {
        fclose(file);
        return false;
    }
    
    if (meetingCount > 10) {
        meetingCount = 10; // Safety check
    }
    
    // Read each meeting
    char line[2000];
    
    for (int i = 0; i < meetingCount; i++) {
        if (fgets(line, sizeof(line), file) == NULL) {
            fclose(file);
            return false;
        }
        
        // Remove newline if present
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        
        // Parse the line
        char* token = strtok(line, "|");
        if (!token) continue;
        
        // id
        strncpy(meetings[i].id, token, sizeof(meetings[i].id) - 1);
        meetings[i].id[sizeof(meetings[i].id) - 1] = '\0';
        
        // title
        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(meetings[i].title, token, sizeof(meetings[i].title) - 1);
        meetings[i].title[sizeof(meetings[i].title) - 1] = '\0';
        
        // description
        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(meetings[i].description, token, sizeof(meetings[i].description) - 1);
        meetings[i].description[sizeof(meetings[i].description) - 1] = '\0';
        
        // date
        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(meetings[i].date, token, sizeof(meetings[i].date) - 1);
        meetings[i].date[sizeof(meetings[i].date) - 1] = '\0';
        
        // time
        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(meetings[i].time, token, sizeof(meetings[i].time) - 1);
        meetings[i].time[sizeof(meetings[i].time) - 1] = '\0';
        
        // duration
        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(meetings[i].duration, token, sizeof(meetings[i].duration) - 1);
        meetings[i].duration[sizeof(meetings[i].duration) - 1] = '\0';
        
        // host
        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(meetings[i].host, token, sizeof(meetings[i].host) - 1);
        meetings[i].host[sizeof(meetings[i].host) - 1] = '\0';
        
        // meetingLink
        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(meetings[i].meetingLink, token, sizeof(meetings[i].meetingLink) - 1);
        meetings[i].meetingLink[sizeof(meetings[i].meetingLink) - 1] = '\0';
        
        // password
        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(meetings[i].password, token, sizeof(meetings[i].password) - 1);
        meetings[i].password[sizeof(meetings[i].password) - 1] = '\0';
        
        // isActive
        token = strtok(NULL, "|");
        if (!token) continue;
        meetings[i].isActive = (atoi(token) == 1);
        
        // participantCount
        token = strtok(NULL, "|");
        if (!token) continue;
        meetings[i].participantCount = atoi(token);
        
        if (meetings[i].participantCount > MAX_PARTICIPANTS) {
            meetings[i].participantCount = MAX_PARTICIPANTS; // Safety check
        }
        
        // participants
        for (int j = 0; j < meetings[i].participantCount; j++) {
            token = strtok(NULL, "|");
            if (!token) break;
            strncpy(meetings[i].participants[j], token, 99);
            meetings[i].participants[j][99] = '\0';
        }
    }
    
    fclose(file);
    return true;
}

bool ZoomMeetingAdapter::exportMeetingDetails(const char* meetingId, const char* outputFile) const {
    // Find the meeting
    int meetingIndex = -1;
    for (int i = 0; i < meetingCount; i++) {
        if (strcmp(meetings[i].id, meetingId) == 0) {
            meetingIndex = i;
            break;
        }
    }
    
    if (meetingIndex == -1) {
        return false; // Meeting not found
    }
    
    // Open the output file
    FILE* file = fopen(outputFile, "w");
    if (!file) {
        return false;
    }
    
    // Write meeting details in a readable format
    const ZoomMeeting& meeting = meetings[meetingIndex]; // Changed to const reference
    
    fprintf(file, "ZOOM MEETING DETAILS\n");
    fprintf(file, "===================\n\n");
    fprintf(file, "Meeting ID: %s\n", meeting.id);
    fprintf(file, "Title: %s\n", meeting.title);
    fprintf(file, "Description: %s\n", meeting.description);
    fprintf(file, "Date: %s\n", meeting.date);
    fprintf(file, "Time: %s\n", meeting.time);
    fprintf(file, "Duration: %s\n", meeting.duration);
    fprintf(file, "Host: %s\n", meeting.host);
    fprintf(file, "Meeting Link: %s\n", meeting.meetingLink);
    fprintf(file, "Password: %s\n", meeting.password);
    fprintf(file, "Status: %s\n\n", meeting.isActive ? "Active" : "Cancelled");
    
    fprintf(file, "PARTICIPANTS (%d):\n", meeting.participantCount);
    fprintf(file, "----------------\n");
    for (int i = 0; i < meeting.participantCount; i++) {
        fprintf(file, "%d. %s\n", i + 1, meeting.participants[i]);
    }
    
    fclose(file);
    return true;
} 