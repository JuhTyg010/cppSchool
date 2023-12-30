#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>

// TODO: implement a dictionary that maps keys to (multiple) values

class Dictionary {
public:
    // hint: use translations.equal_range for finding all values associated with a key


    void add(std::string&& key, std::string&& value) {

        // TODO: add the value to the multimap
        translations.emplace(std::move(key), std::move(value));
    }

    void remove(const std::string& key) {
        // TODO: remove all values associated with the key
        auto [beg, end] = translations.equal_range(key);
        translations.erase(beg, end);
    }

    void remove(const std::string& key, const std::string& value) {
        // TODO: remove the value associated with the key
        auto [beg, end] = translations.equal_range(key);
        auto it = std::find_if(beg, end, [&value](const auto& pair) {return pair.second == value;});
        if(it != end) {
            translations.erase(it);
        }
    }

    // NOTE: this method is const, because it does not modify the dictionary
    void find(const std::string& key, std::ostream& out) const {
        // TODO: print all values associated with the key
        auto [beg, end] = translations.equal_range(key);
        for(auto it = beg; it != end; ++it) {
            out << it->second << ' ';
        }
        out << std::endl;
    }

    // NOTE: this method is const, because it does not modify the dictionary
    void list(std::ostream& out) const {
        // TODO: print all key-value pairs in the dictionary as "key: value"
        for(auto [key, value] : translations) {
            out << key << ": " << value << std::endl;
        }
    }

private:
    std::unordered_multimap<std::string, std::string> translations;
};

void program_loop(Dictionary& dictionary, std::istream& in, std::ostream& out) {
    std::string line;
    std::string command;

    // TODO: read commands from stdin:
    //  - add <key> <value>: add a new key-value pair to the dictionary
    //  - remove <key> <value>: remove a specific key-value pair from the dictionary
    //  - remove <key>: remove all key-value pairs with the given key
    //  - find <key>: print all values associated with the given key
    //  - list: print all key-value pairs in the dictionary
    //  - quit: exit the program

    while (std::getline(in, line)) {
        std::istringstream iss(std::move(line));

        if (!(iss >> command)) {
            continue;
        }

        if (command == "add") {
            std::string key, value;
            iss >> key >> value;
            dictionary.add(std::move(key), std::move(value));
        } else if (command == "remove") {
            std::string key, value;
            iss >> key >> value;
            if(value.empty()) {
                dictionary.remove(key);
            } else {
                dictionary.remove(key, value);
            }
        } else if (command == "find") {
            std::string key;
            iss >> key;
            dictionary.find(key, out);

        } else if (command == "list") {
            dictionary.list(out);
        } else if (command == "quit") {
            break;
        } else {
            out << "Unknown command: " << command << std::endl;
        }
    }
}

int main() {
    Dictionary dictionary;
    program_loop(dictionary, std::cin, std::cout);
}
