#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class BankChatbot {
private:
    string botName;

    // Helper to convert string to lowercase for easier matching
    string toLower(string str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }

public:
    BankChatbot() : botName("NexusBank Bot") {}

    void greet() {
        cout << "[" << botName << "]: Hello! Welcome to NexusBank Support." << endl;
        cout << "How can I help you today? (Type 'exit' to quit)" << endl;
    }

    string getResponse(string input) {
        input = toLower(input);

        // Simple Pattern Matching Logic
        if (input.find("hi") != string::npos || input.find("hello") != string::npos) {
            return "Greetings! How can I assist you with your banking needs?";
        } 
        else if (input.find("balance") != string::npos) {
            return "To check your balance, please log in to our Secure Mobile App or visit the 'Accounts' section on our website.";
        } 
        else if (input.find("open") != string::npos && input.find("account") != string::npos) {
            return "You can open a new savings account online by providing your ID and address proof on our 'New Account' portal.";
        } 
        else if (input.find("loan") != string::npos) {
            return "We offer Home, Auto, and Personal loans. Would you like to see our current interest rates?";
        } 
        else if (input.find("lost") != string::npos || input.find("card") != string::npos) {
            return "URGENT: If you've lost your card, please call 1-800-BANK-HELP immediately to freeze it.";
        } 
        else if (input.find("thank") != string::npos) {
            return "You're very welcome! Is there anything else I can do for you?";
        } 
        else {
            return "I'm sorry, I didn't quite catch that. You can ask about 'account balance', 'opening an account', or 'lost cards'.";
        }
    }
};

int main() {
    BankChatbot bot;
    string userInput;

    bot.greet();

    while (true) {
        cout << "> ";
        getline(cin, userInput);

        if (bot.getResponse(userInput) == "exit" || userInput == "exit") {
            cout << "[NexusBank Bot]: Thank you for visiting. Have a great day!" << endl;
            break;
        }

        cout << "[NexusBank Bot]: " << bot.getResponse(userInput) << endl;
    }

    return 0;
}