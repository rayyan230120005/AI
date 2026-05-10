#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

struct Info {
    string category;
    string answer;
    string contact;
};

class InformationManagementES {
private:
    map<string, Info> knowledgeBase;
    const string FILE_NAME = "knowledge.txt";

    string toLower(string str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }

    // ==================== FILE HANDLING ====================
    void loadFromFile() {
        ifstream file(FILE_NAME);
        if (!file.is_open()) {
            cout << "  knowledge.txt file nahi mili. Default data use kar raha hoon...\n";
            createDefaultData();
            saveToFile();  // Pehli baar file create kar do
            return;
        }

        knowledgeBase.clear();
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            stringstream ss(line);
            string key, category, answer, contact;
            
            getline(ss, key, '|');
            getline(ss, category, '|');
            getline(ss, answer, '|');
            getline(ss, contact, '|');
            
            if (!key.empty()) {
                // Answer mein \n ko actual newline mein convert
                size_t pos = 0;
                while ((pos = answer.find("\\n", pos)) != string::npos) {
                    answer.replace(pos, 2, "\n");
                    pos += 1;
                }
                knowledgeBase[key] = {category, answer, contact};
            }
        }
        file.close();
        cout << " " << knowledgeBase.size() << " topics file se load kiye gaye.\n";
    }

    void saveToFile() {
        ofstream file(FILE_NAME);
        if (!file.is_open()) {
            cout << " File save nahi ho saki!\n";
            return;
        }

        for (auto& pair : knowledgeBase) {
            string answer = pair.second.answer;
            // Newline ko \\n mein convert for file
            size_t pos = 0;
            while ((pos = answer.find("\n", pos)) != string::npos) {
                answer.replace(pos, 1, "\\n");
                pos += 2;
            }
            file << pair.first << "|" 
                 << pair.second.category << "|" 
                 << answer << "|" 
                 << pair.second.contact << "\n";
        }
        file.close();
    }

    void createDefaultData() {
        knowledgeBase = {
            {"leave",    {"HR",      "Annual Leave: 21 days | Sick Leave: 12 days\\nApply via HR Portal → Leave Section", "HR Dept (Ext: 101)"}},
            {"salary",   {"Finance", "Salary slips available in Payroll portal\\nSalary credited on 1st of every month", "Finance (Ext: 102)"}},
            {"password", {"IT",      "Reset password at: https://password.company.com", "IT Helpdesk (Ext: 456)"}},
            {"meeting",  {"General", "Book meeting rooms via Microsoft Teams", "Admin (Ext: 103)"}},
            {"policy",   {"HR",      "All policies available in Shared Drive → HR → Policies", "HR Dept (Ext: 101)"}},
            {"laptop",   {"IT",      "Raise ticket in ServiceNow for laptop issues", "IT Helpdesk (Ext: 456)"}},
            {"email",    {"IT",      "Company email managed via Microsoft Outlook / O365", "IT Helpdesk (Ext: 456)"}},
            {"idcard",   {"HR",      "Request new/replacement ID card via HR portal", "HR Dept (Ext: 101)"}}
        };
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
        loadFromFile();     // ← File se load
    }

    // Destructor - Program band hone pe save
    ~InformationManagementES() {
        saveToFile();
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