/* All 3 functions below are generated with DeepSeek AI (deepseek.com) */

#include <random>
#include <chrono>
#include <cstdlib>

std::string strict_tolower(std::string input) {     // filters input to have only letters and then changes all letters to lowercase
    std::string ret;
    for (char c : input) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            ret += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return ret;
}

bool useVocab(unsigned char maturity) {
    // Clamp maturity to valid percentage range [0, 100]
    if (maturity > 100) maturity = 100;
    
    // Thread-safe random number generation
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    static std::uniform_int_distribution<int> dist(0, 99);
    
    // Generate random number [0, 99] and compare with percentage
    return dist(rng) < maturity;
}

std::string genBabble() {
    static const std::vector<std::string> onsets = {
        "b", "bl", "br", "c", "ch", "cl", "cr", "d", "dr", "f", 
        "fl", "fr", "g", "gl", "gr", "h", "j", "k", "l", "m", 
        "n", "p", "pl", "pr", "qu", "r", "s", "sh", "sl", "sn", 
        "sp", "st", "str", "t", "th", "tr", "v", "w", "y", "z"
    };
    static const std::vector<std::string> nuclei = {
        "a", "e", "i", "o", "u", "ai", "ea", "ee", "oo", "ou"
    };
    static const std::vector<std::string> codas = {
        "", "b", "d", "f", "g", "k", "l", "m", "n", "p", "r", 
        "s", "sh", "t", "th", "x"
    };
    
    int syllables = 1 + rand() % 2;  // 1-2 syllables
    std::string result;
    
    for (int i = 0; i < syllables; ++i) {
        result += onsets[rand() % onsets.size()];
        result += nuclei[rand() % nuclei.size()];
        result += codas[rand() % codas.size()];
    }
    
    return result;
}