#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

std::vector<std::string> tokenize(const std::string &input) {
    std::regex word_regex("(\\w+)");
    std::vector<std::string> tokens{
        std::sregex_token_iterator(input.begin(), input.end(), word_regex),
        std::sregex_token_iterator()
    };
    return tokens;
}

std::string analyzeSentiment(const std::string &input) {
    if (input.find("happy") != std::string::npos || input.find("good") != std::string::npos) {
        return "positive";
    } else if (input.find("sad") != std::string::npos || input.find("bad") != std::string::npos) {
        return "negative";
    }
    return "neutral";
}

class DialogueManager {
private:
    std::map<std::string, std::string> knowledgeBase;

public:
    DialogueManager() {
        knowledgeBase["what is AI"] = "AI stands for Artificial Intelligence.";
        knowledgeBase["how are you"] = "I am just a program, but I am functioning as expected!";
        knowledgeBase["what is your functionality"] = "I am here to provide you answer";

    }

    std::string getResponse(const std::string &input) {
        for (const auto &entry : knowledgeBase) {
            if (input.find(entry.first) != std::string::npos) {
                return entry.second;
            }
        }
        return "I am sorry, I don't have an answer for that.";
    }
};

class Chatbot {
private:
    DialogueManager dialogueManager;

public:
    void processInput(const std::string &input) {
        std::cout << "Tokenizing input...\n";
        auto tokens = tokenize(input);
        std::cout << "Tokens: ";
        for (const auto &token : tokens) {
            std::cout << token << " ";
        }
        std::cout << "\n";

        std::cout << "Analyzing sentiment...\n";
        std::string sentiment = analyzeSentiment(input);
        std::cout << "Sentiment: " << sentiment << "\n";

        std::cout << "Generating response...\n";
        std::string response = dialogueManager.getResponse(input);
        std::cout << "Chatbot: " << response << "\n";
    }
};

int main() {
    Chatbot chatbot;
    std::string userInput;

    std::cout << "Chatbot: Hello! How can I help you today?\n";
    while (true) {
        std::cout << "You: ";
        std::getline(std::cin, userInput);

        if (userInput == "exit" || userInput == "quit") {
            std::cout << "Chatbot: Goodbye!\n";
            break;
        }

        chatbot.processInput(userInput);
    }

    return 0;
}