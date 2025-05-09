#define _CRT_SECURE_NO_WARNINGS
#include "GoogleMeetingAdapter.h"
#include <cstring>
#include <cstdio>

GoogleMeetingAdapter::GoogleMeetingAdapter() {
    clientId[0] = '\0';
    clientSecret[0] = '\0';
    googleAccount[0] = '\0';
    meetingCount = 0;
}

GoogleMeetingAdapter::GoogleMeetingAdapter(const char* clientId, const char* clientSecret, const char* account) {
    strncpy(this->clientId, clientId, sizeof(this->clientId) - 1);
    this->clientId[sizeof(this->clientId) - 1] = '\0';
    
    strncpy(this->clientSecret, clientSecret, sizeof(this->clientSecret) - 1);
    this->clientSecret[sizeof(this->clientSecret) - 1] = '\0';
    
    strncpy(this->googleAccount, account, sizeof(this->googleAccount) - 1);
    this->googleAccount[sizeof(this->googleAccount) - 1] = '\0';
    
    meetingCount = 0;
}

GoogleMeetingAdapter::~GoogleMeetingAdapter() {
    // No dynamic memory to clean up
}

bool GoogleMeetingAdapter::createMeeting(const char* title, const char* date, const char* time, 
                                      const char* duration, const char* host) {
    if (meetingCount >= 10) {
        return false; // Maximum meetings reached
    }
    
    // In a real implementation, this would make API calls to Google
    
    // For demonstration, just store the meeting locally
    GoogleMeeting& meeting = meetings[meetingCount];
    
    sprintf(meeting.id, "google-%d", meetingCount + 1000);
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
    
    sprintf(meeting.meetingLink, "https://meet.google.com/%c%c%c-%c%c%c%c-%c%c%c", 
            'a' + (meetingCount % 26), 
            'b' + ((meetingCount + 1) % 26), 
            'c' + ((meetingCount + 2) % 26),
            'd' + ((meetingCount + 3) % 26),
            'e' + ((meetingCount + 4) % 26),
            'f' + ((meetingCount + 5) % 26),
            'g' + ((meetingCount + 6) % 26),
            'h' + ((meetingCount + 7) % 26),
            'i' + ((meetingCount + 8) % 26),
            'j' + ((meetingCount + 9) % 26));
    
    meeting.participantCount = 0;
    meeting.isActive = true;
    
    meetingCount++;
    
    // Add the meeting to Google Calendar
    addToGoogleCalendar(meeting.id);
    
    // Send out the invitations
    sendGoogleInvitations(meeting.id);
    
    return true;
}

bool GoogleMeetingAdapter::cancelMeeting(const char* meetingId) {
    // Find the meeting
    for (int i = 0; i < meetingCount; i++) {
        if (strcmp(meetings[i].id, meetingId) == 0) {
            meetings[i].isActive = false;
            return true;
        }
    }
    
    return false;
}

bool GoogleMeetingAdapter::rescheduleMeeting(const char* meetingId, const char* newDate, const char* newTime) {
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

bool GoogleMeetingAdapter::addParticipant(const char* meetingId, const char* participantId) {
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

bool GoogleMeetingAdapter::removeParticipant(const char* meetingId, const char* participantId) {
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

void GoogleMeetingAdapter::getParticipants(const char* meetingId, char participants[][100], int& count) const {
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

const char* GoogleMeetingAdapter::getMeetingPlatform() const {
    return "Google Meet";
}

const char* GoogleMeetingAdapter::getMeetingLink(const char* meetingId) const {
    // Find the meeting
    for (int i = 0; i < meetingCount; i++) {
        if (strcmp(meetings[i].id, meetingId) == 0) {
            return meetings[i].meetingLink;
        }
    }
    
    return "";
}

bool GoogleMeetingAdapter::isMeetingValid(const char* meetingId) const {
    // Find the meeting
    for (int i = 0; i < meetingCount; i++) {
        if (strcmp(meetings[i].id, meetingId) == 0) {
            return meetings[i].isActive;
        }
    }
    
    return false;
}

void GoogleMeetingAdapter::setGoogleCredentials(const char* clientId, const char* clientSecret, const char* account) {
    strncpy(this->clientId, clientId, sizeof(this->clientId) - 1);
    this->clientId[sizeof(this->clientId) - 1] = '\0';
    
    strncpy(this->clientSecret, clientSecret, sizeof(this->clientSecret) - 1);
    this->clientSecret[sizeof(this->clientSecret) - 1] = '\0';
    
    strncpy(this->googleAccount, account, sizeof(this->googleAccount) - 1);
    this->googleAccount[sizeof(this->googleAccount) - 1] = '\0';
}

bool GoogleMeetingAdapter::addToGoogleCalendar(const char* meetingId) const {
    // In a real implementation, this would integrate with Google Calendar API
    // For demonstration, just pretend it was successful
    return true;
}

bool GoogleMeetingAdapter::sendGoogleInvitations(const char* meetingId) const {
    // In a real implementation, this would send invitations to participants
    // For demonstration, just pretend it was successful
    return true;
} 