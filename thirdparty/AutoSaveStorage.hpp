/* Made with Google Gemini (gemini.google.com)*/

#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

class AutoSaveStorage {
private:
    json data;
    std::string filename;

    // Helper function to write to disk
    void save_to_disk() {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << data.dump(4); // Save with 4-space indentation
        }
    }

public:
    // Constructor: Loads existing file or starts fresh
    AutoSaveStorage(const std::string& filepath) : filename(filepath) {
        std::ifstream file(filename);
        if (file.is_open()) {
            file >> data;
        } else {
            data = json::object(); // Initialize as empty JSON object {}
        }
    }

    // Proxy structure to intercept the assignment operator (=)
    struct Proxy {
        json& entry;
        AutoSaveStorage& parent;

        // This triggers when you do: storage["key"] = value;
        template <typename T>
        Proxy& operator=(const T& value) {
            entry = value;          // Update RAM
            parent.save_to_disk();   // AUTOMATICALLY Save to Disk!
            return *this;
        }

        // Allows reading the value normally
        operator json() const { return entry; }
    };

    // Overload the [] operator to return our Proxy object
    Proxy operator[](const std::string& key) {
        return Proxy{data[key], *this};
    }

    // Print current state
    void print() {
        std::cout << data.dump(4) << std::endl;
    }
}