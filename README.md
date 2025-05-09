# Project Management System

A comprehensive project management system implemented using a layered architecture in C++. This system provides functionality for task management, team collaboration, messaging, reporting, and Trello-style board management.

## System Description

The Project Management System is designed to help teams manage projects, tasks, and communication. It offers features for:

- User management (Project Managers and Team Members)
- Task creation, assignment, and tracking
- Team messaging
- Report generation
- Meeting scheduling via different platforms
- Performance evaluation
- Trello-style boards with lists and cards
- Card labeling, commenting, and attachment management
- Activity tracking and user collaboration

## Architecture

The system follows a layered architecture with three primary layers:

### 1. Presentation Layer
- Contains classes responsible for user interaction
- Handles input and output
- Displays menus and processes user choices
- Example classes: UserInterface, BoardUI

### 2. Domain Layer (Business Logic)
- Contains the core business logic of the application
- Implements domain models and business rules
- Contains service classes that orchestrate operations
- Example classes: User, Task, Project, Board, TrelloBoard, Card, etc.

### 3. Data Layer
- Handles persistence of data
- Manages file operations
- Example classes: FileManager, BoardStorageHandler

## AI Module Design

The system has two AI adapter modules (design only, not implemented):

1. **AIAdapter**: Provides predictive services for general system usage
   - Task effort prediction
   - Team optimization recommendations

2. **CardAIAdapter**: Specializes in card-related predictions
   - Assignee recommendations
   - Label suggestions
   - Due date predictions
   - Similar card suggestions
   - Priority predictions

Both adapters follow the Adapter pattern to decouple AI implementation from the main system.

## Class Structure

The system implements various design patterns:

1. **Factory Pattern**: TaskFactory creates different types of tasks
2. **Strategy Pattern**: Estimation strategies for task effort calculation
3. **Adapter Pattern**: MeetingAdapter for different meeting platforms, AIAdapter for AI integration
4. **Composite Pattern**: Board/List/Task structure and TrelloBoard/TrelloList/Card structure

## Trello Board Functionality

The system includes a Trello-style board management system with:

- **Boards**: Containers for lists and cards
- **Lists**: Columns within boards (e.g., "To Do", "In Progress", "Done")
- **Cards**: Individual tasks or items within lists
- **Labels**: Color-coded tags for categorizing cards
- **Comments**: User comments on cards
- **Checklists**: Lists of subtasks within cards
- **Activities**: Tracking of all actions on boards and cards

This functionality is managed by the following main classes:
- TrelloBoard
- TrelloList
- Card
- Label
- Member
- ActivityLog
- BoardManager
- BoardUI

## How to Compile and Run

### Prerequisites
- C++ compiler (supporting C++11 or later)
- Standard C++ libraries

### Compilation
```bash
g++ -o trello main.cpp
```

### Running the Application
```bash
./trello
```

## Usage

1. Launch the application
2. Login with credentials or create a new account
3. Navigate through the menu system to access features:
   - Task management
   - Messaging
   - Report generation
   - Board management
4. In the board management section:
   - Create and manage boards
   - Add lists to boards
   - Create cards and assign them to members
   - Use labels to categorize cards
   - Track activities and collaborate with team members

## Design Changes

Any changes to the original design have been made to:
1. Improve modularity and separation of concerns
2. Enhance extensibility for future feature additions
3. Better align with object-oriented principles
4. Ensure compatibility with the layered architecture
5. Add Trello-style board functionality for enhanced task visualization and management

## Contributors

This project was developed as part of the SDA Assignment for the Software Design and Architecture course. 