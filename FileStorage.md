# File Storage System

The Project Management System now includes a comprehensive file storage system that ensures all user data is stored persistently. This document explains how file storage is implemented across different components.

## File Storage Features

1. **ZoomMeetingAdapter File Storage**
   - Meetings are automatically saved to a text file (`zoom_meetings.txt` by default)
   - Meeting data is loaded from file when the adapter is initialized
   - Each meeting is stored with all its details including participants
   - Meeting details can be exported to individual files
   - File format uses pipe-delimited records for maximum compatibility

2. **FileManager Class**
   - A general-purpose file storage manager for all domain objects
   - Provides storage for Users, Tasks, Reports, Messages, and Boards
   - Handles saving, loading, and file management operations
   - Uses CSV format for data interchange
   - Manages file paths for different data types

3. **Export Functionality**
   - Users can export meeting details to text files
   - Export option available in the Meeting Management menu
   - Files are human-readable and well-formatted

## Data Formats

### Meeting Data Format
```
[meeting_count]
id|title|description|date|time|duration|host|meetingLink|password|isActive|participantCount|participant1|participant2|...
```

### User Data Format
```
id,name,email,password,phone
```

### Task Data Format
```
id,title,description,status,priority,assignee,dueDate
```

### Message Data Format
```
id,sender,recipient,content,timestamp,isRead
```

### Report Data Format
```
id,title,content,date,author
```

## Using File Storage

1. **Automatic Storage**
   - All meeting creation, updates, and participant changes are automatically saved
   - The system loads existing data on startup

2. **Manual Export**
   - Use the "Export All Meetings" option in the Meeting Management menu
   - Individual meeting details are exported when creating a new Zoom meeting

3. **Custom File Paths**
   - File paths can be customized for different data types
   - Default paths point to the application's root directory

## Implementation Details

The file storage system uses standard C I/O functions:
- `fopen`, `fclose` for file handling
- `fprintf` for writing formatted data
- `fscanf` and `fgets` for reading data
- `strtok` for parsing delimited data

All data is properly escaped and validated during save/load operations to ensure data integrity. 