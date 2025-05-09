#ifndef MEETING_ADAPTER_H
#define MEETING_ADAPTER_H

#include <cstring>
using namespace std;

const int MAX_PARTICIPANTS = 20;

class MeetingAdapter {
public:
    virtual ~MeetingAdapter() {}
    
    // Meeting creation and management
    virtual bool createMeeting(const char* title, const char* date, const char* time, 
                              const char* duration, const char* host) = 0;
    virtual bool cancelMeeting(const char* meetingId) = 0;
    virtual bool rescheduleMeeting(const char* meetingId, const char* newDate, 
                                 const char* newTime) = 0;
    
    // Participant management
    virtual bool addParticipant(const char* meetingId, const char* participantId) = 0;
    virtual bool removeParticipant(const char* meetingId, const char* participantId) = 0;
    virtual void getParticipants(const char* meetingId, 
                              char participants[][100], int& count) const = 0;
    
    // Meeting details
    virtual const char* getMeetingPlatform() const = 0;
    virtual const char* getMeetingLink(const char* meetingId) const = 0;
    virtual bool isMeetingValid(const char* meetingId) const = 0;
};

#endif // MEETING_ADAPTER_H 