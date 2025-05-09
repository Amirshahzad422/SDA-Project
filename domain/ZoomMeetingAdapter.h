#ifndef ZOOM_MEETING_ADAPTER_H
#define ZOOM_MEETING_ADAPTER_H

#include "MeetingAdapter.h"
#include <cstring>
using namespace std;

class ZoomMeetingAdapter : public MeetingAdapter {
private:
    char apiKey[100];
    char apiSecret[100];
    char zoomAccount[100];
    
    struct ZoomMeeting {
        char id[50];
        char title[100];
        char description[500];
        char date[20];
        char time[20];
        char duration[20];
        char host[100];
        char meetingLink[200];
        char password[50];
        char participants[MAX_PARTICIPANTS][100];
        int participantCount;
        bool isActive;
    };
    
    ZoomMeeting meetings[10]; // Limited to 10 meetings for simplicity
    int meetingCount;
    
    // File path for persistent storage
    char filePath[200];
    
public:
    ZoomMeetingAdapter();
    ZoomMeetingAdapter(const char* apiKey, const char* apiSecret, const char* account);
    ~ZoomMeetingAdapter();
    
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
    
    // Zoom-specific methods
    void setZoomCredentials(const char* apiKey, const char* apiSecret, const char* account);
    bool generateMeetingPassword(char* password, int length) const;
    bool sendZoomInvitations(const char* meetingId) const;
    
    // File storage methods
    void setStorageFilePath(const char* path);
    bool saveMeetingsToFile(); 
    bool loadMeetingsFromFile();
    bool exportMeetingDetails(const char* meetingId, const char* outputFile) const;
    void createMeetingWithDescription(const char* title, const char* description,
                                   const char* date, const char* time,
                                   const char* duration, const char* host);
};

#endif // ZOOM_MEETING_ADAPTER_H 