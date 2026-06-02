#include <SQLiteCpp/SQLiteCpp.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <set>
#include <sstream>
#include <vector>
#include "thirdparty/json.hpp"
#include "thirdparty/AutoSaveStorage.hpp"
#include "include/utils.hpp"

using json = nlohmann::json;

#define DEBUG true

constexpr int lowerThres = 30;
constexpr int upperThres = 1000;

constexpr int MAP_TO_PERCENT(int value) {
    return (value <= lowerThres) ? 0 :
           (value >= upperThres) ? 100 :
           (100 * (value - lowerThres)) / (upperThres - lowerThres);
}

unsigned char g_maturity = 0;

std::string generateResponse(SQLite::Database& db, std::vector<std::string>& words, AutoSaveStorage& localStorage) {
    std::string ret = "";
/*
#if DEBUG
    std::cout << "generateResponse called!" << std::endl;
#endif
*/
    bool i = true;          // This line along with any other reference of this variable in this function is a dummy stop condition!

    while (i) {
        std::string word1 = words.at(words.size() - 2), word2 = words.back();
        std::string nextWord;

        SQLite::Statement nextWordQuery(db, 
            "SELECT word3 FROM trigrams WHERE word1 = ?1 AND word2 = ?2 ORDER BY count DESC LIMIT 1");

        nextWordQuery.bind(1, word1);
        nextWordQuery.bind(2, word2);

        if (nextWordQuery.executeStep()) {
            if (useVocab(g_maturity)) {
                nextWord = nextWordQuery.getColumn(0).getString();
            } else {
                nextWord = genBabble();
            }
        } else {
            nextWord = genBabble();
        }

        words.push_back(nextWord);

        ret += nextWord;
        ret.push_back(' ');

        i = false;
    }

    return ret;
}

void processUserInput(const std::string& input, std::vector<std::string>& words, AutoSaveStorage& localStorage, SQLite::Database& db) {
    std::set<std::string> wordSet;

    json value = localStorage["vocab"];
    if (value.is_array()) {
        wordSet = value.get<std::set<std::string>>();
    }


    SQLite::Transaction transaction(db);

    // Prepare once, reuse many times
    SQLite::Statement stmt(db, "INSERT INTO trigrams (word1, word2, word3, count) VALUES (?1, ?2, ?3, 1) "
                                "ON CONFLICT(word1, word2, word3) DO UPDATE SET count = count + 1");

    // Split sentence into words
    std::istringstream iss(input);
    std::string word;
    while (iss >> word) {
        std::string _word = strict_tolower(word);
        words.push_back(_word);
        wordSet.insert(_word);
    }

    g_maturity = MAP_TO_PERCENT(wordSet.size());

    // Extract trigrams (groups of 3 consecutive words)
    for (size_t i = 0; i + 2 < words.size(); ++i) {
        stmt.bind(1, words[i]);
        stmt.bind(2, words[i + 1]);
        stmt.bind(3, words[i + 2]);
        stmt.exec();
        stmt.reset();  // clears bindings so you can reuse
    }

    transaction.commit();

    localStorage["vocab"] = wordSet;
}

int main() {
    srand(time(NULL));

    const char* username = std::getenv("USER");

    if (username == nullptr) {
        std::cerr << "Error retrieving username" << std::endl;
        return 1;
    }

    std::string AppSupDir = "/Users/" + std::string(username) + "/Library/Application Support/Firstwords";
    std::string braindbpath = AppSupDir + "/brain.db";
    std::string localstoragepath = AppSupDir + "/data.json";

    // Create the directory if it doesn't exist
    try {
        std::filesystem::create_directories(AppSupDir);
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Failed to create directory: " << e.what() << std::endl;
        return 1;
    }

    // If you remove the following 5 comments there would be an error of db being destroyed at the end of the try block

//    try {
        SQLite::Database db(braindbpath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        std::cout << "Database opened successfully at: " << braindbpath << std::endl;
//    } catch (const SQLite::Exception& e) {
//        std::cerr << "Database error: " << e.what() << std::endl;
//        return 1;
//    }

    AutoSaveStorage localStorage(localstoragepath);


    // One-shot execution for statements that return no rows
    db.exec(R"(
        CREATE TABLE IF NOT EXISTS trigrams (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            word1 TEXT NOT NULL,
            word2 TEXT NOT NULL,
            word3 TEXT NOT NULL,
            count INTEGER DEFAULT 1,
            UNIQUE(word1, word2, word3)
        );
    )");

    std::cout << "System: Baby is awake and listening... (type /night to leave)" << std::endl << std::endl;

    while (true) {
        std::string input;
        std::vector<std::string> words;

        std::cout << "You: ";
        std::getline (std::cin, input);
        input += '\n';

        processUserInput(input, words, localStorage, db);
        std::cout << generateResponse(db, words, localStorage);
        std::cout << std::endl;

        if (input == "/night") {
            std::cout << "System: Good night. The baby sleeps and sorts through the day.";
            break;
        }
    }

    return 0;
}