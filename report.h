#ifndef REPORT_H
#define REPORT_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Report {
public:
    void generateReport() {
        ifstream in("tasks.txt");
        string line;
        int total = 0, completed = 0;
        while (getline(in, line)) {
            total++;
            size_t lastComma = line.rfind(",");
            string status = line.substr(lastComma + 1);
            if (status == "Completed") completed++;
        }
        in.close();

        ofstream out("reports.txt", ios::app);
        out << "Total Tasks: " << total << "\n";
        out << "Completed Tasks: " << completed << "\n";
        out << "Efficiency: " << (total ? (completed * 100.0 / total) : 0) << "%\n\n";
        out.close();

        cout << "Report saved to reports.txt\n";
    }
};

#endif