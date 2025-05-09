#define _CRT_SECURE_NO_WARNINGS
#include "ZoomMeetingAdapter.h"
#include <cstring>
#include <cstdio>

ZoomMeetingAdapter::ZoomMeetingAdapter() {
    apiKey[0] = '\0';
    apiSecret[0] = '\0';
    zoomAccount[0] = '\0';
    meetingCount = 0;
}

ZoomMeetingAdapter::ZoomMeetingAdapter(const char* apiKey, const char* apiSecret, const char* account) {
    strncpy(this->apiKey, apiKey, sizeof(this->apiKey) - 1);
    this->apiKey[sizeof(this->apiKey) - 1] = '\0';
    
    strncpy(this->apiSecret, apiSecret, sizeof(this->apiSecret) - 1);
    this->apiSecret[sizeof(this->apiSecret) - 1] = '\0';
    
    strncpy(this->zoomAccount, account, sizeof(this->zoomAccount) - 1);
    this->zoomAccount[sizeof(this->zoomAccount) - 1] = '\0';
    
    meetingCount = 0;
}

ZoomMeetingAdapter::~ZoomMeetingAdapter() {
    // No dynamic memory to clean up
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
    
    return true;
}

bool ZoomMeetingAdapter::cancelMeeting(const char* meetingId) {
    // Find the meeting
    for (int i = 0; i < meetingCount; i++) {
        if (strcmp(meetings[i].id, meetingId) == 0) {
            meetings[i].isActive = false;
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