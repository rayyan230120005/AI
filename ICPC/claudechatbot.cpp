#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

// ============================================================
// IMPROVEMENT 1: Intent Classification with Confidence Scores
// Instead of simple keyword matching, we assign a score to
// each intent based on how many keywords matched. The intent
// with the highest score wins — more like real NLP systems.
// ============================================================

struct Intent {
    string name;
    vector<string> keywords;
    string response;
};

// ============================================================
// IMPROVEMENT 2: Conversation History
// We store the last few user messages so the bot can give
// context-aware responses (e.g., remember if user asked about loans).
// ============================================================

class BankChatbot {
private:
    string botName;
    vector<string> conversationHistory; // stores last N user inputs
    vector<string> unansweredQueries;   // IMPROVEMENT 3: logs unknown queries
    int messageCount;

    vector<Intent> intents = {
        {
            "greeting",
            {"hi", "hello", "hey", "good morning", "good evening", "namaste"},
            "Greetings! Welcome to NexusBank Support. How can I assist you today?"
        },
        {
            "balance",
            {"balance", "check balance", "account balance", "how much", "funds", "amount"},
            "To check your balance, log in to our Secure Mobile App or visit the 'Accounts' section on our website."
        },
        {
            "open_account",
            {"open", "account", "new account", "create account", "savings", "start account"},
            "You can open a new savings account online by providing your ID and address proof on our 'New Account' portal."
        },
        {
            "loan",
            {"loan", "borrow", "emi", "interest rate", "home loan", "auto loan", "personal loan", "credit"},
            "We offer Home, Auto, and Personal loans. Current rates start at 7.5% p.a. Would you like to apply?"
        },
        {
            "lost_card",
            {"lost", "stolen", "missing", "card", "debit", "credit card", "block card", "freeze"},
            "URGENT: Please call 1-800-BANK-HELP immediately to freeze your card. You can also block it via the app."
        },
        {
            "transfer",
            {"transfer", "send money", "neft", "rtgs", "imps", "upi", "pay", "payment"},
            "You can transfer funds via UPI, NEFT, or RTGS through our app or net banking portal."
        },
        {
            "branch",
            {"branch", "atm", "location", "nearest", "where", "address", "visit"},
            "You can find the nearest branch or ATM using our Branch Locator on the website or app."
        },
        {
            "thanks",
            {"thank", "thanks", "thankyou", "grateful", "appreciate"},
            "You're very welcome! Is there anything else I can help you with?"
        }
    };

    // Helper: convert string to lowercase
    string toLower(string str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }

    // ============================================================
    // IMPROVEMENT 1: Confidence-based Intent Matching
    // Count how many keywords from each intent appear in user input.
    // Return the intent with highest match count (confidence score).
    // This is similar to a simple Bag-of-Words classifier in NLP.
    // ============================================================
    string classifyIntent(const string& input) {
        string lowerInput = toLower(input);
        string bestIntent = "";
        int bestScore = 0;

        for (auto& intent : intents) {
            int score = 0;
            for (auto& keyword : intent.keywords) {
                // Check if keyword appears anywhere in the input
                if (lowerInput.find(keyword) != string::npos) {
                    score++;
                }
            }
            if (score > bestScore) {
                bestScore = score;
                bestIntent = intent.name;
            }
        }

        // Only return intent if at least one keyword matched
        return (bestScore > 0) ? bestIntent : "unknown";
    }

    // ============================================================
    // IMPROVEMENT 2: Context-Aware Response
    // Check conversation history to personalize response.
    // E.g., if user previously asked about loans and now asks
    // about interest, we can infer the context.
    // ============================================================
    bool mentionedBefore(const string& topic) {
        for (auto& msg : conversationHistory) {
            if (toLower(msg).find(topic) != string::npos) return true;
        }
        return false;
    }

    string getResponseForIntent(const string& intentName, const string& userInput) {
        // Context-aware: if user previously asked about loans
        if (intentName == "loan" && mentionedBefore("loan")) {
            return "Following up on your earlier loan inquiry — our EMI calculator is available on the app. Want me to explain loan types?";
        }

        for (auto& intent : intents) {
            if (intent.name == intentName) {
                return intent.response;
            }
        }
        return "";
    }

public:
    BankChatbot() : botName("NexusBank Bot"), messageCount(0) {}

    void greet() {
        cout << "\n[" << botName << "]: Hello! Welcome to NexusBank Support." << endl;
        cout << "[" << botName << "]: How can I help you today? (Type 'exit' to quit)\n" << endl;
    }

    string getResponse(const string& input) {
        messageCount++;

        // Store in conversation history (keep last 5 messages)
        conversationHistory.push_back(input);
        if (conversationHistory.size() > 5) {
            conversationHistory.erase(conversationHistory.begin());
        }

        // Classify intent using confidence scoring
        string intent = classifyIntent(input);

        if (intent == "unknown") {
            // IMPROVEMENT 3: Log unanswered queries for future improvement
            unansweredQueries.push_back(input);
            return "I'm sorry, I didn't understand that. You can ask about:\n"
                   "  - Account balance\n  - Opening an account\n"
                   "  - Loans & interest rates\n  - Lost/stolen cards\n  - Fund transfers\n  - Branch locations";
        }

        return getResponseForIntent(intent, input);
    }

    // IMPROVEMENT 3: Show analytics at the end of session
    void showSessionSummary() {
        cout << "\n[" << botName << "]: Session Summary" << endl;
        cout << "  Total messages: " << messageCount << endl;
        if (!unansweredQueries.empty()) {
            cout << "  Queries I couldn't answer (" << unansweredQueries.size() << "):" << endl;
            for (auto& q : unansweredQueries) {
                cout << "    - " << q << endl;
            }
            cout << "  (These will help improve future responses)" << endl;
        } else {
            cout << "  All queries answered successfully!" << endl;
        }
    }
};

int main() {
    BankChatbot bot;
    string userInput;

    bot.greet();

    while (true) {
        cout << "You: ";
        getline(cin, userInput);

        // Trim whitespace
        if (userInput.empty()) continue;

        if (userInput == "exit" || userInput == "quit" || userInput == "bye") {
            bot.showSessionSummary(); // Show what we learned this session
            cout << "\n[NexusBank Bot]: Thank you for visiting NexusBank. Have a great day!\n" << endl;
            break;
        }

        cout << "[NexusBank Bot]: " << bot.getResponse(userInput) << "\n" << endl;
    }

    return 0;
}