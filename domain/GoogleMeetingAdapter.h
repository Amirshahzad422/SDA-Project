#ifndef GOOGLE_MEETING_ADAPTER_H
#define GOOGLE_MEETING_ADAPTER_H

#include "MeetingAdapter.h"
#include <cstring>
using namespace std;

class GoogleMeetingAdapter : public MeetingAdapter {
private:
    char clientId[100];
    char clientSecret[100];
    char googleAccount[100];
    
    struct GoogleMeeting {
        char id[50];
        char title[100];
        char date[20];
        char time[20];
        char duration[20];
        char host[100];
        char meetingLink[200];
        char participants[MAX_PARTICIPANTS][100];
        int participantCount;
        bool isActive;
    };
    
    GoogleMeeting meetings[10]; // Limited to 10 meetings for simplicity
    int meetingCount;
    
public:
    GoogleMeetingAdapter();
    GoogleMeetingAdapter(const char* clientId, const char* clientSecret, const char* account);
    ~GoogleMeetingAdapter();
    
    // Implementation of MeetingAdapter interface
    bool createMeeting(const char* title, const char* date, const char* time, 
                      const char* duration, const char* host) override;
    bool cancelMeeting(const char* meetingId) override;
    bool rescheduleMeeting(const char* meetingId, const char* newDate, 
                         const char* newTime) override;
    bool addParticipant(const char* meetingId, const char* participantId) override;
    bool removeParticipant(const char* meetingId, const char* participantId) override;
    void getParticipants(const char* meetingId, char participants[][100], 
                      int& count) const override;
    const char* getMeetingPlatform() const override;
    const char* getMeetingLink(const char* meetingId) const override;
    bool isMeetingValid(const char* meetingId) const override;
    
    // Google-specific methods
    void setGoogleCredentials(const char* clientId, const char* clientSecret, const char* account);
    bool addToGoogleCalendar(const char* meetingId) const;
    bool sendGoogleInvitations(const char* meetingId) const;
};

#endif // GOOGLE_MEETING_ADAPTER_H 