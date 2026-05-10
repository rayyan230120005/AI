#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct Info {
    string category;
    string answer;
    string contact;
};

class InformationManagementES {
private:
    map<string, Info> knowledgeBase;

    string toLower(string str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }

    string intelligentSearch(string query) {
        query = toLower(query);
        
        // Direct match
        if (knowledgeBase.find(query) != knowledgeBase.end()) {
            return query;
        }

        // Partial match
        for (auto& pair : knowledgeBase) {
            if (pair.first.find(query) != string::npos || query.find(pair.first) != string::npos) {
                return pair.first;
            }
        }

        // Simple fuzzy match (basic)
        for (auto& pair : knowledgeBase) {
            if (pair.first.length() > 3 && query.length() > 3) {
                if (pair.first.substr(0, 4) == query.substr(0, 4)) {
                    return pair.first;
                }
            }
        }
        return "";
    }

public:
    InformationManagementES() {
        knowledgeBase = {
            {"leave",    {"HR",      "Annual Leave: 21 days | Sick Leave: 12 days\nApply via HR Portal → Leave Section", "HR Dept (Ext: 101)"}},
            {"salary",   {"Finance", "Salary slips available in Payroll portal\nSalary credited on 1st of every month", "Finance (Ext: 102)"}},
            {"password", {"IT",      "Reset password at: https://password.company.com", "IT Helpdesk (Ext: 456)"}},
            {"meeting",  {"General", "Book meeting rooms via Microsoft Teams", "Admin (Ext: 103)"}},
            {"policy",   {"HR",      "All policies available in Shared Drive → HR → Policies", "HR Dept (Ext: 101)"}},
            {"laptop",   {"IT",      "Raise ticket in ServiceNow for laptop issues", "IT Helpdesk (Ext: 456)"}},
            {"email",    {"IT",      "Company email managed via Microsoft Outlook / O365", "IT Helpdesk (Ext: 456)"}},
            {"idcard",   {"HR",      "Request new/replacement ID card via HR portal", "HR Dept (Ext: 101)"}}
        };
    }

    void showMenu() {
        cout << "\n" << string(65, '=') << endl;
        cout << "       INFORMATION MANAGEMENT EXPERT SYSTEM" << endl;
        cout << string(65, '=') << endl;
        cout << "1. Search Information" << endl;
        cout << "2. Show All Topics" << endl;
        cout << "3. Exit" << endl;
        cout << string(65, '=') << endl;
    }

    void showAllTopics() {
        cout << "\n Available Topics:\n";
        cout << "HR      : leave, policy, idcard\n";
        cout << "Finance : salary\n";
        cout << "IT      : password, laptop, email\n";
        cout << "General : meeting\n";
    }

    void run() {
        int choice;
        while (true) {
            showMenu();
            cout << "\nEnter your choice (1-3): ";
            cin >> choice;

            if (choice == 1) {
                string query;
                cout << "\nWhat information do you need? : ";
                cin.ignore();
                getline(cin, query);

                string key = intelligentSearch(query);
                if (!key.empty()) {
                    Info info = knowledgeBase[key];
                    cout << "\n" << string(60, '─') << endl;
                    cout << " Found in " << info.category << " Category" << endl;
                    cout << string(60, '─') << endl;
                    cout << info.answer << endl;
                    cout << "\n Contact: " << info.contact << endl;
                    cout << string(60, '─') << endl;
                } else {
                    cout << "\n Sorry, no information found for: " << query << endl;
                }
            }
            else if (choice == 2) {
                showAllTopics();
            }
            else if (choice == 3) {
                cout << "\nThank you for using Information Management Expert System!\n";
                break;
            }
            else {
                cout << "\nInvalid choice! Please try again.\n";
            }
        }
    }
};

int main() {
    InformationManagementES system;
    system.run();
    return 0;
}