#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User {
private:
    string name;
    int role; // 1: Team Member, 2: Project Manager
    string email;
    string password;
    string phone;

public:
    User() : role(0) {}

    bool signup(string n, int r, string e, string p, string ph) {
        ifstream in("users.txt");
        string line;
        while (getline(in, line)) {
            size_t pos = line.find(",");
            if (line.substr(0, pos) == e) {
                in.close();
                return false;
            }
        }
        in.close();

        ofstream out("users.txt", ios::app);
        out << e << "," << p << "," << n << "," << r << "," << ph << "\n";
        out.close();

        name = n;
        role = r;
        email = e;
        password = p;
        phone = ph;
        return true;
    }

    bool login(string e, string p) {
        ifstream in("users.txt");
        string line;
        while (getline(in, line)) {
            size_t pos1 = line.find(",");
            size_t pos2 = line.find(",", pos1 + 1);
            size_t pos3 = line.find(",", pos2 + 1);
            size_t pos4 = line.find(",", pos3 + 1);
            string fileEmail = line.substr(0, pos1);
            string filePassword = line.substr(pos1 + 1, pos2 - pos1 - 1);
            if (fileEmail == e && filePassword == p) {
                email = e;
                password = p;
                name = line.substr(pos2 + 1, pos3 - pos2 - 1);
                role = stoi(line.substr(pos3 + 1, pos4 - pos3 - 1));
                phone = line.substr(pos4 + 1);
                in.close();
                return true;
            }
        }
        in.close();
        return false;
    }

    string getEmail() { return email; }
    int getRole() { return role; }
    string getName() { return name; }
};

#endif