#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <vector>

using namespace std;

class Task {
private:
    string title;
    string description;
    string priority;
    string dependency;
    string assignedTo;
    string status;
    string createdBy;
    string attachedFile;

    string getPriorityFromChoice() {
        int choice;
        cout << "\nSelect Priority:\n";
        cout << "1. High\n";
        cout << "2. Medium\n";
        cout << "3. Low\n";
        cout << "Enter choice (1-3): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: return "High";
        case 2: return "Medium";
        case 3: return "Low";
        default: return "Medium";
        }
    }

    string getStatusFromChoice() {
        int choice;
        cout << "\nSelect Status:\n";
        cout << "1. Not Started\n";
        cout << "2. In Progress\n";
        cout << "3. Completed\n";
        cout << "4. Blocked\n";
        cout << "Enter choice (1-4): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: return "Not Started";
        case 2: return "In Progress";
        case 3: return "Completed";
        case 4: return "Blocked";
        default: return "Not Started";
        }
    }

    string getDependencyFromList() {
        ifstream in("tasks.txt");
        string line;
        int count = 0;
        string dependencies = "";

        cout << "\nSelect Dependencies (Enter 0 when done):\n";
        cout << "0. None/Done\n";

        // Store tasks for later reference
        string tasks[100];  // Using fixed array as per requirement to not use vector
        while (getline(in, line) && count < 100) {
            size_t pos = line.find(",");
            string taskTitle = line.substr(0, pos);
            tasks[count] = taskTitle;
            cout << count + 1 << ". " << taskTitle << "\n";
            count++;
        }
        in.close();

        while (true) {
            int choice;
            cout << "Enter choice (0-" << count << "): ";
            cin >> choice;
            cin.ignore();

            if (choice == 0) break;

            if (choice > 0 && choice <= count) {
                if (dependencies.empty()) {
                    dependencies = tasks[choice - 1];
                }
                else {
                    dependencies += ";" + tasks[choice - 1];
                }
                cout << "Added dependency: " << tasks[choice - 1] << "\n";
                cout << "Current dependencies: " << dependencies << "\n";
            }
        }

        return dependencies.empty() ? "none" : dependencies;
    }

    bool safeRename(const char* oldname, const char* newname) {
        if (rename(oldname, newname) != 0) {
            cout << "Error renaming file.\n";
            return false;
        }
        return true;
    }

    void displayTaskDetails(const string& line) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        size_t pos3 = line.find(",", pos2 + 1);
        size_t pos4 = line.find(",", pos3 + 1);
        size_t pos5 = line.find(",", pos4 + 1);
        size_t pos6 = line.find(",", pos5 + 1);

        string title = line.substr(0, pos1);
        string desc = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string priority = line.substr(pos2 + 1, pos3 - pos2 - 1);
        string dependencies = line.substr(pos3 + 1, pos4 - pos3 - 1);
        string assignedTo = line.substr(pos4 + 1, pos5 - pos4 - 1);
        string createdBy = line.substr(pos5 + 1, pos6 - pos5 - 1);
        string status = line.substr(pos6 + 1);

        cout << "\n+==================================================+\n";
        cout << "|                   TASK DETAILS                    |\n";
        cout << "+==================================================+\n";

        // Title with fixed width
        cout << "| Title       : " << left << setw(35) << title;
        cout << " |\n";
        cout << "+--------------------------------------------------+\n";

        // Description with word wrap
        cout << "| Description : ";
        if (desc.length() > 35) {
            cout << left << setw(35) << desc.substr(0, 35) << " |\n";
            for (size_t i = 35; i < desc.length(); i += 35) {
                cout << "|             " << left << setw(35) << desc.substr(i, 35) << " |\n";
            }
        }
        else {
            cout << left << setw(35) << desc << " |\n";
        }
        cout << "+--------------------------------------------------+\n";

        // Priority
        cout << "| Priority    : " << left << setw(35) << priority << " |\n";
        cout << "+--------------------------------------------------+\n";

        // Dependencies with word wrap
        cout << "| Dependencies: ";
        if (dependencies.length() > 35) {
            cout << left << setw(35) << dependencies.substr(0, 35) << " |\n";
            for (size_t i = 35; i < dependencies.length(); i += 35) {
                cout << "|             " << left << setw(35) << dependencies.substr(i, 35) << " |\n";
            }
        }
        else {
            cout << left << setw(35) << dependencies << " |\n";
        }
        cout << "+--------------------------------------------------+\n";

        // Assigned To
        cout << "| Assigned To : " << left << setw(35) << (assignedTo.empty() ? "Not Assigned" : assignedTo) << " |\n";
        cout << "+--------------------------------------------------+\n";

        // Created By
        cout << "| Created By  : " << left << setw(35) << createdBy << " |\n";
        cout << "+--------------------------------------------------+\n";

        // Status with word wrap
        cout << "| Status      : ";
        if (status.length() > 35) {
            cout << left << setw(35) << status.substr(0, 35) << " |\n";
            for (size_t i = 35; i < status.length(); i += 35) {
                cout << "|             " << left << setw(35) << status.substr(i, 35) << " |\n";
            }
        }
        else {
            cout << left << setw(35) << status << " |\n";
        }
        cout << "+==================================================+\n";
    }

    // Helper function to display task dependencies
    void displayDependencyTree(const string& taskTitle, int level = 0) {
        ifstream in("tasks.txt");
        string line;
        while (getline(in, line)) {
            size_t pos1 = line.find(",");
            string currentTitle = line.substr(0, pos1);
            if (currentTitle == taskTitle) {
                // Extract dependencies
                size_t pos2 = line.find(",", pos1 + 1);
                size_t pos3 = line.find(",", pos2 + 1);
                size_t pos4 = line.find(",", pos3 + 1);
                string deps = line.substr(pos3 + 1, pos4 - pos3 - 1);

                if (deps != "none" && !deps.empty()) {
                    size_t start = 0;
                    size_t end = deps.find(";");
                    while (start < deps.length()) {
                        string depTask = deps.substr(start, (end == string::npos) ? string::npos : end - start);
                        // Print indentation based on level
                        for (int i = 0; i < level; i++) cout << "    ";
                        cout << "└── " << depTask << "\n";

                        // Recursively display dependencies of this task
                        displayDependencyTree(depTask, level + 1);

                        if (end == string::npos) break;
                        start = end + 1;
                        end = deps.find(";", start);
                    }
                }
                break;
            }
        }
        in.close();
    }

    // Helper function to copy a file
    bool copyFile(const string& source, const string& destination) {
        ifstream src(source, ios::binary);
        if (!src) {
            cout << "Error: Cannot open source file " << source << "\n";
            return false;
        }

        ofstream dst(destination, ios::binary);
        if (!dst) {
            cout << "Error: Cannot create destination file " << destination << "\n";
            src.close();
            return false;
        }

        dst << src.rdbuf();

        if (src.fail() || dst.fail()) {
            cout << "Error: Failed to copy file content\n";
            src.close();
            dst.close();
            return false;
        }

        src.close();
        dst.close();
        return true;
    }

