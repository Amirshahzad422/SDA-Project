#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Message {
private:
    string sender;
    string recipient;
    string content;

public:
    void sendMessage(string s, string r, string c) {
        ofstream out("messages.txt", ios::app);
        out << "\n" << s << "," << r << "," << c;
        out.close();
    }

    void viewMessages(string email) {
        ifstream in("messages.txt");
        string line;
        while (getline(in, line)) {
            size_t pos1 = line.find(",");
            size_t pos2 = line.find(",", pos1 + 1);
            string recipient = line.substr(pos1 + 1, pos2 - pos1 - 1);
            if (recipient == email) {
                cout << "From: " << line.substr(0, pos1) << "\n";
                cout << "Message: " << line.substr(pos2 + 1) << "\n\n";
            }
        }
        in.close();
    }
};

#endif