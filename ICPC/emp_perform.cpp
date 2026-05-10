#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class EmployeePerformanceES {
private:
    int getRating(const string& question) {
        int rating;
        while (true) {
            cout << question << " (1-10): ";
            cin >> rating;
            if (rating >= 1 && rating <= 10) {
                return rating;
            }
            cout << "Invalid input! Please enter a number between 1 and 10.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

public:
    void evaluate() {
        string name;
        cout << "\n" << string(60, '=') << endl;
        cout << "   EMPLOYEE PERFORMANCE EVALUATION EXPERT SYSTEM" << endl;
        cout << string(60, '=') << endl;

        cout << "\nEnter Employee Name: ";
        cin.ignore();
        getline(cin, name);

        int productivity = getRating("1. Productivity & Quality of Work");
        int timeliness   = getRating("2. Timeliness & Meeting Deadlines");
        int teamwork     = getRating("3. Teamwork & Collaboration");
        int initiative   = getRating("4. Initiative & Innovation");
        int attendance   = getRating("5. Attendance & Punctuality");

        int score = (productivity + timeliness + teamwork + initiative + attendance) / 5;

        cout << "\n" << string(60, '=') << endl;
        cout << "PERFORMANCE REPORT - " << name << endl;
        cout << string(60, '=') << endl;
        cout << "Overall Score      : " << score << "/10" << endl;

        if (score >= 9) {
            cout << "Performance Rating : Excellent" << endl;
            cout << "\nRecommendations:\n";
            cout << "• Outstanding performer\n";
            cout << "• Strong candidate for promotion & higher responsibilities" << endl;
        }
        else if (score >= 7) {
            cout << "Performance Rating : Good" << endl;
            cout << "\nRecommendations:\n";
            cout << "• Consistent and reliable performer\n";
            cout << "• Minor improvements suggested" << endl;
        }
        else if (score >= 5) {
            cout << "Performance Rating : Average" << endl;
            cout << "\nRecommendations:\n";
            cout << "• Meets basic expectations\n";
            cout << "• Training and mentoring recommended" << endl;
        }
        else {
            cout << "Performance Rating : Poor" << endl;
            cout << "\nRecommendations:\n";
            cout << "• Below expectations\n";
            cout << "• Performance Improvement Plan (PIP) recommended" << endl;
        }
        cout << string(60, '=') << endl;
    }
};

int main() {
    EmployeePerformanceES system;
    system.evaluate();
    return 0;
}