public:
    void createTask(string creator) {
        int attach;
        string fileContent;
        cout << "Enter task title: ";
        getline(cin, title);

        cout << "Enter task description: ";
        getline(cin, description);

        priority = getPriorityFromChoice();
        dependency = getDependencyFromList();

        cout << "Attach file (1/0)? ";
        cin >> attach;
        cin.ignore();


        if (attach == 1) {
            attachedFile = title;
            attachedFile += ".txt";
            cout << "Enter file content (end with a single line containing only '#'):\n";

            string line;
            while (getline(cin, line)) {
                if (line == "#") break;
                fileContent += line + "\n";
            }

            ofstream file(attachedFile);
            if (file.is_open()) {
                file << fileContent;
                file.close();
            }
            else {
                cout << "Failed to write file. Setting attachment to 'None'.\n";
                attachedFile = "None";
            }
        }
        else {
            attachedFile = "None";
        }

        ofstream out("tasks.txt", ios::app);
        out <<"\n" << title << "," << description << "," << priority << "," << dependency << ",," << creator << ",Not Started\n";
        out.close();

        cout << "Task created successfully!\n";
        cout << "Press Enter to continue...";
        cin.get();
    }

    void updateTask(string taskTitle);  // Forward declaration

    void assignTask(string t, string email) {
        ifstream in("tasks.txt");
        ofstream out("temp.txt");
        string line;
        bool found = false;
        while (getline(in, line)) {
            size_t pos1 = line.find(",");
            string taskTitle = line.substr(0, pos1);
            if (taskTitle == t) {
                found = true;
                size_t pos2 = line.find(",", pos1 + 1);
                size_t pos3 = line.find(",", pos2 + 1);
                size_t pos4 = line.find(",", pos3 + 1);
                size_t pos5 = line.find(",", pos4 + 1);
                out << taskTitle << line.substr(pos1, pos4 - pos1) << "," << email << line.substr(pos5) << "\n";
            }
            else {
                out << line << "\n";
            }
        }
        in.close();
        out.close();
        if (found) {
            if (remove("tasks.txt") != 0) {
                cout << "Error removing original file.\n";
                remove("temp.txt");
                return;
            }
            if (rename("temp.txt", "tasks.txt") != 0) {
                cout << "Error updating task.\n";
                return;
            }
            cout << "Task assigned successfully!\n";
        }
        else {
            remove("temp.txt");
            cout << "Task not found.\n";
        }
    }

    void viewTasks() {
        ifstream in("tasks.txt");
        string line;
        cout << "\nAll Tasks:\n";
        cout << "---------\n";
        while (getline(in, line)) {
            displayTaskDetails(line);
            cout << "\n";
        }
        in.close();
    }

    void viewAssignedTasks(string email) {
        ifstream in("tasks.txt");
        string line;
        cout << "\nYour Assigned Tasks:\n";
        cout << "------------------\n";
        bool found = false;

        while (getline(in, line)) {
            size_t pos1 = line.find(",");
            size_t pos2 = line.find(",", pos1 + 1);
            size_t pos3 = line.find(",", pos2 + 1);
            size_t pos4 = line.find(",", pos3 + 1);
            size_t pos5 = line.find(",", pos4 + 1);
            size_t pos6 = line.find(",", pos5 + 1); // 6th comma after assigned-to
            if (pos6 == string::npos) continue; // Safety check

            string assigned = line.substr(pos5 + 1, pos6 - pos5 - 1);

            if (assigned == email) {
                found = true;
                displayTaskDetails(line);
                cout << "\n";
            }
        }

        if (!found) {
            cout << "No tasks assigned to you.\n";
        }
        in.close();
    }


    void viewTaskDependencies(string taskTitle) {
        ifstream in("tasks.txt");
        string line;
        bool found = false;

        while (getline(in, line)) {
            size_t pos1 = line.find(",");
            string currentTitle = line.substr(0, pos1);

            if (currentTitle == taskTitle) {
                found = true;
                cout << "\n+==================================================+\n";
                cout << "|              TASK DEPENDENCY TREE                 |\n";
                cout << "+==================================================+\n";
                cout << "| " << taskTitle << " (Root Task)\n";

                // Display the dependencies recursively
                displayDependencyTree(taskTitle);

                cout << "+==================================================+\n";
                break;
            }
        }
        in.close();

        if (!found) {
            cout << "Task not found.\n";
        }
    }

    void viewAttachedFile(string taskTitle) {
        ifstream in("tasks.txt");
        string line;
        bool found = false;

        while (getline(in, line)) {
            size_t pos1 = line.find(",");
            string currentTitle = line.substr(0, pos1);

            if (currentTitle == taskTitle) {
                // Check if task has attachment
                size_t pos2 = line.find(",", pos1 + 1);
                size_t pos3 = line.find(",", pos2 + 1);
                size_t pos4 = line.find(",", pos3 + 1);
                size_t pos5 = line.find(",", pos4 + 1);
                size_t pos6 = line.find(",", pos5 + 1);

                size_t pos7 = line.find(",", pos6 + 1);
                if (pos7 != string::npos) {
                    string attachmentPath = line.substr(pos7 + 1);
                    found = true;

                    cout << "\n+==================================================+\n";
                    cout << "|                 ATTACHED FILE                     |\n";
                    cout << "+==================================================+\n";
                    cout << "| File: " << attachmentPath << "\n";
                    cout << "+--------------------------------------------------+\n";

                    // Display file info
                    ifstream fileCheck(attachmentPath);
                    if (fileCheck) {
                        fileCheck.seekg(0, ios::end);
                        long fileSize = fileCheck.tellg();
                        fileCheck.close();

                        cout << "| Size: " << fileSize << " bytes\n";
                        cout << "| Location: " << attachmentPath << "\n";
                        cout << "+==================================================+\n";

                        // Provide options to open or view the file
                        cout << "\nOptions:\n";
                        cout << "1. Open file (if supported by your system)\n";
                        cout << "2. Return to menu\n";
                        cout << "Enter choice: ";

                        int choice;
                        cin >> choice;
                        cin.ignore();

                        if (choice == 1) {
                            // Command to open file (platform dependent)
#ifdef _WIN32
                            string command = "start \"\" \"" + attachmentPath + "\"";
#else
                            string command = "xdg-open \"" + attachmentPath + "\" &";
#endif
                            system(command.c_str());
                        }
                    }
                    else {
                        cout << "| Error: File not found or cannot be accessed\n";
                        cout << "+==================================================+\n";
                    }
                }
                else {
                    found = true;
                    cout << "This task has no attached files.\n";
                }
                break;
            }
        }
        in.close();

        if (!found) {
            cout << "Task not found.\n";
        }
    }
};

