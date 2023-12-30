#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

// TODO: implement a dictionary that maps keys to (multiple) values
// start with multimap.cpp, copy most of the code, and modify it

class Translations {
public:
    Translations(std::string&& value) {
        // TODO: construct the set with the given value
        values.emplace(std::move(value));

    }

    void add(std::string&& value) {
        // TODO: add the value to the multimap
        values.emplace(std::move(value));
    }

    bool remove(const std::string& value) {
        values.erase(value);
        return values.empty(); // TODO: return true if the `values` set is empty after removing the value

    }

    void list(std::ostream& out) const {
        for(auto&& value : values) {
            out << value << ' ';
        }
    }

    void list(std::string_view name, std::ostream& out) const {
        for(auto&& value : values) {
            out << name << ": " << value << std::endl;
        }
    }

private:
    std::unordered_set<std::string> values;
};

class Dictionary {
public:
    void add(std::string&& key, std::string&& value) {
        // TODO: add the value to the multimap

        // hint: use translations.try_emplace for adding new keys (without finding the key twice)
        auto [it, success] = translations.try_emplace(std::move(key), std::move(value));

        if(!success) {
            it->second.add(std::move(value));
        }
    }

    void remove(const std::string& key) {
        // TODO: remove all values associated with the key
        translations.erase(key);
    }

    void remove(const std::string& key, const std::string& value) {
        // TODO: remove the value associated with the key
        //        and remove the `Translations` object if it is empty (use the remove method of `Translations`)
        auto it = translations.find(key);
        if(it != translations.end()) {
            if(it->second.remove(value)) {
                translations.erase(it);
            }
        }
    }

    // NOTE: this method is const, because it does not modify the dictionary
    void find(const std::string& key, std::ostream& out) const {
        // TODO: print all values associated with the key
        auto it = translations.find(key);
        if(it != translations.end()) {
            it->second.list(out);
        }
    }

    // NOTE: this method is const, because it does not modify the dictionary
    void list(std::ostream& out) const {
        // TODO: print all key-value pairs in the dictionary as "key: value"
        for(auto&& it : translations) {
            it.second.list(it.first, out);
        }
    }

private:
    std::unordered_map<std::string, Translations> translations;
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
