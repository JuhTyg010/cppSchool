#include <algorithm>
#include <iostream>
#include <list>
#include <deque>
#include <string_view>

void print_help(std::string_view name, std::ostream& out) {
    out << "Usage: " << name << " <deque|list|help>" << std::endl;
}

void deque_test() {
    std::deque<std::string> deque;

    // read commands push_back, push_front, pop_back, pop_front, print, clear from stdin

    std::string command;

    // NOTE: this implementation fails if the input is not formatted correctly
    while (std::cin >> command) {
        if (command == "push_back") {
            std::string value;
            std::cin >> value;
            // TODO: push the value to the back of the deque
            deque.push_back(value);
        } else if (command == "push_front") {
            std::string value;
            std::cin >> value;
            // TODO: push the value to the front of the deque
            deque.push_front(value);
        } else if (command == "pop_back") {
            // TODO: pop the value from the back of the deque
            deque.pop_back();
        } else if (command == "pop_front") {
            // TODO: pop the value from the front of the deque
            deque.pop_front();
        } else if (command == "print") {
            // TODO: print the deque using a range-based for loop
            for(auto&& it = deque.begin(); it != deque.end(); ++it) {
                std::cout << *it << ' ';
            }
        } else if (command == "clear") {
            // TODO: clear the deque
            deque.clear();
        } else {
            std::cerr << "Unknown command: " << command << std::endl;
        }
    }
}

void list_test() {
    std::list<std::string> list;

    // TODO: read commands push_back, push_front, pop_back, pop_front, print, clear from stdin (copy from deque_test)

    // TODO: add commands insert and uniquify

    std::string command;

    // NOTE: this implementation fails if the input is not formatted correctly
    while (std::cin >> command) {
        if (command == "push_back") {
            std::string value;
            std::cin >> value;
            // TODO: push the value to the back of the list
            list.push_back(value);
        } else if (command == "push_front") {
            std::string value;
            std::cin >> value;
            // TODO: push the value to the front of the list
            list.push_front(value);
        } else if (command == "pop_back") {
            // TODO: pop the value from the back of the list
            list.pop_back();
        } else if (command == "pop_front") {
            // TODO: pop the value from the front of the list
            list.pop_front();
        } else if (command == "print") {
            // TODO: print the list using a range-based for loop
            for (auto&& it : list) {
                std::cout << it << ' ';
            }
            std::cout << std::endl;

        } else if (command == "clear") {
            // TODO: clear the list
            list.clear();
        } else if (command == "insert") {
            std::string value, before;
            std::cin >> value;
            std::cin >> before;

            // TODO: insert the value before the first occurrence of before
            auto it = std::find(list.begin(), list.end(), before);
            list.insert(it, value);
            // hint: use std::find to find the first occurrence of before
        } else if (command == "uniquify") {
            if (list.size() < 2) {
                continue; // nothing to do
            }

            // TODO: remove all consecutive duplicates from the list

            auto it = list.begin();
            std::string_view previous = *it;

            for (++it; it != list.end();) {
                // TODO: remove the element if `*it` is equal to `previous`
                //       otherwise, update `previous` and increment `it`
                // hint: list.erase(it) returns the iterator to the removed element's successor
                if(*it == previous) {
                    it = list.erase(it);
                } else {
                    previous = *it;
                    ++it;
                }
            }
        } else {
            std::cerr << "Unknown command: " << command << std::endl;
        }
    }
}

int main(int argc, char** argv) {
    using namespace std::string_literals;

    if (argc != 2) {
        print_help(argv[0], std::cerr);
        return 1;
    }

    if (argv[1] == "deque"s)
        deque_test();
    else if (argv[1] == "list"s)
        list_test();
    else if (argv[1] == "help"s)
        print_help(argv[0], std::cout);
    else
        std::cerr << "Unknown container: " << argv[1] << "\n";
}