// Implementation outside the class
void Task::updateTask(string taskTitle) {
    ifstream in("tasks.txt");
    ofstream out("temp.txt");
    string line;
    bool found = false;

    while (getline(in, line)) {
        size_t pos1 = line.find(",");
        string currentTitle = line.substr(0, pos1);

        if (currentTitle == taskTitle) {
            found = true;
            cout << "\nCurrent task details:\n";
            displayTaskDetails(line);

            cout << "\nWhat would you like to update?\n";
            cout << "1. Description\n";
            cout << "2. Priority\n";
            cout << "3. Dependencies\n";
            cout << "4. Status\n";
            cout << "5. All\n";
            cout << "Enter choice: ";

            int choice;
            cin >> choice;
            cin.ignore();

            // Extract current values
            size_t pos2 = line.find(",", pos1 + 1);
            size_t pos3 = line.find(",", pos2 + 1);
            size_t pos4 = line.find(",", pos3 + 1);
            size_t pos5 = line.find(",", pos4 + 1);
            size_t pos6 = line.find(",", pos5 + 1);

            string newDesc = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string newPriority = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string newDependency = line.substr(pos3 + 1, pos4 - pos3 - 1);
            string newStatus = line.substr(pos6 + 1);

            if (choice == 1 || choice == 5) {
                cout << "Enter new description: ";
                getline(cin, newDesc);
            }
            if (choice == 2 || choice == 5) {
                newPriority = getPriorityFromChoice();
            }
            if (choice == 3 || choice == 5) {
                newDependency = getDependencyFromList();
            }
            if (choice == 4 || choice == 5) {
                string tempStatus = getStatusFromChoice();

                // Check if setting to "Completed" is allowed
                if (tempStatus == "Completed") {
                    bool allDepsDone = true;
                    vector<string> deps;
                    stringstream ss(newDependency);
                    string dep;
                    while (getline(ss, dep, ';')) {
                        deps.push_back(dep);
                    }

                    ifstream checkFile("tasks.txt");
                    string taskLine;
                    map<string, string> taskStatusMap;
                    while (getline(checkFile, taskLine)) {
                        size_t tpos1 = taskLine.find(",");
                        size_t tpos6 = taskLine.rfind(",");
                        string tTitle = taskLine.substr(0, tpos1);
                        string tStatus = taskLine.substr(tpos6 + 1);
                        taskStatusMap[tTitle] = tStatus;
                    }
                    checkFile.close();

                    for (string d : deps) {
                        if (d == "none") continue;
                        if (taskStatusMap.find(d) == taskStatusMap.end() || taskStatusMap[d] != "Completed") {
                            cout << "Cannot mark this task as Completed. Dependency '" << d << "' is not completed.\n";
                            allDepsDone = false;
                            return;
                        }
                    }

                    if (allDepsDone)
                        newStatus = "Completed";
                    else
                        newStatus = line.substr(pos6 + 1); // Keep old status
                }
                else {
                    newStatus = tempStatus;
                }
            }

            string assigneeAndCreator = line.substr(pos4, pos5 - pos4 + 1);
            out << taskTitle << "," << newDesc << "," << newPriority << "," << newDependency << assigneeAndCreator << newStatus << "\n";
        }
        else {
            out << line << "\n";
        }
    }
    in.close();
    out.close();

    if (found) {
        if (remove("tasks.txt") != 0) {
            cout << "Error removing original file.\n";
            remove("temp.txt");
            return;
        }
        if (rename("temp.txt", "tasks.txt") != 0) {
            cout << "Error updating task.\n";
            return;
        }
        cout << "Task updated successfully!\n";
    }
    else {
        remove("temp.txt");
        cout << "Task not found.\n";
    }
}


#endif 