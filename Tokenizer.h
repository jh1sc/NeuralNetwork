#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <map>




std::string OpenFile(const std::string& filePath) {
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return ""; 
    }

    std::stringstream buffer;
    buffer << inputFile.rdbuf(); 
    std::string fileContents = buffer.str(); 

    std::cout << "File opened successfully." << std::endl;

    return fileContents;
}
class Tokenizer {
public:
    Tokenizer(const std::string& input) {
        int currentNumber = 0;

        for (char ch : input) {
            if (seenCharacters.find(ch) == seenCharacters.end()) {
                seenCharacters.insert(ch);
                charToIntMap[ch] = currentNumber;
                intToCharMap[currentNumber] = ch;
                currentNumber++;
            }
        }
    }

    std::vector<int> Encode(const std::string& s) const {
        std::vector<int> result;
        for (char c : s) {
            result.push_back(charToIntMap.at(c));
        }
        return result;
    }

    std::string Decode(const std::vector<int>& l) const {
        std::string result;
        for (int i : l) {
            result.push_back(intToCharMap.at(i));
        }
        return result;
    }

    void CharacterMapping() const {
        std::cout << "Character to Integer Mapping:\n";
        for (int i = 0; i < intToCharMap.size(); i++) {
            std::cout << "'" << intToCharMap.at(i) << "': " << i << std::endl;
        }
    }

private:
    std::map<char, int> charToIntMap;
    std::map<int, char> intToCharMap;
    std::set<char> seenCharacters;
};


void example() {
    std::cout << "hello" << std::endl;
}